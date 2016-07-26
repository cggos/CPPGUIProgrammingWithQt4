#ifndef EXPENSEDIALOG_H
#define EXPENSEDIALOG_H

#include <QDialog>

#include "expense.h"

class QAction;
class QComboBox;
class QDateEdit;
class QDoubleSpinBox;
class QLabel;

class ExpenseDialog : public QDialog
{
    Q_OBJECT

public:
    ExpenseDialog(const Expense &expense, QWidget *parent = 0);

    Expense expense() const { return currentExpense; }

public slots:
    void accept();

private:
    void createActions();
    void createMenuOrToolBar();

    Expense currentExpense;

    QLabel *dateLabel;
    QLabel *descLabel;
    QLabel *amountLabel;
    QDateEdit *dateEdit;
    QComboBox *descComboBox;
    QDoubleSpinBox *amountSpinBox;
    QAction *okAction;
    QAction *cancelAction;
};

#endif
