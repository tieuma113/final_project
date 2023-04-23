#include "jsonmodel.h"
#include "loghelper.h"

JsonModel* JsonModel::m_instance = nullptr;

JsonModel::JsonModel(QObject *parent)
    : QObject(parent)
    , m_initialized(false)
{
    LOG_INFO;
}

JsonModel::~JsonModel(){
    LOG_INFO;
}

JsonModel* JsonModel::getInstance(){
    if (m_instance == nullptr){
        m_instance = new JsonModel();
    }
    return m_instance;
}

void JsonModel::readSetting(){
    QFile file(JSON_PATH);
    if (!file.exists()){
        LOG_INFO << "file not exists";
        int language = 0;
        int volume = 5;
        writeSetting(language, volume);
        emit readData(language, volume);
        return;
    }
    if (file.open(QFile::ReadOnly)){
        LOG_INFO << "file exists";
        QByteArray data = file.readAll();
        QJsonDocument jsDoc = QJsonDocument::fromJson(data);
        QJsonObject jsObj = jsDoc.object();
        int language = jsObj["language"].toInt();
        int volume = jsObj["volume"].toInt();
        emit readData(language, volume);
    }
}

void JsonModel::writeSetting(int language, int volume){
    LOG_INFO;
    QJsonObject jsObj;
    jsObj["language"] = language;
    jsObj["volume"] = volume;
    QJsonDocument jsDoc(jsObj);
    QFile file(JSON_PATH);
    if (file.open(QFile::WriteOnly)){
        LOG_INFO << "open file";
        file.write(jsDoc.toJson());
        file.flush();
        file.close();
        emit writeData(language, volume);
    }
}

void JsonModel::inittialize(QQmlContext *context){
    LOG_INFO << m_initialized;
    if (!m_initialized){
        m_initialized = true;
        context->setContextProperty("JSON_MODEL", this);
    }
}
