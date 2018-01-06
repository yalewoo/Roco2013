#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>

class QTcpSocket;

namespace Ui {
class Client;
}

class Client : public QWidget
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = 0);
    ~Client();

    QTcpSocket *socket;
private slots:
    void on_button_connect_clicked();

    void on_button_send_clicked();

    void socket_disconnected();
    void socket_read();

private:
    Ui::Client *ui;

    bool isConnected;
};

#endif // CLIENT_H
