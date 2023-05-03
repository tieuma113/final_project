#include <QTime>
#include <QFileInfo>
#include <QDir>
#include "videoplaybackmodel.h"
#include "loghelper.h"
#include "appdefines.h"


VideoPlaybackModel::VideoPlaybackModel(QObject *parent)
    :MediaPlayer(parent)
{
    m_fileName = "";
    m_videoSurface = nullptr;
    m_player->setVideoOutput(m_videoSurface);
    connect(m_player, &QMediaPlayer::currentMediaChanged, this, &VideoPlaybackModel::onMediaChanged);
}

VideoPlaybackModel::~VideoPlaybackModel(){

}

QString VideoPlaybackModel::getFileName() const
{
    return m_fileName;
}

void VideoPlaybackModel::setFileName(const QString &newFileName)
{
    if (m_fileName == newFileName)
        return;
    m_fileName = newFileName;
    emit fileNameChanged();
}

void VideoPlaybackModel::onMediaChanged()
{
    m_fileName = m_player->media().request().url().toLocalFile();
    emit fileNameChanged();
}

QAbstractVideoSurface *VideoPlaybackModel::videoSurface() const
{
    return m_videoSurface;
}

void VideoPlaybackModel::setVideoSurface(QAbstractVideoSurface *newVideoSurface)
{
    if (m_videoSurface == newVideoSurface){
        LOG_INFO << "1";
        return;
    }
    LOG_INFO << "2";
    m_videoSurface = newVideoSurface;
    m_player->setVideoOutput(m_videoSurface);
    emit videoSurfaceChanged();
}
