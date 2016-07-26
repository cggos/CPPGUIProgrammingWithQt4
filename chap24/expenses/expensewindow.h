#ifndef EXPENSEWINDOW_H
#define EXPENSEWINDOW_H

#include <QList>
#include <QMainWindow>

#include "expense.h"

class QAction;
class QLabel;
class QListWidget;

class ExpenseWindow : public QMainWindow
{
    Q_OBJECT

public:
    ExpenseWindow(QWidget *parent = 0, Qt::WFlags flags = 0);

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void add();
    void edit();
    void del();
    void send();
    void clear();

private:
    void createActions();
    void createMenuOrToolBar();
    void loadData();
    void showData();

    QWidget *centralWidget;
    QListWidget *listWidget;
    QLabel *totalLabel;
    QLabel *totalAmountLabel;
    QAction *addAction;
    QAction *editAction;
    QAction *deleteAction;
    QAction *sendAction;
    QAction *clearAction;

    QList<Expense> expenses;
};

#endif
