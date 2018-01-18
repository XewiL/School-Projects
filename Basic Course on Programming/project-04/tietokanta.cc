// TIE-02206 Basic Course, projekti04
//
// Petri Leppänen, 160280
//
// Muistion tietokannan toiminta.

#include "tietokanta.hh"

#include <iostream>
#include <string>

// Oletusrakentaja
Tietokanta::Tietokanta():
    tasojenmaara_(0), tehtavienmaara_(0),
    tasofirstptr_(nullptr), tasolastptr_(nullptr) {
}

// Purkaja
Tietokanta::~Tietokanta() {
    tasojenmaara_ = 0;
    tehtavienmaara_ = 0;
    tasofirstptr_ = nullptr;
    tasolastptr_ = nullptr;
}

// Luodaan käyttäjän muistio halutulla määrällä tärkeystasoja.
void Tietokanta::rakennaTietokanta(unsigned int maara) {

    // Aikaisemman listan tuhoaminen -> osoittimet = null
    tasofirstptr_ = nullptr;
    tasolastptr_ = nullptr;
    tasojenmaara_ = 0;
    tehtavienmaara_ = 0;

    // Loopataan tasojen määrän mukaan uusia tasoja.
    for (unsigned int i = 0; i < maara; ++i) {
        shared_ptr<TarkeysTaso_> uusiptr(new TarkeysTaso_);

        // Jos luodaan ensimmäinen taso.
        if (tasofirstptr_ == nullptr) {
            tasofirstptr_ = uusiptr;
        } else {
            tasolastptr_->seuraavataso_ = uusiptr;
        }

        // Tason numero on suurimmasta pienimpään.
        uusiptr->tasonro_ = maara - i;

        uusiptr->tehtavatfirstptr_ = nullptr;
        uusiptr->tehtavatlastptr_ = nullptr;
        uusiptr->seuraavataso_ = nullptr;
        tasolastptr_ = uusiptr;

        ++tasojenmaara_;
    }
}

// Lisätään tehtävä halutulle tasolle.
void Tietokanta::lisaaTehtava(unsigned int taso, string tehtava) {
    shared_ptr<Tehtavat_> uusitehtavaptr(new Tehtavat_);
    shared_ptr<TarkeysTaso_> temptasoptr = tasofirstptr_;

    // Tallennetaan tehtävä sekä tiedetään, että työnnetään aina jonon
    // perälle, niin seuraavaptr on aina null.
    uusitehtavaptr->tehtava_ = tehtava;
    uusitehtavaptr->seuraavatehtavaptr_ = nullptr;


    // Etsitään oikea tärkeystaso pointterille.
    // (Suurimmasta pienimpään).
    for (unsigned int i = 0; i < tasojenmaara_ - taso; ++i) {
        temptasoptr = temptasoptr->seuraavataso_;
    }

    // Nyt ollaan löydetty oikea tärkeystaso johon lisätään uusi tehtävä.

    // Lisätään tyhjään tärkeystasoon
    if (temptasoptr->tehtavatfirstptr_ == nullptr) {
        temptasoptr->tehtavatfirstptr_ = uusitehtavaptr;
        temptasoptr->tehtavatlastptr_ = uusitehtavaptr;

    // Lisätään tärkeystason perään.
    } else {
        temptasoptr->tehtavatlastptr_->seuraavatehtavaptr_ = uusitehtavaptr;
        temptasoptr->tehtavatlastptr_ = uusitehtavaptr;
    }
    ++tehtavienmaara_;
}

// Poistetaan haluttu tehtävä.
void Tietokanta::poistaTehtava(unsigned int poistettavanro) {

    // Lähdetään etsimään oikeaa kohtaa muistion alusta.
    unsigned int tehtavanro = 1;
    shared_ptr<TarkeysTaso_> temptasoptr = tasofirstptr_;
    shared_ptr<Tehtavat_> poistatehtavaptr = tasofirstptr_->tehtavatfirstptr_;
    shared_ptr<Tehtavat_> edellinenpoistatehtavaptr = tasofirstptr_->tehtavatfirstptr_;

    // Loopataan tasoja.
    for (unsigned int i = 0; i < tasojenmaara_; ++i) {

        // Loopataan tason tehtäviä.
        while (poistatehtavaptr != nullptr && tehtavanro < poistettavanro) {

            // Siirretään edellistä pointteria yksi tehtävä jäljessä.
            if (poistatehtavaptr == temptasoptr->tehtavatfirstptr_) {
                edellinenpoistatehtavaptr = poistatehtavaptr;
            } else {
                edellinenpoistatehtavaptr = edellinenpoistatehtavaptr->seuraavatehtavaptr_;
            }
            poistatehtavaptr = poistatehtavaptr->seuraavatehtavaptr_;
            ++tehtavanro;
        }

        if (tehtavanro == poistettavanro && poistatehtavaptr != nullptr) {

            // Nyt poistettavan osoitin osoittaa oikeaan alkioon

            // Poistetaan tason ainoa tehtävä.
            if (temptasoptr->tehtavatfirstptr_ == temptasoptr->tehtavatlastptr_) {
                temptasoptr->tehtavatfirstptr_ = nullptr;
                temptasoptr->tehtavatlastptr_ = nullptr;

            // Poistetaan tason ensimmäinen tehtävä.
            } else if (poistatehtavaptr == temptasoptr->tehtavatfirstptr_) {
                temptasoptr->tehtavatfirstptr_ = poistatehtavaptr->seuraavatehtavaptr_;

            // Poistetaan tason viimeinen tehtävä.
            } else if (poistatehtavaptr == temptasoptr->tehtavatlastptr_) {
                temptasoptr->tehtavatlastptr_ = edellinenpoistatehtavaptr;
                temptasoptr->tehtavatlastptr_->seuraavatehtavaptr_ = nullptr;

            // Poistetaan tason keskeltä tehtävä
            } else {
                edellinenpoistatehtavaptr->seuraavatehtavaptr_ = poistatehtavaptr->seuraavatehtavaptr_;
            }
            // Vähennetään kokonaistehtävien määrää yhdellä ja poistutaan funktiosta
            --tehtavienmaara_;
            return;
        }

        // Siirrytään seuraavalle tehtävätasolle jos ei vielä löydetty oikeaa kohtaa.
        temptasoptr = temptasoptr->seuraavataso_;
        if (temptasoptr != nullptr) {
            poistatehtavaptr = temptasoptr->tehtavatfirstptr_;
            edellinenpoistatehtavaptr = temptasoptr->tehtavatfirstptr_;
        }
    }
}

// Tulostetaan näytölle kaikki tehtävät numerojärjestyksessä.
void Tietokanta::tulostaTehtavat() const {
    unsigned int tehtavanro = 1;
    shared_ptr<TarkeysTaso_> temptasoptr = tasofirstptr_;
    shared_ptr<Tehtavat_> printtehtavaptr = tasofirstptr_->tehtavatfirstptr_;

    // Loopataan tasoja.
    for (unsigned int i = 0; i < tasojenmaara_; ++i) {
        if (temptasoptr->tehtavatfirstptr_ != nullptr) {
            cout << "Priority level " << temptasoptr->tasonro_ << ":" << endl;
        }

        // Loopataan tehtäviä.
        while (printtehtavaptr != nullptr) {
            cout << "  " << tehtavanro << ". " << printtehtavaptr->tehtava_ << endl;
            ++tehtavanro;
            printtehtavaptr = printtehtavaptr->seuraavatehtavaptr_;
        }

        // Siirrytään seuraavalle tasolle.
        temptasoptr = temptasoptr->seuraavataso_;
        if (temptasoptr != nullptr) {
            printtehtavaptr = temptasoptr->tehtavatfirstptr_;
        }
    }
}

// Tulostetaan näytölle seuraava tehtävä ja poistetaan kyseinen tehtävä sen jälkeen.
void Tietokanta::tulostaSeuraavaJaPoista() {
    shared_ptr<TarkeysTaso_> temptasoptr = tasofirstptr_;

    // Loopataan tasoja.
    for (unsigned int i = 0; i < tasojenmaara_; ++i) {
        if (temptasoptr->tehtavatfirstptr_ != nullptr) {

            // Nyt löydetty ensimmäinen taso joka ei ole tyhjä.

            // Tulostetaan tason ensimmäinen tehtävä, jonka jälkeen poistetaan se.
            cout << temptasoptr->tehtavatfirstptr_->tehtava_ << endl;

            // Poistetaan tason ainoa tehtävä.
            if (temptasoptr->tehtavatfirstptr_ == temptasoptr->tehtavatlastptr_) {
                temptasoptr->tehtavatfirstptr_ = nullptr;
                temptasoptr->tehtavatlastptr_ = nullptr;

            // Poistetaan tason ensimmäinen tehtävä.
            } else {
                temptasoptr->tehtavatfirstptr_ = temptasoptr->tehtavatfirstptr_->seuraavatehtavaptr_;
            }
            // Vähennetään kokonaistehtävien määrää yhdellä ja poistutaan funktiosta
            --tehtavienmaara_;
            return;
        }

        // Siirrytään seuraavalle tehtävätasolle, jos ei vielä löydetty oikeaa kohtaa.
        temptasoptr = temptasoptr->seuraavataso_;
    }
}

// Palauttaa tärkeystasojen määrän.
unsigned int Tietokanta::taulukonKoko() const {
    return tasojenmaara_;
}

// Palauttaa muistion tehtävien määrän.
unsigned int Tietokanta::tehtavienMaara() const {
    return tehtavienmaara_;
}
