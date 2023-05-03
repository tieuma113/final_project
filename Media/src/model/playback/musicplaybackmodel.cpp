#include <QImage>
#include "musicplaybackmodel.h"
#include "loghelper.h"
#include "appdefines.h"

MusicPlaybackModel::MusicPlaybackModel(QObject *parent) : MediaPlayer(parent)
{
    m_album = "";
    m_artist = "";
    m_title = "";
    connect(m_player, SIGNAL(metaDataChanged(const QString &, const QVariant &)), this, SLOT(onMediaChanged(const QString &, const QVariant &)));
    connect(m_player, &QMediaPlayer::currentMediaChanged, this, [this](){
        LOG_INFO;
        m_album = "";
        m_artist = "";
        m_title = "";
        QFileInfo temp(MUSIC_UNKNOWN_COVER_ART_PATH);
        m_coverImage = QUrl::fromLocalFile(temp.absoluteFilePath()).toString();
        emit titleChanged(m_title);
        emit artistChanged(m_artist);
        emit titleChanged(m_title);
        emit coverImageChanged(m_coverImage);
    });
}

MusicPlaybackModel::~MusicPlaybackModel()
{

}

QString MusicPlaybackModel::title() const
{
    return m_title;
}

void MusicPlaybackModel::setTitle(const QString &newTitle)
{
    if (m_title == newTitle)
        return;
    m_title = newTitle;
    emit titleChanged(m_title);
}

QString MusicPlaybackModel::artist() const
{
    return m_artist;
}

void MusicPlaybackModel::setArtist(const QString &newArtist)
{
    if (m_artist == newArtist)
        return;
    m_artist = newArtist;
    emit artistChanged(m_artist);
}

QString MusicPlaybackModel::album() const
{
    return m_album;
}

void MusicPlaybackModel::setAlbum(const QString &newAlbum)
{
    if (m_album == newAlbum)
        return;
    m_album = newAlbum;
    emit albumChanged(m_album);
}

QUrl MusicPlaybackModel::coverImage() const
{
    return m_coverImage;
}

void MusicPlaybackModel::setCoverImage(const QUrl &newCoverImage)
{
    if (m_coverImage == newCoverImage)
        return;
    m_coverImage = newCoverImage;
    emit coverImageChanged(m_coverImage);
}

void MusicPlaybackModel::onMediaChanged(const QString &key, const QVariant &value)
{
    if (key == QMediaMetaData::Title){
        LOG_INFO << "song title: " << value.toString();
        m_title = value.toString();
        emit titleChanged(m_title);
    }
    else if (key == QMediaMetaData::ContributingArtist || key == QMediaMetaData::AlbumArtist){
        LOG_INFO << "song artist" << value.toString();
        m_artist = value.toString();
        emit artistChanged(m_artist);
    }
    else if(key == QMediaMetaData::AlbumTitle){
        LOG_INFO << "song album" << value.toString();
        m_album = value.toString();
        emit albumChanged(m_album);
    }
    else if (key == QMediaMetaData::CoverArtImage){
        LOG_INFO;
        QImage cover = value.value<QImage>();
        cover.save(MUSIC_ART_COVER_PATH);
        QFileInfo temp(MUSIC_ART_COVER_PATH);
        m_coverImage = QUrl::fromLocalFile(temp.absoluteFilePath()).toString();
        emit coverImageChanged(m_coverImage);
    }
}
