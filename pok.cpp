#include "pok.h"

Pok::Pok()
{

}

Pok::Pok(Pokemon &poke)
{
    pokemon = poke;
    hp = hp_max = poke.hp;
    ad = poke.ad;
    dd = poke.dd;
    ap = poke.ap;
    dp = poke.dp;
    speed = poke.speed;

    QVector<Skill> *skills_all = GlobalVar::skills_all;
    for (int row = 0; row < poke.skills.size(); ++row)
    {
        int t1 = poke.skills[row].first;
        int t2 = poke.skills[row].second;
        Skill & sk = skills_all[t1][t2];

        pp[row] = sk.pp;
    }

}
