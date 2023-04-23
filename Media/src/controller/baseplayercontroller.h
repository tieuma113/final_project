#ifndef BASEPLAYERCONTROLLER_H
#define BASEPLAYERCONTROLLER_H

#include <QObject>
#include <QQmlContext>
#include <QMediaPlayer>
#include "baseplaybackmodel.h"

class BasePlayerController : public QObject
{
    Q_OBJECT

public:
    ~BasePlayerController();

    // initialize controller
    void initialize(QQmlContext *context);

private:
    bool m_initialized;

protected:
    QMediaPlayer m_player;
    BasePlaybackModel *m_model = nullptr;
};

#endif // MUSICPLAYERCONTROLLER_H
