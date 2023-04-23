#include "settingcontroller.h"
#include "loghelper.h"
#include "appdefines.h"

SettingController* SettingController::m_instance = nullptr;

SettingController::SettingController(QObject *parent)
    : QObject(parent)
    , m_initialized(false)
{
    LOG_INFO;
}

SettingController::~SettingController(){

}

SettingController* SettingController::getInstance(){
    if (m_instance == nullptr){
        m_instance = new SettingController();
    }
    return m_instance;
}

void SettingController::initialize(QQmlContext *context){
    LOG_INFO << m_initialized;
    if (!m_initialized){
        m_initialized = true;
        m_model.setTranslation(AppEnums::LANGUAGE_ENGLISH);
        context->setContextProperty("SETTING_CTRL", this);
        context->setContextProperty("SETTING_MODEL", &m_model);
        setVisible(false);
    }
}

void SettingController::setSetting(int language, int volume){
    LOG_INFO << language << " " << volume;
    m_model.setTranslation(language);
    m_model.setVolume(volume);
    emit volumeChanged(volume);
}

void SettingController::setVisible(bool visible)
{
    LOG_INFO << visible;
    m_model.setVisible(visible);
}
