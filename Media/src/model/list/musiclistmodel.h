#ifndef MUSICLISTMODEL_H
#define MUSICLISTMODEL_H

#include <QAbstractListModel>
#include <QDir>
#include <QFileInfo>
#include <QUrl>
#include "appdefines.h"

class MusicListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int selectedIndex READ getIndex WRITE setIndex NOTIFY indexChanged)

private:
    QFileInfoList m_data;
    QDir m_dir;
    int m_index;

public:
    explicit MusicListModel(QObject *parent = nullptr);
    enum ModeRoles{
        FileName = Qt::UserRole + 1,
    };
    int rowCount(const QModelIndex &p) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE int getIndex() const;
    Q_INVOKABLE void setIndex(const int &index);

    void setNextIndex();
    void setPrevIndex();

signals:
    void indexChanged(QUrl musicPath);
};

#endif // MUSICLISTMODEL_H
