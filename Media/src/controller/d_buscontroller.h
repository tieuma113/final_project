#ifndef D_BUSCONTROLLER_H
#define D_BUSCONTROLLER_H

#include <QObject>
#include <QQmlContext>
#include "d_busmodel_interface.h"

class d_busController : public QObject
{
    Q_OBJECT
public:
    ~d_busController();
    static d_busController* getInstance();
    void initialize(QQmlContext *context);

signals:
    void settingChanged(int language, int volume);
    void modeChanged(int mode);
    void returnHome(bool visible = false);

private:
    explicit d_busController(QObject *parent = nullptr);
    local::d_busModel *m_model;
    bool m_initialized;
    static d_busController* m_instance;

public slots:
    void musicTitle(QString title);
    void musicArtist(QString artist);
    void coverArt(bool have);
    void video(QString videoName);
    Q_INVOKABLE void backHome();
};

#endif // D_BUSCONTROLLER_H
