#include "maindialog.h"
#include "ui_maindialog.h"
#include "startingdialog.hh"
#include "customscene.h"

MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDialog)
{
    ui->setupUi(this);

    // Yhdistä napit.
    QObject::connect( ui->btnQuit, SIGNAL( clicked(bool) ), this, SLOT( close() ) );

    // Lisää scene ui:ssa olevalle viewille..
    ui->graphicsView->setScene( &scene );
    scene.setSceneRect(0,0,ui->graphicsView->width(),ui->graphicsView->height());

    // Aseta scrollbarit pois.
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Luo timer.
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    pEventHandler = std::make_shared<Student::EventHandler>();
    pGalaxy = std::make_shared<Student::Galaxy>();
    pGameRunner = Common::getGameRunner(pGalaxy, pEventHandler);
}

MainDialog::~MainDialog()
{
    delete ui;
}

void MainDialog::startNewGame( int ships )
{

    // Alusta pelitietoja.
    pEventHandler->setPointers( &scene, &statistic );
    std::shared_ptr<Common::WormHoleDrive> engineWormHole = std::make_shared<Common::WormHoleDrive>( pGalaxy );
    player = new Player( engineWormHole, pGalaxy->getRandomSystem(), pEventHandler );
    player->setPos( 10, 10 );
    player->setZValue( 1000 );  // Päällimmäiseksi
    scene.addItem( player );  // Omistajuus siirtyy scenelle.
    timer->start(2000);

    // Lisää galaxyssa olevat starsystemit sceneen.
    for( std::string & systemName : pGalaxy->getSystemNames() )
        scene.addItem( new StarSystemDraw( pGalaxy, pGalaxy->getStarSystemByName( systemName ) ) );  // Ownership of StarSystemDraw is transferred to scene.

    // Piirrä scene.
    scene.redrawAll();

    // Alustetaan laivoja.
    pGameRunner->spawnShips(ships);

    // Edetään pelissä, jotta peli loppuu nopeampaa.
    for( int i = 0; i < 20; i++ )
    {
        pGameRunner->createActions();
        pGameRunner->doActions();
    }
    update();
}

void MainDialog::showGalaxyInfo()
{

}

void MainDialog::update()
{
    // Lisätään uusi laiva joka timer päivityksellä ja tehdään niiden toimintoja.
    pGameRunner->spawnShips( 1 );
    pGameRunner->createActions();
    pGameRunner->doActions();

    // Tilastoidaan pelin etenemistä.
    int lost = statistic.getLostShips();
    int saved = statistic.getSavedShips();
    ui->labelLost->setText( QString( "Kadotetut: %1").arg( lost ) );
    ui->labelSaved->setText( QString( "Pelastetut: %1" ).arg( saved ) );

    // Peli loppuu kun tämä raja laivoja katoaa.
    if( lost >= 10 )
    {
        // Tyhjätään asiat.
        timer->stop();
        scene.clear();

        // Näytetään tilanne käyttäjälle.
        QMessageBox msgBox;
        msgBox.setText(QString( "Sait pisteitä: %1." ).arg( saved ) );
        msgBox.exec();

        // Lähetetään pistetulos starting dilaogille ja suljetaan maindialog.
        emit sendFinalPoints(saved);
        close();
    }
}

void MainDialog::setPointers( std::shared_ptr<Common::IGameRunner> gameRunner_,
    std::shared_ptr<Student::EventHandler> handler_,
    std::shared_ptr<Student::Galaxy> galaxy_)
{
    pGameRunner = gameRunner_;
    pEventHandler = handler_;
    pGalaxy = galaxy_;
}
