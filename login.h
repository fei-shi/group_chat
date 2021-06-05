#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include<QTextEdit>
#include<QLineEdit>
#include<QPushButton>
#include<QDebug>

#include"mainwindow.h"

class login : public QWidget
{
    Q_OBJECT
public:
    explicit login(QWidget *parent = nullptr);


private:
    QLineEdit *a;
    QLabel *tem;
signals:
    void trname(QString tem);
private slots:
    void on_b_clicked();


};

#endif // LOGIN_H
