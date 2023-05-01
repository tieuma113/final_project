#include <QImage>
#include "musicplaybackmodel.h"
#include "loghelper.h"
#include "appdefines.h"

MusicPlaybackModel::MusicPlaybackModel(QObject *parent) : MediaPlayer(parent)
{
    m_album = "";
    m_artist = "";
    m_title = "";
    m_coverImage = "";
    connect(m_player, &QMediaPlayer::mediaChanged, this, &MusicPlaybackModel::onMediaChanged);

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

QByteArray MusicPlaybackModel::coverImage() const
{
    return m_coverImage;
}

void MusicPlaybackModel::setCoverImage(const QByteArray &newCoverImage)
{
    if (m_coverImage == newCoverImage)
        return;
    m_coverImage = newCoverImage;
    emit coverImageChanged(m_coverImage);
}

void MusicPlaybackModel::onMediaChanged()
{
    m_title = m_player->metaData(QMediaMetaData::Title).toString();
    m_artist = m_player->metaData(QMediaMetaData::AlbumArtist).toString();
    m_album = m_player->metaData(QMediaMetaData::AlbumTitle).toString();
    m_coverImage = m_player->metaData(QMediaMetaData::CoverArtImage).value<QByteArray>();;
    emit titleChanged(m_title);
    emit artistChanged(m_artist);
    emit albumChanged(m_album);
    emit coverImageChanged(m_coverImage);
}
