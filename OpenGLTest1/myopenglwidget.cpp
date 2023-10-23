#include "myopenglwidget.h"

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent)
    : QOpenGLWidget{parent}
{


}

void MyOpenGLWidget::draw(Shap shap)
{
    m_shap=shap;
    update();
}

const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0);\n"
                                 "}\n\0";

const char * fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "FragColor= vec4(1.0f, 0.2f, 0.4f, 1.0f);\n"
                                   "}\n\0";
float vertices[]={-0.5f,-0.5f,0.0f,0.5f,-0.5f,0.0f,0.0f,0.5f,0.0f};
float vertices2[]={0.5f,0.5f,0.0f,
                  0.5f,-0.5f,0.0f,
                  -0.5f,0.5f,0.0f,

                  -0.5f,-0.5f,0.0f,
                  0.5f,-0.5f,0.0f,

                  -0.5f,0.5f,0.0f };
float vertices3[]={-0.5f,0.5f,0.0f,
                   0.5f,0.5f,0.0f,
                   -0.5f,-0.5f,0.0f,
                    0.5f,-0.5f,0.0f};
unsigned int indexs[]={
                0,1,3,
                1,2,3
};



unsigned int VBO,VAO,EBO;
unsigned int shaderProgram;
void MyOpenGLWidget::initializeGL()
{

    initializeOpenGLFunctions();

    //创建VAO、VBO对象并赋予ID；

    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);

    //绑定VAO、VBO对象（通过ID绑定）
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);

    //为当前绑定到target的缓冲区对象创建一个新的数据存储
    //如果data不是Null，则使用data的数据初始化数据存储。
    //glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices2),vertices2,GL_STATIC_DRAW);

    //告知显卡如何使用缓冲区内的属性值（解析）
    //使用标号为0的属性，3个内容，每个内容3个float，偏移量为0，不需要标准化。
    //VAO同时对其进行记录
    //glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);

    //开启VAO中第一个属性值
    glEnableVertexAttribArray(0);




    //编写顶点着色器
    unsigned int vertexShader=glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
    glCompileShader(vertexShader);

    int success;
    char infolog[512];
    glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader,512,NULL,infolog);
        qDebug()<<"Error:"<<infolog;
    }


    //编写片段着色器
    unsigned int fragmentShader=glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader,512,NULL,infolog);
        qDebug()<<"Error:"<<infolog;
    }

    //进行连接
    shaderProgram=glCreateProgram();
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    glLinkProgram(shaderProgram);


    glGetProgramiv(shaderProgram,GL_LINK_STATUS,&success);
    if(!success)
    {
        glGetProgramInfoLog(shaderProgram,512,NULL,infolog);
        qDebug()<<"Error:"<<infolog;
    }


#if 1
    //已使用完，对着色器进行回收
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
#endif

    //设置绘制模式--正反面，填充方式
    //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glPolygonMode(GL_FRONT,GL_LINE);
    glPolygonMode(GL_BACK,GL_FILL);

    //默认顺时针是反面，逆时针是正面   GL_CCW 逆时针   GL_CW 顺时针
    glFrontFace(GL_CW); //将顺时针设置为“正面” 同时逆时针变为反面

    //创建EBO，这时候VAO会进行记录所有操作！（包括解绑）
    glGenBuffers(1,&EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indexs),indexs,GL_STATIC_DRAW);


    //设置完毕，解绑
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);
}

void MyOpenGLWidget::resizeGL(int w, int h)
{

}

void MyOpenGLWidget::paintGL()
{
    glClearColor(0.2f,0.2f,0.3f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

#if 1
    glUseProgram(shaderProgram);

    //绑定VAO，从VAO中取点进行绘制  从0开始拿6个数据
    glBindVertexArray(VAO);
   // glDrawArrays(GL_TRIANGLES,0,6);

    //使用EBO进行绘制
    //glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);

    switch (m_shap) {
    case Rect:
        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
        break;
    default:
        break;
    }






#endif
}
