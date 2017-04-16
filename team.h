#ifndef TEAM_H
#define TEAM_H

#include "pok.h"

#include "globalvar.h"

#include <QWidget>

struct AttackData {
    int hp_release;
    int damage;
    bool cuimian;
    bool bingdong;

    AttackData(int a = 0)
    {
        hp_release = a;
        damage = 0;
        cuimian = false;
        bingdong = false;
    }
};

class Team  : public QWidget
{
    Q_OBJECT

public:
    explicit Team(QWidget *parent = 0);
    ~Team();


signals:
    void addlog(QString log);

public:
    void log(QString log);

    QString name;   //队伍名字

    QVector<QPair<int,int> > *poke_skills;

    int current_pok;    //目前上场宠物
    QVector<Pok> poks; //6只宠物
    void init(QVector<Pokemon> *ppokes);




    void attack1(Team & enemy) { attack(1, enemy); }
    void attack2(Team & enemy) { attack(2, enemy); }
    void attack3(Team & enemy) { attack(3, enemy); }
    void attack4(Team & enemy) { attack(4, enemy); }


    AttackData attack(int skill, Team & enemy, AttackData res = 0);

    int sleep = 0;
    int bingdong = 0;
    //可以行动返回true
    bool selfStatus();

};

#endif // TEAM_H
