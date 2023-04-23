#ifndef APPDEFINES_H
#define APPDEFINES_H

#include <QObject>
#include <QMap>
#include <QUrl>
#include <QFileInfo>
#include <QStandardPaths>

#define MAIN_QML    "qrc:/qml/main.qml"
#define MUSIC_PATH  QStandardPaths::standardLocations(QStandardPaths::MusicLocation)[0]
#define VIDEO_PATH  QStandardPaths::standardLocations(QStandardPaths::MoviesLocation)[0]

#define MUSIC_ART_COVER_PATH "../../QtMock/temp/coverart.png"
#define MUSIC_UNKNOWN_COVER_ART_PATH "../../QtMock/temp/unknown_cover.png"
#define JSON_PATH "../../QtMock/temp/setting.json"

class AppEnums: public QObject
{
    Q_OBJECT
    Q_ENUMS(SCREEN_ID)
    Q_ENUMS(APP_MODE)

public:
    enum SCREEN_ID: int
    {
        SCREEN_ID_MUSIC_PLAYBACK,
        SCREEN_ID_MUSIC_LIST,

        SCREEN_ID_VIDEO_PLAYBACK,

        SCREEN_ID_MAX,
    };

    enum APP_MODE: int{
        APP_MUSIC,
        APP_VIDEO,
    };

    enum LANGUAGE_LIST: int
    {
        LANGUAGE_ENGLISH,
        LANGUAGE_VIETNAMESE,
    };
};

const QMap<int, QString> ScreenNameMap
{
    {AppEnums::SCREEN_ID_MUSIC_PLAYBACK,    "qrc:/qml/screens/MusicPlaybackScreen.qml"},
    {AppEnums::SCREEN_ID_MUSIC_LIST,        "qrc:/qml/screens/MusicListScreen.qml"},

    {AppEnums::SCREEN_ID_VIDEO_PLAYBACK,    "qrc:/qml/screens/VideoPlaybackScreen.qml"},
};

const QMap<int, QString> LanguageNameMap
{
    {AppEnums::LANGUAGE_ENGLISH, ":/localization/AppLanguage_en.qm"},
    {AppEnums::LANGUAGE_VIETNAMESE, ":/localization/AppLanguage_vi.qm"},
};
#endif // APPDEFINES_H
