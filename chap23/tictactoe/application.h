#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>

class TicTacToe;

class Application : public QApplication
{
    Q_OBJECT

public:
    Application(int &argc, char *argv[]);

    void setTicTacToe(TicTacToe *toe);
    void saveState(QSessionManager &sessionManager);
    void commitData(QSessionManager &sessionManager);

private:
    TicTacToe *ticTacToe;
};

#endif
