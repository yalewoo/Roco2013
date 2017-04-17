#include "team.h"

#include <QTime>
#include <QtGlobal>
#include <QDebug>
bool ifProb(double p)
{


    double r = qrand() % 10000 / 10000.0;
    if (r < p)
        return true;
    else
        return false;

}

double getrand80100()
{


    double r = qrand() % 2001 + 8000;
    //qDebug() << r;
    r = r / 10000;
    return r;

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

int calc(int ad, int rank)
{
    if (rank >= 0)
        ad = ad * ((rank) * 0.5 + 1);
    else
    {
        ad = ad / ((-1.0 * rank) * 0.5 + 1);
    }
    return ad;
}

AttackData Team::attack(int skill_id, Team & enemy, AttackData last)
{
    AttackData res;

    static double aioi[17][17] = {
        {1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.5,1.0,1.0,1.0,0.5,1.0,1.0},
        {1.0,0.5,2.0,1.0,1.0,1.0,1.0,0.5,2.0,1.0,1.0,0.5,2.0,1.0,0.5,2.0,1.0},
        {1.0,1.0,0.5,0.5,1.0,0.5,1.0,0.5,0.5,1.0,2.0,2.0,2.0,1.0,0.5,0.5,1.0},
        {1.0,1.0,2.0,1.0,1.0,0.5,2.0,0.5,1.0,2.0,1.0,1.0,1.0,0.5,0.5,0.5,0.5},
        {1.0,1.0,0.5,1.0,0.5,1.0,1.0,1.0,0.5,1.0,1.0,2.0,1.0,1.0,1.0,2.0,1.0},
        {1.0,1.0,2.0,1.0,1.0,0.5,1.0,1.0,1.0,1.0,0.5,1.0,0.5,1.0,1.0,1.0,0.5},
        {1.0,1.0,1.0,1.0,1.0,1.0,0.5,1.0,1.0,2.0,1.0,1.0,1.0,0.5,0.5,1.0,2.0},
        {1.0,2.0,2.0,2.0,1.0,1.0,1.0,1.0,0.5,1.0,0.5,0.5,1.0,1.0,2.0,1.0,1.0},
        {1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,2.0,1.0,1.0,1.0,1.0,1.0,0.5,1.0,1.0},
        {1.0,1.0,1.0,1.0,1.0,2.0,1.0,1.0,1.0,0.5,1.0,1.0,1.0,2.0,0.5,1.0,1.0},
        {1.0,2.0,1.0,2.0,1.0,1.0,1.0,2.0,1.0,1.0,1.0,1.0,0.5,0.5,0.5,2.0,1.0},
        {1.0,1.0,0.5,1.0,1.0,1.0,1.0,2.0,0.5,1.0,2.0,1.0,2.0,1.0,1.0,1.0,1.0},
        {1.0,1.0,0.5,0.5,2.0,2.0,1.0,2.0,1.0,1.0,2.0,1.0,1.0,1.0,2.0,1.0,1.0},
        {2.0,2.0,1.0,0.5,1.0,0.5,2.0,1.0,1.0,0.5,2.0,1.0,1.0,1.0,2.0,0.5,1.0},
        {1.0,2.0,1.0,1.0,0.5,1.0,1.0,0.5,1.0,1.0,2.0,0.5,1.0,1.0,0.5,1.0,1.0},
        {1.0,1.0,2.0,2.0,0.5,1.0,1.0,1.0,1.0,1.0,0.5,1.0,1.0,2.0,0.5,1.0,1.0},
        {1.0,1.0,1.0,1.0,1.0,1.0,0.5,1.0,1.0,2.0,1.0,1.0,1.0,1.0,0.5,1.0,2.0}};
    if (skill_id >= 10)
    {
        //换宠物
    }
    else
    {

        Pok & pok = poks[current_pok];
        --pok.pp[skill_id];

        Pok & enemy_pok = enemy.poks[enemy.current_pok];
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

                //伤害＝{ [（攻方宠物等级×0.4＋2）×攻击技能威力×攻方的攻击（魔攻）/守方的防御（魔防）/50＋2]（下舍入）×相克修正×（80%到100%之间随机数）}（下舍入）
                int damage;

                if (sk.attack_type == 0)
                {

                }
                else
                {
                    if (sk.attack_type == 1)
                    {
                        int ad = calc(pok.ad, pok.ad_rank);
                        int enemy_dd = calc(enemy_pok.dd, enemy_pok.dd_rank);
                        damage = 42 * power * ad / enemy_dd / 50 + 2;
                    }
                    else
                    {
                        int ap = calc(pok.ap, pok.ap_rank);
                        int enemy_dp = calc(enemy_pok.dp, enemy_pok.dp_rank);
                        damage = 42 * power * ap / enemy_dp / 50 + 2;
                    }

                    //属性克制
                    if (enemy_pok.pokemon.attr2 == -1)
                    {
                        damage *= aioi[sk.attr][enemy_pok.pokemon.attr];
                    }
                    else
                    {
                        double res = aioi[sk.attr][enemy_pok.pokemon.attr] * aioi[sk.attr][enemy_pok.pokemon.attr2];
                        if (res > 3)
                            damage *= 3;
                        else if (res < 0.4)
                            damage /= 3;
                        else
                            damage *= res;
                    }

                    //随机乘以 0.8到1
                    damage *= getrand80100();

                    //5%几率暴击
                    if (ifProb(0.05))
                    {
                        log("暴击了！");
                        damage *= 2;
                    }

                }

                enemy_pok.hp -= damage;
                log("【" +enemy.name + "】的【" + enemy_pok.pokemon.name + "】受到了【" + QString::number(damage) + "】点伤害！");

                res.damage = damage;

            }
            else
            {
                log("可惜miss了！");
                res.damage = 0;
            }
            res.cuimian = false;
            res.bingdong = false;


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

    int enemy_hp = enemy.poks[enemy.current_pok].hp;
    if (enemy_hp <= 0)
    {
        enemy.poks[enemy.current_pok].hp = 0;
        log("【" +enemy.name + "】的【" + enemy.poks[enemy.current_pok].pokemon.name + "】被击败了！");
    }
    res.hp_release = enemy_hp;

    return res;



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


bool Team::selfStatus()
{
    bool res;
    if (sleep > 0)
    {
        if (sleep == 1)
        {
            sleep = 0;
            res = true;
        }
        else
        {
            int r = qrand() % sleep;
            if (r == 1)
            {
                sleep = 0;
                res = true;
            }
            else
            {
                --sleep;
                res = false;
            }
        }
        if (res)
        {
            log("【" +name + "】的【" + poks[current_pok].pokemon.name + "】醒来了！");
            return true;
        }
        else
        {
            log("【" +name + "】的【" + poks[current_pok].pokemon.name + "】睡着了！");
            return false;
        }

    }
    else if (bingdong > 0)
    {
        if (bingdong == 1)
        {
            bingdong = 0;
            res = true;
        }
        else
        {
            int r = qrand() % bingdong;
            if (r == 1)
            {
                bingdong = 0;
                res = true;
            }
            else
            {
                --bingdong;
                res = false;
            }
        }
        if (res)
        {
            log("【" +name + "】的【" + poks[current_pok].pokemon.name + "】醒来了！");
            return true;
        }
        else
        {
            log("【" +name + "】的【" + poks[current_pok].pokemon.name + "】被冰冻了！");
            return false;
        }
    }


    return true;


}
