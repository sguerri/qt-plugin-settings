#ifndef PSETTINGSDATA_H
#define PSETTINGSDATA_H

#include <QObject>
#include <QSettings>

class PSettingsData: public QObject
{
    Q_OBJECT

public:
    PSettingsData(const QString& group = "application"): QObject() { this->m_group = group; }
    ~PSettingsData() {}

    void beginGroup(const QString& group) { this->m_group = group; }
    void endGroup() { this->m_group = "application"; }

    void addString(const QString& name, const QString& defaultValue, const QString& description = "", bool visible = true, bool editable = true);
    void addBool(const QString& name, bool defaultValue, const QString& description = "", bool visible = true, bool editable = true);
    void setValue(const QString& name, const QVariant& value);
    QVariant value(const QString& name, const QVariant& defaultValue) const;
    QString valueString(const QString& name) const;
    bool valueBool(const QString& name) const;
    void remove(const QString& name);

private:
    QSettings m_settings;
    QString m_group;

    void addValue(const QString& name, const QVariant& defaultValue, const QString& description, bool visible, bool editable);
};

#endif // PSETTINGSDATA_H
