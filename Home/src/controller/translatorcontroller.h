#ifndef TRANSLATORCONTROLLER_H
#define TRANSLATORCONTROLLER_H

#include <QObject>
#include <QQmlContext>
#include "translatormodel.h"

class TranslatorController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int volume READ getVolume WRITE setVolume NOTIFY settingChanged)
    Q_PROPERTY(int language READ getLanguage WRITE setLanguage NOTIFY settingChanged)

private:
    explicit TranslatorController(QObject *parent = nullptr);

public:
    ~TranslatorController();

    // singleton pattern
    static TranslatorController *getInstance();

    // initialize controller
    void initialize(QQmlContext *context);
    int getVolume();
    void setVolume(int volume);
    int getLanguage();
    void setLanguage(int language);

signals:
    void settingChanged(int language, int volume);


public slots:
    Q_INVOKABLE void setSetting(int language, int volume);
    void loadSetting(int language, int volume);

private:
    static TranslatorController *m_instance;
    bool m_initialized;

    int m_language;
    int m_volume;
    TranslatorModel m_model;
};

#endif // TRANSLATORCONTROLLER_H
