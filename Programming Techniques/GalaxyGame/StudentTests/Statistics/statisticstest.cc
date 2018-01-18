#include <QString>
#include <QtTest>
#include <memory>

#include "statistics.hh"
#include "stateexception.hh"

//using namespace Student;

class StatisticsTest : public QObject
{
    Q_OBJECT

public:
    StatisticsTest();

private Q_SLOTS:

    void initTest();
    void statisticsCreating();

    void validSavedShips();
    void validLostShips();

    void validPointsSetting();
    void validCreditsSetting();

    void invalidReduceGamingPoints();
    void invalidReduceCredit();
};

StatisticsTest::StatisticsTest()
{
}

void StatisticsTest::initTest()
{
    // Oletusrakentaja luomisen testaus
    // Student::Statistics stats(0, 0 ,0, 0);
    Student::Statistics stats;
    QCOMPARE(stats.getSavedShips(), 0u);
    QCOMPARE(stats.getLostShips(), 0u);
    QCOMPARE(stats.getPoints(), 0u);
    QCOMPARE(stats.getCreditBalance(), 0);
}

// Rakentajan testaus annetuilla arvoilla
void StatisticsTest::statisticsCreating()
{
    Student::Statistics stats(1, 2, 3, 4);
    QCOMPARE(stats.getSavedShips(), 1u);
    QCOMPARE(stats.getLostShips(), 2u);
    QCOMPARE(stats.getPoints(), 3u);
    QCOMPARE(stats.getCreditBalance(), 4);

}

// Järjestelmässä on oikea määrä pelastettuja laivoja
void StatisticsTest::validSavedShips()
{
    // Alussa pitää olla 0
    unsigned int amount = 0;
    Student::Statistics stats;
    QCOMPARE(stats.getSavedShips(), amount);

    // Lisätään kaksi laivaa
    for( int i = 1; i <= 2; i++) {
        stats.addSavedShip();
        ++amount;
    }
    QCOMPARE(stats.getSavedShips(), amount);
}

// Järjestelmässä on oikea määrä pelastettuja laivoja
void StatisticsTest::validLostShips()
{
    // Alussa pitää olla 0
    unsigned int amount = 0;
    Student::Statistics stats;
    QCOMPARE(stats.getLostShips(), amount);

    // / Lisätään kaksi laivaa
    for( int i = 1; i <= 2; i++) {
        stats.addLostShip();
        ++amount;
    }

    QCOMPARE(stats.getLostShips(), 2u);
}

// Järjestelmässä on oikea määrä pisteitä
void StatisticsTest::validPointsSetting()
{
    // Alussa pisteitä on 0
    unsigned int points = 0;
    Student::Statistics stats;
    QCOMPARE(stats.getPoints(), points);

    // Lisätään pisteitä
    unsigned int amount = 10;
    points = points + amount;
    stats.addPoints(amount);
    QCOMPARE(stats.getPoints(), points);

    // Vähennetään pisteitä
    points = points - amount;
    stats.reducePoints(amount);
    QCOMPARE(stats.getPoints(), points);
}

// Järjestelmässä on oikea määrä rahaa
void StatisticsTest::validCreditsSetting()
{
    // Alussa rahaa on o
    int credits = 0;
    Student::Statistics stats;
    QCOMPARE(stats.getCreditBalance(), credits);

    // Lisätään rahaa
    int amount = 10;
    credits = credits + amount;
    stats.addCredits(amount);
    QCOMPARE(stats.getCreditBalance(), credits);

    // Vähennetään rahaa
    amount = 4;
    credits = credits - amount;
    stats.reduceCredits(amount);
    QCOMPARE(stats.getCreditBalance(), credits);
}

// Testataan, että pisteet eivät voi mennä miinukselle
void StatisticsTest::invalidReduceGamingPoints()
{
    // Lisätään 9 ja vähennetään 5
    Student::Statistics stats;
    stats.addPoints(9);
    stats.reducePoints(5);

    // Vähennetään vielä 5 => tulos -1 => pitää tulla poikkeus
    QVERIFY_EXCEPTION_THROWN(stats.reducePoints(5), Common::StateException);
}

// Testataan, että rahan määrä voi mennä miinukselle (meidän asettama raja)
void StatisticsTest::invalidReduceCredit()
{
    // Lisätään 9 ja vähennetään 5
    Student::Statistics stats;
    stats.addCredits(9);
    stats.reduceCredits(5);

    // Vähennetään vielä 5 => tulos -1 => pitää tulla poikkeus
    QVERIFY_EXCEPTION_THROWN(stats.reduceCredits(5), Common::StateException);
}


QTEST_APPLESS_MAIN(StatisticsTest)

#include "statisticstest.moc"
