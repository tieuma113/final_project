#ifndef MEDIALISTMODEL_H
#define MEDIALISTMODEL_H

#include <QAbstractListModel>
#include <QDir>
#include <QString>
#include <QFileInfo>
#include <QMediaPlaylist>
#include "appdefines.h"

class MediaListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int selectedIndex READ getIndex WRITE setIndex NOTIFY indexChanged)

private:
    QMediaPlaylist *m_data;

public:
    explicit MediaListModel(QObject *parent = nullptr);
    void setMediaList(QString mediaPath, QStringList filter);
    ~MediaListModel();
    enum ModeRoles{
        FileName = Qt::UserRole + 1,
    };
    int rowCount(const QModelIndex &p) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE int getIndex() const;
    Q_INVOKABLE void setIndex(const int &index);
    Q_INVOKABLE void next();
    Q_INVOKABLE void previous();

    void setData(QMediaPlaylist *newData);
    QMediaPlaylist* getData();

signals:
    void indexChanged();
};

#endif // MEDIALISTMODEL_H
