#ifndef GLOBALVAR_H
#define GLOBALVAR_H

#include "skill.h"
#include <QVector>
#include <QPair>
#include "pokemon.h"

class GlobalVar
{
public:
    GlobalVar();
    static QVector<QPair<int,int> > *poke_skills;
    static QVector<Pokemon> *pokes;
    static QVector<Pokemon> *pokes2;
    static QVector<Skill> *skills_all;
    static QVector<Pokemon> * pokemons_all;
};

#endif // GLOBALVAR_H
