#include "musicplayercontroller.h"
#include "loghelper.h"

MusicPlayerController *MusicPlayerController::m_instance = nullptr;

MusicPlayerController::MusicPlayerController(QObject *parent)
    : QObject(parent)
    , m_initialized(false)
{
    LOG_INFO;
    m_model = new MusicPlaybackModel();
}

MusicPlayerController::~MusicPlayerController(){
    delete m_model;
    m_instance = nullptr;
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
        m_model->setMedia(MUSIC_PATH, QStringList() << "*mp3");
        context->setContextProperty("MPLAYER_MODEL", m_model);
    }
}

void MusicPlayerController::setMode(int mode){
    LOG_INFO << mode;
    m_mode = mode;
    if (mode == AppEnums::APP_MUSIC){
        m_model->player()->play();
    }
    else if (mode == AppEnums::APP_VIDEO){
        m_model->player()->pause();
    }
}
