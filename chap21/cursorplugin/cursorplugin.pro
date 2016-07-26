TEMPLATE      = lib
CONFIG       += plugin
HEADERS       = cursorhandler.h \
                cursorplugin.h
SOURCES       = cursorhandler.cpp \
                cursorplugin.cpp
DESTDIR       = $$[QT_INSTALL_PLUGINS]/imageformats
