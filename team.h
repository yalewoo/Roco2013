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
    bool miss = false;
    bool kongju = false;

    AttackData(int a = 0)
    {
        hp_release = a;
        damage = 0;
        cuimian = false;
        bingdong = false;
        miss = false;
        kongju = false;
    }

    void clear()
    {
        hp_release = 0;
        damage = 0;
        cuimian = false;
        bingdong = false;
        miss = false;
        kongju = false;
    }
};

struct LastHuihe{

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


    AttackData res;


    void attack1(Team & enemy) { attack(1, enemy); }
    void attack2(Team & enemy) { attack(2, enemy); }
    void attack3(Team & enemy) { attack(3, enemy); }
    void attack4(Team & enemy) { attack(4, enemy); }

    AttackData attack(int skill, Team & enemy, AttackData res = 0);
    AttackData attack(QPair<int,int> skill, Team & enemy, AttackData res = 0);
    void consume(Team &team, AttackData & res);


    void skill1(Pok &pok, Skill & sk, Team & enemy, AttackData & xianshou);
    void skill2(Pok &pok, Skill & sk, Team & enemy, AttackData & xianshou);
    void skill3(int skill_id, Pok &pok, Skill & sk, Team & enemy, AttackData & xianshou);
    void skill4(Pok &pok, Skill & sk, Team & enemy, AttackData & xianshou);
    void skill5(Pok &pok, Skill & sk, Team & enemy, AttackData & xianshou);
    void skill6(int skill_id, Pok &pok, Skill & sk, Team & enemy, AttackData & xianshou);
    void skill7(Pok &pok, Skill & sk, Team & enemy, AttackData & xianshou);
    void skill8(Pok &pok, Skill & sk, Team & enemy, AttackData & xianshou);
    void skill9(Pok &pok, Skill & sk, Team & enemy, AttackData & xianshou);
    void skill10(Pok &pok, Skill & sk, Team & enemy, AttackData & xianshou);

    int sleep = 0;
    int bingdong = 0;




    bool should_use = false;
    int should_use_id;
    int should_use_huihe;

    //可以行动返回true
    bool selfStatus();

    void logofKezhi(double res);//显示属性克制信息

};

#endif // TEAM_H
