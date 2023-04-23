#include "musiclistcontroller.h"
#include "loghelper.h"

MusicListController* MusicListController::m_instance = nullptr;

MusicListController::MusicListController(QObject *parent)
    : QObject(parent)
    , m_initialized(false)
{
    LOG_INFO;
}

MusicListController::~MusicListController()
{
    LOG_INFO;
}

MusicListController *MusicListController::getInstance()
{
    LOG_INFO;
    if(m_instance == nullptr)
    {
        m_instance = new MusicListController();
    }

    return m_instance;
}

void MusicListController::initialize(QQmlContext *context)
{
    LOG_INFO << m_initialized;
    if(!m_initialized)
    {
        m_initialized = true;
        context->setContextProperty("MLIST_CTRL", this);
        context->setContextProperty("MLIST_MODEL", &m_listModel);
        connect(&m_listModel, &MusicListModel::indexChanged, this, &MusicListController::modelIndexChanged);
        setModelIndex(0);
    }
}

void MusicListController::setModelIndex(int index){
    LOG_INFO << index;
    m_listModel.setIndex(index);
}

void MusicListController::setModelNextIndex(){
    LOG_INFO;
    m_listModel.setNextIndex();
}

void MusicListController::setModelPrevIndex(){
    LOG_INFO;
    m_listModel.setPrevIndex();
}

void MusicListController::setMode(int mode){
    LOG_INFO;

}
