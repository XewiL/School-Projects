#ifndef CUSTOMSCENE_H
#define CUSTOMSCENE_H

#include <QGraphicsScene>
#include <QPoint>
#include <QMouseEvent>
#include "player.h"
#include "starsystem.hh"
#include "starsystemdraw.h"
#include "distressaction.hh"
#include "repairaction.hh"
#include "cargoship.hh"
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QGraphicsTextItem>

// Forward declaration.
class StarSystemDraw;

class CustomScene: public QGraphicsScene
{    
    /**
     * @brief CustomScene hallitsee piirrettäviä asioita sekä hiiri ja näppäimistö klikkauksia.
     *
     */
public:

    /*!
     * \brief Rakentaja, alustaa zoomin ja origin pisteen.
     */
    CustomScene();

    /*!
     * \brief redrawAll piirtää kaikki scenessa olevat asiat uudelleen.
     */
    void redrawAll();

    /*!
     * \brief redrawStarSystemShips piirtää starsystemissä olevat laivat.
     * \param pStarSystem jaettu osoitin starsystemiin.
     */
    void redrawStarSystemShips( std::shared_ptr<Common::StarSystem> pStarSystem );


public slots:

    /*!
     * \brief mousePressEvent seuraa hiiren klikkauksia, liikutetaan pelaajaa
     * \param event
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    /*!
     * \brief keyPressEvent seuraa näppäimistön klikkauksia, liikutetaan maailmaa
     * \param event
     */
    void keyPressEvent(QKeyEvent *event);

    void mouseMoveEvent(QMouseEvent * mouseEvent);

signals:
    void sendGalaxyName(std::string name);
    void sendGalaxyPop(uint64_t pop);
    void sendGalaxyEco(Common::StarSystem::ECONOMY_TYPE eco);

private:

    Common::Point origo = Common::Point(30,30);
    std::vector< std::shared_ptr<Common::Ship> > distressShips;
    float zoom;

    /*!
     * \brief redrawShipsInStarSystem piirtää laivat starsystemiin
     * \param StarSystemDraw pointer jonka laivat piirretään.
     */
    void redrawShipsInStarSystem(StarSystemDraw* ss);
};

#endif // CUSTOMSCENE_H
