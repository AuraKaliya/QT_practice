#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "people.h"
#include<QMetaProperty>
#include<QVector>
#include "translator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void updatePropertiesList();


private slots:
    void on_updateBtn_clicked();
    void on_newBtn_clicked();

    void on_list_currentRowChanged(int currentRow);

private:
    Ui::MainWindow *ui;
    QVector<QMetaProperty> m_properties;
    QVector<QByteArray> m_dynamicProperties;
    People * m_people;
    QMetaProperty* m_nowProperties;
    ModelProperty* m_nowDynamicProperties;
    bool m_mutex=false;


};
#endif // MAINWINDOW_H
