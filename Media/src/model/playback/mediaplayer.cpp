#include "mediaplayer.h"
#include "loghelper.h"
#include "appdefines.h"

MediaPlayer::MediaPlayer(QObject *parent)
    : QObject{parent}
{
    m_player = new QMediaPlayer();
    m_playList = new MediaListModel();
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
    m_duration = "";
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

QString MediaPlayer::duration() const
{
    return m_duration;
}

void MediaPlayer::setDuration(const QString &newDuration)
{
    if (m_duration == newDuration)
        return;
    m_duration = newDuration;
    emit durationChanged();
}

QString MediaPlayer::position() const
{
    return m_position;
}

void MediaPlayer::setPosition(const QString &newPosition)
{
    if (m_position == newPosition)
        return;
    m_position = newPosition;
    emit positionChanged();
}

void MediaPlayer::onDurationChanged(qint64 duration)
{
    QTime tempDuration = QTime(0,0).addMSecs(duration);
    if(duration > 216000)
    {
        m_duration = tempDuration.toString("hh:mm:ss");
    }
    else
    {
        m_duration = tempDuration.toString("mm:ss");
    }
    emit durationChanged();
}

void MediaPlayer::setVolume(int volume)
{
    LOG_INFO << volume;
    m_player->setVolume(volume * 10);
}

