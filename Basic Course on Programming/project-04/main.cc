// TIE-02206 Basic Course, projekti04
//
// --
// To-Do muistio osoittimilla.
// --
//
// Petri Leppänen, 160280

#include "syotteenluku.hh"
#include "paloittelija.hh"
#include "tietokanta.hh"

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main() {

    Tietokanta tehtavalista;

    while (true) {
        cout << "chores> ";
        string syoterivi;
        getline(cin, syoterivi);

        Splitter syote;
        char erotinmerkki = ' ';

        // Paloittelijaan syötetään käyttäjän antama komento,
        // jonka perusteella toimitaan jatkossa.

        syote.asetaPaloiteltavaMerkkijono(syoterivi);
        syote.paloittele(erotinmerkki);

        // Alla IF-hirviö, käyttöliittymä joka tarkistaa, että syöte on laillinen
        // ja toimii sen mukaan. Aina yhden IF viimeiseksi tehdään toiminto,
        // jos syöte on ollut oikein. (Tulostukset laitin nyt tähän main ohjelmaan,
        // vaikka ne varmaan etiketin mukaan tarvitsisi olla aina jos poikkeus niin muualla?).

        // Sallitut komennot:
        // - quit -> lopettaa ohjelman
        // - init <tärkeystasojen määrä> -> Luodaan uusi prioriteettilista,
        //   jossa käyttäjän antama määrä tärkeystasoja.
        // - add <priority_level> <chore_description> -> lisätään uusi tehtävä,
        //   tärkeystason perälle.
        // - print -> koko listan tulostus näytölle.
        // - next -> tulostaa listassa seuraavaksi olevan tehtävän näytölle.
        // - erase <running_number> -> poistetaan listasta numerolla annettu tehtävä.

        // - - - QUIT - - -
        // Poistutaan loopista -> ohjelma päättyy.
        if (syote.haeKentta(1) == "quit" && syote.kenttienLukumaara() == 1) {
            break;

        // - - - INIT - - -
        // Muistion alustaminen käyttäjän antamalla tasojen määrällä.
        } else if (syote.haeKentta(1) == "init") {
            int tasojenmaara = 0;
            if (syote.kenttienLukumaara() > 1) {
                istringstream stream(syote.haeKentta(2));
                stream >> tasojenmaara; // numeron tarkistus myöhemmin
            }

            if (syote.kenttienLukumaara() == 1) {
                cout << "Error: the number of priority levels is missing." << endl;
            } else if(!onkoNumero(syote.haeKentta(2))) {
                cout << "Error: the number of priority levels must be an integer larger than 0." << endl;
            } else if (tasojenmaara < 1) {
                cout << "Error: it is not possible to create a priority list with 0 or less levels." << endl;
            } else {
                tehtavalista.rakennaTietokanta(tasojenmaara);
                cout << "New priority list with levels 1-"
                     << tehtavalista.taulukonKoko() << " initialized." << endl;
            }

        // Tänne päädytään vasta kun muistio ollaan luotu.
        } else if (tehtavalista.taulukonKoko() != 0) {

            // - - - ADD - - -
            // Lisätään tehtävä käyttäjän antamaan tärkeystasson.
            if (syote.haeKentta(1) == "add") {
                unsigned int tasonnro = 0;
                if (syote.kenttienLukumaara() > 1) {
                    istringstream stream(syote.haeKentta(2));
                    stream >> tasonnro;
                }

                if (syote.kenttienLukumaara() == 1) {
                    cout << "Error: priority level and chore description are missing." << endl;
                } else if (tasonnro > tehtavalista.taulukonKoko() ||
                           !onkoNumero(syote.haeKentta(2)) ||
                           syote.haeKentta(2) == "0") {
                    cout << "Error: priority level must be an integer between 1-"
                         << tehtavalista.taulukonKoko() << "." << endl;
                } else if (syote.kenttienLukumaara() < 3) {
                    cout << "Error: chore description is missing." << endl;
                } else {

                    // Kootaan paloiteltu tehtävä takaisin yhteen stringiin.
                    string lisattavatehtava;
                    for (unsigned int i = 3; i <= syote.kenttienLukumaara(); ++i) {
                        lisattavatehtava += syote.haeKentta(i);

                        // Viimeisen sanan jälkeen ei lisätä enää välilyöntiä.
                        if (i != syote.kenttienLukumaara()) {
                            lisattavatehtava += " ";
                        }
                    }
                    tehtavalista.lisaaTehtava(tasonnro, lisattavatehtava);
                    cout << "New chore added to priority level "<< tasonnro << "." << endl;
                }

            // - - - PRINT - - -
            // Tulostetaan näytölle kaikki tehtävät tärkeysjärjestyksessä.
            } else if (syote.haeKentta(1) == "print") {
                if (syote.kenttienLukumaara() == 1) {
                    tehtavalista.tulostaTehtavat();
                } else {
                    cout << "Error: extra text after print command." << endl;
                }

            // - - - NEXT - - -
            // Tulostetaan seuraava tehtävä jonka jälkeen se poistetaan listalta.
            } else if (syote.haeKentta(1) == "next") {
                if (syote.kenttienLukumaara() > 1) {
                    cout << "Error: extra text after next command." << endl;
                } else if (tehtavalista.tehtavienMaara() == 0) {
                    cout << "--- no chores left ---" << endl;
                } else {
                    tehtavalista.tulostaSeuraavaJaPoista();
                }

            // - - - ERASE - - -
            // Poistetaan haluttu tehtävä listalta.
            } else if (syote.haeKentta(1) == "erase") {
                if (syote.kenttienLukumaara() == 1) {
                    cout << "Error: the running number is missing." << endl;
                } else if (syote.haeKentta(2) == "0") {
                    cout << "Error: the running number must be larger than 0." << endl;
                } else if (!onkoNumero(syote.haeKentta(2))) {
                    cout << "Error: there must follow number after erase -command." << endl;
                } else if (syote.kenttienLukumaara() > 2) {
                    cout << "Error: extra text after number." << endl;
                } else {
                    unsigned int tehtavanro = 0;
                    istringstream stream(syote.haeKentta(2));
                    stream >> tehtavanro; // Numeron tarkistus jo rivillä 142 if ehdossa.

                    // Vielä tarkistetaan, että ei koiteta poistaa numeroa jota ei ole olemassa.
                    if (tehtavanro > tehtavalista.tehtavienMaara()) {
                        cout << "Error: there is no such chore." << endl;
                    } else {
                        tehtavalista.poistaTehtava(tehtavanro);
                    }
                }

            // Jos ei syötetty mitään olemassa olevaa komentoa.
            } else {
                cout << "Error: unknown command." << endl;
            }

        // Jos ei olla vielä alustettu muistiota.
        } else if (syote.haeKentta(1) == "add" || syote.haeKentta(1) == "print" ||
                   syote.haeKentta(1) == "next" || syote.haeKentta(1) == "erase") {
            cout << "Error: you must create a priority list first." << endl;

        // Jos ei syötetty mitään olemassa olevaa komentoa.
        } else {
            cout << "Error: unknown command." << endl;
        }
    }
}
