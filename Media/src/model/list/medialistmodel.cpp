#include "medialistmodel.h"
#include "loghelper.h"

void MediaListModel::setData(QMediaPlaylist *newData)
{
    m_data = newData;
}

QMediaPlaylist *MediaListModel::getData()
{
    return m_data;
}

MediaListModel::MediaListModel(QObject *parent) : QAbstractListModel(parent)
{
    m_data = new QMediaPlaylist();
}

void MediaListModel::setMediaList(QString mediaPath, QStringList filter)
{
    LOG_INFO << "init media model";
    QDir m_dir(mediaPath);
    if (!m_dir.exists()){
        LOG_INFO << "dir not exists";
    }else{
        m_dir.setFilter(QDir::Files);
        m_dir.setNameFilters(filter);
        m_dir.setSorting(QDir::Name);
        m_dir.sorting();
        QFileInfoList fileinfoList = m_dir.entryInfoList();
        if (fileinfoList.count() == 0){
            LOG_INFO << "no music file";
        }else{
            for (auto const &info : fileinfoList)
            {
                m_data->addMedia(QUrl::fromLocalFile(info.absoluteFilePath()));
            }
        }
    }
}

MediaListModel::~MediaListModel()
{
    delete m_data;
}

int MediaListModel::rowCount(const QModelIndex &p) const{
    Q_UNUSED(p);
    return m_data->mediaCount();
}

QHash<int, QByteArray> MediaListModel::roleNames() const{
    static QHash<int, QByteArray> roles;
    roles[FileName] = "name";
    return roles;
}

QVariant MediaListModel::data(const QModelIndex &index, int role) const{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::UserRole) {
        return QVariant::fromValue(m_data->media(index.row()));
    }

    return QVariant();
}

int MediaListModel::getIndex() const{
    return m_data->currentIndex();
}

void MediaListModel::setIndex(const int &index){
    if (index < 0 || index >=  m_data->mediaCount() - 1){
        LOG_INFO << "out of number in media list";
        return;
    }
        m_data->setCurrentIndex(index);
        emit indexChanged();
        LOG_INFO << index;
    return;
}
