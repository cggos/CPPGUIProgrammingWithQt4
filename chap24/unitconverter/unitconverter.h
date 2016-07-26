#ifndef UNITCONVERTER_H
#define UNITCONVERTER_H

#include <QMainWindow>
#include <QMap>

class QComboBox;
class QDoubleSpinBox;
class QLabel;

class UnitConverter : public QMainWindow
{
    Q_OBJECT

public:
    UnitConverter(QWidget *parent = 0, Qt::WFlags flags = 0);

private slots:
    void calculate();
    void updateToComboBox();

private:
    QMap<QString, double> unitsOfLength;
    QMap<QString, double> unitsOfWeight;

    QWidget *centralWidget;
    QLabel *titleLabel;
    QLabel *isTheEquivalentOfLabel;
    QDoubleSpinBox *fromAmountSpinBox;
    QLabel *toAmountLabel;
    QComboBox *fromUnitComboBox;
    QComboBox *toUnitComboBox;
};

#endif
