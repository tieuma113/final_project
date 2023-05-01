#include "musicplayercontroller.h"
#include "loghelper.h"

MusicPlayerController *MusicPlayerController::m_instance = nullptr;

MusicPlayerController::MusicPlayerController(QObject *parent)
    : QObject(parent)
    , m_initialized(false)
{
    LOG_INFO;
}

MusicPlayerController::~MusicPlayerController(){

}

MusicPlayerController *MusicPlayerController::getInstance()
{
    if (m_instance == nullptr){
        m_instance = new MusicPlayerController();
    }
    return m_instance;
}

void MusicPlayerController::initialize(QQmlContext *context){
    LOG_INFO << m_initialized;
    if (!m_initialized){
        m_initialized = true;
        context->setContextProperty("MPLAYER_CTRL", this);
        context->setContextProperty("MPLAYER_MODEL", &m_model);
    }
}

void MusicPlayerController::pauseSong(){
    LOG_INFO;
    m_model.requestPause();
}

void MusicPlayerController::setNewSong(){
    LOG_INFO;
    m_model.initialize();
    if (m_mode == AppEnums::APP_MUSIC){
        playSong();
    }
}

void MusicPlayerController::playSong(){
    LOG_INFO;
    m_model.requestPlay();
}

void MusicPlayerController::continueSong(){
    LOG_INFO;
    m_model.requestContinue();
}

void MusicPlayerController::nextSong(){
    LOG_INFO;
    m_model.nextMusic();
}

void MusicPlayerController::prevSong(){
    LOG_INFO;
    m_model.previousMusic();
}

void MusicPlayerController::changePosition(qint64 pos){
    LOG_INFO;
    m_model.changePosition(pos);
}

void MusicPlayerController::setVolume(int volume)
{
    LOG_INFO << volume;
    m_model.setVolume(volume);
}

void MusicPlayerController::setMode(int mode){
    LOG_INFO << mode;
    m_mode = mode;
    if (mode == AppEnums::APP_MUSIC){
        m_model.requestPlay();
    }
    else if (mode == AppEnums::APP_VIDEO){
        m_model.requestPause();
    }
}
