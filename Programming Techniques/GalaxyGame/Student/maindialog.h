#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include "galaxy.hh"
#include "initialize.hh"
#include "igamerunner.hh"
#include "utility.hh"
#include "eventhandler.hh"
#include "starsystemdraw.h"
#include "player.h"
#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include "customscene.h"
#include <QTimer>
#include "statistics.hh"
#include <QMessageBox>
#include "wormholedrive.hh"


namespace Ui {
class MainDialog;
}

class MainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MainDialog(QWidget *parent = 0);
    ~MainDialog();

    void setPointers( std::shared_ptr<Common::IGameRunner> gameRunner_,
                          std::shared_ptr<Student::EventHandler> handler_,
                          std::shared_ptr<Student::Galaxy> galaxy_);
public slots:

    /*!
     * \brief startNewGame alustaa pelin tiedot ja käynnistää kellon.
     */
    void startNewGame( int ships );
    void showGalaxyInfo();

signals:
    void sendFinalPoints(int points);

private slots:

    /*!
     * \brief update kutsutaan kellosta, vastaa yhtä pelin kierrosta.
     */
    void update();

private:
    Ui::MainDialog *ui;
    std::shared_ptr<Common::IGameRunner> pGameRunner;
    std::shared_ptr<Student::EventHandler> pEventHandler;
    std::shared_ptr<Student::Galaxy> pGalaxy;

    Player* player;
    QTimer* timer;
    CustomScene scene;

    Student::Statistics statistic;

};

#endif // MAINDIALOG_H
