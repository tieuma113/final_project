#include "d_buscontroller.h"
#include "loghelper.h"
#include <QDBusConnection>

d_busController* d_busController::m_instance = nullptr;

d_busController::d_busController(QObject *parent)
    :QObject(parent)
    , m_initialized(false)
{
    LOG_INFO;
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
        context->setContextProperty("DBUS_CTRL", this);
        context->setContextProperty("DBUS_MODEL", &m_model);
        QDBusConnection connection = QDBusConnection::sessionBus();
        connection.registerObject("/dbus", &m_model);
        connection.registerService("qtmock.service.dbus");
    }
}

void d_busController::openMode(int mode)
{
    LOG_INFO;
    m_model.setVisible(false);
    emit m_model.openMode(mode);
}

void d_busController::settingChanged(int language, int volume)
{
    LOG_INFO;
    emit m_model.SettingChanged(language, volume);
}
