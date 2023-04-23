#ifndef LOGHELPER_H
#define LOGHELPER_H

#include <QDebug>
#include <unistd.h>
#include <sys/syscall.h>

#define LOG_INFO qDebug().noquote().nospace() << "[Thread #" << syscall(SYS_gettid) << "] " << Q_FUNC_INFO << " "

#endif // LOGHELPER_H
