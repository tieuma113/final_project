#ifndef TRANSLATORMODEL_H
#define TRANSLATORMODEL_H

#include <QObject>
#include <QVariant>
#include <QTranslator>
#include "appdefines.h"


class TranslatorModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString emptyString READ emptyString NOTIFY languageChanged)

public:
        explicit TranslatorModel(QObject *parent = nullptr);
    ~TranslatorModel();

    void setTranslation(int language);

    QString emptyString() const {
        return "";
    }

private:
    QTranslator m_translator;

signals:
    void languageChanged();
};

#endif // TRANSLATORMODEL_H
