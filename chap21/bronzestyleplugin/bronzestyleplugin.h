#ifndef BRONZESTYLEPLUGIN_H
#define BRONZESTYLEPLUGIN_H

#include <QStylePlugin>

class BronzeStylePlugin : public QStylePlugin
{
public:
    QStringList keys() const;
    QStyle *create(const QString &key);
};

#endif
