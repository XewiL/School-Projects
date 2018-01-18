// TIE-02206 Basic Course on Programming, Project03
//
// Graphical Body Mass Index (BMI) calculator
//
// Petri Leppänen, 160280

#include "mainwindow.hh"
#include <QApplication>


// Pääohjelma ei tee muuta kuin avaan pääikkunan.
// Kaikki toiminnallisuus pääasiassa mainwindow.cc
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
