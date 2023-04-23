#ifndef APPENGINE_H
#define APPENGINE_H

#include <QObject>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "appdefines.h"

class AppEngine : public QObject
{
    Q_OBJECT

private:
    explicit AppEngine(QObject *parent = nullptr);

public:
    ~AppEngine();

    // singleton pattern
    static AppEngine *getInstance();

    // initialize app
    void initialize(QGuiApplication *app);
public slots:
    void settingMode(int mode);

private:
    void registerQmlObjects();
    void createControllers();
    void initControllers();
    void initScreens();

private:
    static AppEngine* m_instance;
    bool m_initialized;

    QGuiApplication* m_app;
    QQmlApplicationEngine m_engine;
    int m_mode;
};

#endif // APPENGINE_H
