# Qt插件系统的使用

## 插件的简介

插件是用于扩展主程序功能的额外的动态加载的程序，在插件设计中提供接口和具体实现，在主程序中通过加载插件-调用接口以通过插件中封装的方法处理数据，或加载插件中提供的新功能。

在Qt中，QApplication作为主程序框架，对外部提供统一的接口，可提供动态和静态两类接口。

通过一个插件管理器对插件数据进行管理，对插件行为状态进行监测，保存有一个命令树执行管理插件的元指令。在外部，通过独立编写的插件编译成动态库或封装至程序中的静态库，实现为主程序提供“源”，在主程序中加载-注册实现插件安装 。

使用Qt的插件系统进行插件开发，通常需要经历三个阶段：插件程序编写、主程序逻辑添加、link。

在**插件程序中**需要进行以下步骤：

* 将插件程序build为一个library（以动态库为示例）

* 创建一个插件接口文件作为基类，提供插件的功能接口。

    在该基类中，应该对插件的IID进行定义，同时通过宏对这个接口进行声明

    ```c++
    #define PluginInterfaceIID "com.auratest.PluginInterface/1.0.0"
    //定义插件的IID，类似java中的包命名：组织机构域名加产品名加版本号
    class PluginInterface{...};
    
    Q_DECLARE_INTERFACE(PluginInterface,PluginInterfaceIID)
    //通过宏将该接口进行声明
    //
    //
    ```

    **Q_DECLARE_INTERFACE**用于将一个**字符串标识符**与一个**接口类名**关联起来。这个标识符必须是**唯一**的，用于在运行时识别和转换接口类型。这个宏通常用于定义插件的接口，以便Qt的元对象系统能够识别和使用它们。   

    这个宏必须**放在命名空间之外**，如果接口类在命名空间中定义，则需要在宏中使用完整的限定名。 

    在此例中，这个宏的作用是定义了一个名为PluginInterfaceIID的全局变量，存储了接口的**标识符字符串**，以及一个名为qt_metacast_PluginInterface的全局函数，用于将QObject指针转换为PluginInterface指针。这个函数会调用QObject的metaObject()方法，获取对象的元信息，然后比较元信息中的接口列表是否包含PluginInterfaceIID，如果是，则返回对象的指针，否则返回空指针。

* 具体的**子类**实现中，需要多继承QObject和插件基类，同时需要使用三个宏函数进行元对象注册、配置插件的元数据、对插件接口的IID进行校验。

    ```c++
    class PLUGINDEMO1_EXPORT PluginDemo1:public QObject,public PluginInterface
    {
        Q_OBJECT   //元对象注册
        Q_PLUGIN_METADATA(IID PluginInterfaceIID)    //设置当前插件的元数据并对外提供实例
        Q_INTERFACES(PluginInterface)				//进行插件接口的ID校验
    public:
    	...
    }
    ```

    **Q_PLUGIN_METADATA**用于在插件类中**声明**插件的**元数据**，包括插件的**标识符**和一个包含**插件信息**的JSON文件。这个宏可以让Qt的元对象系统识别和加载插件，以及获取插件的相关属性。这个宏必须放在**插件类的声明中**，且只能使用一次。

    * 第一个**参数IID是必须**的，用于指定插件实现的接口的标识符，这个标识符必须是**唯一**的，通常是一个反向域名形式的字符串。这个标识符用于在运行时**检查**插件是否实现了期望的接口。

    * 第二个**参数FILE是可选**的，用于指定一个本地的JSON文件，该文件可以**描述**插件的相关数据**信息**，如名称，版本，作者，描述等。这些**信息可以通过QPluginLoader::metaData()方法获取**。如果不想为插件提供信息，可以省略这个参数或者保证JSON文件为空。

    **Q_INTERFACES**用于对插件的接口的ID进行校验，此宏应与**Q_DECLARE_INTERFACE**进行配套使用。

* 之后，就是具体规划插件实例需要实现的具体功能。通常，插件实例应该是**单例**的。

在**主程序**中应该拥有以下步骤：

* 使用QPluginLoader进行插件的加载和卸载。

    ```c++
    #include <QPluginLoader>
    
    QPluginLoader m_loader;
    
    QDir dir(qApp->applicationDirPath());//获取当前程序的执行文件所在路径
    m_loader.setFileName(dir.filePath("PluginDemo1.dll")); //选择加载的插件，通过传入dll库进行。
       
    if(!m_loadr.load())
    {
        QMessageBox::critical(this,"",m_loader.errorString());
        return;
    }
    PluginInterface* pi= qobject_cast<PluginInterface*>(m_loader.instance());
    //进行强制类型转换，确保是PluginInterface的插件。
        if(pi)
        {
            QWidget* w=pi->genWidget();
            if(w)
            {
                ui->tabWidget->addTab(w,"hello plugin");
            }
        }
    //执行具体逻辑
    ```

在构建好两个程序后，应有以下步骤：

* 将插件接口文件放置在主程序的工程项目下。（放声明以调用）
* 将插件程序build后生成的dll放于主程序的工程项目下。（提供源）

本质上，**Qt的插件机制是基于C++原有的动态库、静态库的加载而建立的**。



