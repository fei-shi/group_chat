#include "login.h"


login::login(QWidget *parent) : QWidget(parent)
{
    a=new QLineEdit(this);
    this->resize(400,300);
    a->move((width()-a->width())/2,a->y());    setWindowTitle(QString::fromLocal8Bit("起个名字"));
    QPushButton *b=new QPushButton(QString::fromLocal8Bit("确认"),this);
    b->move((width()-b->width())/2,a->y()+a->height());
    connect(b,&QPushButton::clicked,this,&login::on_b_clicked);
    tem=new QLabel(QString::fromLocal8Bit("不可为空"),this);
    //tem->move(width()-tem->text().length(),a->y());
    tem->hide();
    //qDebug()<<tem->text().length()<<" "<<tem->width();
}
void login::on_b_clicked()
{
    if(a->text()=="")
    {
        tem->show();
        qDebug()<<"ok";
    }
    else
    {
        QString tem=a->text();
        trname(tem);
        MainWindow *tmd=new MainWindow(NULL,tem);
        tmd->show();
        hide();
    }
}
