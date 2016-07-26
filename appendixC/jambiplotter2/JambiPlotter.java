import java.lang.Math;
import java.util.ArrayList;
import com.trolltech.qt.core.*;
import com.trolltech.qt.gui.*;
import com.softwareinc.plotter2.Plotter;
import com.softwareinc.plotter2.PlotSettings;

public class JambiPlotter {
    public static void main(String[] args) {
        QApplication.initialize(args);

        PlotSettings settings = new PlotSettings();
        settings.setMinX(0.0);
        settings.setMaxX(100.0);
        settings.setMinY(0.0);
        settings.setMaxY(100.0);

        int numPoints = 100;
        QPointF[] points0 = new QPointF[numPoints];
        QPointF[] points1 = new QPointF[numPoints];
        for (int x = 0; x < numPoints; ++x) {
            points0[x] = new QPointF(x, Math.random() * 100);
            points1[x] = new QPointF(x, Math.random() * 100);
        }

        Plotter plotter = new Plotter();
        plotter.setWindowTitle(plotter.tr("Jambi Plotter"));
        plotter.setPlotSettings(settings);
        plotter.setCurveData(0, points0);
        plotter.setCurveData(1, points1);
        plotter.show();

        QApplication.exec();
    }
}
