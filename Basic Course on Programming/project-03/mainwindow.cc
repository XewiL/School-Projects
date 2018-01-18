// Pääikkunan määrittelyt

#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Action-menuvalikko ja niiden toiminnot
    connect(ui->actionReset, SIGNAL(triggered(bool)),
            this, SLOT(reset_menu_clicked()));
    connect(ui->actionQuit, SIGNAL(triggered(bool)),
             this, SLOT(close())); // close() -> suljetaan ohjelma.

    // Gender-menuvalikko ja sen toiminta
    // Alkuasetuksena on valittu sukupuoleksi nainen.
    QActionGroup *genderActionGroup = new QActionGroup(this);
    genderActionGroup->addAction(ui->actionFemale);
    genderActionGroup->addAction(ui->actionMale);

    ui->actionFemale->setCheckable(true);
    ui->actionFemale->setChecked(true);
    ui->actionMale->setCheckable(true);

    // Signaalien määrittelyt, sukupuolen valinta
    connect(ui->actionFemale, SIGNAL(triggered()),
            this, SLOT(gender_clicked()));
    connect(ui->actionMale, SIGNAL(triggered()),
            this, SLOT(gender_clicked()));

    // Aina kun jomman kumman spinboksin arvo muuttuu,
    // lasketaan BMI.
    connect(ui->spinBox_height, SIGNAL(valueChanged(int)),
            this, SLOT(calculateBMI()));
    connect(ui->spinBox_weight, SIGNAL(valueChanged(int)),
            this, SLOT(calculateBMI()));

    // Loput signaaleista on tehty ui:n puolella.
}

MainWindow::~MainWindow()
{
    delete ui;
}


// Reset-valikko: Nollataan kaikki samaan tilanteeseen
// kuin ohjelmaa käynnistäessä.
void MainWindow::reset_menu_clicked() {
    ui->spinBox_weight->setValue(0);
    ui->spinBox_height->setValue(0);
    ui->actionFemale->setChecked(true);
    ui->label_gender_output->setText("Female");
    ui->label_bmi_output->setText("-");
    ui->label_interp_output->setText("-");
}

// Sukupuolivalikko: näytetään oikea sukupuoli ja lasketaan BMI.
void MainWindow::gender_clicked() {
    if (ui->actionFemale->isChecked()) {
        ui->label_gender_output->setText("Female");
    }
    if (ui->actionMale->isChecked()) {
        ui->label_gender_output->setText("Male");
    }
    calculateBMI();
}


// BMI:n laskenta
void MainWindow::calculateBMI() {

    // Paino ja pituus saadaan spinbokseista value() -funktiolla.
    // Funktio tosin palauttaa arvon int joten se täytyy muuttaa muotoon double.
    // Samalla muutetaan pituus: cm -> m.
    double weight = static_cast<double>(ui->spinBox_weight->value());
    double height = static_cast<double>(ui->spinBox_height->value()) / 100; // cm -> m

    // Kun molemmat syötteet ovat isompia kuin nolla, lasketaan BMI
    // ja tehdään vertailu sukupuolen mukaan.
    // (Siksikin ehto, että ei jaettaisi vahingossa nollalla BMI laskettaessa).
    if (height > 0 && weight > 0) {
        double bmi = weight / (height * height); // BMI = paino(kg) / pituus(cm)²
        // BMI:n näyttäminen kahden desimaalin tarkkuudella
        QString bmistr = QString::number(bmi, 'f', 2);
        ui->label_bmi_output->setText(bmistr);
        // setNum() näyttää numeron aina 6:lla numerolla, apsilla taisi olla tämä(?)
        //ui->label_bmi_output->setNum(bmi);

        // BMI:n oikea tulkinnan näyttö sukupuolen ja bmi:n mukaan.
        if (ui->actionFemale->isChecked()) {
            if (bmi > 0 && bmi <= 19.1) {
                ui->label_interp_output->setText("Underweight");
            } else if (bmi > 19.1 && bmi <= 25.8) {
                ui->label_interp_output->setText("Normal");
            } else if (bmi > 25.8 && bmi <= 27.3) {
                ui->label_interp_output->setText("Slight overweight");
            } else if (bmi > 27.3 && bmi <= 32.2) {
                ui->label_interp_output->setText("Overweight");
            } else {
                ui->label_interp_output->setText("Much overweight");
            }
        }

        if(ui->actionMale->isChecked()) {
            if (bmi > 0 && bmi <= 20.7) {
                ui->label_interp_output->setText("Underweight");
            } else if (bmi > 20.7 && bmi <= 26.4) {
                ui->label_interp_output->setText("Normal");
            } else if (bmi > 26.4 && bmi <= 27.8) {
                ui->label_interp_output->setText("Slight overweight");
            } else if (bmi > 27.8 && bmi <= 31.1) {
                ui->label_interp_output->setText("Overweight");
            } else {
                ui->label_interp_output->setText("Much overweight");
            }
        }
    // Jos jompi kumpi spinboksien lukemista on nolla, näytetään viiva.
    } else {
        ui->label_bmi_output->setText("-");
        ui->label_interp_output->setText("-");
    }
}
