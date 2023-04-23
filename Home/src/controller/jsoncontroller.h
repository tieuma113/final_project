#ifndef JSONCONTROLLER_H
#define JSONCONTROLLER_H

#include <QObject>

class JsonController : public QObject
{
    Q_OBJECT
public:
    explicit JsonController(QObject *parent = nullptr);

signals:

};

#endif // JSONCONTROLLER_H
