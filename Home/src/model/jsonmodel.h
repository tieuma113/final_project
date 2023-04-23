#ifndef JSONMODEL_H
#define JSONMODEL_H

#include <QObject>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QQmlContext>
#include "appdefines.h"

class JsonModel : public QObject
{
    Q_OBJECT
public:
    ~JsonModel();
    static JsonModel *getInstance();
    void inittialize(QQmlContext *context);
public slots:
    Q_INVOKABLE void readSetting();
    Q_INVOKABLE void writeSetting(int language, int volume);
signals:
    void readData(int language, int volume);
    void writeData(int language, int volume);
private:
    static JsonModel *m_instance;
    bool m_initialized;
    explicit JsonModel(QObject *parent = nullptr);

};

#endif // JSONMODEL_H
