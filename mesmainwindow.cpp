#include "mesmainwindow.h"
#include "ui_mesmainwindow.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>

extern void ExitProgram(void);

MesMainWindow::MesMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MesMainWindow)
{
    ui->setupUi(this);

}

MesMainWindow::~MesMainWindow()
{
    delete ui;
}

void MesMainWindow::closeEvent(QCloseEvent *)
{
    on_exit_action_triggered();
}

void MesMainWindow::on_exit_action_triggered()
{
    QMessageBox::StandardButton returnBtn = QMessageBox::information(this,tr("提示"),tr("你确定要退出吗？"),QMessageBox::Yes|QMessageBox::No);
    if(returnBtn== QMessageBox::Yes){
        ExitProgram();
        QApplication::exit();
    }
}
