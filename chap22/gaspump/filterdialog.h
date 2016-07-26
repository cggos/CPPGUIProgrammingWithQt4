#ifndef FILTERDIALOG_H
#define FILTERDIALOG_H

#include <QDialog>
#include <QSet>

#include "ui_filterdialog.h"

class PumpFilter;
class PumpSpreadsheet;

class FilterDialog : public QDialog, private Ui::FilterDialog
{
    Q_OBJECT

public:
    FilterDialog(QWidget *parent = 0);

    void initFromSpreadsheet(PumpSpreadsheet *spreadsheet);
    PumpFilter filter() const;

private:
    void populateComboBox(QComboBox *comboBox,
                          const QSet<QString> &texts);
    QString comboBoxText(const QComboBox *comboBox) const;
};

#endif
