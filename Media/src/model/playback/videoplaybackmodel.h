#ifndef VIDEOPLAYBACKMODEL_H
#define VIDEOPLAYBACKMODEL_H

#include "mediaplayer.h"
#include <QAbstractVideoSurface>

class VideoPlaybackModel : public MediaPlayer
{
    Q_OBJECT
    Q_PROPERTY(QString fileName READ getFileName WRITE setFileName NOTIFY fileNameChanged)
    Q_PROPERTY(QAbstractVideoSurface *videoSurface READ videoSurface WRITE setVideoSurface NOTIFY videoSurfaceChanged)

public:
    VideoPlaybackModel(QObject *parent = nullptr);
    ~VideoPlaybackModel();

    QString getFileName() const;
    void setFileName(const QString &newFileName);

    QAbstractVideoSurface *videoSurface() const;
    void setVideoSurface(QAbstractVideoSurface *newVideoSurface);


signals:
    void fileNameChanged();

    void videoSurfaceChanged();

public slots:
    void onMediaChanged();

private:
    QString m_fileName;
    QAbstractVideoSurface* m_videoSurface;
};

#endif // VIDEOPLAYBACKMODEL_H
