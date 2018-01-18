// TIE-02206 Basic Course, projekti02
//
// Petri Leppänen, 160280
//
// Viikkoharkka03:sta tuttu paloittelija, jonka mallikoodia
// sai käyttää suoraan.

#ifndef PALOITTELIJA_HH
#define PALOITTELIJA_HH

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

const unsigned int SPLITTER_VIRHE = 0;

class Splitter {
  public:
    Splitter(const string& paloiteltava_merkkijono = "");

    // Asetetaan merkkijono, joka halutaan paloitella.
    void aseta_paloiteltava_merkkijono(const string& merkkijono);

    // Paloitellaan merkkijono parametrina annetun
    // erotinmerkin kohdalta osiin.
    void paloittele(char erotinmerkki, bool ohita_tyhjat = false);

    // Palauttaa tiedon siitä, montako kenttää aiemmin
    // suoritetun paloittelun tuloksena syntyi.Paluuarvo on SPLITTER_VIRHE,
    // jos paloittele-metodia ei ole kutsuttu sen jälkeen,
    // kun paloiteltava merkkijono on viimeksi asetettu
    // (rakentajassa tai aseta_paloiteltava_merkkijono-metodissa).
    unsigned int kenttien_lukumaara() const;

    // Kun merkkijono on paloiteltu, tällä metodilla
    // voidaan pyytää Splitter-oliolta tietty kenttä.
    // Oletetaan että kentät on numeroitu vasemmalta
    // oikealle alkaen nollasta.  Jos paloittele-metodia
    // ei ole kutsuttu tai kentan_numero on liian
    // suuri rivillä olleiden kenttien lukumäärään
    // verrattuna, metodi tuottaa out_of_range-tyyppisen
    // poikkeuksen:
    //
    //     #include
    //     ...
    //     throw out_of_range("virheellinen kentan_numero");
    //
    string hae_kentta(unsigned int kentan_numero) const;

  private:
    // Lähtötieto: tätä merkkijonoa paloittele-metodi pätkiin osiin.
    string paloiteltava_;

    // Paloittele-metodi tallentaa tuloksen tähän vektoriin, niin
    // että kun merkkijono on kerran paloiteltu, sen kenttiin päästään
    // käsiksi nopeasti.
    vector<string> kentat_;
};

#endif // PALOITTELIJA_HH
