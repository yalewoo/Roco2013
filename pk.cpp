#include "pk.h"
#include "ui_pk.h"

#include <QMovie>

#include <qglobal.h>
#include <QTime>
#include <QDebug>
#include<QScrollBar>

Pk::Pk(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Pk), team1(parent), team2(parent)
{
    ui->setupUi(this);

    team1.name = "你";
    team2.name = "电脑";

    connect(&team1, SIGNAL(addlog(QString)), this, SLOT(log(QString)));
    connect(&team2, SIGNAL(addlog(QString)), this, SLOT(log(QString)));

}

Pk::~Pk()
{
    delete ui;
}



void Pk::initTeam()
{
    team1.init(GlobalVar::pokes);
    team2.init(GlobalVar::pokes);

    display();

    QVector<Pokemon> &pokemons_all = * GlobalVar::pokemons_all;

    log("【" + team1.name + "】召唤了【" + pokemons_all.at(team1.poks.at(0).pokemon.id).name + "】" );
    log("【" + team2.name + "】召唤了【" + pokemons_all.at(team2.poks.at(0).pokemon.id).name + "】" );
}

void Pk::display()
{
    updatepoks_all(team1);
    updateSkills(team1);

    updatepok();

    ui->huihe->setText(QString::number(huihe));
}
void Pk::log(QString log)
{
    logs += log + "\r\n";
    qDebug() << "here:" << log;
    ui->log->setText(logs);

    ui->log->verticalScrollBar()->setValue(ui->log->verticalScrollBar()->maximum());
}

//更换队伍界面更新
void Pk::updatepoks_all(Team & team)
{
    QVector<Pok> & pokes = team.poks;

    ui->poks->reset();
    ui->poks->clear();

    ui->poks->setViewMode(QListView::IconMode);

    ui->poks->setIconSize(QSize(80,80));

    for (int i = 0; i < pokes.size(); ++i)
    {
        QString text = pokes.at(i).pokemon.name;
        QString file;
        int id = pokes.at(i).pokemon.id;
        file.sprintf("F:/Project/Roco/Pic/gif/%d.gif", id);

        QListWidgetItem* l = new QListWidgetItem(QIcon(file), text, ui->poks);
        l->setSizeHint(QSize(105, 105));

        ui->poks->insertItem(i+1, l);
    }

}


void Pk::updateSkills(Team & team)
{
    QVector<Pok> & pokes = team.poks;

    int id = pokes[team.current_pok].pokemon.id;


    QVector<Skill> *skills_all = GlobalVar::skills_all;

    QPushButton * qpb[4] = {ui->skill1, ui->skill2, ui->skill3, ui->skill4};

    for (int row = 0; row < 4; ++row)
    {
        int t1 = pokes[team.current_pok].pokemon.skills[row].first;
        int t2 = pokes[team.current_pok].pokemon.skills[row].second;
        Skill & sk = skills_all[t1][t2];
        //qDebug() << row << "\n";
        QString text = sk.name;

        QString tmp;

        static QString idtoPri[17] = {"普","冰","草","虫","电","毒","恶","火","龙","萌","石","水","土","武","械","翼","幽"};
        text = text + " " + idtoPri[sk.attr];

        tmp.sprintf("(%d/%d)\n",pokes[team.current_pok].pp[row], sk.pp);
        text += tmp;

        static QString attr[3] = {"变化","物理","魔法"};
        text = text + attr[sk.attack_type];
        tmp.sprintf(" 威力:%d\n", sk.power);
        text += tmp;

        text += sk.description;

        qpb[row]->setText(text);
    }


}

void Pk::updatepok()
{
    updatepok1();
    updatepok2();
}

void Pk::updatepok1()
{
    Pok & pok = team1.poks[team1.current_pok];
    int id = pok.pokemon.id;

    static QString idtoPri[17] = {"普","冰","草","虫","电","毒","恶","火","龙","萌","石","水","土","武","械","翼","幽"};

    QVector<Pokemon> &pokemons_all = * GlobalVar::pokemons_all;

    ui->name->setText(pokemons_all.at(id).name);
    ui->attr->setText(idtoPri[pokemons_all.at(id).attr]);
    if (pokemons_all.at(id).attr2 != -1)
        ui->attr2->setText(idtoPri[pokemons_all.at(id).attr2]);
    else
        ui->attr2->setText("");

    //宠物图片
    QString file;
    file.sprintf("F:/Project/Roco/Pic/gif/%d.gif", id);
    QMovie *movie = new QMovie(file);
    movie->setScaledSize(ui->poke_img->size());
    ui->poke_img->setMovie(movie);
    movie->start();

    QString text;
    text.sprintf("%d/%d", pok.hp, pok.hp_max);
    ui->hp->setText(text);
}
void Pk::updatepok2()
{
    Pok & pok = team2.poks[team2.current_pok];
    int id = pok.pokemon.id;

    static QString idtoPri[17] = {"普","冰","草","虫","电","毒","恶","火","龙","萌","石","水","土","武","械","翼","幽"};

    QVector<Pokemon> &pokemons_all = * GlobalVar::pokemons_all;

    ui->name_2->setText(pokemons_all.at(id).name);
    ui->attr_2->setText(idtoPri[pokemons_all.at(id).attr]);
    if (pokemons_all.at(id).attr2 != -1)
        ui->attr2_2->setText(idtoPri[pokemons_all.at(id).attr2]);
    else
        ui->attr2_2->setText("");

    //宠物图片
    QString file;
    file.sprintf("F:/Project/Roco/Pic/gif/%d.gif", id);
    QMovie *movie = new QMovie(file);
    movie->setScaledSize(ui->poke_img_2->size());
    ui->poke_img_2->setMovie(movie);
    movie->start();

    QString text;
    text.sprintf("%d/%d", pok.hp, pok.hp_max);
    ui->hp_2->setText(text);
}

void Pk::skill_clicked(int i)
{
    choose1 = i;
    choose2 = computer_ai();

    int speed1 = calcSpeed(team1, choose1);
    int speed2 = calcSpeed(team2, choose2);

    if (speed1 == speed2)
    {
        qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
        while (speed1 == speed2)
        {
            speed1 = qrand();
            speed2 = qrand();
        }
    }

    qDebug() <<speed1 << " " << speed2<<endl;

    log("回合" + QString::number(huihe) + ":");
    if (speed1 > speed2)
    {
        team1.attack(choose1, team2);
        team2.attack(choose2, team1);
    }
    else
    {
        team2.attack(choose2, team1);
        team1.attack(choose1, team2);
    }
    ++huihe;

    display();
}
int Pk::calcSpeed(Team & team, int n)
{
    int speed;
    QVector<Pok> & pokes = team.poks;
    Pok & pok = pokes[team.current_pok];
    int id = pokes[team.current_pok].pokemon.id;

    speed = pok.speed;
    int rank = pok.speed_rank;
    if (rank >= 0)
        speed = speed * ((rank) * 0.5 + 1);
    else
    {
        speed = speed / ((-1.0 * rank) * 0.5 + 1);
    }

    if (n >= 10)
    {
        //换宠物

    }
    else
    {
        QVector<Skill> *skills_all = GlobalVar::skills_all;

        int t1 = pok.pokemon.skills[n].first;
        int t2 = pok.pokemon.skills[n].second;
        Skill & sk = skills_all[t1][t2];
        //qDebug() << row << "\n";
        int r = sk.speed;
        speed = 10000*r + speed;
    }

    return speed;
}

void Pk::on_skill1_clicked()
{
    skill_clicked(0);
}
void Pk::on_skill2_clicked()
{
    skill_clicked(1);
}
void Pk::on_skill3_clicked()
{
    skill_clicked(2);
}
void Pk::on_skill4_clicked()
{
    skill_clicked(3);
}

void Pk::on_pushButton_clicked()
{
    int row = ui->poks->currentRow();
    if (row < 0 || row >= 6)
        return;
    skill_clicked(10+row);
}

int Pk::computer_ai()
{
    return 0;
}
