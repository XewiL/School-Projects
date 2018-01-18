#include "starsystemdraw.h"

StarSystemDraw::StarSystemDraw( std::shared_ptr<Common::IGalaxy> pGalaxy, std::shared_ptr<Common::StarSystem> pStarSystem )
{
    // Luodaan pixmap kuvasta, joka on resurssina.
    setPixmap(QPixmap(":/images/starsystem.png"));
    m_pGalaxy = pGalaxy;
    m_pStarSystem = pStarSystem;
}

Common::IGalaxy::ShipVector StarSystemDraw::getShips()
{
    return m_pGalaxy->getShipsInStarSystem( m_pStarSystem->getName() );
}

void StarSystemDraw::destroyShipDraws( CustomScene * scene )
{
    for( auto p: ships )
        scene->removeItem( p );

    ships.clear();
}

void StarSystemDraw::addShipDraw(QGraphicsRectItem *shipdraw)
{
    ships.push_back( shipdraw );
}

std::shared_ptr<Common::StarSystem> StarSystemDraw::AccessStarSystem()
{
    return m_pStarSystem;
}

std::shared_ptr<Common::IGalaxy> StarSystemDraw::AccessGalaxy()
{
    return m_pGalaxy;
}

Common::Point StarSystemDraw::getPoint()
{
    return m_pStarSystem->getCoordinates();
}
