#ifndef JSONMODEL_H
#define JSONMODEL_H

#include <QObject>
#include <QQmlContext>

class JsonModel : public QObject
{
    Q_OBJECT
public:
    ~JsonModel();
    void initiallize(QQmlContext* context);
    static JsonModel* getInstance();
public slots:
    Q_INVOKABLE void readSetting();
signals:
    void readData(int language, int volume);
private:
    static JsonModel *m_instance;
    bool m_initialized;
    explicit JsonModel(QObject *parent = nullptr);
};

#endif // JSONMODEL_H
