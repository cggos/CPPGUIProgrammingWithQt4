#include <QtGui>

#include "unitconverter.h"

UnitConverter::UnitConverter(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags)
{
    unitsOfLength.insert(tr("Millimeters"), 0.001);
    unitsOfLength.insert(tr("Meters"), 1.0);
    unitsOfLength.insert(tr("Kilometers"), 1000.0);
    unitsOfLength.insert(tr("Inches"), 0.0254);
    unitsOfLength.insert(tr("Feet"), 0.3048);
    unitsOfLength.insert(tr("Yards"), 0.9144);
    unitsOfLength.insert(tr("Miles"), 1609.344);

    unitsOfWeight.insert(tr("Ounces"), 28.3495231);
    unitsOfWeight.insert(tr("Pounds"), 453.59237);
    unitsOfWeight.insert(tr("Grams"), 1.0);
    unitsOfWeight.insert(tr("Kilograms"), 1000.0);

    centralWidget = new QWidget;
    setCentralWidget(centralWidget);

    titleLabel = new QLabel(tr("<font size=\"+2\"><b>"
                               "Unit Converter</b></font>"));
    titleLabel->setAlignment(Qt::AlignCenter);

    fromAmountSpinBox = new QDoubleSpinBox;
    fromAmountSpinBox->setDecimals(3);
    fromAmountSpinBox->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    fromAmountSpinBox->setValue(1.0);
    fromAmountSpinBox->setRange(0.001, 99999999.999);

    fromUnitComboBox = new QComboBox;
    fromUnitComboBox->addItems(unitsOfLength.keys()
                               + unitsOfWeight.keys());
    fromUnitComboBox->setCurrentIndex(
            fromUnitComboBox->findText(tr("Kilometers")));

    toAmountLabel = new QLabel;
    toAmountLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    toAmountLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    toUnitComboBox = new QComboBox;

    isTheEquivalentOfLabel = new QLabel(tr("is the equivalent of"));
    isTheEquivalentOfLabel->setAlignment(Qt::AlignCenter);

    QGridLayout *middleLayout = new QGridLayout;
    middleLayout->addWidget(fromAmountSpinBox, 0, 0);
    middleLayout->addWidget(fromUnitComboBox, 0, 1);
    middleLayout->addWidget(isTheEquivalentOfLabel, 1, 0, 1, 2);
    middleLayout->addWidget(toAmountLabel, 2, 0);
    middleLayout->addWidget(toUnitComboBox, 2, 1);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(titleLabel);
    mainLayout->addLayout(middleLayout);
    mainLayout->addStretch();
    centralWidget->setLayout(mainLayout);

    connect(fromAmountSpinBox, SIGNAL(valueChanged(double)),
            this, SLOT(calculate()));
    connect(toUnitComboBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(calculate()));
    connect(fromUnitComboBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(updateToComboBox()));

    setWindowTitle(tr("Unit Converter"));
    updateToComboBox();
}

void UnitConverter::updateToComboBox()
{
    QString unit = fromUnitComboBox->currentText();
    QMap<QString, double> relevantUnits;
    if (unitsOfLength.contains(unit)) {
        relevantUnits = unitsOfLength;
    } else if (unitsOfWeight.contains(unit)) {
        relevantUnits = unitsOfWeight;
    }

    if (toUnitComboBox->findText(unit) == -1) {
        toUnitComboBox->clear();
        toUnitComboBox->addItems(relevantUnits.keys());
        toUnitComboBox->setCurrentIndex(relevantUnits.count() - 1);
    }
    calculate();
}

void UnitConverter::calculate()
{
    QMap<QString, double> allUnits = unitsOfLength;
    allUnits.unite(unitsOfWeight);

    double amount = fromAmountSpinBox->value();
    amount *= allUnits.value(fromUnitComboBox->currentText());
    amount /= allUnits.value(toUnitComboBox->currentText());
    toAmountLabel->setText(tr("%1").arg(amount, 0, 'g', 6));
}
