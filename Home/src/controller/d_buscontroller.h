#ifndef D_BUSCONTROLLER_H
#define D_BUSCONTROLLER_H

#include <QObject>
#include <QQmlContext>
#include <d_busmodel.h>

class d_busController : public QObject
{
    Q_OBJECT
private:
    explicit d_busController(QObject *parent = nullptr);
public:
    static d_busController* getInstance();

    void initialize(QQmlContext *context);

public slots:
    Q_INVOKABLE void openMode(int mode);
    Q_INVOKABLE void settingChanged(int language, int volume);
private:
    d_busModel m_model;
    static d_busController* m_instance;
    bool m_initialized;
};

#endif // D_BUSCONTROLLER_H
