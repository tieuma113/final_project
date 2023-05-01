#ifndef MUSICLISTCONTROLLER_H
#define MUSICLISTCONTROLLER_H

#include <QObject>
#include <QQmlContext>
#include "medialistmodel.h"
#include "appdefines.h"

class MusicListController : public QObject
{
    Q_OBJECT

//private:
//    explicit MusicListController(QObject *parent = nullptr);

//public:
//    ~MusicListController();

//    // singleton pattern
//    static MusicListController *getInstance();

//    // initialize controller
//    void initialize(QQmlContext *context);
//    void setMode(int mode);

//public slots:
//    Q_INVOKABLE void setModelIndex(int index);
//    void setModelNextIndex();
//    void setModelPrevIndex();

//signals:
//    void modelIndexChanged(QUrl musicPath);

//private:
//    static MusicListController *m_instance;
//    bool m_initialized;

//    MediaListModel m_listModel;
};

#endif // MUSICLISTCONTROLLER_H
