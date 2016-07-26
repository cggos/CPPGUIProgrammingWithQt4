#ifndef HTTPGET_H
#define HTTPGET_H

#include <QFile>
#include <QHttp>

class QUrl;

class HttpGet : public QObject
{
    Q_OBJECT

public:
    HttpGet(QObject *parent = 0);

    bool getFile(const QUrl &url);

signals:
    void done();

private slots:
    void httpDone(bool error);

private:
    QHttp http;
    QFile file;
};

#endif
