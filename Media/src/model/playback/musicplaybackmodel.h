#ifndef MUSICPLAYERMODEL_H
#define MUSICPLAYERMODEL_H

#include <QObject>
#include <QMediaPlayer>
#include <QMediaMetaData>
#include <QFileInfoList>
#include <QMediaPlaylist>
#include <QDir>

class MusicPlaybackModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString Title READ getTitle NOTIFY TitleChanged);
    Q_PROPERTY(QString Artist READ getArtist NOTIFY ArtistChanged);
    Q_PROPERTY(QString Album READ getAlbum NOTIFY AlbumChanged);
    Q_PROPERTY(QString Duration READ getDuration NOTIFY DurationChanged)
    Q_PROPERTY(qint64 msDuration READ getMsDuration NOTIFY DurationChanged)
    Q_PROPERTY(qint64 position READ getPosition NOTIFY PositionChanged)
    Q_PROPERTY(QString coverImagePath READ getCoverArtUrl NOTIFY coverChanged)
    Q_PROPERTY(bool isPlay READ isPlay NOTIFY musicState)
    Q_PROPERTY(QString valuePosition READ valuePosition NOTIFY valuePositionChanged)

public:
    MusicPlaybackModel(QObject *parent = nullptr);
    ~MusicPlaybackModel();

    void initialize();
    void requestPlay();
    void requestPause();
    void requestContinue();
    QString getTitle();
    QString getArtist();
    QString getAlbum();
    QString getDuration();
    qint64 getMsDuration();
    qint64 getPosition();
    void changePosition(qint64 pos);
    QString getCoverArtUrl();
    bool isPlay();
    void stop();
    QString valuePosition();
    void nextMusic();
    void previousMusic();

signals:
    void musicEnd();
    void coverChanged(bool have);
    void TitleChanged(QString title);
    void ArtistChanged(QString artist);
    void AlbumChanged();
    void DurationChanged();
    void PositionChanged();
    void musicState();
    void valuePositionChanged();

public slots:
    void handlePlayingTimeChanged(qint64 position);
    void handleMediaStatus(QMediaPlayer::MediaStatus status);
    void onMetaDataChanged(const QString &key, const QVariant &value);
    void handleStateChanged(QMediaPlayer::State state);
    void setVolume(int volume);
private:
    QMediaPlayer *m_player;
    QMediaPlayer::State m_state;
    QMediaPlaylist* m_mediaPlaylist;
//    QUrl m_currentUrl;
    QString m_title;
    QString m_artist;
    QString m_album;
    QString m_duration;
    qint64 m_msDuration;
    qint64 m_position;
    QString m_coverImageUrl;
    QString m_positionValue;
    bool m_isPlay;
};

#endif // MUSICPLAYERMODEL_H
