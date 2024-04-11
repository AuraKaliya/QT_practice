// 引入一些必要的头文件
#include <vector> // 向量容器
#include <queue> // 队列容器
#include <memory> // 智能指针
#include <thread> // 线程库
#include <mutex> // 互斥锁
#include <condition_variable> // 条件变量
#include <future> // 异步操作结果
#include <functional> // 函数对象
#include <stdexcept> // 标准异常

// 定义一个线程池类
class ThreadPool {
public:
    // 构造函数，接受一个线程数作为参数
    ThreadPool(size_t);
    // 入队函数，接受一个可调用对象和一些参数，返回一个future对象
    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args)
        -> std::future<typename std::result_of<F(Args...)>::type>;
    // 析构函数，等待所有线程结束
    ~ThreadPool();
private:
    // 用一个向量容器存储工作线程
    std::vector< std::thread > workers;
    // 用一个队列容器存储任务
    std::queue< std::function<void()> > tasks;

    // 同步相关的成员变量
    std::mutex queue_mutex; // 队列互斥锁
    std::condition_variable condition; // 队列条件变量
    bool stop; // 停止标志
};

// 构造函数的实现，创建一定数量的工作线程，并让它们执行一个无限循环的函数
inline ThreadPool::ThreadPool(size_t threads)
    :   stop(false) // 初始化停止标志为false
{
    for(size_t i = 0;i<threads;++i) // 循环创建线程
        workers.emplace_back( // 向工作线程向量中添加一个新的线程对象
            [this] // 用lambda表达式定义线程要执行的函数，捕获this指针
            {
                for(;;) // 无限循环，直到线程结束
                {
                    std::function<void()> task; // 定义一个空的函数对象，用来存储从队列中取出的任务

                    {
                        std::unique_lock<std::mutex> lock(this->queue_mutex); // 创建一个互斥锁，锁住队列互斥锁，防止多个线程同时访问队列
                        this->condition.wait(lock, // 让线程在条件变量上等待，直到满足以下条件之一：
                                             [this]{ return this->stop || !this->tasks.empty(); }); // 停止标志为true或者任务队列不为空
                        if(this->stop && this->tasks.empty()) // 如果停止标志为true并且任务队列为空，说明线程池要结束了
                            return; // 退出循环，结束线程
                        task = std::move(this->tasks.front()); // 否则，用移动语义将队列中的第一个任务赋给task变量
                        this->tasks.pop(); // 弹出队列中的第一个任务
                    } // 互斥锁在离开作用域时自动解锁

                    task(); // 执行task变量中存储的任务函数
                }
            }
            );
}

// 入队函数的实现，使用模板参数推导返回类型和参数类型，接受一个可调用对象和一些参数，返回一个future对象
template<class F, class... Args>
auto ThreadPool::enqueue(F&& f, Args&&... args)
    -> std::future<typename std::result_of<F(Args...)>::type>
{
    using return_type = typename std::result_of<F(Args...)>::type; // 使用result_of模板推导出f函数的返回类型，并定义为return_type别名

    auto task = std::make_shared< std::packaged_task<return_type()> >( // 创建一个shared_ptr指向一个packaged_task对象，该对象封装了f函数和args参数，并返回一个future对象用于获取异步操作结果
        std::bind(std::forward<F>(f), std::forward<Args>(args)...) // 使用bind函数将f函数和args参数绑定在一起，使用forward函数保持参数的完美转发
        );

    std::future<return_type> res = task->get_future(); // 调用packaged_task对象的get_future函数，获取一个future对象，用于之后获取异步操作结果
    {
        std::unique_lock<std::mutex> lock(queue_mutex); // 创建一个互斥锁，锁住队列互斥锁

        // 如果线程池已经停止，就不能再添加新的任务，抛出一个运行时异常
        if(stop)
            throw std::runtime_error("enqueue on stopped ThreadPool");

        //tasks.emplace(task{ (*task)(); }); // 将task指针所指向的packaged_task对象转换为一个无参的函数对象，并添加到任务队列中
        tasks.emplace( [&task](){(*task)(); });
    }
    condition.notify_one(); // 通知一个在条件变量上等待的线程，有新的任务可以执行了
    return res; // 返回future对象，供调用者获取异步操作结果
}

// 析构函数的实现，等待所有线程结束
inline ThreadPool::~ThreadPool()
{
    {
        std::unique_lock<std::mutex> lock(queue_mutex); // 创建一个互斥锁，锁住队列互斥锁
        stop = true; // 将停止标志设为true，让所有线程在执行完当前任务后退出循环
    }
    condition.notify_all(); // 通知所有在条件变量上等待的线程，停止标志已经改变了
    for(std::thread &worker: workers) // 遍历工作线程向量中的每个线程对象
        worker.join(); // 等待线程结束
}
