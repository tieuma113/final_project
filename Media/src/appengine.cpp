#include "appengine.h"
#include "screencontroller.h"
#include "musicplayercontroller.h"
#include "musiclistcontroller.h"
#include "videoplayercontroller.h"
#include "settingcontroller.h"
#include "jsonmodel.h"
#include "appdefines.h"
#include "loghelper.h"
#include "d_buscontroller.h"

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
    MusicPlayerController::getInstance();
    MusicListController::getInstance();
    VideoPlayerController::getInstance();
    SettingController::getInstance();
    JsonModel::getInstance();
    d_busController::getInstance();
    LOG_INFO << "=> End";
}

void AppEngine::initControllers()
{
    LOG_INFO << "=> Start";
    ScreenController::getInstance()->initialize(m_engine.rootContext());
    MusicPlayerController::getInstance()->initialize(m_engine.rootContext());
    MusicListController::getInstance()->initialize(m_engine.rootContext());
    VideoPlayerController::getInstance()->initialize(m_engine.rootContext());
    SettingController::getInstance()->initialize(m_engine.rootContext());
    JsonModel::getInstance()->initiallize(m_engine.rootContext());
    d_busController::getInstance()->initialize(m_engine.rootContext());

    connect(MusicPlayerController::getInstance(),
            &MusicPlayerController::modelMusicEnd,
            MusicListController::getInstance(),
            &MusicListController::setModelNextIndex);

    connect(MusicPlayerController::getInstance(),
            &MusicPlayerController::setNextSong,
            MusicListController::getInstance(),
            &MusicListController::setModelNextIndex);

    connect(MusicPlayerController::getInstance(),
            &MusicPlayerController::setPrevSong,
            MusicListController::getInstance(),
            &MusicListController::setModelPrevIndex);

    connect(MusicListController::getInstance(),
            &MusicListController::modelIndexChanged,
            MusicPlayerController::getInstance(),
            &MusicPlayerController::setNewSong);

    connect(JsonModel::getInstance(),
            &JsonModel::readData,
            SettingController::getInstance(),
            &SettingController::setSetting);

    connect(SettingController::getInstance(),
            &SettingController::volumeChanged,
            MusicPlayerController::getInstance(),
            &MusicPlayerController::setVolume);

    connect(&MusicPlayerController::getInstance()->m_model,
            &MusicPlaybackModel::TitleChanged,
            d_busController::getInstance(),
            &d_busController::musicTitle);

    connect(&VideoPlayerController::getInstance()->m_model,
            &VideoPlaybackModel::fileNameChanged,
            d_busController::getInstance(),
            &d_busController::video);

    connect(&MusicPlayerController::getInstance()->m_model,
            &MusicPlaybackModel::ArtistChanged,
            d_busController::getInstance(),
            &d_busController::musicArtist);

    connect(&MusicPlayerController::getInstance()->m_model,
            &MusicPlaybackModel::coverChanged,
            d_busController::getInstance(),
            &d_busController::coverArt);

    connect(d_busController::getInstance(),
            &d_busController::modeChanged,
            AppEngine::getInstance(),
            &AppEngine::settingMode);

    connect(d_busController::getInstance(),
            &d_busController::settingChanged,
            SettingController::getInstance(),
            &SettingController::setSetting);

    connect(d_busController::getInstance(),
            &d_busController::returnHome,
            SettingController::getInstance(),
            &SettingController::setVisible);

    JsonModel::getInstance()->readSetting();
    MusicListController::getInstance()->setModelIndex(0);


    LOG_INFO << "=> End";
}

void AppEngine::initScreens()
{
    LOG_INFO << "=> Start";
    ScreenController::getInstance()->initializeScreen(&m_engine);
    LOG_INFO << "=> End";
}

void AppEngine::settingMode(int mode){
    m_mode = mode;
    ScreenController::getInstance()->setMode(mode);
    MusicPlayerController::getInstance()->setMode(mode);
    MusicListController::getInstance()->setMode(mode);
    VideoPlayerController::getInstance()->setMode(mode);

    SettingController::getInstance()->setVisible(true);
}
