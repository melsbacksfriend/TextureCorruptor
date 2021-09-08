#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <cstdlib>
#include <ctime>

QString iPath;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), pm(QPixmap())
{
    srand(time(0));
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionOpen_triggered()
{
    iPath = QFileDialog::getOpenFileName(this, tr("Open an image"), "", tr("Images (*.png *.jpg *.bmp)"));
    pm = QPixmap(iPath);
    ui->label->setPixmap(pm);
    ui->actionCorrupt->setEnabled(true);
}

void MainWindow::on_actionCorrupt_triggered()
{
    QImage img = pm.toImage();
    for (int i = 0; i < img.size().width(); i++)
    {
        for (int j = 0; j < img.size().height(); j++)
        {
            img.setPixelColor(i, j, QColor(rand() % 256, rand() % 256, rand() % 256));
        }
    }
    pm = QPixmap::fromImage(img);
    ui->label->setPixmap(pm);
    ui->actionSave->setEnabled(true);
}

void MainWindow::on_actionSave_triggered()
{
    QString oPath = QFileDialog::getSaveFileName(this, tr("Save your corrupted file"), "", tr("Images (*.png *.jpg *.bmp)"));
    pm.save(oPath);
}
