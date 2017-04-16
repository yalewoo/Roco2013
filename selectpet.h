#ifndef SELECTPET_H
#define SELECTPET_H

#include <QWidget>

#include <QVector>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>
#include <QMap>

#include "pokemon.h"
#include "skill.h"

#include "globalvar.h"

namespace Ui {
class SelectPet;
}



class SelectPet : public QWidget
{
    Q_OBJECT

public:
    explicit SelectPet(QWidget *parent = 0);
    ~SelectPet();

private slots:
    void on_ok_clicked();

    void xingge_clicked(int index);

    void updatedataWhenChangePok(); //更新所有
    void updatedata();  //更新宠物自身属性
    void updatedata2(int row); //使用用户选的6个宠物之一来更新属性面板
    void updatepoks();

    void updateSkillsselected();

    void displaySkillInfo(int row);
    void selectAPoke(int row);



    void on_insert_clicked();

    void on_add_skill_clicked();

    void on_del_skill_clicked();

    void on_modify_clicked();

    void on_delete_poke_clicked();

    void on_save_clicked();


    void on_load_clicked();
    void load(QString path);

    void on_start_clicked();

signals:
    void startGame();

private:
    Ui::SelectPet *ui;

    QVector<Pokemon> pokemons_all; //记录所有宠物基础信息
    QVector<Skill> skills_all[16];  //记录所有技能 分为10类 下标16多余了6

    QMap<QString, int> skilltoid1;
    QMap<QString, int> skilltoid2;

    QVector<QPair<int,int> > poke_skills[2048]; //记录每个宠物的所有技能

    QVector<int> pokes_have_skills; //拥有可选技能的宠物id

    QVector<Pokemon> pokes;  //用户选的宠物，最多6只

    QVector<QPair<int,int> > skills_selected;    //已选择的技能



    Pokemon getPokemon(int id);
};

#endif // SELECTPET_H
