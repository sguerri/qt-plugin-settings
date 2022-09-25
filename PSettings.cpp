#include "PSettings.h"

#include <QFile>
#include <QTextStream>
#include <QTranslator>

QTranslator* PSettings::Translator()
{
    Q_INIT_RESOURCE(pluginSettings);

    QTranslator* appTranslator = new QTranslator();
    if (appTranslator->load(QLocale(), QLatin1String("pluginSettings"), QLatin1String("_"), QLatin1String(":/i18n"))) {
        return appTranslator;
    } else {
        // TODO Error message
    }
    return nullptr;
}

QString PSettings::Theme()
{
    Q_INIT_RESOURCE(pluginSettings);

    QFile fTheme(":/theme/pluginSettings.qss");
    fTheme.open(QFile::ReadOnly);
    QTextStream inTheme(&fTheme);
    QString theme = inTheme.readAll();
    fTheme.close();

    return theme;
}
