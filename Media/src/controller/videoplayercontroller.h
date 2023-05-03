#ifndef VIDEOPLAYERCONTROLLER_H
#define VIDEOPLAYERCONTROLLER_H

#include <QObject>
#include <QQmlContext>
#include <QVariant>
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

    VideoPlaybackModel* m_model;

private:
    static VideoPlayerController *m_instance;
    bool m_initialized;


signals:

public slots:
};

#endif // VIDEOPLAYERCONTROLLER_H
