qtopia_project(qtopia app)
depends(libraries/qtopiapim)

CONFIG       += qtopia_main no_quicklaunch
HEADERS      += expense.h \
                expensedialog.h \
                expensewindow.h
SOURCES      += expense.cpp \
                expensedialog.cpp \
                expensewindow.cpp \
                main.cpp
INSTALLS     += desktop pics

desktop.files = expenses.desktop
desktop.path  = /apps/Applications
desktop.hint  = desktop

pics.files    = pics/*
pics.path     = /pics/expenses
pics.hint     = pics

pkg.name      = expenses
pkg.desc      = A program to record and SMS expenses
pkg.version   = 1.0.0
pkg.domain    = window
