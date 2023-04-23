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
    MusicPlaybackModel m_model;

    Q_INVOKABLE void nextSong();
    Q_INVOKABLE void prevSong();
    Q_INVOKABLE void playSong();


private:
    static MusicPlayerController *m_instance;
    bool m_initialized;


signals:
    void modelMusicEnd();
    void setNextSong();
    void setPrevSong();

public slots:
    Q_INVOKABLE void setNewSong(QUrl musicPath);
    Q_INVOKABLE void pauseSong();
    Q_INVOKABLE void continueSong();
    Q_INVOKABLE void changePosition(qint64 pos);
    Q_INVOKABLE void setVolume(int volume);
};

#endif // MUSICPLAYERCONTROLLER_H
