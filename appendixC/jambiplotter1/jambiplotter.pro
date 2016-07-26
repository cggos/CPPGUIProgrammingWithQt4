TEMPLATE      = lib
TARGET        = com_softwareinc_plotter
DLLDESTDIR    = .
HEADERS       = ../plotter/plotter.h
SOURCES       = ../plotter/plotter.cpp
RESOURCES     = ../plotter/plotter.qrc
INCLUDEPATH  += ../plotter \
                $$(JAMBIPATH)/include \
                $$(JAVA)/include
unix {
    INCLUDEPATH  += $$(JAVA)/include/linux
}
win32 {
    INCLUDEPATH  += $$(JAVA)/include/win32
}
LIBS         += -L$$(JAMBIPATH)/lib -lqtjambi

include(../cpp/com_softwareinc_plotter/com_softwareinc_plotter.pri)
