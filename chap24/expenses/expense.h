#ifndef EXPENSE_H
#define EXPENSE_H

#include <QDate>
#include <QString>

class Expense
{
public:
    Expense();
    Expense(const QDate &date, const QString &desc, qreal amount);

    bool isNull() const;
    void setDate(const QDate &date);
    QDate date() const;
    void setDescription(const QString &desc);
    QString description() const;
    void setAmount(qreal amount);
    qreal amount() const;

private:
    QDate myDate;
    QString myDesc;
    qreal myAmount;
};

#endif
