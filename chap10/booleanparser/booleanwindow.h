#ifndef BOOLEANWINDOW_H
#define BOOLEANWINDOW_H

#include <QWidget>

class QLabel;
class QLineEdit;
class QTreeView;
class BooleanModel;

class BooleanWindow : public QWidget
{
    Q_OBJECT

public:
    BooleanWindow();

private slots:
    void booleanExpressionChanged(const QString &expr);

private:
    QLabel *label;
    QLineEdit *lineEdit;
    BooleanModel *booleanModel;
    QTreeView *treeView;
};

#endif
