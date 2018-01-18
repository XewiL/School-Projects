#include "eventhandler.hh"
#include <QTextStream>

Student::EventHandler::EventHandler()
{
    //QTextStream(stdout) << "EvenHandler constructor" << endl;
}

Student::EventHandler::~EventHandler()
{
    //QTextStream(stdout) << "EvenHandler destructor"<< endl;
}

void Student::EventHandler::shipSpawned(std::shared_ptr<Common::Ship> ship)
{
    //QTextStream(stdout) << "ShipSpawned:" << ship->getName().c_str()<< endl;
    m_pScene->redrawStarSystemShips( ship->getLocation() );
}

void Student::EventHandler::shipRemoved(std::shared_ptr<Common::Ship> ship)
{
    //QTextStream(stdout) << "ShipRemoved:" << ship->getName().c_str()<< endl;
    m_pScene->redrawStarSystemShips( ship->getLocation() );
}

void Student::EventHandler::shipRelocated(std::shared_ptr<Common::Ship> ship,
                   std::shared_ptr<Common::StarSystem> starSystem)
{
    //QTextStream(stdout) << "ShipRelocated:" << ship->getName().c_str();
    m_pScene->redrawStarSystemShips( ship->getLocation() );

    if( starSystem != nullptr )
    {
    //    QTextStream(stdout) << ", " << starSystem->getName().c_str()<< endl;
        m_pScene->redrawStarSystemShips( starSystem );
    }
    //else
    //    QTextStream(stdout) << " " << endl;
}

void Student::EventHandler::shipMoved(std::shared_ptr<Common::Ship> ship,
               Common::Point origin,
               Common::Point target)
{
    // Warningit pois.
    origin.toString();
    target.toString();
    //QTextStream(stdout) << "ShipMoved:" << ship->getName().c_str()<< endl;
    m_pScene->redrawStarSystemShips( ship->getLocation() );
}

void Student::EventHandler::exceptionInExecution(std::shared_ptr<Common::Ship> ship, std::string const& msg)
{
    QTextStream(stdout) << "ExceptionInExecution:" << ship->getName().c_str() << ": " << msg.c_str()<< endl;
}

void Student::EventHandler::distressOn(std::shared_ptr<Common::Ship> ship)
{
    //QTextStream(stdout) << "DistressOn:" << ship->getName().c_str()<< endl;
    m_pScene->redrawStarSystemShips( ship->getLocation() );
}

void Student::EventHandler::distressOff(std::shared_ptr<Common::Ship> ship)
{
    //QTextStream(stdout) << "DistressOff:" << ship->getName().c_str()<< endl;
    m_pScene->redrawStarSystemShips( ship->getLocation() );
    m_pStatistic->addSavedShip();
}

void Student::EventHandler::shipAbandoned(std::shared_ptr<Common::Ship> ship)
{
    //QTextStream(stdout) << "ShipAbandoned:" << ship->getName().c_str()<< endl;
    m_pScene->redrawStarSystemShips( ship->getLocation() );
     m_pStatistic->addLostShip();
}

void Student::EventHandler::setPointers(CustomScene *pScene, Student::Statistics* pStatistic)
{
    m_pScene = pScene;
    m_pStatistic = pStatistic;
}

