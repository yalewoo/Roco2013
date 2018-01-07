#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QCloseEvent>
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
    selectPet->client = client;

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

void MainWindow::closeEvent( QCloseEvent * event )
{
    switch( QMessageBox::information( this, tr("Exit"),  tr("Do you really want to exit?"),  tr("Yes"), tr("No"),  0, 1 ) )
 {
    case 0:
        client->closeSocket();
        event->accept();
        break;
    case 1:
    default:
        event->ignore();
        break;
 }
}

