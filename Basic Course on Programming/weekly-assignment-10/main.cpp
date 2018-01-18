// TIE-02206 Basic Course on Programming - Viikkoharkka10
//
// Petri Leppänen, 160280

#include "editor.hh"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Editor w;
    w.show();

    return a.exec();
}
