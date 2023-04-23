#include "videoplayercontroller.h"
#include "loghelper.h"

VideoPlayerController *VideoPlayerController::m_instance = nullptr;

VideoPlayerController::VideoPlayerController(QObject *parent)
    :QObject(parent)
    , m_initialized(false)
{
    LOG_INFO;
}

VideoPlayerController::~VideoPlayerController(){

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
        context->setContextProperty("MVIDEO_CTRL", this);
        context->setContextProperty("MVIDEO_MODEL", &m_model);
        fullScreen(false);
    }
}

void VideoPlayerController::setMode(int mode){
    LOG_INFO << mode;
    if (mode == AppEnums::APP_MUSIC){
        m_model.requestPause();
    }else if (mode == AppEnums::APP_VIDEO){
        m_model.requestPlay();
        fullScreen(false);
    }
}

void VideoPlayerController::pauseVideo(){
    LOG_INFO;
    m_model.requestPause();
}

void VideoPlayerController::playVideo(){
    LOG_INFO;
    m_model.requestPlay();
}

void VideoPlayerController::continueVideo(){
    LOG_INFO;
    m_model.requestContinue();
}

void VideoPlayerController::nextVideo(){
    LOG_INFO;
    m_model.next();
}

void VideoPlayerController::prevVideo(){
    LOG_INFO;
    m_model.prev();
}

void VideoPlayerController::fullScreen(bool s_fullScreen)
{
    LOG_INFO << s_fullScreen;
    m_model.setFullScreen(s_fullScreen);
}
void VideoPlayerController::changePosition(qint64 pos){
    LOG_INFO;
    m_model.changePosition(pos);
}
