#ifndef SCREENCONTROLLER_H
#define SCREENCONTROLLER_H

#include <QStack>
#include <QObject>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include "screenmodel.h"

class ScreenController : public QObject
{
    Q_OBJECT

private:
    explicit ScreenController(QObject *parent = nullptr);

public:
    ~ScreenController();

    // singleton pattern
    static ScreenController *getInstance();

    // initialize controller
    void initialize(QQmlContext *context);
    void initializeScreen(QQmlApplicationEngine *engine);

    // screen transition
    Q_INVOKABLE void pushScreen(int screenId, bool animation = true);
    Q_INVOKABLE void popScreen(bool animation = true);
    Q_INVOKABLE void popToRoot(bool animation = true);

private:
    void updateCurrentScreen();

private:
    static ScreenController *m_instance;
    bool m_initialized;

    ScreenModel m_model;
    QStack<int> m_screenStack;
    QQmlApplicationEngine *m_engine;
};

#endif // SCREENCONTROLLER_H
