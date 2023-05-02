#include "mediaplayer.h"
#include "loghelper.h"
#include "appdefines.h"

MediaPlayer::MediaPlayer(QObject *parent)
    : QObject{parent}
{
    m_player = new QMediaPlayer();
    m_playList = new MediaListModel();
    connect(m_player, &QMediaPlayer::positionChanged,
            this, &MediaPlayer::onPositionChanged);
    connect(m_player, &QMediaPlayer::durationChanged,
            this, &MediaPlayer::onDurationChanged);
}

MediaPlayer::~MediaPlayer()
{
    delete m_player;
    delete m_playList;
}

void MediaPlayer::setMedia(QString path, QStringList filter)
{
    m_playList->setMediaList(path, filter);
    m_player->setPlaylist(m_playList->getData());
    m_duration = 0;
}

QMediaPlayer *MediaPlayer::player() const
{
    return m_player;
}

void MediaPlayer::setPlayer(QMediaPlayer *newPlayer)
{
    if (m_player == newPlayer)
        return;
    m_player = newPlayer;
    emit playerChanged();
}

MediaListModel *MediaPlayer::playList() const
{
    return m_playList;
}

qint64 MediaPlayer::duration() const
{
    return m_duration;
}

void MediaPlayer::setDuration(const int &newDuration)
{
    if (m_duration == newDuration)
        return;
    m_duration = newDuration;
    emit durationChanged();
}

int MediaPlayer::position() const
{
    return m_position;
}

void MediaPlayer::setPosition(const int &newPosition)
{
    m_position = newPosition;
    emit positionChanged();
}

void MediaPlayer::onPositionChanged(int pos)
{
    m_position = pos;
    emit positionChanged();
}

void MediaPlayer::onDurationChanged(int dur)
{
    m_duration = dur;
    emit durationChanged();
}

void MediaPlayer::setVolume(int volume)
{
    LOG_INFO << volume;
    m_player->setVolume(volume * 10);
}

