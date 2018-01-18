#include "galaxy.hh"
#include <algorithm>

Student::Galaxy::Galaxy()
{

}
Student::Galaxy::~Galaxy()
{

}

void Student::Galaxy::addShip(std::shared_ptr<Common::Ship> ship)
{
    // Loop current ships.
    for( auto &s : vecShips )
    {
        // Throw error if ship already exists.
        if( s == ship )
            throw Common::StateException("Cannot add same ship twice");
    }

    // Add ship to galaxy.
    vecShips.push_back( ship );
}

void Student::Galaxy::removeShip(std::shared_ptr<Common::Ship> ship)
{
    // Find given ship from galaxy.
    auto it = std::find( vecShips.begin(), vecShips.end(), ship );

    // Erase found ship, if not found throw exception.
    if( it == vecShips.end() )
        throw Common::ObjectNotFoundException("Ship to be removed was not found");
    else
        vecShips.erase( it );
}

void Student::Galaxy::addStarSystem(std::shared_ptr<Common::StarSystem> starSystem)
{
    // Loop current star systems.
    for( auto &ss : vecStarSystem )
    {
        // Validate that star systems does not exists.
        if( ss->getName() == starSystem->getName() )
            throw Common::StateException("Cannot add starsystem with name that exist already" );
        if( ss->getId() == starSystem->getId() )
            throw Common::StateException("Cannot add starsystem with ID that exist already" );
        if( ss->getCoordinates() == starSystem->getCoordinates() )
            throw Common::StateException("Cannot add starsystem to same location.");
    }

    // Add star system to galaxy.
    vecStarSystem.push_back( starSystem );
}

std::shared_ptr<Common::IGalaxy::ShipVector> Student::Galaxy::getShips()
{
    // Return shared pointer to ships in galaxy.
    return std::make_shared<Common::IGalaxy::ShipVector>( vecShips );
}

Common::StarSystem::StarSystemVector Student::Galaxy::getSystemsInRange(std::shared_ptr<Common::StarSystem> origin, int range)
{
    // Loop star systems in galaxy.
    Common::StarSystem::StarSystemVector vecStarSystemsInRange;
    bool bOriginFound = false;
    for( auto &ss : vecStarSystem )
    {
        // Do not add itself.
        if( ss->getId() == origin->getId() )
        {
            // Origin found from this  galaxy.
            bOriginFound = true;
            continue;
        }

        // Do not add if distance is to far.
        if( Common::distance(
                    ss->getCoordinates().x,
                    ss->getCoordinates().y,
                    origin->getCoordinates().x,
                    origin->getCoordinates().y
                    )
                > range )
            continue;

        // Add to output vector.
        vecStarSystemsInRange.push_back( ss );
    }

    // If origin star system was not found from galaxy, throw error.
    if( !bOriginFound )
        throw Common::ObjectNotFoundException( "Did not found origin from galaxy" );

    // Return star systems within range.
    return vecStarSystemsInRange;
}

std::shared_ptr<Common::StarSystem> Student::Galaxy::getRandomSystem()
{
    // If no star systems, throw exception.
    if( vecStarSystem.size() == 0 )
        throw Common::ObjectNotFoundException( "No ships found" ) ;

    // Return random star system.
    return vecStarSystem.at( Common::randomMinMax( 0, vecStarSystem.size() - 1 ) );
}

Common::IGalaxy::ShipVector Student::Galaxy::getShipsInStarSystem(std::string name)
{
    // Loop every ship in galaxy.
    Common::IGalaxy::ShipVector vecShipsInStarSystem;
    for( auto &ship : vecShips )
    {
        // If ship location is same as parameter name, add it to output vecotr.
        if( ship->getLocation() != nullptr )
            if( ship->getLocation()->getName() == name )
                vecShipsInStarSystem.push_back( ship );
    }

    // Retrun ships in star system.
    return vecShipsInStarSystem;
}

std::vector<std::string> Student::Galaxy::getSystemNames()
{
    // Loop star systems in galaxy.
    std::vector<std::string> vecNames;
    for( auto &starSystem : vecStarSystem )
    {
        // Push system names to vecotr.
        vecNames.push_back( starSystem->getName() );
    }

    // Return vector with star system names.
    return vecNames;
}

std::shared_ptr<Common::StarSystem> Student::Galaxy::getStarSystemByName(std::string name)
{
    // Loop star systems in galaxy.
    for( auto &starSystem : vecStarSystem )
    {
        // If star system is found by name, return it.
        if( starSystem->getName() == name )
            return starSystem;
    }

    // Not found any star systems by name.
    throw Common::ObjectNotFoundException( "StarSystem not found by name: " + name );
}

std::shared_ptr<Common::StarSystem> Student::Galaxy::getStarSystemById(unsigned id)
{
    // Loop star systems in galaxy.
    for( auto &starSystem : vecStarSystem )
    {
        // If star system is found by id, return it.
        if( starSystem->getId() == id )
            return starSystem;
    }

    // Not found any star systems by id.
    throw Common::ObjectNotFoundException( "StarSystem not found by id: " + id );
}

