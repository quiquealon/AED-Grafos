#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "edge.h"
#include "node.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    widget= new GraphWidget(this);
    widget->move(500,60);
    widget->show();




}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    widget->scene->clear();
    widget->edgelist.clear();
    widget->actual=0;
}

void MainWindow::on_pushButton_2_clicked()
{
    for(int i=0;i<widget->edgelist.size();i++)
        qDebug()<<widget->edgelist[i]->sourceNode()->name<<widget->edgelist[i]->destNode()->name<<widget->edgelist[i]->value;
}
