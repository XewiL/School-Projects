// TIE-02206 Basic Course, projekti02
//
// Petri Leppänen, 160280
//
// Tietokannan luvun ja virheiden toteutus

#include "paloittelija.hh"
#include "tietokanta.hh"

#include <iostream>
#include <fstream>  // Tiedoston avaaminen
#include <sstream>  // String streamin muuntaminen double
#include <string>
#include <map>

using namespace std;

// Tiedoston yhden string-vektorin virhetarkastelut.
// Palauttaa true, jos rivistä löytyy tehtävänannon vastaista.
bool onkoRivissaVirhe(const Splitter& rivi, string& virheteksti) {

    // Jos tiedoston rivillä eri määrä kuin neljä kenttää.
    if (rivi.kenttien_lukumaara() != 4) {
        virheteksti = "Error: the input file can not be read.";
        return true;
    }

    // Käydään paloittelija-vektorin kaikki indeksit läpi joita
    // tiedetään olevan nyt neljä kpl.
    for (int i = 0; i < 4; ++i) {
        // Kentät tiedoston riveillä eivät saaneet olla tyhjiä.
        if (rivi.hae_kentta(i).empty()) {
            virheteksti = "Error: the input file can not be read.";
            return true;
        }
        // Kentässä ei saanut olla välilyöntejä.
        if (rivi.hae_kentta(i).find(" ") != string::npos) {
            virheteksti = "Error: the input file can not be read.";
            return true;
        }
    }

    // Viimeisen kentän pitää olla numero.
    double temppi;
    istringstream stream(rivi.hae_kentta(3));
    if (!(stream >> temppi)) {
        virheteksti = "Error: the input file can not be read.";
        return true;
    }
    // Vielä pitää tarkistaa, että numeroiden perässä ei ole mitään,
    // eli viimeisessä kentässä ei ole muuta kuin numeroita
    // joka myöhemmin voidaan muuntaa.
    if ( stream.peek() != EOF ) {
        virheteksti = "Error: the input file can not be read.";
        return true;
    }
    // Muussa tapauksessa rivissä ei ollut virheitä eli palautetaan false
    return false;
}


// Luetaan annettu tiedosto ja tehdään samalla virhetarkasteluja
// projektin vaatimalla tasolla ja annetaan niistä virheilmoitus.
// virheteksti viiteparametrina ei sikäli olisi tarvinnut
// (koska nyt syy on aina sama), mutta itse olisin kyllä halunnut tietää
// syyn miksi tiedostonluku epäonnistui.Virhetekstin näin olisi voinut
// kantaa pääohjelmaan takaisin ja printata siellä ulos.
bool lueTiedosto(Tietorakenne& kaupat, const string& tiedosto, string& virheteksti) {
    char erotinmerkki = ';';
    ifstream tiedosto_olio(tiedosto);

    // Aukeaako tiedosto josta luetaan.
    if(!tiedosto_olio) {
        virheteksti = "Error: the input file can not be read.";
        return false;

    } else {
        string rivi;

        // Luetaan tiedosto-streamia rivi kerrallaan ja työnneään se paloittelijaan
        // joka on toteutettu viikkoharjoituksissa aikaisemmin.
        while (getline(tiedosto_olio, rivi)) {

            Splitter rivillinentekstia;

            rivillinentekstia.aseta_paloiteltava_merkkijono(rivi);
            rivillinentekstia.paloittele(erotinmerkki);

            // Tarkastetaan rivin oikeellisuus.
            // Jos todennetaan että rivissä on virhe, lukeminen lopetetaan
            // heti ja suljetaan tiedosto-streami.
            if (onkoRivissaVirhe(rivillinentekstia, virheteksti)) {
                tiedosto_olio.close();
                return false;
            }

            // Rivin oikeellisuus on nyt projektin02 vaatimusten mukaisella
            // tavalla testattu, voidaan rakentaa tietorakennetta rivistä
            // saaduilla kentillä.
            // Tiedostossa tiedot ovat muodossa:
            // <kauppa>;<sijainti>;<tuote>;<hinta>
            kaupat.asetaKauppaketju(rivillinentekstia.hae_kentta(0));
            kaupat.asetaKauppa(rivillinentekstia.hae_kentta(0),
                               rivillinentekstia.hae_kentta(1));
            kaupat.asetaTuote(rivillinentekstia.hae_kentta(0),
                               rivillinentekstia.hae_kentta(1),
                               rivillinentekstia.hae_kentta(2),
                               stod(rivillinentekstia.hae_kentta(3))); // hinta = double
        }
    }
    // Suljetaan tiedosto-streami, kun koko tiedosto ollaan luettu
    // ja palautetaan true.
    tiedosto_olio.close();
    return true;
}
