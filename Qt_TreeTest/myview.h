#ifndef MYVIEW_H
#define MYVIEW_H

#include <QAbstractItemView>
#include <QLabel>
#include <QObject>
#include <QStandardItemModel>
#include <qpainter.h>

class MyView : public QAbstractItemView
{
    Q_OBJECT
public:
    explicit MyView(QWidget *parent = nullptr);

    //必要实现
    QRect visualRect(const QModelIndex &index) const override;      //索引对应的Item所在位置
    QModelIndex indexAt(const QPoint &point) const override;        //鼠标位置对应的Item的索引

    //其他实现
    void setSelection(const QRect &rect, QItemSelectionModel::SelectionFlags flags) override;  //处理对项目的选择，当选择视图中的项目时，Qt才会调用
    QRegion visualRegionForSelection(const QItemSelection &s) const override;       //选择区域的大小


    //必要实现
    int horizontalOffset() const override;  //水平偏移量设置
    int verticalOffset() const	override;   //垂直偏移量设置
    void scrollTo(const QModelIndex &index, ScrollHint hint = EnsureVisible) override;  //滚动视图的逻辑
    bool isIndexHidden(const QModelIndex &index) const override;     //Item是否隐藏

    QModelIndex moveCursor(CursorAction cursorAction ,Qt::KeyboardModifiers modifiers)override;  //处理（通过按键）焦点变化时的逻辑

    void paintEvent(QPaintEvent *e) override;           //用于绘制视图的外观
signals:
};

class V:public QAbstractItemView{
public:
    //1、以下函数用于计算项目所占据的矩形(即位置和大小)
    QRect visualRect(const QModelIndex &index) const{
        //该函数在初次运行时便会由Qt调用，调用次数依模型而定，本例3*3的表格模型，
        //该函数会被调用18次。参数index包含模型的索引，index会在调用时循环传递。
        //比如对于本例，第一次调用时的索引为(0,0)，第二次为(0,1)，第3次为(0,2)...

        //计算项目的矩形：项目大小始终为(110,33)，位置随索引而不同。
        return QRect(index.column()*110,index.row()*33+20,110,33);		}

    //2、以下函数返回鼠标光标所在位置的项目的索引
    QModelIndex indexAt(const QPoint &point) const{		//该函数在点击鼠标时Qt会调用。
        //参数point包含了鼠标光标的坐标位置(视图坐标)
        int r=(point.y()-20)/33;			//计算光标位于哪一行。
        int c=point.x()/110;  				//计算光标位于哪一列。
        return model()->index(r,c);  } 		//返回该项目的索引。

    //3、以下两个函数主要用于处理对项目的选择，当选择视图中的项目时，Qt才会调用他们。
    //当不需要选择项目时，以下两个函数可以不用实现。
    void setSelection(const QRect &rect, QItemSelectionModel::SelectionFlags flags) {
        //参数rect包含了所选项目的矩形(位置和大小，使用视图坐标)
        //参数flags包含了选择项目时的选择标志。
        int r=(rect.y()-20)/33;			//计算选中的是哪一行。
        int c=rect.x()/110;			//计算选中的是哪一列。
        selectionModel()->select(model()->index(r,c),flags);	}    //选择所选中的索引。

    QRegion visualRegionForSelection(const QItemSelection &s) const {
        //此函数用于计算所有被选择的项目占据的区域(即位置和大小)。
        //参数s包含了所选择的项目的范围。
        return QRegion();    }

    //4、以下函数用于计算视图的滚动，本例是最小实现，不需要滚动，所以不需要实现以下3个函数。
    int horizontalOffset() const{      return 0;	}
    int verticalOffset() const	{      return 0; 	}
    void scrollTo(const QModelIndex &index, ScrollHint hint = EnsureVisible){}

    //5、本示例不需要隐藏项目，所以以下函数直接返回0即可。
    bool isIndexHidden(const QModelIndex &index) const{    return 0;   }

    //6、以下函数用于处理键盘按键(比如按下左键应返回左侧的项目索引等)，本示例不处理键盘按键，
    //所以不需要实现。
    QModelIndex moveCursor(CursorAction cursorAction ,Qt::KeyboardModifiers modifiers){
        return QModelIndex(); 	}

    //7、以下函数是核心，用于绘制视图的外观，也就是说若没有以下函数，则视图什么也不会显示。
    void paintEvent(QPaintEvent *e){
        QPainter pt(viewport());   //在视口上绘制图形
        //使用QAbstractItemView::viewOptions()获取需要绘制的图形的信息(此步骤比较重要)
        QStyleOptionViewItem po;
        //循环遍历模型的大小。
        for(int r=0;r<model()->rowCount();r++)
            for(int c=0;c<model()->columnCount();c++){
                QModelIndex i=model()->index(r,c);
                QRect rect=visualRect(i);        //获取索引i所指项目的矩形(位置和大小)
                //  --- po.rect=visualRect(i);
                //处理项目被选择的情形
                if(selectionModel()->isSelected(i)){  po.state |= QStyle::State_Selected;}
                //使用代理绘制数据项(即项目)，这里也可使用自定义的代理(若已添加)
                itemDelegate()->paint(&pt,po,i);
                //以下代码用于绘制视图单元格的轮廓线。
                pt.save();
                pt.setPen(QPen(QColor(111,1,1)));  //创建画笔。
                pt.drawLine(rect.bottomLeft(),rect.bottomRight());
                pt.drawLine(rect.bottomRight(),rect.topRight());
                pt.restore(); 		}  //for结束
    }  //paintEvent结束
};

class B:public QWidget{    Q_OBJECT
public:    QStandardItemModel *d;    V *pv;
    B(QWidget *p=0):QWidget(p){
        d=new QStandardItemModel(3,3);
        V* pv=new V;    		//使用自定义的视图
        //向模型中添加数据
        d->setData(d->index(0,0),"AAA");    d->setData(d->index(0,1),"BBB");
        d->setData(d->index(1,0),"CCC");    d->setData(d->index(1,2),"DDD");
        d->setData(d->index(1,1),"EEE");    d->setData(d->index(2,0),"FFF");
        d->setData(d->index(1,1),QIcon("F:/1i.png"),Qt::DecorationRole);

        //向视图中添加标签，以用于视图的标头，以下代码主要演示视图还可以像使用一个QFrame那样使用。
        QLabel *pp=new QLabel("111",pv);
        pp->setAutoFillBackground(1);  //使标签不透明。
        pp->setAlignment(Qt::AlignCenter);   pp->resize(111,20);
        QLabel *pp1=new QLabel("222",pv);    pp1->setAutoFillBackground(1);
        pp1->setAlignment(Qt::AlignCenter);  pp1->resize(111,20);   pp1->move(111,0);
        QLabel *pp2=new QLabel("333",pv);	pp2->setAutoFillBackground(1);
        pp2->setAlignment(Qt::AlignCenter); 	pp2->resize(111,20);	pp2->move(222,0);

        //pv->setItemDelegate(pt);   //也可以添加自定义代理，以使用自定义代理绘制数据项。
        pv->setModel(d);    pv->resize(333,222);    pv->show();         }
};

#endif // MYVIEW_H
