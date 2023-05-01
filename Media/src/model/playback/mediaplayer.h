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
    Q_PROPERTY(QString duration READ duration WRITE setDuration NOTIFY durationChanged)
    Q_PROPERTY(QString position READ position WRITE setPosition NOTIFY positionChanged)

public:
    explicit MediaPlayer(QObject *parent = nullptr);
    ~MediaPlayer();

    virtual void setMedia(QString path, QStringList filter);
    virtual QMediaPlayer *player() const;
    virtual void setPlayer(QMediaPlayer *newPlayer);
    virtual MediaListModel *playList() const;
    virtual QString duration() const;
    virtual void setDuration(const QString &newDuration);
    virtual QString position() const;
    virtual void setPosition(const QString &newPosition);

signals:
    void playerChanged();
    void playListChanged();
    void durationChanged();
    void positionChanged();

public slots:
    virtual void onDurationChanged(qint64 duration);
    virtual void setVolume(int volume);

protected:
    QMediaPlayer *m_player;
    MediaListModel *m_playList;
    QString m_duration;
    QString m_position;
    bool m_initialized;
};

Q_DECLARE_METATYPE(QMediaPlayer*)
#endif // MEDIAPLAYER_H
