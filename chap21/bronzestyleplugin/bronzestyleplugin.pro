TEMPLATE      = lib
CONFIG       += plugin
HEADERS       = ../bronze/bronzestyle.h \
                bronzestyleplugin.h
SOURCES       = ../bronze/bronzestyle.cpp \
                bronzestyleplugin.cpp
RESOURCES     = ../bronze/bronze.qrc
DESTDIR       = $$[QT_INSTALL_PLUGINS]/styles
