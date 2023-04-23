#ifndef D_BUSMODEL_H
#define D_BUSMODEL_H

#include <QObject>
#include <QUrl>
#include <QFileInfo>
#include "appdefines.h"

class d_busModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title NOTIFY titleChanged)
    Q_PROPERTY(QString artist READ artist NOTIFY artistChanged)
    Q_PROPERTY(QUrl cover READ cover NOTIFY coverChanged)
    Q_PROPERTY(bool visible READ visible NOTIFY visibleChanged)
    Q_PROPERTY(QString videoName READ videoName NOTIFY videoNameChanged)
public:
    explicit d_busModel(QObject *parent = nullptr);

    QString title(){
        return m_title;
    }

    QString artist(){
        return m_artist;
    }

    QUrl cover(){
        QFileInfo temp;
        if (m_cover){
            temp = QFileInfo(MUSIC_ART_COVER_PATH);
        }else{
            temp = QFileInfo(MUSIC_UNKNOWN_COVER_ART_PATH);
        }
        return QUrl::fromLocalFile(temp.absoluteFilePath()).toString();

    }

    QString videoName(){
        return m_videoName;
    }

    bool visible(){
        return m_visible;
    }

    void setVisible(bool s_visible){
        m_visible = s_visible;
        emit visibleChanged();
    }

signals:
    void SettingChanged(int language, int volume);
    void openMode(int mode);
    void titleChanged();
    void artistChanged();
    void coverChanged();
    void videoNameChanged();
    void visibleChanged();

public slots:
    void onMusicTitleChanged(QString title);
    void onArtistChanged(QString artist);
    void onCoverChanged(bool have);
    void onVideoChanged(QString videoName);
    void returnHome();

private:
    int m_mode;
    QString m_title;
    QString m_artist;
    bool m_cover;
    QString m_videoName;
    bool m_visible;
};

#endif // D_BUSMODEL_H
