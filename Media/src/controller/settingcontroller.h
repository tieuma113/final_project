#ifndef SETTINGCONTROLLER_H
#define SETTINGCONTROLLER_H

#include <QObject>
#include <QQmlContext>
#include "settingmodel.h"

class SettingController : public QObject
{
    Q_OBJECT
private:
    explicit SettingController(QObject *parent = nullptr);

public:
    ~SettingController();

    static SettingController* getInstance();

    void initialize(QQmlContext *context);
public slots:
    void setSetting(int language, int volume);
    void setVisible(bool visible);

private:
    static SettingController* m_instance;
    bool m_initialized;
    SettingModel m_model;

signals:
    void volumeChanged(int volume);
    void languageChanged(int language);
};

#endif // SETTINGCONTROLLER_H
