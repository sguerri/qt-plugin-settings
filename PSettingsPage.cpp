#include "PSettingsPage.h"
#include "ui_PSettingsPage.h"

#include <QSettings>
#include <QLineEdit>

PSettingsPage::PSettingsPage(QMainWindow* parent) :
    QWidget(parent),
    ui(new Ui::PSettingsPage),
    parent(parent)
{
    ui->setupUi(this);

    connect(ui->btBack, &QPushButton::clicked, this, &PSettingsPage::hide);
    connect(ui->lstGroups, &QListWidget::currentItemChanged, this, &PSettingsPage::onGroupSelected);

    this->initUi();
    this->load();
}

PSettingsPage::~PSettingsPage()
{
    delete ui;
}

void PSettingsPage::show()
{
    plugin->setVisible(true);
    main->setVisible(false);
}

void PSettingsPage::hide()
{
    plugin->setVisible(false);
    main->setVisible(true);
}

void PSettingsPage::initUi()
{
    main = parent->centralWidget();

    QHBoxLayout* layout = new QHBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(this);
    layout->addWidget(parent->centralWidget());

    QWidget* global = new QWidget();
    global->setLayout(layout);

    plugin = this;
    plugin->setVisible(false);

    parent->setCentralWidget(global);
}

void PSettingsPage::load()
{
    QStringList groups = settings.childGroups();
    groups.sort();
    ui->lstGroups->clear();
    for (const QString& group: groups) {
        ui->lstGroups->addItem(group);
    }
}

void PSettingsPage::onGroupSelected(QListWidgetItem* item)
{
    const QString& groupKey = item->text();

    auto layout = static_cast<QVBoxLayout*>(ui->settings->layout());

    settings.beginGroup(groupKey);

    auto keys = settings.childKeys();
    for (const auto& key: keys) {
        if (key.endsWith("::description")) continue;
        if (key.endsWith("::visible")) continue;
        if (key.endsWith("::editable")) continue;

        bool visible = settings.value(key + "::visible", true).toBool();
        if (!visible) continue;

        const auto& value = settings.value(key);
        const auto& description = settings.value(key + "::description", "").toString();
        bool editable = settings.value(key + "::editable", true).toBool();
        if (value.type() == QVariant::String) {

            auto widget = this->createSettingString(groupKey, key, description, value.toString(), editable);
            layout->addWidget(widget);
        }
    }

    settings.endGroup();
}

QPair<QWidget*, QVBoxLayout*> PSettingsPage::createSettingHeader(const QString& group, const QString& key, const QString& description)
{
    QWidget* widget = new QWidget(ui->settingsArea);

    QVBoxLayout* layout = new QVBoxLayout(widget);
    layout->setMargin(0);
    layout->setSpacing(5);

    auto labelTitle = new QLabel();
    labelTitle->setObjectName("itemTitle");
    labelTitle->setTextFormat(Qt::MarkdownText);
    labelTitle->setText(group + ": **" + key + "**");
    layout->addWidget(labelTitle);

    if (description != "") {
        auto labelDescription = new QLabel();
        labelDescription->setObjectName("itemDescription");
        QFont fontDescription(labelDescription->font());
        fontDescription.setPointSize(10);
        labelDescription->setFont(fontDescription);
        labelDescription->setWordWrap(true);
        labelDescription->setTextFormat(Qt::MarkdownText);
        labelDescription->setText(description);
        layout->addWidget(labelDescription);
    }

    return QPair<QWidget*, QVBoxLayout*>(widget, layout);
}

QWidget* PSettingsPage::createSettingString(const QString& group, const QString& key, const QString& description, const QString& value, bool editable)
{
    auto [widget, layout] = this->createSettingHeader(group, key, description);

    auto edit = new QLineEdit();
    edit->setObjectName("itemEdit");
    edit->setReadOnly(!editable);
    edit->setText(value);
    connect(edit, &QLineEdit::textEdited, this, [=](const QString& text){
        settings.setValue(group + "/" + key, text);
        emit this->settingUpdated(group + "/" + key, text);
    });
    layout->addWidget(edit);

    return widget;
}













