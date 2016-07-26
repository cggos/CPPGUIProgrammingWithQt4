#ifndef TEAMLEADERSDIALOG_H
#define TEAMLEADERSDIALOG_H

#include <QDialog>

class QDialogButtonBox;
class QListView;
class QStringListModel;

class TeamLeadersDialog : public QDialog
{
    Q_OBJECT

public:
    TeamLeadersDialog(const QStringList &leaders, QWidget *parent = 0);

    QStringList leaders() const;

private slots:
    void insert();
    void del();

private:
    QListView *listView;
    QDialogButtonBox *buttonBox;
    QStringListModel *model;
};

#endif
