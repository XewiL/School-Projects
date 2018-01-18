#include "customscene.h"


CustomScene::CustomScene()
{
    zoom = 10.0;
    origo = Common::Point(30,30);
}


void CustomScene::redrawAll()
{
    // Loopataan kaikki itemit scenestä.
    QList<QGraphicsItem*> itemList = items();
    for (int i = 0; i < itemList.size(); i++)
    {
        // Käsitellään vain star systemit.
        StarSystemDraw * ss = dynamic_cast<StarSystemDraw*>( itemList.at(i) );
        if( ss == nullptr )
            continue;

        // Asetetaan starsystemin sijainti xoomin ja origon perusteella.
        ss->setPos(
                ( ss->getPoint().x * zoom ) + ( origo.x * zoom ),
                ( ss->getPoint().y * zoom ) + ( origo.y * zoom ) );

        // Piirretään laivat tälle starsystemille.
        redrawShipsInStarSystem(ss);

    }
}

void CustomScene::redrawStarSystemShips( std::shared_ptr<Common::StarSystem> pStarSystem )
{
    QList<QGraphicsItem*> itemList = items();
    for (int i = 0; i < itemList.size(); i++)
    {
        StarSystemDraw * ss = dynamic_cast<StarSystemDraw*>( itemList.at(i) );
        if( ss == nullptr )
            continue;

        // Haluttu starsystem löytyi.
        if( ss->AccessStarSystem() == pStarSystem )
        {
            redrawShipsInStarSystem(ss);
            break;
        }
    }
}

void CustomScene::redrawShipsInStarSystem(StarSystemDraw* ss)
{
    ss->destroyShipDraws( this );
    int diff = 0;
    for( std::shared_ptr<Common::Ship> ship : ss->getShips() )
    {
        if( ship->isAbandoned() ) continue;

        std::shared_ptr<Common::CargoShip> cargoShip = std::dynamic_pointer_cast<Common::CargoShip>( ship );
        if( cargoShip == nullptr )
            continue;

        // Piirretään laiva
        QGraphicsRectItem * shipdraw = new QGraphicsRectItem;
        shipdraw->setRect( ss->pos().x(), ss->pos().y() + (diff++) * 11, 10, 10);
        shipdraw->setBrush( Qt::cyan );

        // Punaisella laivat jolla hätähuuto.
        std::shared_ptr<Common::DistressAction> distress =
                std::dynamic_pointer_cast<Common::DistressAction>( cargoShip->getAction() );
        if( distress != nullptr )
           shipdraw->setBrush( Qt::red );

        // Lisää laiva.
        addItem( shipdraw );
        ss->addShipDraw( shipdraw );
    }
}

void CustomScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mousePressEvent(event);
    QPointF playerPoint = QPointF();
    QList<QGraphicsItem*> itemList = items();
    for (int i = 0; i < itemList.size(); i++)
    {
        Player * player = dynamic_cast<Player*>( itemList.at(i) );
        if( player )
        {
            // Siirrä pelaaja hiiren osoittamaan paikkaan.
            player->setPos( event->scenePos().x(), event->scenePos().y() );
            playerPoint = player->pos();

            break;
        }
    }
    for (int i = 0; i < itemList.size(); i++)
    {
        StarSystemDraw * ss = dynamic_cast<StarSystemDraw*>( itemList.at(i) );
        if( ss != nullptr )
        {
            // Tarkistetaan että onko pelaaja starsystemin lähellä.
            if( Common::distance( ss->pos().x(), ss->pos().y(), playerPoint.x(), playerPoint.y() ) < 50 )
            {
                for( std::shared_ptr<Common::Ship>& ship : ss->AccessGalaxy()->getShipsInStarSystem( ss->AccessStarSystem()->getName() ) )
                {

                    std::shared_ptr<Common::CargoShip> cargoShip = std::dynamic_pointer_cast<Common::CargoShip>( ship );
                    if( cargoShip == nullptr )
                        continue;

                    std::shared_ptr<Common::DistressAction> distress =
                            std::dynamic_pointer_cast<Common::DistressAction>( cargoShip->getAction() );

                    // Korjaa laiva mikäli laivalla on hätähuuto.
                    if( distress != nullptr )
                    {
                        Common::RepairAction repair = Common::RepairAction( ship, ship->getEngine(), true );
                        repair.execute();
                    }
                }
            }
        }
    }

}

void CustomScene::keyPressEvent(QKeyEvent *event)
{
    bool moved = false;
    int iMove = 2;
    float fZoom = 1.3;

    // Liikuteaan origoa/zoomia jos painettiin haluttuja nappeja.
    if( event->key() == Qt::Key_A)
    {
        origo.x = origo.x + iMove;
        moved = true;
    }
    else if( event->key() == Qt::Key_D)
    {
        origo.x = origo.x - iMove;
        moved = true;
    }
    else if( event->key() == Qt::Key_W)
    {
        origo.y = origo.y + iMove;
        moved = true;
    }
    else if( event->key() == Qt::Key_S)
    {
        origo.y = origo.y - iMove;
        moved = true;
    }
    else if( event->key() == Qt::Key_E)
    {
        zoom *= fZoom;
        if (zoom > 62)
            zoom /=fZoom;
        moved = true;
    }
    else if( event->key() == Qt::Key_Q)
    {
        zoom /= fZoom;
        if (zoom < 10)
            zoom *= fZoom;
        moved = true;
    }

    // Piirretään kaikki uusiin paikkoihin jos liikutettiin galaxyä.
    if( moved )
        redrawAll();
}

void CustomScene::mouseMoveEvent(QMouseEvent *mouseEvent)
{
    //QGraphicsScene::mouseMoveEvent(mouseEvent);
    QList<QGraphicsItem*> itemList = items();
    QPoint mouse_pos = mouseEvent->pos();

    if (mouse_pos.x() <= this->width() && mouse_pos.y() <= this->height()
            && mouse_pos.x() >= 0 && mouse_pos.y() >= 0) {
        for (int i = 0; i < itemList.size(); i++)
        {
            StarSystemDraw * ss = dynamic_cast<StarSystemDraw*>( itemList.at(i) );
            if( ss )
            {
                // Tarkistetaan että onko hiiren osoitin starsystemin lähellä.
                if( Common::distance( ss->pos().x(), ss->pos().y(), mouse_pos.x(), mouse_pos.y() ) < 50 )
                {
//                    for( std::shared_ptr<Common::StarSystem>& star : ss->AccessGalaxy()->getShipsInStarSystem( ss->AccessStarSystem()->getName() ) )
//                    {

//                        std::shared_ptr<Common::CargoShip> cargoShip = std::dynamic_pointer_cast<Common::CargoShip>( ship );
//                        if( cargoShip == nullptr )
//                            continue;

//                        std::shared_ptr<Common::DistressAction> distress =
//                                std::dynamic_pointer_cast<Common::DistressAction>( cargoShip->getAction() );

//                        // Korjaa laiva mikäli laivalla on hätähuuto.
//                        if( distress != nullptr )
//                        {
//                            Common::RepairAction repair = Common::RepairAction( ship, ship->getEngine(), true );
//                            repair.execute();
//                        }
//                    }
                }
            }
        }
    }
}
