// TIE-02206 Basic Course, projekti04
//
// Petri Leppänen, 160280
//
// Viikkoharkka03:sta tuttu paloittelija, mutta tehty
// nyt osoittimilla.

#ifndef PALOITTELIJA_HH
#define PALOITTELIJA_HH

#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class Splitter {
  public:
    Splitter();
    ~Splitter();

    // Asetetaan merkkijono, joka halutaan paloitella.
    void asetaPaloiteltavaMerkkijono(const string& merkkijono);

    // Paloitellaan merkkijono parametrina annetun
    // erotinmerkin kohdalta osiin.
    void paloittele(char erotinmerkki, bool ohita_tyhjat = false);

    // Palauttaa tiedon siitä, montako kenttää aiemmin
    // suoritetun paloittelun tuloksena syntyi.
    // (Virhetarkastelut jätetty nyt pois)
    unsigned int kenttienLukumaara() const;

    // Kun merkkijono on paloiteltu, tällä metodilla
    // voidaan pyytää Splitter-oliolta tietty kenttä.
    // Ensimmäisen osoittimen päässä oleva on kenttänumero 1.
    string haeKentta(unsigned int kentan_numero) const;

    // Lisataan kentanteksti talteen eli ns. bushpack nyt vaan osoittimilla.
    void lisaaKenttaanTeksti(string tekstiosa);

  private:
    // Lähtötieto: tätä merkkijonoa paloittele-metodi pätkiin osiin.
    string paloiteltava_;
    unsigned int koko_;

    // Paloittele-metodi tallentaa tuloksen tähän, niin että kun merkkijono on
    // kerran paloiteltu,sen kenttiin päästään käsiksi.
    struct Kentat_ {
        string kentanteksti_;
        shared_ptr<Kentat_> nextptr_;
    };

    shared_ptr<Kentat_> firstprt_;
    shared_ptr<Kentat_> lastprt_;
};

#endif // PALOITTELIJA_HH
