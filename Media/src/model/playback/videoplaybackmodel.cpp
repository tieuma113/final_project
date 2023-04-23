#include <QTime>
#include <QFileInfo>
#include <QDir>
#include "videoplaybackmodel.h"
#include "loghelper.h"
#include "appdefines.h"


VideoPlaybackModel::VideoPlaybackModel(QObject *parent)
    :QObject(parent)
{
    m_fileName = "";
    m_player = new QMediaPlayer();
    m_state = QMediaPlayer::StoppedState;
    QDir contentDir(VIDEO_PATH);
    if (!contentDir.exists()){
        LOG_INFO <<"dir not exists";
    }else{
        contentDir.setFilter(QDir::Files);
        contentDir.setNameFilters(QStringList()<<("*.mp4"));
        contentDir.setSorting(QDir::Name);
        contentDir.sorting();
        contentList = contentDir.entryInfoList();
        foreach (QFileInfo file, contentList) {
            m_playlist.addMedia(QMediaContent(QUrl::fromLocalFile(file.absoluteFilePath())));
        }
        if (m_playlist.mediaCount() > 0){
            m_playlist.setCurrentIndex(0);
            m_fileName = contentList.at(0).fileName();
        }
        emit fileNameChanged(m_fileName);
    }
    m_position = 0;
    emit PositionChanged();
    m_player->setPlaylist(&m_playlist);

    connect(m_player,
            &QMediaPlayer::stateChanged,
            this,
            &VideoPlaybackModel::handleStateChanged);

    connect(m_player,
            &QMediaPlayer::mediaStatusChanged,
            this,
            &VideoPlaybackModel::handleMediaStatus);

    connect(m_player,
            &QMediaPlayer::positionChanged,
            this,
            &VideoPlaybackModel::handlePlayingTimeChanged);
}

QString VideoPlaybackModel::valuePosition(){
    int second = m_position /1000;
    int minute = second / 60;
    second = second % 60;
    int hour = minute / 60;
    minute = minute % 60;
    QString currentTime;
    QTime convert(hour,minute,second);
    if (hour > 0){
        currentTime = convert.toString("hh:mm:ss");
    }else{
        currentTime = convert.toString("mm:ss");
    }
    return currentTime;
}

VideoPlaybackModel::~VideoPlaybackModel(){
    m_videoPlayer = nullptr;
    m_player->setVideoOutput(m_videoPlayer);
}

QAbstractVideoSurface* VideoPlaybackModel::videoSurface() const{
    return m_videoPlayer;
}

void VideoPlaybackModel::setVideoSurface(QAbstractVideoSurface* surface){
    if (m_videoPlayer != surface){
        m_videoPlayer = surface;
        m_player->setVideoOutput(m_videoPlayer);
        emit videoSurfaceChanged();
    }
}

void VideoPlaybackModel::next(){
    LOG_INFO;
    if (m_player->playlist()->currentIndex() == m_playlist.mediaCount() - 1){
        return;
    }
    m_playlist.next();
    m_fileName = contentList.at(m_playlist.currentIndex()).fileName();
    m_player->play();
    emit fileNameChanged(m_fileName);

}

void VideoPlaybackModel::prev(){
    LOG_INFO;
    if (m_player->playlist()->currentIndex() == 0){
        return;
    }
    m_player->playlist()->previous();
    m_fileName = contentList.at(m_player->playlist()->currentIndex()).fileName();
    m_player->play();
    emit fileNameChanged(m_fileName);
}

void VideoPlaybackModel::requestPlay(){
    LOG_INFO;
    if (m_player->playlist()->currentIndex()  > m_player->playlist()->mediaCount() - 1){
        LOG_INFO << "out off video";
        return;
    }
    m_player->play();
    m_fileName = contentList.at(m_player->playlist()->currentIndex()).fileName();
    emit fileNameChanged(m_fileName);
}

void VideoPlaybackModel::handlePlayingTimeChanged(qint64 position){
    LOG_INFO;
    m_position = position;
    emit PositionChanged();
    emit valuePositionChanged();
}

void VideoPlaybackModel::handleMediaStatus(QMediaPlayer::MediaStatus status){
    LOG_INFO;
    if (status == QMediaPlayer::EndOfMedia){
        LOG_INFO;
        emit videoEnd();
    }
    else if (status == QMediaPlayer::BufferedMedia){
        m_msDuration = m_player->duration();
        int second = m_msDuration /1000;
        int minute = second / 60;
        second = second % 60;
        int hour = minute / 60;
        minute = minute % 60;
        QTime convert(hour,minute,second);
        if (hour > 0){
            m_duration = convert.toString("hh:mm:ss");
        }else{
            m_duration = convert.toString("mm:ss");
        }
        qDebug() << m_duration;
        emit DurationChanged();
    }
}

void VideoPlaybackModel::stop(){
    m_player->stop();
}

bool VideoPlaybackModel::fullScreen()
{
    return m_fullScreen;
}

void VideoPlaybackModel::setFullScreen(bool s_fullScreen)
{
    LOG_INFO << s_fullScreen;
    m_fullScreen = s_fullScreen;
    emit fullScreenChanged();
}

void VideoPlaybackModel::handleStateChanged(QMediaPlayer::State state){
    m_state = state;
    LOG_INFO;
    if (state == QMediaPlayer::PlayingState){
        m_isPlay = true;
        emit videoState();
    }
    else if (state == QMediaPlayer::PausedState){
        m_isPlay = false;
        emit videoState();
    }
    else if (state == QMediaPlayer::StoppedState){
        m_isPlay = false;
        emit videoState();
    }
}

void VideoPlaybackModel::requestPause(){
    LOG_INFO;
    if (m_state != QMediaPlayer::PausedState){
        m_player->pause();
    }
}

void VideoPlaybackModel::requestContinue(){
    LOG_INFO;
    if (m_state != QMediaPlayer::PlayingState){
        m_player->play();
    }
}

QString VideoPlaybackModel::getDuration(){
    LOG_INFO;
    return m_duration;
}

qint64 VideoPlaybackModel::getMsDuration(){
    LOG_INFO;
    return m_msDuration;
}

qint64 VideoPlaybackModel::getPosition(){
    LOG_INFO;
    return m_position;
}

void VideoPlaybackModel::changePosition(qint64 pos){
    LOG_INFO;
    m_player->setPosition(pos);
}

bool VideoPlaybackModel::isPlay(){
    LOG_INFO;
    return m_isPlay;
}

QString VideoPlaybackModel::getFileName(){
    LOG_INFO;
    return m_fileName;
}
