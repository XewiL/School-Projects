#ifndef STARSYSTEMDRAW_H
#define STARSYSTEMDRAW_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QColor>
#include "starsystem.hh"
#include "igalaxy.hh"
#include "ship.hh"
#include "customscene.h"

// Forward declaration.
class CustomScene;

class StarSystemDraw: public QObject, public QGraphicsPixmapItem
{
public:
    StarSystemDraw( std::shared_ptr<Common::IGalaxy> pGalaxy, std::shared_ptr<Common::StarSystem> pStarSystem );

    Common::Point getPoint();
    Common::IGalaxy::ShipVector getShips();
    
    /*!
     * \brief destroyShipDraws tuhoaa laivat ikonit tältä starsystemiltä.
     * \param scene Scene.
     * \post Piirretyt laivat on tuhottu.
     */
    void destroyShipDraws( CustomScene * scene );

    /*!
     * \brief addShipDraw lisää starsystemille uuden laiva ikonin.
     * \param shipdraw Laiva ikoni.
     * \post Laiva on lisätty.
     */
    void addShipDraw( QGraphicsRectItem * shipdraw );

    /*!
     * \brief AccessStarSystem palauttaa jaetun osoittimen starsystemiin.
     */
    std::shared_ptr<Common::StarSystem> AccessStarSystem();

    /*!
     * \brief AccessGalaxy palauttaa jaetun osoittimen galaxyyn.
     */
    std::shared_ptr<Common::IGalaxy> AccessGalaxy();


private:
    std::shared_ptr<Common::IGalaxy> m_pGalaxy;
    std::shared_ptr<Common::StarSystem> m_pStarSystem;
    std::vector< QGraphicsRectItem * > ships;
};

#endif // STARSYSTEMDRAW_H
