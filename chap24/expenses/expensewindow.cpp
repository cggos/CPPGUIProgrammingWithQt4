#include <QtGui>
#include <QtopiaServiceRequest>
#include <QtopiaApplication>
#include <QContactModel>
#include <QContactSelector>
#include <QSoftMenuBar>

#include "expensedialog.h"
#include "expensewindow.h"

ExpenseWindow::ExpenseWindow(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags)
{
    centralWidget = new QWidget;
    setCentralWidget(centralWidget);

    listWidget = new QListWidget;

    totalLabel = new QLabel(tr("Total"));

    totalAmountLabel = new QLabel;

    createActions();
    createMenuOrToolBar();

    connect(listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem *)),
            this, SLOT(edit()));

    QHBoxLayout *labelLayout = new QHBoxLayout;
    labelLayout->addStretch();
    labelLayout->addWidget(totalLabel);
    labelLayout->addWidget(totalAmountLabel);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->addWidget(listWidget);
    mainLayout->addLayout(labelLayout);
    centralWidget->setLayout(mainLayout);

    setWindowTitle(tr("Expenses"));
    loadData();
}

void ExpenseWindow::closeEvent(QCloseEvent *event)
{
    QByteArray data;

    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_2);

    foreach (Expense expense, expenses) {
        out << expense.date() << expense.description()
            << expense.amount();
    }

    QSettings settings("BookSoft Ltd", "Expenses");
    settings.setValue("data", data);

    event->accept();
}

void ExpenseWindow::add()
{
    ExpenseDialog dialog(Expense(), this);
    if (QtopiaApplication::execDialog(&dialog)) {
        expenses.append(dialog.expense());
        showData();
    }
}

void ExpenseWindow::edit()
{
    int row = listWidget->currentRow();
    if (row == -1)
        return;

    ExpenseDialog dialog(expenses[row], this);
    if (QtopiaApplication::execDialog(&dialog)) {
        expenses[row] = dialog.expense();
        showData();
    }
}

void ExpenseWindow::del()
{
    int row = listWidget->currentRow();
    if (row == -1)
        return;

    Expense expense = expenses[row];

    int r = QMessageBox::warning(this, tr("Expenses"),
                    tr("Delete %1 $%2\n%3?")
                    .arg(expense.date().toString(Qt::ISODate))
                    .arg(expense.amount(), 0, 'f', 2)
                    .arg(expense.description()),
                    QMessageBox::Yes | QMessageBox::No);
    if (r == QMessageBox::Yes) {
        expenses.removeAt(row);
        showData();
    }
}

void ExpenseWindow::send()
{
    QContactSelector dialog(false, this);
    dialog.setModel(new QContactModel);
    QtopiaApplication::execDialog(&dialog);
    if (!dialog.contactSelected())
        return;

    QTemporaryFile file;
    file.setAutoRemove(false);
    if (!file.open()) {
        QMessageBox::warning(this, tr("Expenses"),
                             tr("Failed to send expenses: %1.")
                             .arg(file.errorString()));
        return;
    }

    QString fileName = file.fileName();
    qreal total = 0.00;

    QTextStream out(&file);
    out.setCodec("UTF-8");

    out << tr("Expenses\n");
    foreach (Expense expense, expenses) {
        out << tr("%1 $%2 %3\n")
               .arg(expense.date().toString(Qt::ISODate))
               .arg(expense.amount(), 0, 'f', 2)
               .arg(expense.description());
        total += expense.amount();
    }
    out << tr("Total $%1\n").arg(total, 0, 'f', 2);
    file.close();

    QContact contact = dialog.selectedContact();
    QtopiaServiceRequest request("SMS",
                                 "writeSms(QString,QString,QString)");
    request << QString("%1 %2").arg(contact.firstName())
                               .arg(contact.lastName())
            << contact.defaultPhoneNumber() << fileName;
    request.send();
}

void ExpenseWindow::clear()
{
    int r = QMessageBox::warning(this, tr("Expenses"),
                    tr("Delete all expenses?"),
                    QMessageBox::Yes | QMessageBox::No);
    if (r == QMessageBox::Yes) {
        listWidget->clear();
        expenses.clear();
    }
}

void ExpenseWindow::createActions()
{
    addAction = new QAction(tr("Add"), this);
    addAction->setIcon(QIcon(":icon/add"));
    connect(addAction, SIGNAL(triggered()), this, SLOT(add()));

    editAction = new QAction(tr("Edit"), this);
    editAction->setIcon(QIcon(":icon/edit"));
    connect(editAction, SIGNAL(triggered()), this, SLOT(edit()));

    deleteAction = new QAction(tr("Delete"), this);
    deleteAction->setIcon(QIcon(":icon/delete"));
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(del()));

    sendAction = new QAction(tr("Send"), this);
    sendAction->setIcon(QIcon(":icon/send"));
    connect(sendAction, SIGNAL(triggered()), this, SLOT(send()));

    clearAction = new QAction(tr("Clear"), this);
    clearAction->setIcon(QIcon(":icon/clear"));
    connect(clearAction, SIGNAL(triggered()), this, SLOT(clear()));
}

void ExpenseWindow::createMenuOrToolBar()
{
#ifdef QTOPIA_PHONE
    QMenu *menuOrToolBar = QSoftMenuBar::menuFor(listWidget);
#else
    QToolBar *menuOrToolBar = new QToolBar;
    addToolBar(menuOrToolBar);
#endif

    menuOrToolBar->addAction(addAction);
    menuOrToolBar->addAction(editAction);
    menuOrToolBar->addAction(deleteAction);
    menuOrToolBar->addAction(sendAction);
    menuOrToolBar->addAction(clearAction);
}

void ExpenseWindow::loadData()
{
    QSettings settings("BookSoft Ltd", "Expenses");
    QByteArray data = settings.value("data").toByteArray();
    if (data.isEmpty())
        return;

    expenses.clear();
    QDataStream in(&data, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_4_2);

    while (!in.atEnd()) {
        QDate date;
        QString desc;
        qreal amount;

        in >> date >> desc >> amount;
        expenses.append(Expense(date, desc, amount));
    }
    showData();
}

void ExpenseWindow::showData()
{
    listWidget->clear();
    qreal total = 0.00;
    foreach (Expense expense, expenses) {
        listWidget->addItem(tr("%1 $%2 %3")
                            .arg(expense.date().toString(Qt::ISODate))
                            .arg(expense.amount(), 0, 'f', 2)
                            .arg(expense.description()));
        total += expense.amount();
    }
    totalAmountLabel->setText(tr("$%1").arg(total, 0, 'f', 2));
}
