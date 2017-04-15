#include "selectpet.h"
#include "ui_selectpet.h"

#include <QMovie>
#include <QFileDialog>

int convertPri(QString s)
{
    if (s == "普") return 0;
    if (s == "冰") return 1;
    if (s == "草") return 2;
    if (s == "虫") return 3;
    if (s == "电") return 4;
    if (s == "毒") return 5;
    if (s == "恶") return 6;
    if (s == "火") return 7;
    if (s == "龙") return 8;
    if (s == "萌") return 9;
    if (s == "石") return 10;
    if (s == "水") return 11;
    if (s == "土") return 12;
    if (s == "武") return 13;
    if (s == "械") return 14;
    if (s == "翼") return 15;
    if (s == "幽") return 16;
}

int xingge_idid2id(int t1, int t2)
{
    static QString xgtable[6][6] = {
    {"平衡","孤僻","固执","调皮","勇敢","平衡"},
    {"大胆","平衡","淘气","无虑","悠闲","平衡"},
    {"保守","稳重","平衡","马虎","冷静","平衡"},
    {"沉着","温顺","慎重","平衡","狂妄","平衡"},
    {"胆小","急躁","开朗","天真","平衡","平衡"},
    {"平衡","平衡","平衡","平衡","平衡","平衡"}};

    static QMap<QString, int> xgtoint;
    xgtoint["平衡"] = 0;
    xgtoint["固执"] = 1;
    xgtoint["孤僻"] = 2;
    xgtoint["调皮"] = 3;
    xgtoint["勇敢"] = 4;
    xgtoint["保守"] = 5;
    xgtoint["稳重"] = 6;
    xgtoint["马虎"] = 7;
    xgtoint["冷静"] = 8;
    xgtoint["胆小"] = 9;
    xgtoint["开朗"] = 10;
    xgtoint["急躁"] = 11;
    xgtoint["天真"] = 12;
    xgtoint["大胆"] = 13;
    xgtoint["淘气"] = 14;
    xgtoint["悠闲"] = 15;
    xgtoint["无虑"] = 16;
    xgtoint["沉着"] = 17;
    xgtoint["慎重"] = 18;
    xgtoint["狂妄"] = 19;
    xgtoint["温顺"] = 20;

    return xgtoint[xgtable[t1][t2]];
}
QPair<int,int> xingge_idtoidid(int id)
{
    static QString xgtable[6][6] = {
    {"平衡","孤僻","固执","调皮","勇敢","平衡"},
    {"大胆","平衡","淘气","无虑","悠闲","平衡"},
    {"保守","稳重","平衡","马虎","冷静","平衡"},
    {"沉着","温顺","慎重","平衡","狂妄","平衡"},
    {"胆小","急躁","开朗","天真","平衡","平衡"},
    {"平衡","平衡","平衡","平衡","平衡","平衡"}};

    static QMap<QString, int> xgtoint;
    xgtoint["平衡"] = 0;
    xgtoint["固执"] = 1;
    xgtoint["孤僻"] = 2;
    xgtoint["调皮"] = 3;
    xgtoint["勇敢"] = 4;
    xgtoint["保守"] = 5;
    xgtoint["稳重"] = 6;
    xgtoint["马虎"] = 7;
    xgtoint["冷静"] = 8;
    xgtoint["胆小"] = 9;
    xgtoint["开朗"] = 10;
    xgtoint["急躁"] = 11;
    xgtoint["天真"] = 12;
    xgtoint["大胆"] = 13;
    xgtoint["淘气"] = 14;
    xgtoint["悠闲"] = 15;
    xgtoint["无虑"] = 16;
    xgtoint["沉着"] = 17;
    xgtoint["慎重"] = 18;
    xgtoint["狂妄"] = 19;
    xgtoint["温顺"] = 20;

    QString xgtable2[21] = {"平衡", "固执", "孤僻", "调皮", "勇敢", "保守", "稳重", "马虎", "冷静", "胆小", "开朗", "急躁", "天真", "大胆", "淘气", "悠闲", "无虑", "沉着", "慎重", "狂妄", "温顺"};
    QPair<int,int> r;
    QString xg = xgtable2[id];
    if (xg == "平衡")
    {
        r.first = 5;
        r.second = 5;
        return r;
    }

    int i, j;
    for (i = 0; i < 5; ++i)
    {
        for (j = 0; j < 5; ++j)
        {
            if (xg == xgtable[i][j])
            {
                r.first = i;
                r.second = j;
                return r;
            }
        }
    }

    return r;
}


SelectPet::SelectPet(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectPet)
{
    ui->setupUi(this);

    Pokemon pet(0);
    pokes.push_back(pet);
    for (int i = 1; i <= 10; ++i)
    {
        Skill s;
        skills[i].push_back(s);
    }

    QFile file("F:/Project/Roco/QtRoco/roco.csv");
    if(!file.open(QIODevice::ReadOnly))
         qDebug()<<"OPEN FILE FAILED";

    QTextStream * out = new QTextStream(&file);//文本流
    QString all = out->readAll();
    qDebug() << all;
    QStringList tempOption = all.split("\r\n");//每行以\n区分
    for(int i = 0 ; i < tempOption.count() ; i++)
    {
         QStringList pl = tempOption.at(i).split(",");//一行中的单元格以，区分
         Pokemon pet(pl.at(0).toInt());
         pet.name = pl.at(1);

         QStringList pri = pl.at(2).split(" ");
         pet.attr = convertPri(pri.at(0));
         if (pri.count() == 2)
             pet.attr2 = convertPri(pri.at(1));
         else
             pet.attr2 = -1;

         pet.hp = pl.at(4).toInt();
         pet.ad = pl.at(5).toInt();
         pet.dd = pl.at(6).toInt();
         pet.ap = pl.at(7).toInt();
         pet.dp = pl.at(8).toInt();
         pet.speed = pl.at(9).toInt();


         pokes.push_back(pet);


    }
    file.close();//操作完成后记得关闭文件



    QFile file2("F:/Project/Roco/skill.csv");
    if(!file2.open(QIODevice::ReadOnly))
         qDebug()<<"OPEN FILE FAILED";

    out = new QTextStream(&file2);//文本流
    all = out->readAll();
    qDebug() << all;
    tempOption = all.split("\r\n");//每行以\n区分
    for(int i = 1 ; i < tempOption.count() ; i++)
    {
        if (tempOption.at(i).isEmpty())
            continue;

         QStringList pl = tempOption.at(i).split(",");//一行中的单元格以，区分
         int type = pl.at(0).toInt();
         Skill ski(type);



         ski.attr = convertPri(pl.at(1));
         ski.id = pl.at(2).toInt();
        ski.name = pl.at(3);

        skilltoid1[ski.name] = type;
        skilltoid2[ski.name] = ski.id;

        ski.description = pl.at(4);

        ski.pp = pl.at(5).toInt();

        ski.attack_type = pl.at(6).toInt();

        ski.power = pl.at(7).toInt();

        ski.prob = pl.at(8).toDouble();

    ski.speed = pl.at(9).toInt();

    ski.special = pl.at(10).toInt() ? 1 : 0;

    ski.fandan = pl.at(11).toDouble();

        ski.self_adp = pl.at(12).toInt();
        ski.self_ddp = pl.at(13).toInt();
        ski.self_app = pl.at(14).toInt();
        ski.self_dpp = pl.at(15).toInt();
        ski.self_speedp = pl.at(16).toInt();

        ski.self_status = pl.at(17);

        QStringList huihe = pl.at(18).split("-");
        if (huihe.count() == 1)
        {
            ski.min_time = huihe.at(0).toInt();
        }
        else if (huihe.count() == 2)
        {
            ski.min_time = huihe.at(0).toInt();
            ski.max_time = huihe.at(1).toInt();
        }

        ski.value = pl.at(19).toDouble();

        ski.prob2 = pl.at(20).toDouble();

        ski.enemy_status = pl.at(21);

        QStringList hc = pl.at(22).split("-");
        if (hc.count() == 1)
        {
            ski.min_time = hc.at(0).toInt();
        }
        else if (hc.count() == 2)
        {
            ski.min_time = hc.at(0).toInt();
            ski.max_time = hc.at(1).toInt();
        }

        ski.enemy_adp = pl.at(23).toInt();
        ski.enemy_ddp = pl.at(24).toInt();
        ski.enemy_app = pl.at(25).toInt();
        ski.enemy_dpp = pl.at(26).toInt();
        ski.enemy_speedp = pl.at(27).toInt();

        ski.qianghuafirst = pl.at(28).toInt()?1:0;

        ski.self_cond = pl.at(29);
        ski.enemy_cond = pl.at(30);
        ski.prob2_self = pl.at(31).toDouble();



         skills[type].push_back(ski);


    }
    file2.close();//操作完成后记得关闭文件




    QFile file3("F:/Project/Roco/poke_skill.csv");
    if(!file3.open(QIODevice::ReadOnly))
         qDebug()<<"OPEN FILE FAILED";

    out = new QTextStream(&file3);//文本流
    all = out->readAll();
    qDebug() << all;
    tempOption = all.split("\r\n");//每行以\n区分
    for(int i = 0 ; i < tempOption.count() ; i++)
    {
        if (tempOption.at(i).isEmpty())
            continue;

         QStringList pl = tempOption.at(i).split(",");//一行中的单元格以，区分
         int id = pl.at(1).toInt();
         pokes_have_skills.push_back(id);
         for (int j = 2; j < pl.count(); ++j)
         {
             QStringList huihe = pl.at(j).split(".");
             QPair<int,int> qp;

             if (huihe.count() == 2)
             {
                 qp.first = huihe.at(0).toInt();
                 qp.second = huihe.at(1).toInt();
             }
             else
             {
                 qp.first = this->skilltoid1[huihe.at(0)];
                 qp.second = this->skilltoid2[huihe.at(0)];
             }
             poke_skills[id].push_back(qp);




         }



    }
    file3.close();//操作完成后记得关闭文件
    for (int i = 0; i < pokes_have_skills.size(); ++i)
    {
        QString text;
        text.sprintf("%d ", pokes_have_skills[i]);
        text += pokes[pokes_have_skills[i]].name;
        QListWidgetItem* l = new QListWidgetItem(text, ui->pokes);
        ui->skills->insertItem(i+1, l);
    }
    connect(ui->pokes, SIGNAL(currentRowChanged(int)), this, SLOT(selectAPoke(int)));










    connect(ui->adp, SIGNAL(clicked(bool)), this, SLOT(updatedata()));
    connect(ui->ddp, SIGNAL(clicked(bool)), this, SLOT(updatedata()));
    connect(ui->app, SIGNAL(clicked(bool)), this, SLOT(updatedata()));
    connect(ui->dpp, SIGNAL(clicked(bool)), this, SLOT(updatedata()));
    connect(ui->speedp, SIGNAL(clicked(bool)), this, SLOT(updatedata()));
    connect(ui->adm, SIGNAL(clicked(bool)), this, SLOT(updatedata()));
    connect(ui->ddm, SIGNAL(clicked(bool)), this, SLOT(updatedata()));
    connect(ui->apm, SIGNAL(clicked(bool)), this, SLOT(updatedata()));
    connect(ui->dpm, SIGNAL(clicked(bool)), this, SLOT(updatedata()));
    connect(ui->speedm, SIGNAL(clicked(bool)), this, SLOT(updatedata()));
    connect(ui->nom, SIGNAL(clicked(bool)), this, SLOT(updatedata()));

    connect(ui->hp2, SIGNAL(valueChanged(int)), this, SLOT(updatedata()));
    connect(ui->ad2, SIGNAL(valueChanged(int)), this, SLOT(updatedata()));
    connect(ui->dd2, SIGNAL(valueChanged(int)), this, SLOT(updatedata()));
    connect(ui->ap2, SIGNAL(valueChanged(int)), this, SLOT(updatedata()));
    connect(ui->dp2, SIGNAL(valueChanged(int)), this, SLOT(updatedata()));
    connect(ui->speed2, SIGNAL(valueChanged(int)), this, SLOT(updatedata()));

    connect(ui->skills, SIGNAL(currentRowChanged(int)), this, SLOT(addSkill(int)));
    connect(ui->skills_selected, SIGNAL(currentRowChanged(int)), this, SLOT(addSkill(int)));

    connect(ui->poks, SIGNAL(currentRowChanged(int)), this, SLOT(updatedata2(int)));

    connect(ui->xg, SIGNAL(currentIndexChanged(int)), this, SLOT(on_xingge_clicked(int)));

}

SelectPet::~SelectPet()
{
    delete ui;
}

void SelectPet::on_ok_clicked()
{
    static QString idtoPri[17] = {"普","冰","草","虫","电","毒","恶","火","龙","萌","石","水","土","武","械","翼","幽"};
    int id = ui->id->text().toInt();
    ui->name->setText(pokes.at(id).name);
    ui->attr->setText(idtoPri[pokes.at(id).attr]);
    if (pokes.at(id).attr2 != -1)
        ui->attr2->setText(idtoPri[pokes.at(id).attr2]);
    else
        ui->attr2->setText("");

    updatedataWhenChangePok();
}

void SelectPet::updatedataWhenChangePok()
{
    updatedata();

    poke_skills_selected.clear();
    updateSkillsselected();
}

void SelectPet::updatedata()
{
    int id = ui->id->text().toInt();
    //精力＝[种族值×2＋天赋＋（努力值／4）]×Lv／100＋10＋Lv
    int hp = 0;
    int hp2 = ui->hp2->value();
    hp = pokes.at(id).hp * 2 + 31 + (hp2 / 4) + 10 + 100;
    ui->hp->setText(QString::number(hp));

    //其余＝{[种族值×2＋天赋＋（努力值／4）]×Lv／100＋5}×性格修正
    int ad2 = ui->ad2->value();
    int ad = pokes.at(id).ad * 2 + 31 + (ad2 / 4) + 5;
    if (ui->adp->isChecked())
        ad *= 1.1;
    if (ui->adm->isChecked())
        ad *= 0.9;
    ui->ad->setText(QString::number(ad));

    int dd2 = ui->dd2->value();
    int dd = pokes.at(id).dd * 2 + 31 + (dd2 / 4) + 5;
    if (ui->ddp->isChecked())
        dd *= 1.1;
    if (ui->ddm->isChecked())
        dd *= 0.9;
    ui->dd->setText(QString::number(dd));

    int ap2 = ui->ap2->value();
    int ap = pokes.at(id).ap * 2 + 31 + (ap2 / 4) + 5;
    if (ui->app->isChecked())
        ap *= 1.1;
    if (ui->apm->isChecked())
        ap *= 0.9;
    ui->ap->setText(QString::number(ap));

    int dp2 = ui->dp2->value();
    int dp = pokes.at(id).dp * 2 + 31 + (dp2 / 4) + 5;
    if (ui->dpp->isChecked())
        dp *= 1.1;
    if (ui->dpm->isChecked())
        dp *= 0.9;
    ui->dp->setText(QString::number(dp));

    int speed2 = ui->speed2->value();
    int speed = pokes.at(id).speed * 2 + 31 + (speed2 / 4) + 5;
    if (ui->speedp->isChecked())
        speed *= 1.1;
    if (ui->speedm->isChecked())
        speed *= 0.9;
    ui->speed->setText(QString::number(speed));

    ui->nulizhi->setText(QString::number(510 - hp2 - ad2 - ap2 - dd2 - dp2 - speed2));


//    QString text;
//    for (int i = 0; i < poke_skills[id].size(); ++i)
//    {
//        int t1 = poke_skills[id].at(i).first;
//        int t2 = poke_skills[id].at(i).second;

//        text += skills[t1][t2].name;
//    }
//    ui->skills->setText(text);


    ui->skills->reset();
    ui->skills->clear();
    for (int i = 0; i < poke_skills[id].size(); ++i)
    {
        int t1 = poke_skills[id].at(i).first;
        int t2 = poke_skills[id].at(i).second;


        QListWidgetItem* l = new QListWidgetItem(skills[t1][t2].name, ui->skills);
        ui->skills->insertItem(i+1, l);
    }

    //宠物图片
    QString file;
    file.sprintf("F:/Project/Roco/Pic/gif/%d.gif", id);
//    QMovie *movie = new QMovie(file);
//    movie->setScaledSize(ui->poke_img->size());
//    ui->poke_img->setMovie(movie);
//    movie->start();

    //显示性格
    int t1, t2;
    if (ui->adp->isChecked()) t1 = 0;
    else if (ui->ddp->isChecked()) t1 = 1;
    else if (ui->app->isChecked()) t1 = 2;
    else if (ui->dpp->isChecked()) t1 = 3;
    else if (ui->speedp->isChecked()) t1 = 4;
    else t1 = 5;
    if (ui->adm->isChecked()) t2 = 0;
    else if (ui->ddm->isChecked()) t2 = 1;
    else if (ui->apm->isChecked()) t2 = 2;
    else if (ui->dpm->isChecked()) t2 = 3;
    else if (ui->speedm->isChecked()) t2 = 4;
    else t2 = 5;


    ui->xg->setCurrentIndex(xingge_idid2id(t1, t2));


}

//根据性格编号设置性格
void SelectPet::on_xingge_clicked(int index)
{
    QPair<int,int> qp = xingge_idtoidid(index);
    QRadioButton * btp[6] = {ui->adp, ui->ddp, ui->app, ui->dpp, ui->speedp, ui->nop};
    QRadioButton * btm[6] = {ui->adm, ui->ddm, ui->apm, ui->dpm, ui->speedm, ui->nom};

    btp[qp.first]->setChecked(true);
    btm[qp.second]->setChecked(true);
    updatedata();
}

void SelectPet::addSkill(int row)
{

    int id = ui->id->text().toInt();
    int t1 = poke_skills[id].at(row).first;
    int t2 = poke_skills[id].at(row).second;
    Skill & sk = skills[t1][t2];
    qDebug() << row << "\n";
    QString text = sk.name;

    QString tmp;

    static QString idtoPri[17] = {"普","冰","草","虫","电","毒","恶","火","龙","萌","石","水","土","武","械","翼","幽"};
    text = text + " " + idtoPri[sk.attr];

    tmp.sprintf("(PP:%d)\n", sk.pp);
    text += tmp;

    static QString attr[3] = {"变化","攻击","魔法"};
    text = text + "类型：" + attr[sk.attack_type];
    tmp.sprintf(" 威力:%d\n\n描述：", sk.power);
    text += tmp;

    text += sk.description;

    ui->skill_descp->setText(text);
}


void SelectPet::selectAPoke(int row)
{
    ui->id->setText(QString::number(pokes_have_skills[row]));
    on_ok_clicked();
}


Pokemon SelectPet::getPokemon(int id)
{

    Pokemon pok(id);

    pok.name = pokes[id].name;
    pok.hp = pokes[id].hp;
    pok.ad = pokes[id].ad;
    pok.dd = pokes[id].dd;
    pok.ap = pokes[id].ap;
    pok.dp = pokes[id].dp;

    pok.hpn = ui->hp2->value();
    pok.adn = ui->ad2->value();
    pok.ddn = ui->dd2->value();
    pok.apn = ui->ap2->value();
    pok.dpn = ui->dp2->value();
    pok.speedn = ui->speed2->value();

    pok.nature = ui->xg->currentIndex();

    pok.skills = poke_skills_selected;

    return pok;
}

void SelectPet::on_insert_clicked()
{
    int id = ui->id->text().toInt();
    if (poks.size() >= 6)
        return;

    poks.push_back(getPokemon(id));

    updatepoks();
}
void SelectPet::on_modify_clicked()
{
    int id = ui->id->text().toInt();
    int row = ui->poks->currentRow();
    poks[row] = getPokemon(id);
    updatepoks();
}

void SelectPet::updatepoks()
{
    ui->poks->reset();
    ui->poks->clear();

    ui->poks->setViewMode(QListView::IconMode);

    ui->poks->setIconSize(QSize(80,80));

    for (int i = 0; i < poks.size(); ++i)
    {
        QString text = poks.at(i).name;
        QString file;
        int id = poks.at(i).id;
        file.sprintf("F:/Project/Roco/Pic/gif/%d.gif", id);

        QListWidgetItem* l = new QListWidgetItem(QIcon(file), text, ui->poks);
        l->setSizeHint(QSize(105, 105));

        ui->poks->insertItem(i+1, l);
    }

}

void SelectPet::on_add_skill_clicked()
{
    if (poke_skills_selected.size() >= 4)
        return;

    int id = ui->id->text().toInt();
    int row = ui->skills->currentRow();
    int t1 = poke_skills[id].at(row).first;
    int t2 = poke_skills[id].at(row).second;

    QPair<int,int> qp;
    qp.first = t1;
    qp.second = t2;


    poke_skills_selected.push_back(qp);

    updateSkillsselected();
}
void SelectPet::updateSkillsselected()
{
    ui->skills_selected->reset();
    ui->skills_selected->clear();
    for (int i = 0; i < poke_skills_selected.size(); ++i)
    {
        int t1 = poke_skills_selected[i].first;
        int t2 = poke_skills_selected[i].second;

        QListWidgetItem* l = new QListWidgetItem(skills[t1][t2].name, ui->skills_selected);
        ui->skills_selected->insertItem(i+1, l);
    }
}

void SelectPet::on_del_skill_clicked()
{
    if (poke_skills_selected.size() == 0)
        return;
    int row = ui->skills_selected->currentRow();
    poke_skills_selected.erase(poke_skills_selected.begin()+row, poke_skills_selected.begin()+row+1);

    updateSkillsselected();
}

void SelectPet::updatedata2(int row)
{
    ui->id->setText(QString::number(poks[row].id));

    ui->hp2->setValue(poks[row].hpn);
    ui->ad2->setValue(poks[row].adn);
    ui->dd2->setValue(poks[row].ddn);
    ui->ap2->setValue(poks[row].apn);
    ui->dp2->setValue(poks[row].dpn);
    ui->speed2->setValue(poks[row].speedn);

    on_xingge_clicked(poks[row].nature);

    updatedata();

    poke_skills_selected.clear();
    for (int i = 0; i < poks[row].skills.size(); ++i)
        poke_skills_selected.push_back(poks[row].skills[i]);

    updateSkillsselected();
}



void SelectPet::on_delete_poke_clicked()
{
    if (poks.size() == 0)
        return;
    int row = ui->poks->currentRow();
    poks.erase(poks.begin() + row, poks.begin() + row + 1);

    updatepoks();
}

//保存选择的宠物到文本文件
void SelectPet::on_save_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this,
        tr("Save Pokes"),
        "",
        tr("*.txt")); //选择路径
    if(!filename.isEmpty())
    {
        QFile file(filename);
        if (!file.open(QIODevice::WriteOnly)) {
            return;
        }
        QTextStream out(&file);

        for (int i = 0; i < poks.size(); ++i)
        {
            QString output;
            output = QString::number(poks[i].id);
            output = output + "," + poks[i].name + ",";
            QString buf, buf2;
            int skill_num = poks[i].skills.size();
            buf.sprintf("%d,%d,%d,%d,%d,%d,%d,%d",
                    poks[i].hpn, poks[i].adn,poks[i].ddn,poks[i].apn,poks[i].dpn,
                    poks[i].speedn,
                        poks[i].nature,
                        skill_num);
            output += buf;
            for (int j = 0; j < poks[i].skills.size(); ++j)
            {
                buf.sprintf(",%d.%d", poks[i].skills[j].first, poks[i].skills[j].second);
                output += buf;
            }


            out << output << endl;
        }
        file.close();
    }

}

void SelectPet::on_load_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,
        tr("Load Pokes"),
        "",
        tr("*.txt")); //选择路径
    if(!filename.isEmpty())
    {

        poks.clear();

        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly)) {
            return;
        }


        QTextStream * out = new QTextStream(&file);//文本流
        QString all = out->readAll();
        qDebug() << all;
        QStringList tempOption = all.split("\n");//每行以\n区分
        for(int i = 0 ; i < tempOption.count() ; i++)
        {
            if (tempOption.at(i).size() == 0)
                continue;
             QStringList pl = tempOption.at(i).split(",");//一行中的单元格以，区分
             Pokemon pet(pl.at(0).toInt());
             pet.name = pl.at(1);



             pet.hpn = pl.at(2).toInt();
             pet.adn = pl.at(3).toInt();
             pet.ddn = pl.at(4).toInt();
             pet.apn = pl.at(5).toInt();
             pet.dpn = pl.at(6).toInt();
             pet.speedn = pl.at(7).toInt();

             pet.nature = pl.at(8).toInt();

             int skill_num = pl.at(9).toInt();
             for (int j = 10; j < 10+skill_num; ++j)
             {
                 QStringList huihe = pl.at(j).split(".");
                 QPair<int,int> qp;

                 if (huihe.count() == 2)
                 {
                     qp.first = huihe.at(0).toInt();
                     qp.second = huihe.at(1).toInt();
                 }

                 pet.skills.push_back(qp);
             }


             poks.push_back(pet);


        }
        file.close();//操作完成后记得关闭文件

        updatepoks();
    }

}