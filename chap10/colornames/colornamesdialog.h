#ifndef COLORNAMESDIALOG_H
#define COLORNAMESDIALOG_H

#include <QDialog>

class QComboBox;
class QLabel;
class QLineEdit;
class QListView;
class QSortFilterProxyModel;
class QStringListModel;

class ColorNamesDialog : public QDialog
{
    Q_OBJECT

public:
    ColorNamesDialog(QWidget *parent = 0);

private slots:
    void reapplyFilter();

private:
    QStringListModel *sourceModel;
    QSortFilterProxyModel *proxyModel;
    QListView *listView;
    QLabel *filterLabel;
    QLabel *syntaxLabel;
    QLineEdit *filterLineEdit;
    QComboBox *syntaxComboBox;
};

#endif
