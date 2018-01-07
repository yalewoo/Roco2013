#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "pokemon.h"

class QTabWidget;
class Pk;
class SelectPet;
class Client;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void startGame();


private:
    QTabWidget * tabWidget;
    Pk *pk;
    SelectPet * selectPet;
    Client * client;

protected:
    void closeEvent( QCloseEvent * event );
};

#endif // MAINWINDOW_H
