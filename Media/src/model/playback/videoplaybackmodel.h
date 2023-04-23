#ifndef VIDEOPLAYBACKMODEL_H
#define VIDEOPLAYBACKMODEL_H

#include <QObject>
#include <QMediaPlayer>
#include <QAbstractVideoSurface>
#include <QMediaPlaylist>
#include <QFileInfo>

class VideoPlaybackModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString FileName READ getFileName NOTIFY fileNameChanged)
    Q_PROPERTY(QString Duration READ getDuration NOTIFY DurationChanged)
    Q_PROPERTY(qint64 msDuration READ getMsDuration NOTIFY DurationChanged)
    Q_PROPERTY(qint64 position READ getPosition NOTIFY PositionChanged)
    Q_PROPERTY(bool isPlay READ isPlay NOTIFY videoState)
    Q_PROPERTY(QAbstractVideoSurface* videoSurface READ videoSurface WRITE setVideoSurface NOTIFY videoSurfaceChanged)
    Q_PROPERTY(bool fullScreen READ fullScreen NOTIFY fullScreenChanged)
    Q_PROPERTY(QString valuePosition READ valuePosition NOTIFY valuePositionChanged)

public:
    VideoPlaybackModel(QObject *parent = nullptr);
    ~VideoPlaybackModel();

    void requestPlay();
    void requestPause();
    void requestContinue();
    QString getDuration();
    qint64 getMsDuration();
    qint64 getPosition();
    void changePosition(qint64 pos);
    bool isPlay();
    QAbstractVideoSurface *videoSurface() const;
    void setVideoSurface(QAbstractVideoSurface *surface);
    QString getFileName();
    void next();
    void prev();
    void stop();
    bool fullScreen();
    void setFullScreen(bool s_fullScreen);
    QString valuePosition();

signals:
    void fileNameChanged(QString fileName);
    void videoEnd();
    void DurationChanged();
    void PositionChanged();
    void videoState();
    void videoSurfaceChanged();
    void fullScreenChanged();
    void valuePositionChanged();

public slots:
    void handlePlayingTimeChanged(qint64 position);
    void handleMediaStatus(QMediaPlayer::MediaStatus status);
    void handleStateChanged(QMediaPlayer::State state);

private:
    QFileInfoList contentList;
    QString m_fileName;
    QMediaPlayer *m_player;
    QAbstractVideoSurface *m_videoPlayer;
    QMediaPlayer::State m_state;
    QString m_duration;
    qint64 m_msDuration;
    qint64 m_position;
    bool m_isPlay;
    QMediaPlaylist m_playlist;
    bool m_fullScreen;
};

#endif // VIDEOPLAYBACKMODEL_H
