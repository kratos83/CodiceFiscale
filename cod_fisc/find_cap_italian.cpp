#include "find_cap_italian.h"
#include "ui_find_cap_italian.h"
#include <QFile>
#include <QCompleter>
#include <QDebug>
#include <QtSql>

find_cap_italian::find_cap_italian(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::find_cap_italian)
{
    ui->setupUi(this);
    connect(ui->esci,SIGNAL(clicked()),this,SLOT(close()));
    connect(ui->cerca,SIGNAL(clicked()),this,SLOT(cap_trovato()));
    setWindowTitle(tr("Cerca CAP"));
    find_comune();
}

/*************************************************
 * Cerco il comune all'interno del database
 * ***********************************************/
void find_cap_italian::find_comune()
{
    QSqlQuery query;
    query.prepare("select * from comuni_cap");

    QStringList list;
    if(query.exec())
    {
        while(query.next()){
            list << query.value(0).toString();
        }
        ui->comune->addItems(list);
    }
    QCompleter *complete = new QCompleter(list,this);
    complete->setCaseSensitivity(Qt::CaseInsensitive);
    ui->comune->setCompleter(complete);
}

void find_cap_italian::vis_cap_comune()
{
    QSqlQuery query;
    query.prepare("select * from comuni_cap where comune='"+ui->comune->currentText()+"'");

    QStringList list;
    if(query.exec())
    {
        while(query.next()){
            list << query.value(1).toString();
            cap = list.at(0);
        }
    }
}

void find_cap_italian::cap_trovato()
{
    vis_cap_comune();

    found = cap;
    ui->vis_cap->clear();
    ui->vis_cap->setText(found);
}

find_cap_italian::~find_cap_italian()
{
    delete ui;
}
