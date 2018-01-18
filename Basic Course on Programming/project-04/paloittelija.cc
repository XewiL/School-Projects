// TIE-02206 Basic Course, projekti04
//
// Petri Leppänen, 160280
//
// Viikkoharkka03:sta tuttu paloittelija, joka nyt muokattu
// toimimaan osoittimilla.

#include "paloittelija.hh"

#include <iostream>
#include <string>
#include <memory>


Splitter::Splitter():
    paloiteltava_(""), koko_(0), firstprt_(nullptr), lastprt_(nullptr) {
}

Splitter::~Splitter() {
    paloiteltava_ = "";
    koko_ = 0;
    firstprt_ = nullptr;
    lastprt_ = nullptr;
}


void Splitter::asetaPaloiteltavaMerkkijono(const string& merkkijono) {
    paloiteltava_ = merkkijono;
    firstprt_ = nullptr; // Samalla tulee tyhjennettyä vanha lista jos on käytetty ennen.
    lastprt_ = nullptr;
}


void Splitter::paloittele(char erotinmerkki, bool ohita_tyhjat) {
    // Alkukohta pitää kirjaa siitä, missä kohdassa merkkijonoa
    // on seuraava kenttä, jota ei vielä ole siirretty kentat_-vektoriin.
    string::size_type alkukohta = 0;
    string kentan_teksti;

    while (true) {
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
        if (!(ohita_tyhjat and kentan_teksti.empty()) ) {
            lisaaKenttaanTeksti(kentan_teksti);
        }

        // Siirretään alkukohta seuraavan käsittelemättömän
        // kentän ensimmäiseen merkkiin.
        alkukohta = loppukohta + 1;
    }

    // Otetaan viimeisen erotinmerkin perässä oleva teksti talteen.
    // koska se on rivin viimeinen kenttä.
    kentan_teksti = paloiteltava_.substr(alkukohta);

    if (!(ohita_tyhjat && kentan_teksti.empty()) ) {
        lisaaKenttaanTeksti(kentan_teksti);
    }
}

unsigned int Splitter::kenttienLukumaara() const {
    return koko_;
}

// Haetaan kentän numerossa oleva tieto.
string Splitter::haeKentta(unsigned int kentan_numero) const {
    shared_ptr<Kentat_> iterptr = firstprt_;

    // Loopataan kunnes löydetään oikea kohta jonosta.
    for (unsigned int i = 1; i < kentan_numero; ++i) {
        iterptr = iterptr->nextptr_;
    }
    return iterptr->kentanteksti_;
}

// Työnnetään seuraava tekstiosa jonon perälle.
void Splitter::lisaaKenttaanTeksti(string tekstiosa) {
    shared_ptr<Kentat_> uusiptr(new Kentat_);

    uusiptr->kentanteksti_ = tekstiosa;
    uusiptr->nextptr_ = nullptr;

    // Jos lisätään ensimmäinen osa.
    if (firstprt_ == nullptr) {
        firstprt_ = uusiptr;
        lastprt_ = uusiptr;

    // Työnnetään seuraava osa aina jonon perälle.
    } else {
        lastprt_->nextptr_ = uusiptr;
        lastprt_ = uusiptr;
    }
    ++koko_;
}
