#ifndef CITYSCAPE_H
#define CITYSCAPE_H

#include <QMainWindow>

class QGraphicsScene;
class CityView;

class Cityscape : public QMainWindow
{
    Q_OBJECT

public:
    Cityscape();

private:
    void generateCityBlocks();

    QGraphicsScene *scene;
    CityView *view;
};

#endif
