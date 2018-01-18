// TIE-02206 Basic Course, projekti02
// --
// Kauppojen tuotteiden tietorakenteen rakentaminen tietokannasta
// ja sieltä tietojen hakeminen.
// --
// Petri Leppänen, 160280

#include "paloittelija.hh"
#include "tiedostonluku.hh"
#include "tietokanta.hh"

#include <iostream>
#include <string>
#include <map>


using namespace std;

// Pääohjelma käyttöliittymää varten.
int main() {
    bool jatketaanko = true;
    Tietorakenne kaupat;
    string virheteksti;
    string tiedoston_nimi = "products.txt";
    
    // Syötetään tietokanta (txt-tiedosto), josta luetaan tiedot
    // ja jonka perusteella luodaan tietorakenne.
    if (!lueTiedosto(kaupat, tiedoston_nimi, virheteksti)) {
        cout << virheteksti << endl;
        jatketaanko = false;
    }

    // Jos tiedoston lukeminen jollain tapaa epäonnistuu,
    // niin ohjelma päättyy samantien.
    while (jatketaanko) {
        cout << "product search> ";
        string syoterivi;
        getline(cin, syoterivi);

        Splitter syote;
        char erotinmerkki = ' ';

        // Paloittelijaan syötetään käyttäjän antama komento,
        // jonka perusteella toimitaan jatkossa.
        //
        // Sallitut komennot:
        // quit -> lopettaa ohjelman
        // chains -> tulostaa kaikki kauppaketjut
        // stores <ketjun nimi> -> tulostaa kauppaketjun kaikki kaupat
        // selection <ketjun nimi> <kaupan nimi> -> tulostaa kaupan kaikki tuotteet ja vastaavat hinnat
        // cheapest <tuotteen nimi> -> hakee halvimman tuotteen hinnan ja kaupa(n/t)

        syote.aseta_paloiteltava_merkkijono(syoterivi);
        syote.paloittele(erotinmerkki);
        
        if (syote.hae_kentta(0) == "quit" && syote.kenttien_lukumaara() == 1) {
            break;
        }
        else if (syote.hae_kentta(0) == "chains" && syote.kenttien_lukumaara() == 1) {
            kaupat.tulostaKauppaketjut();
        }
        else if (syote.hae_kentta(0) == "stores" && syote.kenttien_lukumaara() == 2) {
            kaupat.tulostaKaupat(syote.hae_kentta(1));
        }
        else if (syote.hae_kentta(0) == "selection" && syote.kenttien_lukumaara() == 3) {
            kaupat.tulostaKaupanTuotteet(syote.hae_kentta(1), syote.hae_kentta(2));
        }
        else if (syote.hae_kentta(0) == "cheapest" && syote.kenttien_lukumaara() == 2){
            kaupat.tulostaHalvin(syote.hae_kentta(1));
        }
        else {
            cout << "Error: unknown command." << endl;
        }
    }
}
