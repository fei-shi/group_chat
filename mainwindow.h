#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include<QPainter>
#include<QTextBrowser>
#include<QPushButton>
#include<QLabel>
#include<QTableWidget>
#include<QString>
#include <QUdpSocket>
#include<QHostInfo>
#include<QMessageBox>
#include<QDebug>
#include<QDateTime>
#include<QNetworkInterface>
#include<QVector>


enum MsgType{Msg,UserEnter,UserLeft};
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr,QString name="fuck");
    ~MainWindow();

private:

    void userEnter(QString username,QString ipaddress);
    void userLeft(QString username,QString time);
    void sendMse(MsgType type,QString srvaddr="");
    QString getip();
    QString getUsr();
    QString getMsg();

    int nop;
    QUdpSocket *udpSocket;
    qint16 port;
    QString uName;
    QTextEdit *b;
    QPushButton *d;
    QTextBrowser *a;
    QVector<QString> listofp;
private slots:
    void processPendingDatagrams();
    void on_d_clicked();
};
#endif // MAINWINDOW_H
