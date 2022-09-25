#include "PSettingsData.h"

void PSettingsData::addString(const QString& name, const QString& defaultValue, const QString& description, bool visible, bool editable)
{
    const QString& prefix = this->m_group == "" ? "" : this->m_group + "/";
    this->m_settings.setValue(prefix + name + "::description", description);
    this->m_settings.setValue(prefix + name + "::visible", visible);
    this->m_settings.setValue(prefix + name + "::editable", editable);

    if (this->m_settings.contains(prefix + name)) return;
    this->m_settings.setValue(prefix + name, defaultValue);
}

void PSettingsData::setValue(const QString& name, const QVariant& value)
{
    const QString& prefix = this->m_group == "" ? "" : this->m_group + "/";
    this->m_settings.setValue(prefix + name, value);
}

QVariant PSettingsData::value(const QString& name, const QVariant& defaultValue) const
{
    const QString& prefix = this->m_group == "" ? "" : this->m_group + "/";
    return this->m_settings.value(prefix + name, defaultValue);
}

QString PSettingsData::valueString(const QString& name) const
{
    return this->value(name, "").toString();
}

void PSettingsData::remove(const QString& name)
{
    const QString& prefix = this->m_group == "" ? "" : this->m_group + "/";
    this->m_settings.remove(prefix + name);
    this->m_settings.remove(prefix + name + "::description");
    this->m_settings.remove(prefix + name + "::visible");
    this->m_settings.remove(prefix + name + "::editable");
}
