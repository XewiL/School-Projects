// TIE-02206 Basic Course, projekti02
//
// Petri Leppänen, 160280
//
// Viikkoharkka03:sta tuttu paloittelija, jonka mallikoodia
// sai käyttää suoraan.

#include "paloittelija.hh"

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>


using namespace std;

Splitter::Splitter(const string& paloiteltava_merkkijono):
    paloiteltava_(paloiteltava_merkkijono), kentat_( {} ) {
}


void Splitter::aseta_paloiteltava_merkkijono(const string& merkkijono) {
    paloiteltava_ = merkkijono;
    kentat_ = {};  // kentat.clear();
}


void Splitter::paloittele(char erotinmerkki, bool ohita_tyhjat) {
    // Tyhjennetään kentat_-vektori siltä varalta, että samaa oliota
    // on jo aiemmin käytetty jokin toisen merkkijonon paloitteluun,
    // minkä seurauksena vektorissa on jotain vanhaa tietoa.
    kentat_.clear();

    // Alkukohta pitää kirjaa siitä, missä kohdassa merkkijonoa
    // on seuraava kenttä, jota ei vielä ole siirretty kentat_-vektoriin.
    string::size_type alkukohta = 0;
    string kentan_teksti;

    while ( true ) {
        // Loppukohtaan etsitään find-metodilla, missä kohdassa
        // on ensimmäinen alkukohdan jälkeen tuleva erotinmerkki.
        string::size_type loppukohta;

        loppukohta = paloiteltava_.find(erotinmerkki, alkukohta);

        // Jos alkukohdan perästä ei löydy erotinmerkkiä, merkkojonossa
        // on enää yksi kenttä jäljellä (viimeinen kenttä, jonka perässä
        // ei ole erotinmerkkiä).  Käsitellään se erikseen silmukän perässä.
        if ( loppukohta == string::npos ) {
            break;
        }

        // Otetaan talteen kentän sisältö indeksien
        // alkukohta ja loppukohta välistä.
        kentan_teksti = paloiteltava_.substr(alkukohta, loppukohta - alkukohta);

        // Tyhjiä kenttiä ei tallenneta, mikäli parametri
        // ohita_tyhjat on true.
        if ( not (ohita_tyhjat and kentan_teksti.empty()) ) {
            kentat_.push_back(kentan_teksti);
        }

        // Siirretään alkukohta seuraavan käsittelemättömän
        // kentän ensimmäiseen merkkiin.
        alkukohta = loppukohta + 1;
    }

    // Otetaan viimeisen erotinmerkin perässä oleva teksti talteen.
    // koska se on rivin viimeinen kenttä.
    kentan_teksti = paloiteltava_.substr(alkukohta);

    if ( not (ohita_tyhjat and kentan_teksti.empty()) ) {
        kentat_.push_back(kentan_teksti);
    }
}


unsigned int Splitter::kenttien_lukumaara() const {
    // Paloittelua ei ole suoritettu, jos kentat_-vektori on tyhjä.
    if ( kentat_.size() == 0 ) {
        return SPLITTER_VIRHE;

    } else {

        return kentat_.size();
    }
}


string Splitter::hae_kentta(unsigned int kentan_numero) const {
    // Paloittelua ei ole suoritettu tai kentän numero on liian suuri.
    if ( kentat_.empty() or kentan_numero >= kentat_.size() ) {
        throw out_of_range("virheellinen kentan_numero");
    }

    return kentat_.at(kentan_numero);
}
