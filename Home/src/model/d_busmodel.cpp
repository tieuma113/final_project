#include "d_busmodel.h"
#include "d_busmodel_adaptor.h"

d_busModel::d_busModel(QObject *parent) : QObject(parent), m_cover(false)
{
    new D_busModelAdaptor(this);
}

void d_busModel::onMusicTitleChanged(QString title){
    m_title = title;
    emit titleChanged();
}

void d_busModel::onArtistChanged(QString artist){
    m_artist = artist;
    emit artistChanged();
}

void d_busModel::onCoverChanged(bool have){
    m_cover = have;
    emit coverChanged();
}

void d_busModel::onVideoChanged(QString videoName){
    m_videoName = videoName;
    emit videoNameChanged();
}

void d_busModel::returnHome()
{
    setVisible(true);
}
