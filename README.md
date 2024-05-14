# QT_practice
这是在QT学习的过程中想到的一些好点子，由于学习性的目的只制作了半成品，不过觉得有趣便保留下来慢慢更新。  
当做出半成品时我会先上传exe文件，待完成度达到能够让我推荐给好友玩之后会添加相应的代码和注释。
---
* keyStudio ： 一个能够给按键赋予音效的程序，可隐藏到托盘，运用hook信号连接QMedia实现，制作起因是想给我打游戏过程中添加点乐趣，但是制作完半成品才发现现在的游戏已经屏蔽掉这个接口了（悲
* slideWidget ：一个滑动窗体的测试，采用两个计时器进行检测窗体隐藏或显示，利用动画模块实现窗体的滑动。
* characterHubWidget： 一个页面原型，除开布局之外，还实现了一个小功能：验证码滑块。
* SLide_Widegt:一个滑动窗体的原型，仿造原神角色栏展开关闭设计，并添加了两种排布方式，同时尝试给窗体状态改变时添加变化的动画。
* QtLinkMySQLTest：一个Qt链接MySQL的测试，用于验证我在进行工程构建时的一些想法，目前印证过的有：利用表名和表结构在程序中建立简单的反射机制，实现数据的动态初始化。
* rotateTest：手卡圆弧展开的原型，测试使用QGraphicsProxyWidget代理QLabel放在Scene中，通过旋转和平移View来达到圆弧展开的功能。
* QtThreadTest：Qt多线程的练手项目，实现了一种方式的多线程下进行数据生成-排序然后传回主线程进行展示的功能。
* QtPluginsTest 和 PluginDemo1：Qt插件的练习项目，配套学习整理《Qt插件系统的使用.md》，用于构建项目中的插件系统（后续可能会再做一个更详细的练习用作原型）。
* QtPluginSystemCardDynamic、QtPluginSystemMainAppStatic和QtPluginSystemTest:作为面向工程开发的软件原型，实现逻辑、UI、插件结构分离开发，为项目提供可扩展功能（技术点和设计理念整理至《Qt插件系统的使用.md》）。
* QtSocketTest、QtServerTest：一个简易的双端通信原型。
* QtSendFileClientTest、QtSendFileServerTest：一个简易的文件传输原型。
* QtServerListTest：一个多端通信原型。
* StatusMachineTest：状态机框架的原型，供毕设的想法测试。
* PropertyTest：属性系统的练习，作为毕设参考的原型。
* OpenGLTest1/2：OpenGL学习的记录，作为技术积累。
* TemplateTest：将反射框架抽象成模板，作为毕设的参考原型。
* Qt_TreeTest：基于Qt的View/Model框架搭建的视图-模型结构的测试，尝试了基于Abstract基类衍生自定义View、Model、ProxyModel的练习，作为毕设UI和TOOL之间交互的一个选择。
* luaTest：lua和Qt的相互调用的测试，我打算以这个作为毕设的脚本系统的原型（本来预想的是通过指令系统控制图元的，但是想了一星期没想到该如何去组织这部分的控制结构和显示关系，还是参考unity的脚本系统来设计吧）。
* QGraphicViewTEST: 在里面测试了毕设所设计的四个基础Item的功能，作为毕设的参考原型。（目前包括地图：Map2DItem、角色：DynamicItem）
* ChartDemo: 一个线表的样例，实现基础功能：拖拽、缩放、框选高亮（设置和添加）保存为图片。
* DrawPieTest:一个环形选择界面的样例，实现基础排布与可选择性。

* AuraUITest01:一个非阻塞运算的样例，四种方式实现：QCore、QTimer、QThread、QObject:toThread

* BlueprintsTest:一个蓝图系统的示例，实现基于QGraphics框架下模块化结构的流式执行蓝图。
