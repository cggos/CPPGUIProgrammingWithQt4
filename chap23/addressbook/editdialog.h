#ifndef EDITDIALOG_H
#define EDITDILAOG_H

#include <QDialog>

#include "ui_editdialog.h"

class QTreeWidget;
class ABItem;

class EditDialog : public QDialog, private Ui::EditDialog
{
    Q_OBJECT

public:
    EditDialog(QTreeWidget *treeWidget, QWidget *parent = 0);
    EditDialog(ABItem *item, QWidget *parent = 0);

    void accept();

private:
    QTreeWidget *treeWidget;
    ABItem *currentItem;
};

#endif
