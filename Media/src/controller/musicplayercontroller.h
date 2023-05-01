#ifndef MUSICPLAYERCONTROLLER_H
#define MUSICPLAYERCONTROLLER_H

#include <QObject>
#include <QQmlContext>
#include "musicplaybackmodel.h"
#include "appdefines.h"

class MusicPlayerController : public QObject
{
    Q_OBJECT
private:
    explicit MusicPlayerController(QObject *parent = nullptr);
    int m_mode;

public:
    ~MusicPlayerController();

    // singleton pattern
    static MusicPlayerController *getInstance();


    void initialize(QQmlContext *context);
    void setMode(int mode);
    MusicPlaybackModel* m_model;

private:
    static MusicPlayerController *m_instance;
    bool m_initialized;

};

#endif // MUSICPLAYERCONTROLLER_H
