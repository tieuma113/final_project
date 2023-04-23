#include "translatorcontroller.h"
#include "loghelper.h"
#include "appdefines.h"

TranslatorController* TranslatorController::m_instance = nullptr;

TranslatorController::TranslatorController(QObject *parent)
    : QObject(parent)
    , m_initialized(false)
    , m_volume(0)
{
    LOG_INFO;
}

TranslatorController::~TranslatorController()
{
    LOG_INFO;
}

TranslatorController *TranslatorController::getInstance()
{
    if(m_instance == nullptr)
    {
        m_instance = new TranslatorController();
    }

    return m_instance;
}

void TranslatorController::initialize(QQmlContext *context)
{
    LOG_INFO << m_initialized;
    if(!m_initialized)
    {
        m_initialized = true;
        m_model.setTranslation(AppEnums::LANGUAGE_ENGLISH);
        context->setContextProperty("TRANSLATOR_CTRL", this);
        context->setContextProperty("TRANSLATOR_MODEL", &m_model);
    }
}

void TranslatorController::setSetting(int language, int volume){
    m_model.setTranslation(language);
    m_language = language;
    m_volume = volume;
    emit settingChanged(language, volume);
}

int TranslatorController::getVolume(){
    return m_volume;
}

void TranslatorController::setVolume(int volume){
    if (volume >= 0 && volume <= 10){
        setSetting(m_language, volume);
    }
}

void TranslatorController::loadSetting(int language, int volume){
    m_model.setTranslation(language);
    m_language = language;
    m_volume = volume;
}

int TranslatorController::getLanguage(){
    return m_language;
}

void TranslatorController::setLanguage(int language){
    setSetting(language, m_volume);
}

