// TIE-02206 Basic Course, projekti04
//
// Petri Leppänen, 160280
//
// Käyttäjän syötteen oikeellisuus ja eri virheilmoitukset
// (Tähän tulikin vain nyt numeron oikeellisuus tarkistus)

#include "paloittelija.hh"
#include "syotteenluku.hh"

#include <iostream>
#include <sstream>  // String streamin muuntaminen int
#include <string>


bool onkoNumero(string teksti) {
    int temppi;
    istringstream stream(teksti);
    if (!(stream >> temppi)) {
        return false;
    }
    // Vielä pitää tarkistaa, että numeroiden perässä ei ole mitään,
    // eli viimeisessä kentässä ei ole muuta kuin numeroita
    // joka myöhemmin voidaan muuntaa.
    if (stream.peek() != EOF) {
        return false;
    }
    // Muussa tapauksessa on numero
    return true;
}
