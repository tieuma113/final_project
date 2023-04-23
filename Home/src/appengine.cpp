#include "appengine.h"
#include "screencontroller.h"
#include "appdefines.h"
#include "loghelper.h"
#include "translatorcontroller.h"
#include "jsonmodel.h"
#include "d_buscontroller.h"
#include <QtQml>

AppEngine* AppEngine::m_instance = nullptr;

AppEngine::AppEngine(QObject *parent)
    : QObject(parent)
    , m_initialized(false)
    , m_app(nullptr)
{
    LOG_INFO;
}

AppEngine::~AppEngine()
{
    LOG_INFO;
    m_app = nullptr;
}

AppEngine *AppEngine::getInstance()
{
    if(m_instance == nullptr)
    {
        m_instance = new AppEngine();
    }

    return m_instance;
}

void AppEngine::initialize(QGuiApplication *app)
{
    LOG_INFO << m_initialized;
    if(!m_initialized)
    {

        m_initialized = true;
        m_app = app;

        // init app
        registerQmlObjects();
        createControllers();
        initControllers();
        initScreens();
    }

}

void AppEngine::registerQmlObjects()
{
    LOG_INFO << "=> Start";
    qmlRegisterType<AppEnums>("AppEnums", 1, 0, "AppEnums");
    LOG_INFO << "=> End";
}

void AppEngine::createControllers()
{
    LOG_INFO << "=> Start";
    ScreenController::getInstance();
    TranslatorController::getInstance();
    JsonModel::getInstance();
    d_busController::getInstance();
    LOG_INFO << "=> End";
}

void AppEngine::initControllers()
{
    LOG_INFO << "=> Start";
    ScreenController::getInstance()->initialize(m_engine.rootContext());
    TranslatorController::getInstance()->initialize(m_engine.rootContext());
    JsonModel::getInstance()->inittialize(m_engine.rootContext());
    d_busController::getInstance()->initialize(m_engine.rootContext());
    connect(JsonModel::getInstance(),
            &JsonModel::readData,
            TranslatorController::getInstance(),
            &TranslatorController::loadSetting);

    connect(TranslatorController::getInstance(),
            &TranslatorController::settingChanged,
            JsonModel::getInstance(),
            &JsonModel::writeSetting);

    connect(TranslatorController::getInstance(),
            &TranslatorController::settingChanged,
            d_busController::getInstance(),
            &d_busController::settingChanged);

    JsonModel::getInstance()->readSetting();

    LOG_INFO << "=> End";
}

void AppEngine::initScreens()
{
    LOG_INFO << "=> Start";
    ScreenController::getInstance()->initializeScreen(&m_engine);
    LOG_INFO << "=> End";
}
