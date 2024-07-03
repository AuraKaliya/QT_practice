#include "aurapixtool.h"
#include <QPainter>
#include <QPainterPath>

QPixmap AuraPixTool::getRoundRectPixmap(const QPixmap &srcPixMap, const QSize &size, int radius)
{
    if (srcPixMap.isNull()) {
        return srcPixMap;
    }

    // 获取图片尺寸
    int imageWidth = size.width();
    int imageHeight = size.height();

    // 处理大尺寸的图片，保证图片显示区域完整
    QPixmap newPixMap = srcPixMap.scaled(imageWidth, imageHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    // 创建目标图像
    QPixmap destImage(imageWidth, imageHeight);
    destImage.fill(Qt::transparent); // 填充透明背景

    QPainter painter(&destImage);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform); // 设置抗锯齿和平滑变换

    // 创建圆角矩形路径
    QPainterPath path;
    path.addRoundedRect(QRect(0, 0, imageWidth, imageHeight), radius, radius);

    // 设置剪裁路径
    painter.setClipPath(path);

    // 绘制原始图像到目标图像
    painter.drawPixmap(0, 0, newPixMap);

    return destImage;
}

void AuraPixTool::burlImage(QImage &blurImage, qreal radius, bool quality, bool alphaOnly, int transposed)
{
    QtPixTool::qt_blurImage(blurImage,radius,quality,alphaOnly,transposed);
}

QPixmap AuraPixTool::createColoredCircle(QColor color, unsigned int a, unsigned int diameter)
{
    if(a<=diameter) diameter=a;

    QPixmap pix(a,a);
    pix.fill(Qt::transparent);

    QPainter painter(&pix);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(color));

    painter.drawEllipse((a-diameter)/2,(a-diameter)/2,diameter,diameter);
    painter.end();
    return pix;
}

QPixmap AuraPixTool::applyGaussianBlur(QPixmap pix, qreal radius)
{
    // 创建一个图形场景
    QGraphicsScene scene;
    // 创建一个图形项并添加到场景中
    QGraphicsPixmapItem item;
    item.setPixmap(pix);
    scene.addItem(&item);

    // 创建高斯模糊效果并设置半径
    QGraphicsBlurEffect blur;
    blur.setBlurRadius(radius);
    // 将模糊效果应用于图形项
    item.setGraphicsEffect(&blur);

    // 创建一个QImage来存储模糊后的图像
    QImage blurredImage(pix.size(), QImage::Format_ARGB32);
    blurredImage.fill(Qt::transparent); // 透明背景

    // 使用QPainter将模糊后的图像绘制到QImage上
    QPainter painter(&blurredImage);
    scene.render(&painter);

    // 将QImage转换回QPixmap并返回
    return QPixmap::fromImage(blurredImage);
}

AuraPixTool::AuraPixTool()
{

}
