#include "screencontroller.h"
#include "appdefines.h"
#include "loghelper.h"

ScreenController* ScreenController::m_instance = nullptr;

ScreenController::ScreenController(QObject *parent)
    : QObject(parent)
    , m_initialized(false)
    , m_engine(nullptr)
{
    LOG_INFO;
}

ScreenController::~ScreenController()
{
    LOG_INFO;
    m_engine = nullptr;
}

ScreenController *ScreenController::getInstance()
{
    if(m_instance == nullptr)
    {
        m_instance = new ScreenController();
    }

    return m_instance;
}

void ScreenController::initialize(QQmlContext *context)
{
    LOG_INFO << m_initialized;
    if(!m_initialized)
    {
        m_initialized = true;
        context->setContextProperty("SCREEN_CTRL", this);
        context->setContextProperty("SCREEN_MODEL", &m_model);
    }
}

void ScreenController::initializeScreen(QQmlApplicationEngine *engine)
{
    LOG_INFO;
    if(m_engine == nullptr)
    {
        m_engine = engine;

        // load main qml
        m_engine->load(QUrl(QStringLiteral(MAIN_QML)));

        // show home menu screen
        //pushScreen(AppEnums::SCREEN_ID_MUSIC_PLAYBACK);
//        pushScreen(AppEnums::SCREEN_ID_VIDEO_PLAYBACK);
    }
}

void ScreenController::pushScreen(int screenId, bool animation)
{
    LOG_INFO << "screenId: " << screenId << ", animation: " << animation;
    m_screenStack.push(screenId);
    updateCurrentScreen();
    emit m_model.screenPushed(animation);
}

void ScreenController::popScreen(bool animation)
{
    LOG_INFO << "animation: " << animation << ", stack: " << m_screenStack.count();
    if(m_screenStack.count() > 1)
    {
        m_screenStack.pop();
        updateCurrentScreen();
        emit m_model.screenPopped(animation);
    }
}

void ScreenController::popToRoot(bool animation)
{
    LOG_INFO << "animation: " << animation << ", stack: " << m_screenStack.count();
    if(m_screenStack.count() > 1)
    {
        while(m_screenStack.count() > 1)
        {
            m_screenStack.pop();
        }
        updateCurrentScreen();
        emit m_model.screenPopped(animation);
    }
}

void ScreenController::updateCurrentScreen()
{
    LOG_INFO;
    if(!m_screenStack.isEmpty())
    {
        QString screenName = ScreenNameMap.value(m_screenStack.top());
        m_model.setCurrentScreen(screenName);
    }
}

void ScreenController::setMode(int mode){
    LOG_INFO << mode;
    if (mode == AppEnums::APP_MUSIC){
        m_screenStack.clear();
        pushScreen(AppEnums::SCREEN_ID_MUSIC_PLAYBACK);
        updateCurrentScreen();
    }else if(mode == AppEnums::APP_VIDEO){
        m_screenStack.clear();
        pushScreen(AppEnums::SCREEN_ID_VIDEO_PLAYBACK);
        updateCurrentScreen();
    }
}
