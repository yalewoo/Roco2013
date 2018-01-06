#include "pk.h"
#include "ui_pk.h"

#include <QMovie>

#include <qglobal.h>
#include <QTime>
#include <QDebug>
#include<QScrollBar>
#include <QTcpSocket>


Pk::Pk(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Pk), team1(parent, logs), team2(parent, logs)
{
    ui->setupUi(this);

    team1.name = "你";
    team2.name = "电脑";

    team1.textedit_logs = ui->log;
    team2.textedit_logs = ui->log;


    connect(&team1, SIGNAL(updatePK()), this, SLOT(display()));
    connect(&team2, SIGNAL(updatePK()), this, SLOT(display()));


    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    ui->tabWidget->setCurrentIndex(0);

    connect(ui->log, SIGNAL(textChanged()), this, SLOT(update()));
}

Pk::~Pk()
{
    delete ui;
}



void Pk::initTeam()
{
    logs.clear();
    huihe = 1;

    dead1 = false;
    dead2 = false;

    team1.init(GlobalVar::pokes);
    team2.init(GlobalVar::pokes);

    display();

    QVector<Pokemon> &pokemons_all = * GlobalVar::pokemons_all;

    log("【" + team1.name + "】召唤了【" + pokemons_all.at(team1.poks.at(0).pokemon.id).name + "】" );
    log("【" + team2.name + "】召唤了【" + pokemons_all.at(team2.poks.at(0).pokemon.id).name + "】" );
}

void Pk::delay(int time)
{
    QTime _Timer = QTime::currentTime();
    QTime _NowTimer;
    do{
        _NowTimer=QTime::currentTime();
    }while (_Timer.msecsTo(_NowTimer)<=time);
}

void Pk::display()
{
    updatepoks_all(team1);
    updateSkills(team1);

    updatepok();

    ui->huihe->setText(QString::number(huihe));

    updateStatus();


}
void Pk::log(QString log)
{
    logs += log + "\r\n";
    //qDebug() << "here:" << log;

    ui->log->setText(logs);

    ui->log->verticalScrollBar()->setValue(ui->log->verticalScrollBar()->maximum());

}
void Pk::updateStatus()
{
    ui->status->setText(getStatus(team1));
    ui->status_2->setText(getStatus(team2));
}
QString Pk::getStatus(Team & team)
{
    QString res;
    Pok & pok = team.poks[team.current_pok];
    if (team.sleep > 0)
        res += "睡眠 ";
    if (team.bingdong > 0)
        res += "冰冻 ";

    if (pok.jisheng > 0)
        res += "寄生 ";
    if (pok.judu > 0)
        res += "剧毒 ";
    if (pok.zhongdu > 0)
        res += "中毒 ";

    res += "\n";

    if (pok.ad_rank != 0)
        res += "攻击" + QString::number(pok.ad_rank) + " ";
    if (pok.dd_rank != 0)
        res += "物抗" + QString::number(pok.dd_rank) + " ";
    if (pok.ap_rank != 0)
        res += "魔攻" + QString::number(pok.ap_rank) + " ";
    if (pok.dp_rank != 0)
        res += "魔抗" + QString::number(pok.dp_rank) + " ";
    if (pok.speed_rank != 0)
        res += "速度" + QString::number(pok.speed_rank) + " ";

    return res;
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




    QVector<Skill> *skills_all = GlobalVar::skills_all;

    QPushButton * qpb[4] = {ui->skill1, ui->skill2, ui->skill3, ui->skill4};

    for (int row = 0; row < pokes[team.current_pok].pokemon.skills.size(); ++row)
    {
        int t1 = pokes[team.current_pok].pokemon.skills[row].first;
        int t2 = pokes[team.current_pok].pokemon.skills[row].second;
        Skill & sk = skills_all[t1][t2];
        //qDebug() << row << "\n";
        QString text = sk.name;

        QString tmp;

        static QString idtoPri[17] = {"普","冰","草","虫","电","毒","恶","火","龙","萌","石","水","土","武","械","翼","幽"};
        text = text + " " + idtoPri[sk.attr];

        int current_pp = pokes[team.current_pok].pp[row];
        tmp.sprintf("(%d/%d)\n",current_pp, sk.pp);


        if (pokes[team.current_pok].hp == 0 || current_pp == 0)
            qpb[row]->setEnabled(false);
        else
            qpb[row]->setEnabled(true);



        text += tmp;

        static QString attr[3] = {"变化","物理","魔法"};
        text = text + attr[sk.attack_type];
        tmp.sprintf(" 威力:%.0lf\n", sk.power);
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

    ui->hp_bar->setMaximum(pok.hp_max);
    ui->hp_bar->setValue(pok.hp);
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

    ui->hp_2_bar->setMaximum(pok.hp_max);
    ui->hp_2_bar->setValue(pok.hp);
}

void Pk::skill_clicked(int i)
{
    ui->skill1->setEnabled(false);
    ui->skill2->setEnabled(false);
    ui->skill3->setEnabled(false);
    ui->skill4->setEnabled(false);
    display();

    choose1 = i;
    choose2 = computer_ai(team2);

    if (dead1)
    {
        dead1 = false;
        team1.attack(choose1, team2);
        ++huihe;

        display();
    }


    int speed1 = calcSpeed(team1, choose1);
    int speed2 = calcSpeed(team2, choose2);

    if (speed1 == speed2)
    {

        while (speed1 == speed2)
        {
            speed1 = qrand();
            speed2 = qrand();
        }
    }

    //qDebug() <<speed1 << " " << speed2<<endl;

    log("回合" + QString::number(huihe) + ":");
    AttackData res;
    if (speed1 > speed2)
    {
        if (team1.selfStatus())
        {
            res = team1.attack(choose1, team2);
            team1.consume(team2, res);

            if (team2.poks[team2.current_pok].hp > 0 && !res.cuimian && !res.bingdong)
            {
                if (team2.selfStatus())
                {
                    team2.attack(choose2, team1, res);
                    team2.consume(team1, res);
                }
            }

        }
        else
        {
            if (team2.selfStatus())
            {
                team2.attack(choose2, team1);
                team2.consume(team1, res);
            }
        }

    }
    else
    {
        if (team2.selfStatus())
        {
            res = team2.attack(choose2, team1);
            team2.consume(team1, res);

            if (team1.poks[team1.current_pok].hp > 0 && !res.cuimian && !res.bingdong)
            {
                if (team1.selfStatus())
                {
                    team1.attack(choose1, team2, res);
                    team1.consume(team2, res);
                }
            }

        }
        else
        {
            if (team1.selfStatus())
            {
                team1.attack(choose1, team2);
                team1.consume(team2, res);
            }
        }
    }

    if (team2.poks.at(team2.current_pok).hp <= 0)
    {
        dead2 = true;
    }
    if (team1.poks.at(team1.current_pok).hp <= 0)
    {
        dead1 = true;
    }


    if (dead2)
    {
        choose2 = computer_ai(team2);
        if (choose2 != 888888)
        {
            dead2 = false;
            team2.attack(choose2, team1);
        }

    }



    ++huihe;

    display();
    ui->skill1->setEnabled(true);
    ui->skill2->setEnabled(true);
    ui->skill3->setEnabled(true);
    ui->skill4->setEnabled(true);
}
int Pk::calcSpeed(Team & team, int n)
{
    int speed;
    QVector<Pok> & pokes = team.poks;
    Pok & pok = pokes[team.current_pok];


    speed = pok.speed;
    int rank = pok.speed_rank;
    if (rank >= 0)
        speed = speed * ((rank) * 0.5 + 1);
    else
    {
        speed = speed / ((-1.0 * rank) * 0.5 + 1);
    }

    if (n >= 100)
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

//换宠物
void Pk::on_pushButton_clicked()
{
    ui->tabWidget->setCurrentIndex(0);

    int row = ui->poks->currentRow();
    if (row < 0 || row >= 6)
        return;
    skill_clicked(100+row);
}

int Pk::computer_ai(Team & team)
{
    bool use_computer = false;
    if (use_computer)
    {
        Pok & pok = team.poks[team.current_pok];

        if (pok.hp != 0)
            return qrand() % pok.pokemon.skills.size();
        else
        {
            QVector<int> can;
            int count = 0;
            for (int i = 0; i < team.poks.size(); ++i)
            {
                if (team.poks.at(i).hp > 0)
                {
                    can.push_back(i);
                }
            }
            int r = qrand() % can.size();
            if (can.size() > 0)
                return can[r] + 100;
            else
            {
                log("你胜利了！");
                return 888888;
            }
        }
    }
    else
    {
        Pok & pok = team.poks[team.current_pok];
        QString send;
        if (pok.hp != 0)
        {
             send = "skill";
        }
        else
        {
             send = "change";
        }


        client->socket->write(send.toLatin1());
        client->socket->flush();

        QByteArray buffer;
        client->socket->waitForReadyRead();
        buffer = client->socket->readAll();
        QString str;
        if (!buffer.isEmpty())
        {
            str = buffer;
        }

        qDebug() << "socket receive : " << str;

        return str.toInt();
    }

}
