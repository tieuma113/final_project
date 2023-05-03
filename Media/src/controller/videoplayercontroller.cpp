#include "videoplayercontroller.h"
#include "loghelper.h"

VideoPlayerController *VideoPlayerController::m_instance = nullptr;

VideoPlayerController::VideoPlayerController(QObject *parent)
    :QObject(parent)
    , m_initialized(false)
{
    LOG_INFO;
    m_model = new VideoPlaybackModel();
}

VideoPlayerController::~VideoPlayerController(){
    delete m_model;
    m_instance = nullptr;
}

VideoPlayerController *VideoPlayerController::getInstance()
{
    LOG_INFO;
    if (m_instance ==nullptr){
        m_instance = new VideoPlayerController();
    }
    return m_instance;
}

void VideoPlayerController::initialize(QQmlContext *context){
    LOG_INFO << m_initialized;
    if (!m_initialized){
        m_initialized = true;
        m_model->setMedia(VIDEO_PATH, QStringList() << "*mp4");
        context->setContextProperty("MVIDEO_MODEL", m_model);
    }
}

void VideoPlayerController::setMode(int mode){
    LOG_INFO << mode;
    if (mode == AppEnums::APP_MUSIC){
        m_model->player()->stop();
    }else if (mode == AppEnums::APP_VIDEO){
        m_model->player()->play();
    }
}
