#ifndef DIRECTORYVIEWER_H
#define DIRECTORYVIEWER_H

#include <QDialog>

class QDialogButtonBox;
class QDirModel;
class QTreeView;

class DirectoryViewer : public QDialog
{
    Q_OBJECT

public:
    DirectoryViewer(QWidget *parent = 0);

private slots:
    void createDirectory();
    void remove();

private:
    QTreeView *treeView;
    QDirModel *model;
    QDialogButtonBox *buttonBox;
};

#endif
