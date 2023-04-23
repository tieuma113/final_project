#include "screenmodel.h"
#include "loghelper.h"

ScreenModel::ScreenModel(QObject *parent)
    : QObject(parent)
{

}

ScreenModel::~ScreenModel()
{

}

QString ScreenModel::currentScreen() const
{
    return m_currentScreen;
}

void ScreenModel::setCurrentScreen(const QString &currentScreen)
{
    LOG_INFO;
    if(m_currentScreen != currentScreen)
    {
        m_currentScreen = currentScreen;
        emit currentScreenChanged();
    }
}
