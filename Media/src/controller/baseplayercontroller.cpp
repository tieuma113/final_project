#include "baseplayercontroller.h"
#include "loghelper.h"

BasePlayerController::~BasePlayerController()
{

}

void BasePlayerController::initialize(QQmlContext *context)
{
    LOG_INFO << m_initialized;
    if(!m_initialized)
    {
        m_initialized = true;
    }
}
