#include "startingdialog.hh"
#include "ui_startingdialog.h"

#include <QString>

startingdialog::startingdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::startingdialog)
{
    ui->setupUi(this);

    connect(ui->quitGameButton, SIGNAL(clicked(bool)),
                     this, SLOT(reject()));

    connect(ui->startGameButton, SIGNAL(clicked(bool)),
                     this, SLOT(accept()));
}

startingdialog::~startingdialog()
{
    delete ui;
}

int startingdialog::exec()
{
    QDialog::exec();

    if(result() == QDialog::Accepted)
        emit sendData(ui->shipsnumberSpinBox->value());

    return result();
}

void startingdialog::finalPoints(int points)
{
    QString pointsstr = QString::number(points);
    pointsstr = "Sait pisteitä: " + pointsstr;
    ui->finalPointsLabel->setText(pointsstr);
}

