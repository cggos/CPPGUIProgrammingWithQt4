qtopia_project(qtopia app)

TARGET        = unitconverter
CONFIG       += qtopia_main no_quicklaunch
HEADERS      += unitconverter.h
SOURCES      += main.cpp \
                unitconverter.cpp
INSTALLS     += desktop pics

desktop.files = unitconverter.desktop
desktop.path  = /apps/Applications
desktop.hint  = desktop

pics.files    = pics/*
pics.path     = /pics/unitconverter
pics.hint     = pics

pkg.name      = unitconverter
pkg.desc      = A program to convert between various units of measurement
pkg.version   = 1.0.0
pkg.domain    = window
