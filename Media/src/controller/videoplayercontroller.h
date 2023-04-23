#ifndef VIDEOPLAYERCONTROLLER_H
#define VIDEOPLAYERCONTROLLER_H

#include <QObject>
#include <QQmlContext>
#include "videoplaybackmodel.h"
#include "appdefines.h"

class VideoPlayerController : public QObject
{
    Q_OBJECT
private:
    explicit VideoPlayerController(QObject *parent = nullptr);

public:
    // singleton pattern
    ~VideoPlayerController();

    static VideoPlayerController* getInstance();

    void initialize(QQmlContext *context);

    void setMode(int mode);

    Q_INVOKABLE void nextVideo();
    Q_INVOKABLE void prevVideo();
    Q_INVOKABLE void fullScreen(bool s_fullScreen);
    VideoPlaybackModel m_model;

private:
    static VideoPlayerController *m_instance;
    bool m_initialized;


signals:

public slots:
    Q_INVOKABLE void playVideo();
    Q_INVOKABLE void pauseVideo();
    Q_INVOKABLE void continueVideo();
    Q_INVOKABLE void changePosition(qint64 pos);
};

#endif // VIDEOPLAYERCONTROLLER_H
