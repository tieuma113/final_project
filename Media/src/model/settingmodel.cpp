#include "settingmodel.h"
#include <QGuiApplication>
#include "appdefines.h"
#include "loghelper.h"

SettingModel::SettingModel(QObject *parent)
    : QObject(parent)
{

}

SettingModel::~SettingModel(){

}

void SettingModel::setTranslation(int language){
    LOG_INFO;
    m_translator.load(LanguageNameMap[language]);
    qApp->installTranslator(&m_translator);
    emit languageChanged();
}
