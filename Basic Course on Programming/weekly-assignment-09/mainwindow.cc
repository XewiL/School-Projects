#include "mainwindow.hh"
#include "ui_mainwindow.h"

Mainwindow::Mainwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Mainwindow)
{
    ui->setupUi(this);

    // Nappien kontaktit
    connect(ui->clearButton, SIGNAL(clicked()),
            this, SLOT(clear_button_clicked()));

    connect(ui->kmhspinBox, SIGNAL(valueChanged(int)),
            this, SLOT(kmh2miles(int)));
}

Mainwindow::~Mainwindow()
{
    delete ui;
}

// Clear-napin toiminto
void Mainwindow::clear_button_clicked()
{
    ui->kmhspinBox->setValue(0);
    ui->mileslcd->display(0.0);
}

// km/h maileihin display näyttöön
void Mainwindow::kmh2miles(int kmh)
{
    ui->mileslcd->display(kmh/1.609);
}
