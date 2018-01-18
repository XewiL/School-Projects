#include "galaxy.hh"
#include "initialize.hh"
#include "igamerunner.hh"
#include "utility.hh"
#include "eventhandler.hh"
#include <QApplication>
#include <memory>
#include <time.h>
#include "maindialog.h"
#include "startingdialog.hh"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    startingdialog startdialog;
    Common::utilityInit(time(NULL));

    while(true)
    {
        MainDialog mainDialog;

        // Alustenmäärän välittäminen pääikkunaan
        QObject::connect( &startdialog, SIGNAL( sendData(int) ),
                            &mainDialog, SLOT( startNewGame(int) ) );

        // Pisteitten välittäminen aloitusikkunaan
        QObject::connect(&mainDialog, SIGNAL (sendFinalPoints(int)),
                         &startdialog, SLOT(finalPoints(int)));

        // Lopetetaan while-true loop jos saadaan jokin muu kuin Accept.
        if( startdialog.exec() != QDialog::Accepted)
            break;

        // Ajetaan maindialog.
        mainDialog.exec();
    }

    return 0;
}
