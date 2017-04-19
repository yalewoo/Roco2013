#ifndef POK_H
#define POK_H

#include "pokemon.h"
#include "skill.h"
#include "globalvar.h"
class Pok
{


public:
    Pok();
    Pok(Pokemon &pokemon);

    Pokemon pokemon;


    int hp_max;
    int ad,dd,ap,dp,speed;

    int hp; //目前血量

    //变化等级
    int ad_rank = 0;
    int dd_rank = 0;
    int ap_rank = 0;
    int dp_rank = 0;
    int speed_rank = 0;

    int pp[4] = {0};    //各个技能的可用PP

    int jisheng = 0;

    bool zhongdu = false;
    int judu = 0;
    bool shaoshang = false;
    bool mazui = false;

    int qingxing = 0;
    int shouhuzhili = 0;
    int bingtianxuedi = 0;
    int dadikuanshu = 0;
    int wudun = 0;

    int add_hp = 0;
    double add_hp_value = 0;

    int damage_xishou = 0;
    int damage_xishou_value = 0;




};

#endif // POK_H
