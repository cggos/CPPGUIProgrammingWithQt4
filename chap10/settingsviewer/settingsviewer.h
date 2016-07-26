#ifndef SETTINGSVIEWER_H
#define SETTINGSVIEWER_H

#include <QDialog>

class QDialogButtonBox;
class QSettings;
class QTreeWidget;
class QTreeWidgetItem;

class SettingsViewer : public QDialog
{
    Q_OBJECT

public:
    SettingsViewer(QWidget *parent = 0);

private slots:
    void open();

private:
    void readSettings();
    void addChildSettings(QSettings &settings, QTreeWidgetItem *item,
                          const QString &group);

    QTreeWidget *treeWidget;
    QDialogButtonBox *buttonBox;

    QString organization;
    QString application;
};

#endif
