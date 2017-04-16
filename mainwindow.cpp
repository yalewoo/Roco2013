#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tabWidget->setCurrentIndex(0);

    connect(ui->selectPet, SIGNAL(startGame()), this, SLOT(startGame()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startGame()
{
    ui->tabWidget->setCurrentIndex(1);

    ui->pk->initTeam();
}

