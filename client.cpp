#include "client.h"
#include "ui_client.h"

#include <QTcpSocket>
#include <QDebug>

#include <QFile>

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

bool Client::sendTxt(QString filename)
{
    QString s = "sendfile";
    socket->write(s.toLatin1());
    socket->flush();

    QByteArray buffer;
    socket->waitForReadyRead();
    buffer = socket->readAll();
    QString str;
    if (!buffer.isEmpty())
    {
        str = buffer;
    }

    QFile *f = new QFile(filename);
    f->open(QFile::ReadOnly);
    int size = f->size();
    qDebug() << "size = " << size;

    s = QString::number(size);
    socket->write(s.toLatin1());
    socket->flush();

    socket->waitForReadyRead();
    buffer = socket->readAll();
    if (!buffer.isEmpty())
    {
        str = buffer;
    }
    qDebug() << "recv " << str;

#define BUF_SIZE 1024
    qint64 len = 0;
    qint64 sendSize = 0;
    do{
        //一次发送的大小
        char buf[BUF_SIZE] = {0};
        len = 0;
        len = f->read(buf,BUF_SIZE);  //len为读取的字节数
        len = socket->write(buf,len);    //len为发送的字节数

        //已发数据累加
        sendSize += len;
    }while(len > 0);
    socket->flush();
}

bool Client::askTxt(QString filename)
{
    QString s = "askfile";
    socket->write(s.toLatin1());
    socket->flush();

    QByteArray buffer;
    socket->waitForReadyRead();
    buffer = socket->readAll();
    QString str;
    if (!buffer.isEmpty())
    {
        str = buffer;
    }
    qDebug() << "recv " << str;


    socket->waitForReadyRead();
    buffer = socket->readAll();
    if (!buffer.isEmpty())
    {
        str = buffer;
    }
    qDebug() << "recv file size = " << str;

    s = "start";
    socket->write(s.toLatin1());
    socket->flush();

    qint64 file_size = str.toInt();

    qDebug() << "file_size = " << file_size;

    QFile *f = new QFile(filename);
    f->open(QFile::WriteOnly);

    qint64 len = 0;
    qint64 now = 0;
    while (len < file_size)
    {
        socket->waitForReadyRead();
        buffer = socket->readAll();
        now = f->write(buffer);
        len += now;
        qDebug() << "len = " << len;
    }
    f->close();
    qDebug() << "recv file finished";

}

QString Client::askForSkill(QString send)
{
    socket->write(send.toLatin1());
    socket->flush();

    QByteArray buffer;
    socket->waitForReadyRead();
    buffer = socket->readAll();
    QString str;
    if (!buffer.isEmpty())
    {
        str = buffer;
    }
    return str;
}

void Client::closeSocket()
{
    if (this->isConnected)
        socket_disconnected();
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

void Client::on_button_test_clicked()
{
    askTxt("recv.txt");
}
