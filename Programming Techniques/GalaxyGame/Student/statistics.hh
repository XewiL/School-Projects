#ifndef STATISTICS_HH
#define STATISTICS_HH

#include "istatistics.hh"
#include "stateexception.hh"

namespace Student {


/*!
 * \file statistics.hh
 * \brief The Statistics class
 */
class Statistics : public Common::IStatistics
{

public:
    /*!
     * \brief Rakentaja alustaa tilastot alkuarvoon 0
     * \pre sships >= 0 && lships >= 0 && points >= 0 && credits >= 0
     */
    Statistics(unsigned int sships, unsigned int lships, unsigned int points, int credits);

    Statistics();
    ~Statistics();

    /*!
     * \brief addSavedShip asettaa pelastetun aluksen määrää yhdellä
     * \pre
     * \exception
     */
    void addSavedShip();

    /*!
     * \brief getSavedShips palautta pelastettujen alusten määrän
     * \pre
     * \exception
     * \return Statisticsin savedships_
     */
    unsigned getSavedShips() const;

    /*!
     * \brief addLostShip asettaa kadotetun aluksen määrää yhdellä
     * \pre
     * \exception
     */
    void addLostShip();

    /*!
     * \brief getLostShips palauttaa kadotettujen alusten määrän
     * \pre
     * \exception
     * \return Statisticsin lostships_
     */
    unsigned getLostShips() const;

    /*!
     * \brief addPoints lisää pistemäärää
     * \param amount montako pistettä lisätään
     * \pre
     * \post Pistemäärää on lisätty amount määrä lisää
     * \exception
     */
    void addPoints(unsigned amount);

    /*!
     * \brief reducePoints vähentää pistemäärää
     * \param amount montako pistettä vähennetään
     * \pre gamingpoints >= 0
     * \post Pistemäärää on vähennetty amount määrä
     * \exception Vähennyksen jälkeen menee miinukselle
     */
    void reducePoints(unsigned amount);

    /*!
     * \brief getPoints palauttaa pistemäärän
     * \return Statisticsin gamingpoints_
     */
    unsigned getPoints() const;

    /*!
     * \brief addCredits lisää rahaa
     * \param amount paljonko rahaa lisätään
     * \pre
     * \post Rahaa on lisätty amount määrä lisää
     * \exception
     */
    void addCredits(unsigned amount);

    /*!
     * \brief reduceCredits vähentää rahaa
     * \param amount paljonko rahaa lisätään
     * \pre gamingcredits >= 0
     * \post Rahaa on lisätty amount määrä lisää
     * \exception Saldo menee minuukselle vähennyksen jälkeen
     */
    void reduceCredits(unsigned amount);

    /*!
     * \brief getCreditBalance palauttaa rahamäärän
     * \pre
     * \exception
     * \return Statisticsin gamingcredits_
     */
    int getCreditBalance() const;

private:
    unsigned int savedships_;
    unsigned int lostships_;
    unsigned int gamingpoints_;
    int gamingcredits_;
    const int maxLoan_ = 0;

    void invariantti() const;
};

}//Student

#endif // STATISTICS_HH
