#ifndef APPDEFINES_H
#define APPDEFINES_H

#include <QObject>
#include <QMap>

#define MAIN_QML    "qrc:/qml/main.qml"
#define JSON_PATH   "../../QtMock/temp/setting.json"
#define MUSIC_ART_COVER_PATH "../../QtMock/temp/coverart.png"
#define MUSIC_UNKNOWN_COVER_ART_PATH "../../QtMock/temp/unknown_cover.png"

class AppEnums: public QObject
{
    Q_OBJECT
    Q_ENUMS(SCREEN_ID)
    Q_ENUMS(LANGUAGE_LIST)
    Q_ENUMS(APP_MODE)

public:
    enum SCREEN_ID: int
    {
        SCREEN_ID_HOME_MENU,
        SCREEN_ID_HOME_SETUP,

        SCREEN_ID_MAX,
    };

    enum LANGUAGE_LIST: int
    {
        LANGUAGE_ENGLISH,
        LANGUAGE_VIETNAMESE,
    };

    enum APP_MODE: int{
        APP_MUSIC,
        APP_VIDEO,
    };

};

const QMap<int, QString> ScreenNameMap
{
    {AppEnums::SCREEN_ID_HOME_MENU,         "qrc:/qml/screens/HomeMenuScreen.qml"},
    {AppEnums::SCREEN_ID_HOME_SETUP,        "qrc:/qml/screens/HomeSetupScreen.qml"},
};

const QMap<int, QString> LanguageNameMap
{
    {AppEnums::LANGUAGE_ENGLISH, ":/localization/AppLanguage_en.qm"},
    {AppEnums::LANGUAGE_VIETNAMESE, ":/localization/AppLanguage_vi.qm"},
};

#endif // APPDEFINES_H
