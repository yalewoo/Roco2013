#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTabWidget>
#include "pk.h"
#include "selectpet.h"
#include "client.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    tabWidget = new QTabWidget(this);

    client = new Client(this);
    tabWidget->addTab(client, "在线");

    selectPet = new SelectPet(this);
    tabWidget->addTab(selectPet, "选择宠物");

    pk = new Pk(this);
    tabWidget->addTab(pk, "对战");



    pk->client = client;

    this->setCentralWidget(tabWidget);
    this->resize(1055,740);

    connect(selectPet, SIGNAL(startGame()), this, SLOT(startGame()));

    tabWidget->setCurrentIndex(0);

}

MainWindow::~MainWindow()
{

}

void MainWindow::startGame()
{
    tabWidget->setCurrentIndex(2);

    pk->initTeam();
}

