#include "d_buscontroller.h"
#include "loghelper.h"

d_busController* d_busController::m_instance = nullptr;

d_busController::d_busController(QObject *parent)
    : QObject(parent),
      m_initialized(false)
{
    LOG_INFO;
}

void d_busController::backHome()
{
    LOG_INFO;
    m_model->returnHome();
    emit returnHome();
}

d_busController::~d_busController(){

}

d_busController* d_busController::getInstance(){
    if (m_instance == nullptr){
        m_instance = new d_busController();
    }
    return m_instance;
}

void d_busController::initialize(QQmlContext *context){
    LOG_INFO << m_initialized;
    if (!m_initialized){
    m_initialized = true;
    m_model = new local::d_busModel("qtmock.service.dbus", "/dbus", QDBusConnection::sessionBus(), this);
    context->setContextProperty("DBUS_CTRL", this);
    context->setContextProperty("DBUS_MODEL", m_model);

    connect(m_model, &local::d_busModel::openMode, this, &d_busController::modeChanged);
    connect(m_model, &local::d_busModel::SettingChanged, this, &d_busController::settingChanged);
    }
}

void d_busController::musicTitle(QString title){
    LOG_INFO;
    m_model->onMusicTitleChanged(title);
}

void d_busController::musicArtist(QString artist){
    LOG_INFO;
    m_model->onArtistChanged(artist);
}

void d_busController::coverArt(bool have){
    LOG_INFO;
    m_model->onCoverChanged(have);
}

void d_busController::video(QString videoName){
    LOG_INFO;
    m_model->onVideoChanged(videoName);
}
