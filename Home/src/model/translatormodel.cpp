#include "translatormodel.h"
#include <QGuiApplication>

TranslatorModel::TranslatorModel(QObject *parent)
    : QObject(parent)
{

}

TranslatorModel::~TranslatorModel()
{
}

void TranslatorModel::setTranslation(int language){
    m_translator.load(LanguageNameMap[language]);
    qApp->installTranslator(&m_translator);
    emit languageChanged();
}
