// TIE-02206 Basic Course, projekti02
//
// Petri Leppänen, 160280
//
// Moduulin esittely, joka hoitaa tietokannan luvun sekä virhetarkastelut
// annetusta tiedostosta (tietokannasta).

#ifndef TIEDOSTONLUKU_HH
#define TIEDOSTONLUKU_HH

#include "paloittelija.hh"
#include "tietokanta.hh"

#include <iostream>
#include <string>

using namespace std;

bool lueTiedosto(Tietorakenne& kaupat, const string& tiedosto, string& virheteksti);
bool onkoRivissaVirhe(const Splitter& rivi, string& virheteksti);


#endif // TIEDOSTONLUKU_HH
