#include "imageprovider.h"

ImageProvider::ImageProvider()
    :QQuickImageProvider(QQuickImageProvider::Image)
{

}

QImage ImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize){
    return m_image;
}

void ImageProvider::updateImage(QImage newImage){
    m_image = newImage;
}
