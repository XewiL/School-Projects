#include "statistics.hh"


#include <QtDebug>

namespace Student {

Statistics::Statistics()
 :  savedships_(0),
    lostships_(0),
    gamingpoints_(0),
    gamingcredits_(0)
{

}

Statistics::Statistics(unsigned int sships, unsigned int lships, unsigned int points, int credits):
    savedships_(sships), lostships_(lships), gamingpoints_(points), gamingcredits_(credits)
{
  invariantti();
}

Statistics::~Statistics()
{
}

void Statistics::addSavedShip()
{
    ++savedships_;
    invariantti();
}

unsigned Statistics::getSavedShips() const
{
    return savedships_;
}

void Statistics::addLostShip()
{
    ++lostships_;
    invariantti();
}

unsigned Statistics::getLostShips() const
{
    return lostships_;
}

void Statistics::addPoints(unsigned amount)
{
    gamingpoints_ = gamingpoints_ + amount;
    invariantti();
}

void Statistics::reducePoints(unsigned amount)
{
    if (gamingpoints_< amount) {
        throw Common::StateException("Gaming points can't go negative");
    }
    gamingpoints_ = gamingpoints_ - amount;
    invariantti();
}

unsigned Statistics::getPoints() const
{
    return gamingpoints_;
}

void Statistics::addCredits(unsigned amount)
{
    gamingcredits_ = gamingcredits_ + amount;
    invariantti();
}

void Statistics::reduceCredits(unsigned amount)
{
    gamingcredits_ = gamingcredits_ - amount;
    invariantti();
}

int Statistics::getCreditBalance() const
{
    return gamingcredits_;
}

void Statistics::invariantti() const
{
    if (maxLoan_ > gamingcredits_) {
        throw Common::StateException("Credit can't go under max loan");
    }

}
}
