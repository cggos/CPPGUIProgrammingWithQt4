#include <QtGui>
#include <QSoftMenuBar>

#include "expensedialog.h"

ExpenseDialog::ExpenseDialog(const Expense &expense, QWidget *parent)
    : QDialog(parent)
{
    currentExpense = expense;

    dateLabel = new QLabel(tr("Date:"));

    dateEdit = new QDateEdit;
    dateEdit->setMinimumDate(QDate::currentDate().addDays(-7));
    dateEdit->setMaximumDate(QDate::currentDate().addDays(2));
    dateEdit->setDisplayFormat(tr("yyyy-MM-dd"));

    descLabel = new QLabel(tr("Description:"));

    QStringList descriptions;
    descriptions << tr("Boat Ticket") << tr("Bus Ticket")
                 << tr("Car Hire") << tr("Flight Ticket") << tr("Fuel")
                 << tr("Hotel") << tr("Meal") << tr("Road Toll");

    descComboBox = new QComboBox;
    descComboBox->addItems(descriptions);
    descComboBox->setEditable(true);

    amountLabel = new QLabel(tr("Amount:"));

    amountSpinBox = new QDoubleSpinBox;
    amountSpinBox->setRange(0.00, 100000.00);
    amountSpinBox->setPrefix(tr("$"));

    if (!currentExpense.isNull()) {
        dateEdit->setDate(currentExpense.date());
        int i = descComboBox->findText(currentExpense.description());
        if (i >= 0) {
            descComboBox->setCurrentIndex(i);
        } else {
            descComboBox->insertItem(0, currentExpense.description());
            descComboBox->setCurrentIndex(0);
        }
        amountSpinBox->setValue(currentExpense.amount());
    } else {
        dateEdit->setDate(QDate::currentDate());
        descComboBox->setCurrentIndex(
                descComboBox->findText(tr("Meal")));
        amountSpinBox->setValue(0.00);
    }

    createActions();
    createMenuOrToolBar();

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(3);
    mainLayout->addWidget(dateLabel, 0, 0);
    mainLayout->addWidget(dateEdit, 0, 1);
    mainLayout->addWidget(descLabel, 1, 0);
    mainLayout->addWidget(descComboBox, 1, 1);
    mainLayout->addWidget(amountLabel, 2, 0);
    mainLayout->addWidget(amountSpinBox, 2, 1);
    setLayout(mainLayout);

    if (currentExpense.date().isNull()) {
        setWindowTitle(tr("Add Expense"));
    } else {
        setWindowTitle(tr("Edit Expense"));
    }
}

void ExpenseDialog::createActions()
{
    okAction = new QAction(tr("OK"), this);
    okAction->setIcon(QIcon(":icon/ok"));
    connect(okAction, SIGNAL(triggered()), this, SLOT(accept()));

    cancelAction = new QAction(tr("Cancel"), this);
    cancelAction->setIcon(QIcon(":icon/cancel"));
    connect(cancelAction, SIGNAL(triggered()), this, SLOT(reject()));
}

void ExpenseDialog::createMenuOrToolBar()
{
#ifdef QTOPIA_PHONE
    QMenu *menuOrToolBar = QSoftMenuBar::menuFor(this);
#else
    QToolBar *menuOrToolBar = new QToolBar;
    menuOrToolBar->setMovable(false);
    addToolBar(menuOrToolBar);
#endif

    menuOrToolBar->addAction(okAction);
    menuOrToolBar->addAction(cancelAction);
}

void ExpenseDialog::accept()
{
    currentExpense.setDate(dateEdit->date());
    currentExpense.setDescription(descComboBox->currentText());
    currentExpense.setAmount(amountSpinBox->value());
    QDialog::accept();
}
