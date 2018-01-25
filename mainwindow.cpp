#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QTableWidget>
#include<QTableWidgetItem>
#include<QTcpServer>
#include<QDebug>
#include<QMessageBox>


int rowcount;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ////////////////////////////////////////////////////////////////////

    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Product Name" << "Volume" << "Market Capital" << "Credit Ratings") ;

    Server=new QTcpServer(this);

    if(!Server->listen(QHostAddress::Any,123))
    {
        qDebug()<<"server not started"<<Server->errorString();
    }
    else
    {
        qDebug()<<"server Started";
    }
connect(Server,SIGNAL(newConnection()),this,SLOT(AcceptConnection()));
}

MainWindow::~MainWindow()
{
    delete ui;
    Socket->close();
    Server->close();
}

void MainWindow::AcceptConnection()//server
{
    Socket=new QTcpSocket(this);
    Socket=Server->nextPendingConnection();
    if(!Socket)
    {
        ui->statusBar->showMessage("connection Refused",3000);
        qDebug()<<"Connection Refused"<<Socket->errorString();

    }
    else
    {
        ui->statusBar->showMessage("connected",4000);
        qDebug()<<"connection ACCEPTED";
    }
    connect(Socket,SIGNAL(readyRead()),this,SLOT(StartReading()));
}

void MainWindow::StartReading()
{
    char buff[512]={0};
    Socket->read(buff,Socket->bytesAvailable());
    qDebug()<<"reading from client"<<buff;

    QString string(buff);
    QStringList stringlist=string.split(",",QString::SkipEmptyParts);
    rowcount=1;
    int l=0,k=0;
    qDebug()<<stringlist;
    for(int i=0;i<stringlist.count()/4;i++)
    {
        ui->tableWidget->setRowCount(rowcount);
        ui->tableWidget->setColumnCount(4);

        ui->tableWidget->setItem((rowcount-1),l,new QTableWidgetItem(stringlist.at(k++)));
         ui->tableWidget->setItem((rowcount-1),l+1,new QTableWidgetItem(stringlist.at(k++)));
          ui->tableWidget->setItem((rowcount-1),l+2,new QTableWidgetItem(stringlist.at(k++)));
           ui->tableWidget->setItem((rowcount-1),l+3,new QTableWidgetItem(stringlist.at(k++)));
  rowcount++;
    }

    buff[64]={0};
    ui->statusBar->showMessage("Started reading data",4000);

}

void MainWindow::on_pushButton_clicked()
{
    this->close();
}
