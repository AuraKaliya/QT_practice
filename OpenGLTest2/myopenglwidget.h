#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>
#include <QTimer>
class MyOpenGLWidget : public QOpenGLWidget,QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    enum Shap{None,Rect,Circle,Triangle};   //用策略模式优化
    explicit MyOpenGLWidget(QWidget *parent = nullptr);
    void draw(Shap shap);
public slots:
    void timeoutFunc();
protected:
     void initializeGL()override;
     void resizeGL(int w, int h)override;
     void paintGL()override;
signals:
private:
    Shap m_shap=None;
    QOpenGLShaderProgram* m_shaderProgram;
    QTimer * m_timer;

};

#endif // MYOPENGLWIDGET_H
