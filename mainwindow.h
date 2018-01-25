#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"qtcpserver.h"
#include"QTcpSocket"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
     void AcceptConnection();//server
     void StartReading();

private:
    Ui::MainWindow *ui;
    QTcpServer *Server;
    QTcpSocket *Socket;
};

#endif // MAINWINDOW_H
