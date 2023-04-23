#include "musiclistmodel.h"
#include "loghelper.h"

MusicListModel::MusicListModel(QObject *parent) : QAbstractListModel(parent)
{
    m_dir = QDir(MUSIC_PATH);
    if (!m_dir.exists()){
        LOG_INFO << "dir not exists";
    }else{
        m_dir.setFilter(QDir::Files);
        m_dir.setNameFilters(QStringList()<<("*.mp3"));
        m_dir.setSorting(QDir::Name);
        m_dir.sorting();
        m_data = m_dir.entryInfoList();
        if (m_data.count() == 0){
            LOG_INFO << "no music file";
        }else{
            setIndex(0);
        }
    }
}

int MusicListModel::rowCount(const QModelIndex &p) const{
    Q_UNUSED(p);
    return m_data.size();
}

QHash<int, QByteArray> MusicListModel::roleNames() const{
    static QHash<int, QByteArray> roles;
    roles[FileName] = "name";
    return roles;
}

QVariant MusicListModel::data(const QModelIndex &index, int role) const{
    Q_UNUSED(role);
    QString value;
    switch (role) {
    case FileName:
        value = m_data.at(index.row()).fileName();
        break;
    default:
        break;
    }
    return value;
}

int MusicListModel::getIndex() const{
    return m_index;
}

void MusicListModel::setIndex(const int &index){
    if (index < 0 || index >=  m_data.count() - 1){
        return;
    }
        m_index = index;
        emit indexChanged(QUrl::fromLocalFile(m_data.at(index).absoluteFilePath()));
        LOG_INFO << m_index;
    return;
}

void MusicListModel::setNextIndex(){
    if (m_index == m_data.size() - 1){
        LOG_INFO << "end of folder";
        return;
    }
    setIndex(m_index + 1);
}

void MusicListModel::setPrevIndex(){
    if (m_index == 0){
        LOG_INFO << "first element";
        return;
    }
    setIndex(m_index - 1);
}
