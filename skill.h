#ifndef SKILL_H
#define SKILL_H

#include <QString>
class Skill
{
public:
    int type;
    int id;
    QString name;   //名称
    QString description;    //技能描述
    int attr;   //属性

    int pp;

    int attack_type; //0变化 1物攻 2魔攻
    double power;  //威力
    double prob;    //成功率 >1所有情况必中 =1对方无闪避必中
    int speed = 0;  //先手
    bool special = false;
    double fandan;  //反弹伤害







    double prob2;   //成功后产生其余效果的概率
     double prob2_self;   //成功后产生其余效果的概率



    int self_adp = 0;
    int self_ddp = 0;
    int self_app = 0;
    int self_dpp = 0;
    int self_speedp = 0;

    QString self_status;
    int min_time;
    int max_time;
    double value;

    QString enemy_status;



    int enemy_adp = 0;
    int enemy_ddp = 0;
    int enemy_app = 0;
    int enemy_dpp = 0;
    int enemy_speedp = 0;


    int cannotchange;
    bool qianghuafirst =false;


    QString self_cond;
    QString enemy_cond;


    Skill();
    Skill(int type): type(type){}
};

#endif // SKILL_H
