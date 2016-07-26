#ifndef CURSORPLUGIN_H
#define CURSORPLUGIN_H

#include <QImageIOPlugin>

class CursorPlugin : public QImageIOPlugin
{
public:
    QStringList keys() const;
    Capabilities capabilities(QIODevice *device,
                              const QByteArray &format) const;
    QImageIOHandler *create(QIODevice *device,
                            const QByteArray &format) const;
};

#endif
