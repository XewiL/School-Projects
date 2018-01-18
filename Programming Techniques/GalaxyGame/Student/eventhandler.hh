#ifndef EVENTHANDLER_HH
#define EVENTHANDLER_HH


#include "ieventhandler.hh"
#include "../Course/point.hh"
#include "../Course/ship.hh"
#include "customscene.h"
#include "statistics.hh"

namespace Student {
class EventHandler: public Common::IEventHandler
{
public:
    EventHandler();
    ~EventHandler();
    void shipSpawned(std::shared_ptr<Common::Ship> ship);
    void shipRemoved(std::shared_ptr<Common::Ship> ship);
    void shipRelocated(std::shared_ptr<Common::Ship> ship,
                       std::shared_ptr<Common::StarSystem> starSystem);
    void shipMoved(std::shared_ptr<Common::Ship> ship,
                   Common::Point origin,
                   Common::Point target);
    void exceptionInExecution(std::shared_ptr<Common::Ship> ship, std::string const& msg);
    void distressOn(std::shared_ptr<Common::Ship> ship);
    void distressOff(std::shared_ptr<Common::Ship> ship);
    void shipAbandoned(std::shared_ptr<Common::Ship> ship);

    /*!
     * \brief setPointers asettaa tarvittavat pointerit.
     * \param pScene Scene.
     * \param pStatistic Statistic.
     */
    void setPointers( CustomScene * pScene, Student::Statistics * pStatistic );

private:
    CustomScene* m_pScene;
    Student::Statistics* m_pStatistic;
};
}

#endif // EVENTHANDLER_HH
