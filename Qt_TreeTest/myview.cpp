#include "myview.h"

MyView::MyView(QWidget *parent)
    : QAbstractItemView{parent}
{

}

QRect MyView::visualRect(const QModelIndex &index) const
{
    //1、以下函数用于计算项目所占据的矩形(即位置和大小)

        //该函数在初次运行时便会由Qt调用，调用次数依模型而定，本例3*3的表格模型，
        //该函数会被调用18次。参数index包含模型的索引，index会在调用时循环传递。
        //比如对于本例，第一次调用时的索引为(0,0)，第二次为(0,1)，第3次为(0,2)...

        //计算项目的矩形：项目大小始终为(110,33)，位置随索引而不同。
        return QRect(index.column()*110,index.row()*33+20,110,33);

}

QModelIndex MyView::indexAt(const QPoint &point) const
{
        //2、以下函数返回鼠标光标所在位置的项目的索引

            //参数point包含了鼠标光标的坐标位置(视图坐标)
            int r=(point.y()-20)/33;			//计算光标位于哪一行。
            int c=point.x()/110;  				//计算光标位于哪一列。
            return model()->index(r,c);   		//返回该项目的索引。
}

void MyView::setSelection(const QRect &rect, QItemSelectionModel::SelectionFlags flags)
{
    //3、以下两个函数主要用于处理对项目的选择，当选择视图中的项目时，Qt才会调用他们。
    //当不需要选择项目时，以下两个函数可以不用实现。

            //参数rect包含了所选项目的矩形(位置和大小，使用视图坐标)
            //参数flags包含了选择项目时的选择标志。
            int r=(rect.y()-20)/33;			//计算选中的是哪一行。
            int c=rect.x()/110;			//计算选中的是哪一列。
            selectionModel()->select(model()->index(r,c),flags);


            //selectionModel:
            //SelectionFlags:
}

QRegion MyView::visualRegionForSelection(const QItemSelection &s) const
{
            //此函数用于计算所有被选择的项目占据的区域(即位置和大小)。
            //参数s包含了所选择的项目的范围。
            return QRegion();
}


int MyView::horizontalOffset() const
{
            return 0;
}

int MyView::verticalOffset() const
{
            return 0;
}

void MyView::scrollTo(const QModelIndex &index, ScrollHint hint)
{
    //逻辑实现：可以不做滚动
}

bool MyView::isIndexHidden(const QModelIndex &index) const
{
            //Item是否隐藏
            return false;
}

QModelIndex MyView::moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers)
{
            return QModelIndex();
}

void MyView::paintEvent(QPaintEvent *e)
{
    QPainter painter(viewport());     //表示在视口上绘制图形
            //使用QAbstractItemView::viewOptions()获取需要绘制的图形的信息(此步骤比较重要)
            QStyleOptionViewItem po;
            //循环遍历模型的大小。
            for(int r=0;r<model()->rowCount();r++)
                for(int c=0;c<model()->columnCount();c++){
                    QModelIndex i=model()->index(r,c);
                    QRect rect=visualRect(i);        //获取索引i所指项目的矩形(位置和大小)
                     po.rect=visualRect(i);
                    //处理项目被选择的情形
                    if(selectionModel()->isSelected(i)){  po.state |= QStyle::State_Selected;}
                    //使用代理绘制数据项(即项目)，这里也可使用自定义的代理(若已添加)
                    itemDelegate()->paint(&painter,po,i);
                    //以下代码用于绘制视图单元格的轮廓线。
                    painter.save();
                    painter.setPen(QPen(QColor(111,1,1)));  //创建画笔。
                    painter.drawLine(rect.bottomLeft(),rect.bottomRight());
                    painter.drawLine(rect.bottomRight(),rect.topRight());
                    painter.restore();
                }  //for结束
}  //paintEvent结束



