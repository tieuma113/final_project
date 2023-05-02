#ifndef MUSICPLAYERMODEL_H
#define MUSICPLAYERMODEL_H

#include "mediaplayer.h"

class MusicPlaybackModel : public MediaPlayer
{
    Q_OBJECT
    Q_PROPERTY(QString Title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QString Artist READ artist WRITE setArtist NOTIFY artistChanged)
    Q_PROPERTY(QString Album READ album WRITE setAlbum NOTIFY albumChanged)
    Q_PROPERTY(QByteArray CoverImage READ coverImage WRITE setCoverImage NOTIFY coverImageChanged)

public:
    MusicPlaybackModel(QObject *parent = nullptr);
    ~MusicPlaybackModel();

    QString title() const;
    void setTitle(const QString &newTitle);
    QString artist() const;
    void setArtist(const QString &newArtist);
    QString album() const;
    void setAlbum(const QString &newAlbum);
    QByteArray coverImage() const;
    void setCoverImage(const QByteArray &newCoverImage);

signals:

    void titleChanged(QString sTitle);
    void artistChanged(QString sArtist);
    void albumChanged(QString sAlbum);
    void coverImageChanged(QByteArray sCoverImage);

public slots:
    void onMediaChanged();
private:
    QString m_title;
    QString m_artist;
    QString m_album;
    QByteArray m_coverImage;
};

#endif // MUSICPLAYERMODEL_H
