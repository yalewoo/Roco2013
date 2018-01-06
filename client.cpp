#include "client.h"
#include "ui_client.h"

#include <QTcpSocket>
#include <QDebug>

Client::Client(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);

    isConnected = false;
    socket = new QTcpSocket(this);
    ui->button_send->setEnabled(false);

    connect(socket, &QTcpSocket::disconnected, this, &Client::socket_disconnected);
    //connect(socket, &QTcpSocket::readyRead, this, &Client::socket_read);

}

Client::~Client()
{
    delete ui;
}

void Client::on_button_connect_clicked()
{
    if(!isConnected)
    {
        socket->abort();
        socket->connectToHost(ui->ip->text(), ui->port->text().toInt());
        if (!socket->waitForConnected())
        {
            qDebug() << "Connection failed";
            return;
        }
        qDebug() << "connect successfully!";

        isConnected = true;
        ui->button_connect->setText("取消连接");
        ui->button_send->setEnabled(true);
    }
    else
    {
        socket->disconnectFromHost();
        ui->button_connect->setText("连接");
        isConnected = false;
        ui->button_send->setEnabled(false);

    }
}

void Client::on_button_send_clicked()
{
    socket->write(ui->text->text().toLatin1());
    socket->flush();
}

void Client::socket_disconnected()
{
    ui->button_connect->setText("连接");
    isConnected = false;
    ui->button_send->setEnabled(false);

    qDebug() << "disconnected by host";
}

void Client::socket_read()
{
    QByteArray buffer;
    buffer = socket->readAll();
    if (!buffer.isEmpty())
    {
        QString str = buffer;
        ui->text_receive->setText(str);
    }
}
