#include <QImage>
#include <QTime>
#include <QFileInfo>
#include "musicplaybackmodel.h"
#include "loghelper.h"
#include "appdefines.h"

MusicPlaybackModel::MusicPlaybackModel(QObject *parent)
    : QObject(parent)
{
    m_player = new QMediaPlayer();
    m_state = QMediaPlayer::StoppedState;
    m_mediaPlaylist = new QMediaPlaylist();
    connect(m_player,
            &QMediaPlayer::stateChanged,
            this,
            &MusicPlaybackModel::handleStateChanged);

    connect(m_player,
            &QMediaPlayer::mediaStatusChanged,
            this,
            &MusicPlaybackModel::handleMediaStatus);

    connect(m_player,
            &QMediaPlayer::positionChanged,
            this,
            &MusicPlaybackModel::handlePlayingTimeChanged);

    connect(m_player,
            SIGNAL(metaDataChanged(const QString &, const QVariant &)),
            this,
            SLOT(onMetaDataChanged(const QString &, const QVariant &)));
}

MusicPlaybackModel::~MusicPlaybackModel(){
    m_player->setMedia(nullptr);
}

void MusicPlaybackModel::initialize(){
    LOG_INFO << "Request play";
    QDir m_dir(MUSIC_PATH);
    if (!m_dir.exists()){
        LOG_INFO << "dir not exists";
    }else{
        m_dir.setFilter(QDir::Files);
        m_dir.setNameFilters(QStringList()<<("*.mp3"));
        m_dir.setSorting(QDir::Name);
        m_dir.sorting();
        QFileInfoList fileinfoList = m_dir.entryInfoList();
        if (fileinfoList.count() == 0){
            LOG_INFO << "no music file";
        }else{
//            setIndex(0);
            for (auto const &info : fileinfoList)
            {
                m_mediaPlaylist->addMedia(QUrl::fromLocalFile(info.absoluteFilePath()));
            }
        }
    }
    m_player->setPlaylist(m_mediaPlaylist);
    m_msDuration = 0;
    m_title = "";
    m_artist = "";
    m_album = "";
    QFileInfo tempCover (MUSIC_UNKNOWN_COVER_ART_PATH);
    m_coverImageUrl = QUrl::fromLocalFile(tempCover.absoluteFilePath()).toString();
    emit coverChanged(false);
    emit TitleChanged("Unknown");
    emit ArtistChanged("Unknown");
    emit AlbumChanged();
    emit DurationChanged();
    emit valuePositionChanged();
}

void MusicPlaybackModel::requestPlay(){
    m_player->play();
}

void MusicPlaybackModel::handlePlayingTimeChanged(qint64 position){
    LOG_INFO << "position change to: " << position;
    m_position = position;
    LOG_INFO << m_position;
    emit PositionChanged();
    emit valuePositionChanged();
}

void MusicPlaybackModel::handleMediaStatus(QMediaPlayer::MediaStatus status){
    if (status == QMediaPlayer::EndOfMedia){
        LOG_INFO << "music end";
        emit musicEnd();
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
        emit DurationChanged();
    }
}

QString MusicPlaybackModel::valuePosition(){
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

void MusicPlaybackModel::nextMusic()
{
    m_player->playlist()->next();
}

void MusicPlaybackModel::previousMusic()
{
    m_player->playlist()->previous();
}

void MusicPlaybackModel::onMetaDataChanged(const QString &key, const QVariant &value){
    if (key == QMediaMetaData::Title){
        LOG_INFO << "song title: " << value.toString();
        m_title = value.toString();
        emit TitleChanged(m_title);
    }
    else if (key == QMediaMetaData::AlbumArtist){
        LOG_INFO << "song artist" << value.toString();
        m_artist = value.toString();
        emit ArtistChanged(m_artist);
    }
    else if(key == QMediaMetaData::AlbumTitle){
        LOG_INFO << "song album" << value.toString();
        m_album = value.toString();
        emit AlbumChanged();
    }
    else if (key == QMediaMetaData::CoverArtImage){
        LOG_INFO;
        QImage cover = value.value<QImage>();
        cover.save(MUSIC_ART_COVER_PATH);
        QFileInfo temp(MUSIC_ART_COVER_PATH);
        m_coverImageUrl = QUrl::fromLocalFile(temp.absoluteFilePath()).toString();
        emit coverChanged(true);
    }
}

void MusicPlaybackModel::handleStateChanged(QMediaPlayer::State state){
    m_state = state;
    LOG_INFO << "state change to" << (int) state;
    if (state == QMediaPlayer::PlayingState){
        m_isPlay = true;
        emit musicState();
    }
    else if(state == QMediaPlayer::PausedState){
        m_isPlay = false;
        emit musicState();

    }else if (state == QMediaPlayer::StoppedState){
        m_isPlay = false;
        emit musicState();
    }
}

void MusicPlaybackModel::setVolume(int volume)
{
    qDebug() << volume;
    m_player->setVolume(volume * 10);
}

void MusicPlaybackModel::stop(){
    m_player->stop();
}

void MusicPlaybackModel::requestPause(){
    if (m_state != QMediaPlayer::PausedState){
        m_player->pause();
    }
}

void MusicPlaybackModel::requestContinue(){
    if (m_state != QMediaPlayer::PlayingState){
        m_player->play();
    }
}

QString MusicPlaybackModel::getTitle(){
    return m_title;
}

QString MusicPlaybackModel::getArtist(){
    return m_artist;
}

QString MusicPlaybackModel::getAlbum(){
    return m_album;
}

QString MusicPlaybackModel::getDuration(){
    return m_duration;
}

qint64 MusicPlaybackModel::getMsDuration(){
    return m_msDuration;
}

qint64 MusicPlaybackModel::getPosition(){
    return m_position;
}

void MusicPlaybackModel::changePosition(qint64 pos){
    m_player->setPosition(pos);
}

QString MusicPlaybackModel::getCoverArtUrl(){
    return m_coverImageUrl;
}

bool MusicPlaybackModel::isPlay(){
    return m_isPlay;
}
