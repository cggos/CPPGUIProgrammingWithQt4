import com.trolltech.qt.core.*;
import com.trolltech.qt.gui.*;

public class GoToCellDialog extends QDialog {
    private Ui_GoToCellDialogClass ui = new Ui_GoToCellDialogClass();

    public GoToCellDialog(QWidget parent) {
        super(parent);
        ui.setupUi(this);

        ui.okButton.setEnabled(false);

        QRegExp regExp = new QRegExp("[A-Za-z][1-9][0-9]{0,2}");
        ui.lineEdit.setValidator(new QRegExpValidator(regExp, this));

        ui.okButton.clicked.connect(this, "accept()");
        ui.cancelButton.clicked.connect(this, "reject()");
    }

    private void on_lineEdit_textChanged(String text) {
        ui.okButton.setEnabled(!text.isEmpty());
    }

    public static void main(String[] args) {
        QApplication.initialize(args);
        GoToCellDialog testGoToCellDialog = new GoToCellDialog(null);
        testGoToCellDialog.show();
        QApplication.exec();
    }
}
