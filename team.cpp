#include "team.h"

#include <QTime>
#include <QtGlobal>
#include <QDebug>

#include <QTextEdit>
#include<QScrollBar>

#include <QEventLoop>
#include <QCoreApplication>

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

Team::Team(QWidget *parent, QString &log)  :  QWidget(parent), logs(log)
{
    poke_skills = GlobalVar::poke_skills;
}
Team::~Team()
{

}

void Team::log(QString log)
{
    //QString logs = textedit_logs->toPlainText();
    logs += log + "\r\n";
    //qDebug() << "here:" << log;

    textedit_logs->setText(logs);

    textedit_logs->verticalScrollBar()->setValue(textedit_logs->verticalScrollBar()->maximum());

    emit updatePK();

    delay(1000);
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

void Team::logofKezhi(double res)
{
    if (res > 2.9 && res < 3.1)
        log("双重克制了对面！");
    else if (res > 1.9 && res < 2.1)
        log("克制了对面！");
    else if (res > 0.9 && res < 1.1)
        ;
    else if (res > 0.4 && res < 0.6)
        log("被抵抗了！");
    else if (res < 0.4 && res > 0.2)
        log("被双重抵抗了");

}

void Team::delay(int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() <dieTime )
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
AttackData attack(QPair<int,int> skill, Team & enemy, AttackData res = 0)
{

}

AttackData Team::attack(int skill_id, Team & enemy, AttackData last)
{

    res.clear();


    if (skill_id >= 100 && skill_id <= 200)
    {
        //换宠物
        int new_id = skill_id % 10;
        current_pok = new_id;
        log("【" + name + "】换上了【" + this->poks[new_id].pokemon.name + "】");
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
            skill1(pok, sk, enemy, last);

        }
        else if (t1 == 2)
        {
            skill2(pok, sk, enemy, last);

        }
        else if (t1 == 3)
        {
            skill3(skill_id, pok, sk, enemy, last);

        }
        else if (t1 == 4)
        {
            skill4(pok, sk, enemy, last);
        }
        else if (t1 == 5)
        {
            skill5(pok, sk, enemy, last);
        }
        else if (t1 == 6)
        {
            skill6(skill_id, pok, sk, enemy, last);
        }
        else if (t1 == 7)
        {
            skill7(pok, sk, enemy, last);
        }
        else if (t1 == 8)
        {
            skill8(pok, sk, enemy, last);
        }
        else if (t1 == 9)
        {
            skill9(pok, sk, enemy, last);
        }
        else
        {
            skill10(pok, sk, enemy, last);
        }
    }

    int enemy_hp = enemy.poks[enemy.current_pok].hp;
    if (enemy_hp <= 0)
    {
        enemy.poks[enemy.current_pok].hp = 0;
        log("【" +enemy.name + "】的【" + enemy.poks[enemy.current_pok].pokemon.name + "】被击败了！");
    }
    if (poks[current_pok].hp <= 0)
    {
        poks[current_pok].hp = 0;
        log("【" + name + "】的【" + poks[current_pok].pokemon.name + "】被击败了！");
    }
    res.hp_release = enemy_hp;



    return res;



}


void Team::skill1(Pok &pok, Skill & sk, Team & enemy, AttackData & xianshou)
{
    Pok & enemy_pok = enemy.poks[enemy.current_pok];

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



    if (ifProb(sk.prob) && !xianshou.kongju || sk.prob > 1.8)
    {
        double power = sk.power;

        //伤害＝{ [（攻方宠物等级×0.4＋2）×攻击技能威力×攻方的攻击（魔攻）/守方的防御（魔防）/50＋2]（下舍入）×相克修正×（80%到100%之间随机数）}（下舍入）
        int damage = 0;

        if (sk.attack_type == 0)
        {
            damage += sk.damage_hard_cap;
            damage += sk.damage_percent * enemy_pok.hp_max;
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

            damage += sk.damage_hard_cap;
            damage += sk.damage_percent * enemy_pok.hp_max;

            //属性克制
            double xishu;
            if (enemy_pok.pokemon.attr2 == -1)
            {
                xishu = aioi[sk.attr][enemy_pok.pokemon.attr];
            }
            else
            {
                xishu = aioi[sk.attr][enemy_pok.pokemon.attr] * aioi[sk.attr][enemy_pok.pokemon.attr2];
                if (xishu > 3)
                    xishu = 3;
                else if (xishu < 0.4)
                    xishu = 1/3.0;
            }
            logofKezhi(xishu);
            damage *= xishu;

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
        if (sk.fandan > 0)
        {
            int self_damage = damage * sk.fandan;
            pok.hp -= self_damage;
            log("【" + name + "】的【" + pok.pokemon.name + "】受到了反弹【" + QString::number(self_damage) + "】点伤害！");
        }
        res.damage = damage;

        if (enemy.sleep > 0 && sk.power > 1)
        {
            enemy.sleep = 0;
            log("【" +enemy.name + "】的【" + enemy.poks[enemy.current_pok].pokemon.name + "】醒来了！");
        }

    }
    else
    {
        log("可惜miss了！");
        res.miss = true;
        res.damage = 0;
    }

    return;
}
void Team::skill2(Pok &pok, Skill & sk, Team & enemy, AttackData & xianshou)
{
    Pok & enemy_pok = enemy.poks[enemy.current_pok];


    if ( sk.prob > 1.8 || !xianshou.kongju && ifProb(sk.prob))
    {
        if (sk.self_adp > 0)
        {
            pok.ad_rank += sk.self_adp;
            log("【" + name + "】的【" + pok.pokemon.name + "】的【攻击】提升了【" + QString::number(sk.self_adp) + "】级");
        }
        if (sk.self_ddp > 0)
        {
            pok.dd_rank += sk.self_ddp;
            log("【" + name + "】的【" + pok.pokemon.name + "】的【物抗】提升了【" + QString::number(sk.self_ddp) + "】级");
        }
        if (sk.self_app > 0)
        {
            pok.ap_rank += sk.self_app;
            log("【" + name + "】的【" + pok.pokemon.name + "】的【魔攻】提升了【" + QString::number(sk.self_app) + "】级");
        }
        if (sk.self_dpp > 0)
        {
            pok.dp_rank += sk.self_dpp;
            log("【" + name + "】的【" + pok.pokemon.name + "】的【魔抗】提升了【" + QString::number(sk.self_dpp) + "】级");
        }
        if (sk.self_speedp > 0)
        {
            pok.speed_rank += sk.self_speedp;
            log("【" + name + "】的【" + pok.pokemon.name + "】的【速度】提升了【" + QString::number(sk.self_speedp) + "】级");
        }
    }
    else
    {
        log("可惜miss了！");
        res.miss = true;
    }
    return;
}
void Team::skill3(int skill_id, Pok &pok, Skill & sk, Team & enemy, AttackData & xianshou)
{

    Pok & enemy_pok = enemy.poks[enemy.current_pok];


    if ( sk.prob > 1.8 || !xianshou.kongju && ifProb(sk.prob))
    {
        int huihe;
        if (sk.self_max_time == sk.self_min_time)
            huihe = sk.self_max_time;
        else
        {
            huihe = qrand() % (sk.self_max_time - sk.self_min_time) + sk.self_min_time;
        }

        if (sk.self_status == "清醒")
        {
            pok.qingxing = huihe;
        }
        else if (sk.self_status == "守护之力")
        {
            pok.shouhuzhili = huihe;
        }
        else if (sk.self_status == "加血")
        {
            pok.add_hp = huihe;
            pok.add_hp_value = sk.self_value;
        }
        else if (sk.self_status == "减伤")
        {
            pok.damage_xishou = huihe;
            pok.damage_xishou_value = sk.self_value;
        }
        else if (sk.self_status == "冰天雪地")
        {
            pok.bingtianxuedi = huihe;
        }
        else if (sk.self_status == "大地宽恕")
        {
            pok.dadikuanshu = huihe;
        }
        else if (sk.self_status == "物盾")
        {
            pok.wudun = huihe;
        }
        else if (sk.self_status == "继续使用")
        {
            if (should_use)
            {
                --should_use_huihe;
                if (should_use_huihe == 0)
                    should_use = false;
            }
            else
            {
                should_use = true;
                should_use_huihe = huihe;
                should_use_id = skill_id;
            }
        }
    }
    else
    {
        log("可惜miss了！");
        res.miss = true;
    }
    return;
}
void Team::skill4(Pok &pok, Skill & sk, Team & enemy, AttackData & xianshou)
{
    Pok & enemy_pok = enemy.poks[enemy.current_pok];


    if ( sk.prob > 1.8 || !xianshou.kongju && ifProb(sk.prob))
    {
        int huihe;
        if (sk.self_max_time == sk.self_min_time)
            huihe = sk.self_max_time;
        else
        {
            huihe = qrand() % (sk.self_max_time - sk.self_min_time) + sk.self_min_time;
        }
        qDebug() << "回合数：" << huihe << endl;

        if (enemy_pok.shouhuzhili > 0)
        {
            log("受到【守护之力】的化解！");
            return;
        }


        if (sk.enemy_status == "睡眠")
        {
            if (enemy_pok.qingxing > 0)
            {
                log("受到【清醒】的化解！");
                return;
            }
            if (enemy.sleep == 0)
            {
                enemy.sleep = huihe;
                res.cuimian = true;
                log("【" +enemy.name + "】的【" + enemy_pok.pokemon.name + "】睡着了！");
            }
            if (sk.name == "生命火焰")
            {
                pok.hp = 0;
            }

        }
        else if (sk.enemy_status == "冰冻")
        {
            enemy.bingdong = huihe;
            res.bingdong = true;
            log("【" +enemy.name + "】的【" + enemy_pok.pokemon.name + "】被冰冻了！");
        }
        else if (sk.enemy_status == "寄生")
        {
            enemy_pok.jisheng = 8;
            log("【" +enemy.name + "】的【" + enemy_pok.pokemon.name + "】被寄生了！");
        }
        else if (sk.enemy_status == "中毒")
        {
            enemy_pok.zhongdu = true;
            log("【" +enemy.name + "】的【" + enemy_pok.pokemon.name + "】中毒了！");
        }
        else if (sk.enemy_status == "中毒")
        {
            enemy_pok.judu = 1;
            log("【" +enemy.name + "】的【" + enemy_pok.pokemon.name + "】中剧毒了！");
        }
        else if (sk.enemy_status == "烧伤")
        {
            enemy_pok.shaoshang = true;
            log("【" +enemy.name + "】的【" + enemy_pok.pokemon.name + "】被烧伤了！");
        }
        else if (sk.enemy_status == "麻醉")
        {
            enemy_pok.mazui = true;
            log("【" +enemy.name + "】的【" + enemy_pok.pokemon.name + "】被麻醉了！");
        }
        else if (sk.enemy_status == "恐惧")
        {
            res.kongju = true;
            log("【" +enemy.name + "】的【" + enemy_pok.pokemon.name + "】恐惧了！");
        }


    }
    else
    {
        log("可惜" + sk.enemy_status + "效果miss了！");
        res.miss = true;
    }
    return;
}
void Team::skill5(Pok &pok, Skill & sk, Team & enemy, AttackData & xianshou)
{
    Pok & enemy_pok = enemy.poks[enemy.current_pok];


    if ( sk.prob > 1.8 || !xianshou.kongju && ifProb(sk.prob))
    {
        if (sk.enemy_adp != 0)
        {
            enemy_pok.ad_rank += sk.enemy_adp;
            log("【" + enemy.name + "】的【" + enemy_pok.pokemon.name + "】的【攻击】降低了【" + QString::number(sk.enemy_adp) + "】级");
        }
        if (sk.enemy_ddp != 0)
        {
            enemy_pok.dd_rank += sk.enemy_ddp;
            log("【" + enemy.name + "】的【" + enemy_pok.pokemon.name + "】的【物抗】降低了【" + QString::number(sk.enemy_ddp) + "】级");
        }
        if (sk.enemy_app != 0)
        {
            enemy_pok.ap_rank += sk.enemy_app;
            log("【" + enemy.name + "】的【" + enemy_pok.pokemon.name + "】的【魔攻】降低了【" + QString::number(sk.enemy_app) + "】级");
        }
        if (sk.enemy_dpp != 0)
        {
            enemy_pok.dp_rank += sk.enemy_dpp;
            log("【" + enemy.name + "】的【" + enemy_pok.pokemon.name + "】的【魔抗】降低了【" + QString::number(sk.enemy_dpp) + "】级");
        }
        if (sk.enemy_speedp != 0)
        {
            enemy_pok.speed_rank += sk.enemy_speedp;
            log("【" + enemy.name + "】的【" + enemy_pok.pokemon.name + "】的【速度】降低了【" + QString::number(sk.enemy_speedp) + "】级");
        }
    }
    else
    {
        log("可惜miss了！");
        res.miss = true;
    }
    return;
}void Team::skill6(int skill_id, Pok &pok, Skill & sk, Team & enemy, AttackData & xianshou)
{
    Pok & enemy_pok = enemy.poks[enemy.current_pok];



    skill1(pok, sk, enemy, xianshou);
    if (!res.miss)
        skill3(skill_id, pok, sk, enemy, xianshou);


    return;
}
void Team::skill7(Pok &pok, Skill & sk, Team & enemy, AttackData & xianshou)
{
    Pok & enemy_pok = enemy.poks[enemy.current_pok];



        skill1(pok, sk, enemy, xianshou);
        Skill sk2 = sk;
        sk2.prob = sk.prob2;
        if (!res.miss)
        {
            skill4(pok, sk2, enemy, xianshou);
        }


    return;
}
void Team::skill8(Pok &pok, Skill & sk, Team & enemy, AttackData & xianshou)
{
    Pok & enemy_pok = enemy.poks[enemy.current_pok];


    if (sk.qianghuafirst)
    {
        Skill sk2 = sk;
        sk2.prob = sk.prob2_self;
        skill2(pok, sk2, enemy, xianshou);
    }


        skill1(pok, sk, enemy, xianshou);
        if (!res.miss)
        {
            Skill sk2 = sk;
            sk2.prob = sk.prob2_self;
            skill2(pok, sk2, enemy, xianshou);
        }




    return;
}
void Team::skill9(Pok &pok, Skill & sk, Team & enemy, AttackData & xianshou)
{
    Pok & enemy_pok = enemy.poks[enemy.current_pok];



        skill1(pok, sk, enemy, xianshou);
        if (!res.miss)
        {
            Skill sk2 = sk;
            sk2.prob = sk.prob2;
            skill5(pok, sk2, enemy, xianshou);
        }



    return;
}
void Team::skill10(Pok &pok, Skill & sk, Team & enemy, AttackData & xianshou)
{
    Pok & enemy_pok = enemy.poks[enemy.current_pok];


    return;
}


void Team::init(QVector<Pokemon> *ppokes)
{
    poks.clear();

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


    bool res = true;
    if (sleep > 0)
    {
        res = false;
        if (sleep == 1)
        {
            sleep = 0;
        }
        else
        {
            int r = qrand() % sleep;
            if (r == 1)
            {
                sleep = 0;
            }
            else
            {
                --sleep;
            }
        }
        //qDebug() <<"sleep = " << sleep;

        if (sleep == 0)
        {
            log("【" +name + "】的【" + poks[current_pok].pokemon.name + "】醒来了！");
        }
        else
        {
            log("【" +name + "】的【" + poks[current_pok].pokemon.name + "】睡着了！");
        }

    }
    else if (bingdong > 0)
    {
        res = false;
        if (bingdong == 1)
        {
            bingdong = 0;
        }
        else
        {
            int r = qrand() % bingdong;
            if (r == 1)
            {
                bingdong = 0;
            }
            else
            {
                --bingdong;
            }
        }
        if (bingdong == 0)
        {
            log("【" +name + "】的【" + poks[current_pok].pokemon.name + "】醒来了！");
        }
        else
        {
            log("【" +name + "】的【" + poks[current_pok].pokemon.name + "】被冰冻了！");
        }
    }


    return res;


}

void Team::consume(Team &team, AttackData & res)
{


    Team &enemy = team;
    static QString idtoPri[17] = {"普","冰","草","虫","电","毒","恶","火","龙","萌","石","水","土","武","械","翼","幽"};
    Pok & pok = poks[current_pok];
    if (pok.dadikuanshu > 0)
    {
        --pok.dadikuanshu;
        res.kongju = true;
    }

    Pok & enemy_pok = team.poks[team.current_pok];

    if (pok.bingtianxuedi > 0)
    {
        --pok.bingtianxuedi;
        int damage = enemy_pok.hp_max / 6 * getrand80100();
        enemy_pok.hp -= damage;


        log("【" + name + "】的【" + pok.pokemon.name + "】的冰天雪地生效了！");
        if (idtoPri[enemy_pok.pokemon.attr] == "冰" || enemy_pok.pokemon.attr2 != -1 && idtoPri[enemy_pok.pokemon.attr2] == "冰")
        {
            log("冰天雪地miss了!");
        }
        else
        {
            log("对【" + enemy.name + "】的【" + enemy_pok.pokemon.name + "】造成了" + QString::number(damage) + "点伤害");
        }
    }
    if (enemy_pok.jisheng > 0)
    {
        --enemy_pok.jisheng;
        int damage = enemy_pok.hp_max / 8;
        enemy_pok.hp -= damage;
        pok.hp += damage;
        if (pok.hp > pok.hp_max)
            pok.hp = pok.hp_max;

        log("【" + enemy.name + "】的【" + enemy_pok.pokemon.name + "】被寄生造成伤害【" + QString::number(damage) +"】点");
    }
    if (enemy_pok.zhongdu)
    {
        int damage = enemy_pok.hp_max / 8;
        enemy_pok.hp -= damage;

        log("【" + enemy.name + "】的【" + enemy_pok.pokemon.name + "】中毒造成伤害【" + QString::number(damage) +"】点");
    }
    if (enemy_pok.judu)
    {
        int damage = enemy_pok.hp_max / 8;
        damage *= enemy_pok.judu;
        enemy_pok.judu++;
        enemy_pok.hp -= damage;

        log("【" + enemy.name + "】的【" + enemy_pok.pokemon.name + "】剧毒造成伤害【" + QString::number(damage) +"】点");
    }

    if (enemy_pok.hp < 0)
        enemy_pok.hp = 0;
}
