#ifndef PSETTINGSPAGE_H
#define PSETTINGSPAGE_H

#include <QWidget>
#include <QSettings>
#include <QMainWindow>
#include <QListWidgetItem>
#include <QVBoxLayout>

namespace Ui {
    class PSettingsPage;
}

class PSettingsPage: public QWidget
{
    Q_OBJECT

public:
    explicit PSettingsPage(QMainWindow* parent);
    ~PSettingsPage();

    void show();
    void hide();

private:
    Ui::PSettingsPage* ui;
    QSettings settings;

    QMainWindow* parent;
    //QWidget* plugin;
    //QWidget* main;

    //void hide();
    void initUi();
    void load();
    //void reload();

    void onGroupSelected(QListWidgetItem* item);

    QPair<QWidget*, QVBoxLayout*> createSettingHeader(const QString& group, const QString& key, const QString& description);
    QWidget* createSettingString(const QString& group, const QString& key, const QString& description, const QString& value, bool editable);

signals:
    void settingUpdated(const QString& key, const QVariant& value);

};

#endif // PSETTINGSPAGE_H
