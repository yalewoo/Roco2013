#ifndef PK_H
#define PK_H

#include <QWidget>
#include <QString>
#include "team.h"

#include "client.h"

namespace Ui {
class Pk;
}

class Pk : public QWidget
{
    Q_OBJECT

public:
    explicit Pk(QWidget *parent = 0);
    ~Pk();

    void initTeam();


        Client * client;

private:
    Ui::Pk *ui;


    QString logs;




    Team team1; //我方队伍

    Team team2; //敌方队伍

    int choose1;    //我方选择
    int choose2;    //敌方选择



    int computer_ai(Team & team);  //敌方ai

    int huihe = 1;  //回合数

    bool dead1 = false;
    bool dead2 = false;

    void displayGroups(Team & team);
    void updateSkills(Team & team);
    void updatepok();
    void updatepok1();
    void updatepok2();

    void updateStatus();
    QString getStatus(Team & team);

    void skill_clicked(int i);
    int calcSpeed(Team & team, int n);

private slots:
    void log(QString log);
    void on_skill1_clicked();
    void on_skill2_clicked();
    void on_skill3_clicked();
    void on_skill4_clicked();
    void on_pushButton_clicked();

    void display();
};

#endif // PK_H
