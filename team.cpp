#include "team.h"

#include <QTime>
#include <QtGlobal>

bool ifProb(double p)
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    double r = qrand() % 10000 / 10000.0;
    if (r < p)
        return true;
    else
        return false;

}

Team::Team(QWidget *parent)  :  QWidget(parent)
{
    poke_skills = GlobalVar::poke_skills;
}
Team::~Team()
{

}

void Team::log(QString log)
{
    emit addlog(log);
}

void Team::attack(int skill_id, Team & enemy)
{
    if (skill_id >= 10)
    {
        //换宠物
    }
    else
    {
        Pok & pok = poks[current_pok];
        int id = poks[current_pok].pokemon.id;

        QVector<Skill> *skills_all = GlobalVar::skills_all;

        int t1 = pok.pokemon.skills[skill_id].first;
        int t2 = pok.pokemon.skills[skill_id].second;
        Skill & sk = skills_all[t1][t2];

        log("【" + name + "】的【" + pok.pokemon.name + "】使用了" + sk.name);

        if (t1 == 1)
        {
            if (ifProb(sk.prob))
            {
                double power = sk.power;
            }
            else
            {
                log("可惜miss了！");
            }


        }
        else if (t1 == 2)
        {

        }
        else if (t1 == 3)
        {

        }
        else if (t1 == 4)
        {

        }else if (t1 == 5)
        {

        }
        else if (t1 == 6)
        {

        }
        else if (t1 == 7)
        {

        }
        else if (t1 == 8)
        {

        }
        else if (t1 == 9)
        {

        }
        else
        {

        }
    }




}


void Team::init(QVector<Pokemon> *ppokes)
{
    QVector<Pokemon> &pokes = *ppokes;

    for (int i = 0; i < pokes.size(); ++i)
    {
        Pok pok(pokes[i]);
        poks.push_back(pok);
    }

    current_pok = 0;
}
