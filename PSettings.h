#ifndef PSETTINGS_H
#define PSETTINGS_H

#include <QObject>
#include <QApplication>

class PSettings: public QObject
{
    Q_OBJECT

public:
    PSettings(): QObject() {}
    ~PSettings() {}

    static QTranslator* Translator();
    static QString Theme();
};

#endif // PSETTINGS_H
