#ifndef SETTINGMODEL_H
#define SETTINGMODEL_H

#include <QObject>
#include <QObject>
#include <QVariant>
#include <QTranslator>

class SettingModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString emptyString READ emptyString NOTIFY languageChanged)
    Q_PROPERTY(int volume READ volume NOTIFY volumeChanged)
    Q_PROPERTY(bool visible READ visible NOTIFY visibleChanged)

public:
    explicit SettingModel(QObject *parent = nullptr);
    ~SettingModel();
    void setTranslation(int language);
    QString emptyString() const{
        return "";
    }
    int volume(){
        return m_volume;
    }
    void setVolume(int volume){
        m_volume = volume;
    }
    bool visible(){
        return m_visible;
    }
    void setVisible(bool s_visible){
        m_visible = s_visible;
        emit visibleChanged();
    }

private:
    QTranslator m_translator;
    int m_volume;
    bool m_visible;

signals:
    void volumeChanged();
    void languageChanged();
    void visibleChanged();
};

#endif // SETTINGMODEL_H
