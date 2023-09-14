#《QtThreadTest》项目介绍 

本项目是以用于练习QThread基础使用的实践。

## QThread

QThread是Qt中实现多线程应用和管理的类，隶属于Qt的Core模块，继承自QObject。

* QThread的常用函数

    ```c++
    //判断子线程状态
    QThread::isFinished() const;
    QThread::isRunning() const;
    
    //设置线程优先级
    QThread::priority();
    QThread::setPriority(Priority priority);    
    //Priority是QThread中的枚举量，用于表征优先级。
    
    //线程退出
    QThread::exit(int returnCode=0);   //立即退出run函数，但可能会执行其他操作。
    QThread::wait(unsigned long time =ULONG_MAX);  // 等待其他操作执行完毕再关闭线程。
    //需要退出线程时，一般exit之后添加wait。
    
    //信号
    QThread::finished();  //run函数(工作函数)执行完毕。
    QThread::started();  //run函数开始执行。
    
    //槽
    QThread::quit();   //和exit使用效果相同
    QThread::start();  //开始执行，可传入优先级参数进行启动。
    
    //静态方法
    QThread* QThread::currentThread();  //返回当前执行的QThread的指针。
    int QThread::idealThreadCount();   //返回理想情况下的最大线程数（即和CPU核心数相同的值）。
    
    //线程休眠函数
    msleep();  //毫秒
    sleep();   //秒
    usleep();  //微秒
    ```

    ##  在Qt中使用多线程的方法

    * 继承QThread类

        Step1： 创建一个线程子类，共有继承自QThread。

        Step2： 重写run()方法。

        Step3： 在主线程中New出一个子线程类的对象，在进行初始化设置之后调用start()方法。 

    * 继承Object类并利用QThread进行处理

        Step1： 从Object中派生出一个任务子类。

        Step2： 在类中添加一个任务函数用于执行处理逻辑。

        Step3： 在主线程中创建一个任务类对象并进行初始化设置。

        Step4： 在主线程中创建一个子线程QThread对象，对任务类对象调用moveToThread(thread)将任务类对象放于该子线程中。

        Step5： 调用子线程的start()方法启动子线程，在需要调用工作函数的时候进行调用即可。

        注意：任务类对象创建时**不能有父类对象**，子线程一般单一处理一个对象树。可以通过connect连接**多个**工作函数的触发。在connect之后，传入的参数和调用操作都进入阻塞，只有start()后才会执行，**可以先传参再调用执行**。

        在对多个线程进行处理时，需要**分开进行绑定**，因为Qt的信号-槽机制决定槽函数实际上是在信号接收者所在的线程中执行。

    * 利用QThreadPool线程池进行管理

        Step1： 用GlobleInstance获取线程池的全局对象。（单例）

        Step2： 通过线程池的start(QRunnable*,int poriority=0);进行多线程的调用和自动管理。

        注意： 需要将工作对象封装成一个QRunnable对象放入线程池中。通过继承QRunnable类并重写纯虚函数run()，设置自动释放资源：setAutoDelete(true)。若想要使用信号-槽机制，则需要多继承自QObject。

        ## 项目简介

        该项目实践第一种方式实现QT的多线程应用，在主线程中创立了三个子线程，按钮点击时会分别生成指定数量的随机数、进行冒泡排序和快速排序，然后将处理结果传回主线程并进行展示。

        * 通过QElapsedTimer实现单调时钟用于统计处理的时间。
        * 通过Qt6提供的QRandomGenerator::global()->bounded(0,100000)生成随机数。
        * 当Qt不支持自定义元对象时，在QApplication中使用qRegisterMetaType<Typename T>(QString)进行元对象注册。