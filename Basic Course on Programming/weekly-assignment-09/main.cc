// TIE-02206 Basic Course on Programming, graafinen käyttöliittymä
//
// Petri Leppänen, 160280

#include "mainwindow.hh"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Mainwindow w;
    w.show();

    return a.exec();
}
