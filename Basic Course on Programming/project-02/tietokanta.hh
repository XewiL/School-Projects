// TIE-02206 Basic Course, projekti02
//
// Petri Leppänen, 160280
//
// Tietorakenne -luokan esittely, jossa yksinkertaisuudessaan on
// rakenteeseen tiedon asettaminen ja tulostaminen.

#ifndef TIETOKANTA_HH
#define TIETOKANTA_HH

#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;


class Tietorakenne {
public:
    Tietorakenne();

    void asetaKauppaketju(string nimi);
    void asetaKauppa(string ketju, string sijainti);
    void asetaTuote(string ketju, string kauppa, string tuote, double hinta);

    void tulostaKauppaketjut() const;
    void tulostaKaupat(string ketju) const;
    void tulostaKaupanTuotteet(string ketju, string kauppa) const;
    void tulostaHalvin(string tuotteennimi) const;

private:
    // Tietorakenne muotoa
    // {Kauppaketju, {Sijainti, {Tuote, Hinta} } }

    map<string, map<string, map<string, double>>> kaikkikaupat_;
};

#endif // TIETOKANTA_HH
