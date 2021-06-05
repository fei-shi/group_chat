#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent,QString name)
    : QMainWindow(parent)
{
    udpSocket=new QUdpSocket(this);
    port=25233;
    udpSocket->bind(port,QUdpSocket::ShareAddress|QUdpSocket::ReuseAddressHint);
    uName=name;
    setFixedSize(800,600);
    setWindowTitle(QString::fromLocal8Bit("群聊界面"));
    setWindowIcon(QPixmap(":/ticon.jpg"));
    setPalette(QPalette(QColor("#FFFFFF")));
    setAutoFillBackground(true);
    a=new QTextBrowser(this);
    a->resize(this->width()*6/10,this->height()*6/10);
    a->move(20,20);
    b=new QTextEdit(this);
    b->move(20,20+a->height()+15);
    b->resize(this->width()*6/10,this->height()*2/10);
    b->setFocus();
    QTableWidget *c=new QTableWidget(this);
    //c->setHorizontalHeaderLabels(QStringList()<<"ID"<<"ip");
    c->resize(this->width()-a->width()-60,this->height()-40);
    c->move(40+a->width(),20);
    d=new QPushButton(QString::fromLocal8Bit("发送"),this);

    d->move(b->x()+b->width()-d->width(),b->y()+b->height()+20);
//    QPushButton *e=new QPushButton(QString::fromLocal8Bit(""),this);
//    e->move(20,b->y()+b->height()+20);
    QString tem=QString::fromLocal8Bit("在线人数:");
    QLabel *nop=new QLabel(tem,this);
    nop->move(b->x(),b->y()+b->height()+20);
    this->nop=1;
    QLabel *nop1=new QLabel(this);
    nop1->setNum(this->nop);
    nop1->move(nop->x()+nop->width(),nop->y());
    sendMse(UserEnter);
    qDebug()<<"tmd"<<1;
    connect(udpSocket,&QUdpSocket::readyRead,this,&MainWindow::processPendingDatagrams);
    connect(d,&QPushButton::clicked,this,&MainWindow::on_d_clicked);
}
MainWindow::~MainWindow()
{
}
void MainWindow::processPendingDatagrams()
{
    while(udpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(),datagram.size());
        QDataStream in(&datagram,QIODevice::ReadOnly)
                ;
        int msgType;
        in>>msgType;
        QString userName,ipAddr,msg;
        QString time=QDateTime::currentDateTime().toString("yyyy-MM-ddhh:mm:ss");
           //qDebug()<<time;
        qDebug()<<msgType;
        if(msgType<0||msgType>2)return;
        switch(msgType)
        {
            case Msg:
            in>>userName>>ipAddr>>msg;
            a->setTextColor(Qt::blue);
            a->append("["+userName+"]"+time);
            a->append(msg);
            qDebug()<<1;
            break;

        case UserEnter:
            in>>userName>>ipAddr;
            userEnter(userName,ipAddr);
            qDebug()<<1;
            break;
        case UserLeft:
            in>>userName;
            userLeft(userName,time);
            qDebug()<<1;
            break;
        }
    }
    qDebug()<<"pendig ok";
}
void MainWindow::sendMse(MsgType type, QString srvaddr)
{
    QByteArray data;
    QDataStream out(&data,QIODevice::WriteOnly);
    qDebug()<<"wuhu";
    QString address=getip();
    //qDebug()<<address;
    out<<type<<getUsr();
    qDebug()<<type;
    switch(type)
    {
        case Msg:
        if(this->b->toPlainText()=="")
        {
            QMessageBox::warning(0,QString::fromLocal8Bit("异常"),QString::fromLocal8Bit("发送内容为空"),
                                 QMessageBox::Ok);
            return;
        }
        out<<address<<getMsg();
        break;

    case UserLeft:
        break;
    case UserEnter:
        out<<address;
        userEnter(uName,address);
        break;
    }
    udpSocket->writeDatagram(data,data.length(),QHostAddress::Broadcast,port);
    qDebug()<<"tmd"<<1;
}
QString MainWindow::getip()
{
    QList<QHostAddress> list=QNetworkInterface::allAddresses();
    foreach(QHostAddress addr,list)
    {
        if(addr.protocol()==QAbstractSocket::IPv4Protocol)
        {
            qDebug()<<addr.toString()<<endl;
            return addr.toString();
        }

    }
    //qDebug()<<"ip ok";
    return 0;
}
QString MainWindow::getMsg()
{
    QString msg=b->toPlainText();
    b->clear();
    b->setFocus();
    qDebug()<<"getm ok"<<' '<<msg;
    return  msg;
}
QString MainWindow::getUsr()
{
    qDebug()<<"unmae ok"<<' '<<uName;
    return uName;
}
void MainWindow::on_d_clicked()
{
    qDebug()<<">";
    sendMse(Msg);

}
void MainWindow::userLeft(QString username, QString time)
{
    a->append("leave");;
}
void MainWindow::userEnter(QString username, QString ipaddress)
{

    if(qFind(listofp.begin(),listofp.end(),ipaddress)==listofp.end())
    {
        a->append(uName+" join the online_chat");
        listofp.push_back(ipaddress);
        sendMse(UserEnter);
    }
}
