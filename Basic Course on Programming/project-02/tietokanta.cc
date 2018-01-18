// TIE-02206 Basic Course, projekti02
//
// Petri Leppänen, 160280
//
// Tietorakenne -luokan määrittelyt.

#include "tietokanta.hh"

#include <iostream>
#include <iomanip>  // setprecision()
#include <string>
#include <map>
#include <vector>
#include <cmath>    // abs()

using namespace std;

// Oletusrakentaja
Tietorakenne::Tietorakenne():
    kaikkikaupat_ () {
}

// Jos kauppaketjua ei ennestään ole niin lisätään se.
// insert tosin ei tee mitään jos tieto-pari ennestään löytyisikin,
// mutta selkeemmin näin.
void Tietorakenne::asetaKauppaketju(string nimi) {
    if (kaikkikaupat_.find(nimi) == kaikkikaupat_.end()) {
        kaikkikaupat_.insert({nimi, { } });
    }
}

void Tietorakenne::asetaKauppa(string ketju, string sijainti) {
    if(kaikkikaupat_.at(ketju).find(sijainti) == kaikkikaupat_.at(ketju).end()) {
        kaikkikaupat_.at(ketju).insert({sijainti, { }});
    }
}

void Tietorakenne::asetaTuote(string ketju, string kauppa, string tuote, double hinta) {
    if (kaikkikaupat_.at(ketju).at(kauppa).find(tuote)
            == kaikkikaupat_.at(ketju).at(kauppa).end()) {
        kaikkikaupat_.at(ketju).at(kauppa).insert({tuote, hinta});
    }

    // Tehtävänannon mukaan, jos tuote jo ennestään oli tietorakenteessa
    // päivittyy uusi hinta.
    if (kaikkikaupat_.at(ketju).at(kauppa).find(tuote)
            != kaikkikaupat_.at(ketju).at(kauppa).end()) {
        kaikkikaupat_.at(ketju).at(kauppa).at(tuote) = hinta;
    }
}

// -- Tulostaminen --
void Tietorakenne::tulostaKauppaketjut() const {
    for (const auto& iteraattori : kaikkikaupat_){
        cout << iteraattori.first << endl;
    }
}

void Tietorakenne::tulostaKaupat(string ketju) const {
    if (kaikkikaupat_.find(ketju) != kaikkikaupat_.end()) {
        for (const auto& iteraattori : kaikkikaupat_.at(ketju)) {
            cout << iteraattori.first << endl;
        }

    } else {
        // Jos ei löydy, ilmoitetaan virhetulostuksella.
        cout << "Error: chain not found." << endl;
    }
}

void Tietorakenne::tulostaKaupanTuotteet(string ketju, string kauppa) const {
    if (kaikkikaupat_.find(ketju) != kaikkikaupat_.end()) {
        if (kaikkikaupat_.at(ketju).find(kauppa) !=
                kaikkikaupat_.at(ketju).end()) {
            for (const auto& iteraattori : kaikkikaupat_.at(ketju).at(kauppa)) {
                // Tulostus haluttiin {Tuote, hinta} ja hinta kahdella desimaalilla.
                cout << iteraattori.first << " "
                     << setprecision (2) << fixed << iteraattori.second << endl;
            }
        } else {
            // Jos ei löydy, ilmoitetaan virhetulostuksella.
            cout << "Error: store not found." << endl;
        }
    } else {
        // Jos ei löydy, ilmoitetaan virhetulostuksella.
        cout << "Error: chain not found." << endl;
    }
}

// Hakiessa halvinta tuotetta tallennetaan hinta sekä halvimman
// hinnan paikat vektoriin.
void Tietorakenne::tulostaHalvin(string tuotteennimi) const {
    // Vertailuhinnaksi ennen hakua asetetaan iso luku,
    // johon verrataan ensimmäisenä.
    double halvinhinta = 9999;

    // Halvimman kauppaketjun nimi sekä sijainti eri vektoreihin.
    vector<string> halvinketju;
    vector<string> halvinkauppa;

// Haku while-loopilla tehty itse oppimisen takia ja jätetty komemmentteihin.
//
//    KauppaketjutMap::iterator ketjut_iter = kaikkikaupat_.begin();
//    while (ketjut_iter != kaikkikaupat_.end()) {
//        KauppojenSijainnitMap::iterator kaupat_iter = ketjut_iter->second.begin();
//        while (kaupat_iter != (ketjut_iter->second).end()) {
//            HinnastoMap::iterator hinnasto_iter = kaupat_iter->second.begin();
//            while (hinnasto_iter != (kaupat_iter->second).end()) {
//                if (hinnasto_iter->first == tuotteennimi) {
//                    if (hinnasto_iter->second == halvinhinta) {
//                        halvinketju.push_back(ketjut_iter->first);
//                        halvinkauppa.push_back(kaupat_iter->first);
//                    }
//                    if (hinnasto_iter->second < halvinhinta) {
//                        halvinhinta = hinnasto_iter->second;
//                        halvinketju.clear();
//                        halvinkauppa.clear();
//                        halvinketju.push_back(ketjut_iter->first);
//                        halvinkauppa.push_back(kaupat_iter->first);
//                    }
//                }
//                ++hinnasto_iter;
//            }

//            ++kaupat_iter;
//        }

//        ++ketjut_iter;
//    }

    for (const auto& iter_ketjut : kaikkikaupat_) {
        for (const auto& iter_kaupat : iter_ketjut.second) {
            // Etsitään tuote, jos löydetään -> vertailu.
            if (iter_kaupat.second.find(tuotteennimi)
                    != iter_kaupat.second.end()) {
                // double -muuttujia ei koskaan pitäisi yhtäsuuruusvertailla
                // joten tehty näin. Tosin tässä tapauksessa tuskin olisi tullut
                // mitään pyöristysvirheitä kun ei ole tehty mitään laskutoimituksiakaan.
                // Eli jos hinta oli sama kuin edellinen halvin, lisätään vektoreihin
                // kauppa sekä sijainti lisää.
                if (abs(iter_kaupat.second.at(tuotteennimi) - halvinhinta) < 1E-8) {
                    halvinketju.push_back(iter_ketjut.first);
                    halvinkauppa.push_back(iter_kaupat.first);
                }
                // Jos lyödetään uusi halvin hinta, päivitetään uusi hinta
                // sekä tyhjennetään vektori ja lisätään vektoriin halvimman sijainti.
                if (iter_kaupat.second.at(tuotteennimi) < halvinhinta) {
                    halvinhinta = iter_kaupat.second.at(tuotteennimi);
                    halvinketju.clear();
                    halvinkauppa.clear();
                    halvinketju.push_back(iter_ketjut.first);
                    halvinkauppa.push_back(iter_kaupat.first);
                }
            }
        }
    }

    // Jos vektori(t) on tyhjä, ei tuotetta löytynyt mistään.
    if (halvinketju.empty()) {
        cout << "This product is not available anywhere." << endl;
    } else {
        // Tulostus tehtävänannon mukaan, hinta kahdella desimaalilla ja
        // kauppaketjun nimi sekä sijainti.
        cout << setprecision(2) << fixed << halvinhinta << endl;
        vector<string>::iterator i = halvinketju.begin();
        vector<string>::iterator j = halvinkauppa.begin();
        while (i != halvinketju.end()) {
            cout << *i << " " << *j << endl;
            ++i;
            ++j;
        }
    }
}
