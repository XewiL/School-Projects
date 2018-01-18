#include "player.h"

Player::Player( std::shared_ptr<Common::ShipEngine> engine,
                std::shared_ptr<Common::StarSystem> initialLocation,
                std::shared_ptr<Common::IEventHandler> events)
    : Ship( engine, initialLocation, events )
{
    // Luodaan pixmap kuvasta, joka on resurssina.
    setPixmap(QPixmap(":/images/player.png"));
    setName( "Player" );
}

bool Player::decideAction()
{
    // Pelaaja alus ei tee actioneita.
    return false;
}
