import com.trolltech.qt.core.*;
import com.trolltech.qt.gui.*;

public class FindDialog extends QDialog {
    public Signal2<String, Qt.CaseSensitivity> findNext =
            new Signal2<String, Qt.CaseSensitivity>();

    public Signal2<String, Qt.CaseSensitivity> findPrevious =
            new Signal2<String, Qt.CaseSensitivity>();

    public FindDialog(QWidget parent) {
        super(parent);

        label = new QLabel(tr("Find &what:"));
        lineEdit = new QLineEdit();
        label.setBuddy(lineEdit);

        caseCheckBox = new QCheckBox(tr("Match &case"));
        backwardCheckBox = new QCheckBox(tr("Search &backward"));

        findButton = new QPushButton(tr("&Find"));
        findButton.setDefault(true);
        findButton.setEnabled(false);

        closeButton = new QPushButton(tr("Close"));

        lineEdit.textChanged.connect(this, "enableFindButton(String)");
        findButton.clicked.connect(this, "findClicked()");
        closeButton.clicked.connect(this, "reject()");

        QHBoxLayout topLeftLayout = new QHBoxLayout();
        topLeftLayout.addWidget(label);
        topLeftLayout.addWidget(lineEdit);

        QVBoxLayout leftLayout = new QVBoxLayout();
        leftLayout.addLayout(topLeftLayout);
        leftLayout.addWidget(caseCheckBox);
        leftLayout.addWidget(backwardCheckBox);

        QVBoxLayout rightLayout = new QVBoxLayout();
        rightLayout.addWidget(findButton);
        rightLayout.addWidget(closeButton);
        rightLayout.addStretch();

        QHBoxLayout mainLayout = new QHBoxLayout();
        mainLayout.addLayout(leftLayout);
        mainLayout.addLayout(rightLayout);
        setLayout(mainLayout);

        setWindowTitle(tr("Jambi Find"));
        setFixedHeight(sizeHint().height());
    }

    private void findClicked() {
        String text = lineEdit.text();
        Qt.CaseSensitivity cs = caseCheckBox.isChecked()
                ? Qt.CaseSensitivity.CaseSensitive
                : Qt.CaseSensitivity.CaseInsensitive;
        if (backwardCheckBox.isChecked()) {
            findPrevious.emit(text, cs);
        } else {
            findNext.emit(text, cs);
        }
    }

    private void enableFindButton(String text) {
        findButton.setEnabled(text.length() == 0);
    }

    private QLabel label;
    private QLineEdit lineEdit;
    private QCheckBox caseCheckBox;
    private QCheckBox backwardCheckBox;
    private QPushButton findButton;
    private QPushButton closeButton;

    public static void main(String[] args) {
        QApplication.initialize(args);
        FindDialog dialog = new FindDialog(null);
        dialog.show();
        QApplication.exec();
    }
}
