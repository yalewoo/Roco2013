#ifndef POKEMON_H
#define POKEMON_H

#include <QVector>
#include <QString>
//QString attr_name[17] = {"普","冰","草","虫","电","毒","恶","火","龙","萌","石","水","土","武","械","翼","幽"};
#include <QPair>
class Pokemon
{


public:
    int id; //宠物编号
    QString name;
    int attr;   //属性0-16
    int attr2;

    int hp; //血
    int ad; //物攻
    int ap; //魔攻
    int dd; //物抗
    int dp; //魔抗
    int speed;  //速度

    int nature; //性格

    //努力值分配
    int hpn;
    int adn;
    int apn;
    int ddn;
    int dpn;
    int speedn;

    //技能选择
    QVector<QPair<int,int> > skills;   //技能

    Pokemon();
    Pokemon(int id):id(id){}

};

#endif // POKEMON_H
