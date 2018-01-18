#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QColor>
#include "ship.hh"

class Player: public QObject, public QGraphicsPixmapItem, public Common::Ship
{
public:
    Player( std::shared_ptr<Common::ShipEngine> engine,
            std::shared_ptr<Common::StarSystem> initialLocation,
            std::shared_ptr<Common::IEventHandler> events );

    virtual bool decideAction();
};

#endif // PLAYER_H
