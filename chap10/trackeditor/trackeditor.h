#ifndef TRACKEDITOR_H
#define TRACKEDITOR_H

#include <QDialog>
#include <QList>

class QDialogButtonBox;
class QTableWidget;

class Track
{
public:
    Track(const QString &title = "", int duration = 0);

    QString title;
    int duration;
};

class TrackEditor : public QDialog
{
    Q_OBJECT

public:
    TrackEditor(QList<Track> *tracks, QWidget *parent = 0);

    void done(int result);

private slots:
    void addTrack();

private:
    QTableWidget *tableWidget;
    QDialogButtonBox *buttonBox;
    QList<Track> *tracks;
};

#endif
