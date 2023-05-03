#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include <QObject>
#include <QMediaPlayer>
#include <QTime>
#include <QMediaMetaData>
#include <QFileInfoList>
#include <QMediaPlaylist>
#include <QDir>
#include <QQmlContext>
#include "medialistmodel.h"

class MediaPlayer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QMediaPlayer *player READ player WRITE setPlayer NOTIFY playerChanged)
    Q_PROPERTY(MediaListModel *playList READ playList NOTIFY playListChanged)
    Q_PROPERTY(qint64 duration READ duration WRITE setDuration NOTIFY durationChanged)
    Q_PROPERTY(int position READ position WRITE setPosition NOTIFY positionChanged)

public:
    explicit MediaPlayer(QObject *parent = nullptr);
    ~MediaPlayer();

    virtual void setMedia(QString path, QStringList filter);
    virtual QMediaPlayer *player() const;
    virtual void setPlayer(QMediaPlayer *newPlayer);
    virtual MediaListModel *playList() const;
    virtual qint64 duration() const;
    virtual void setDuration(const int &newDuration);
    virtual int position() const;
    virtual void setPosition(const int &newPosition);

signals:
    void playerChanged();
    void playListChanged();
    void durationChanged();
    void positionChanged();

public slots:
    virtual void onPositionChanged(int pos);
    virtual void onDurationChanged(int dur);
    virtual void setVolume(int volume);

protected:
    QMediaPlayer *m_player;
    MediaListModel *m_playList;
    qint64 m_duration;
    int m_position;
};

Q_DECLARE_METATYPE(QMediaPlayer*)
#endif // MEDIAPLAYER_H
