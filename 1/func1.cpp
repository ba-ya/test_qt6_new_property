#include "func1.h"
#include "./ui_func1.h"

#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_spinBox_test1_editingFinished()
{
    auto cnt = ui->spinBox_test1->value();
    timer.start();

    QTimer::singleShot(cnt, this, [this]() {
        QString str = "during time:" + QString::number(timer.elapsed() * 1.0 / 1000) + "s";
        ui->label_test1->setText(str);
    });
}


