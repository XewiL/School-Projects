// TIE-02206 Basic Course, projekti04
//
// Petri Leppänen, 160280
//
// Tietokannan rakentaminen ja toiminta osoittimilla

#ifndef TIETOKANTA_HH
#define TIETOKANTA_HH

#include <iostream>
#include <string>
#include <memory>

using namespace std;

class Tietokanta {
public:
    Tietokanta();
    ~Tietokanta();

    void rakennaTietokanta(unsigned int maara);
    void lisaaTehtava(unsigned int taso, string tehtava);
    void poistaTehtava(unsigned int poistettavanro);

    void tulostaTehtavat() const;
    void tulostaSeuraavaJaPoista();

    unsigned int taulukonKoko() const;
    unsigned int tehtavienMaara() const;

// Muistio koostuu tehtävän tärkeystasoista, jossa jonossa aina
// tehtävät jonossa (yhteen suuntaan linkitetty lista).

// (Toteutus mahdollistaisi myös uusien tärkeystasojen lisääminen
// jälkikäteen sen sijaan, että tehdään aina uusi :))
private:
    unsigned int tasojenmaara_;
    unsigned int tehtavienmaara_;

    struct Tehtavat_ {
        string tehtava_;
        shared_ptr<Tehtavat_> seuraavatehtavaptr_;
    };

    struct TarkeysTaso_ {
        unsigned int tasonro_;
        shared_ptr<Tehtavat_> tehtavatfirstptr_;
        shared_ptr<Tehtavat_> tehtavatlastptr_;
        shared_ptr<TarkeysTaso_> seuraavataso_;
    };

    shared_ptr<TarkeysTaso_> tasofirstptr_;
    shared_ptr<TarkeysTaso_> tasolastptr_;
};

#endif // TIETOKANTA_HH
