#include <QtCore>

#include "expense.h"

Expense::Expense()
{
    myAmount = 0.0;
}

Expense::Expense(const QDate &date, const QString &desc, qreal amount)
{
    myDate = date;
    myDesc = desc;
    myAmount = amount;
}

bool Expense::isNull() const
{
    return myDate.isNull();
}

void Expense::setDate(const QDate &date)
{
    myDate = date;
}

QDate Expense::date() const
{
    return myDate;
}

void Expense::setDescription(const QString &desc)
{
    myDesc = desc;
}

QString Expense::description() const
{
    return myDesc;
}

void Expense::setAmount(qreal amount)
{
    myAmount = amount;
}

qreal Expense::amount() const
{
    return myAmount;
}
