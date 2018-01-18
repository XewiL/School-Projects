// TIE-02206, projekti 01, päivämääräluokka
//
// Petri Leppänen, 160280

// Vertailupäivämääräksi valitaan 31.12.1799 ja katsotaan kalenterista,
// että se oli tiistai.
// Lasketaan sen jälkeen montako päivää on kulunut pyydettyyn päivämäärään.
// Ideoita otettu ohj1-prujusta.



#include <iostream>
#include <string>
#include <vector>  // STL-vain syötteen parsimista varten
#include <sstream> // Muunnetaan streamin kautta string -> int
#include <cstdio>  // EOF-vakiota varten


using namespace std;


// Vakioiden määrittelyt
const unsigned int ALOITUSVUOSI = 1800;
const unsigned int NORMAALIVUODEN_PITUUS = 365;
const unsigned int KARKAUSVUODEN_PITUUS = 366;
const unsigned int PITKAN_KUUN_PITUUS = 31;
const unsigned int LYHYEN_KUUN_PITUUS = 30;
const unsigned int KARKAUSHELMIKUUSSA = 29;
const unsigned int HELMIKUUSSA = 28;

const unsigned int TAMMI = 1;
const unsigned int HELMI = 2;
const unsigned int MAALIS = 3;
const unsigned int HUHTI = 4;
const unsigned int TOUKO = 5;
const unsigned int KESA = 6;
const unsigned int HEINA = 7;
const unsigned int ELO = 8;
const unsigned int SYYS = 9;
const unsigned int LOKA = 10;
const unsigned int MARRAS = 11;
const unsigned int JOULU = 12;

const unsigned int PAIVIA_VIIKOSSA = 7;

// 7-jakojäännöksistä saadaan viikonpäivät
// Referenssipäivänä käytetään 1.1.1799 joka oli tiistai.
const unsigned int MAANANTAI = 0;
const unsigned int TIISTAI = 1;
const unsigned int KESKIVIIKKO = 2;
const unsigned int TORSTAI = 3;
const unsigned int PERJANTAI = 4;
const unsigned int LAUANTAI = 5;
const unsigned int SUNNUNTAI = 6;


class Paivamaara {
public:
    Paivamaara();
    Paivamaara(unsigned int paiva, unsigned int kuukausi, unsigned int vuosi);

    void AsetaPaivamaara(unsigned int paiva, unsigned int kuukausi, unsigned int vuosi);

    unsigned int AnnaPaiva() const;
    unsigned int AnnaKuukausi() const;
    unsigned int AnnaVuosi() const;

    void TulostaViikonpaiva() const;
    unsigned int LaskeViikonpaivaNumero() const;

    bool OnkoPaivamaaraLaillinen() const;
    bool OnkoHelmikuu() const;
    bool OnkoLyhytKuukausi() const; // Onko 30-päivää
    bool OnkoPitkaKuukausi() const; // Onko 31-päivää
    bool OnkoKarkausvuosi() const;

    void AsetaSeuraavaPaiva();
    void AsetaEdellinenPaiva();

private:
    unsigned int paiva_;
    unsigned int kuukausi_;
    unsigned int vuosi_;
};


// - - -
// Muut funktiot:
// - - -

// Rivin pilkkominen "-" -merkillä ja talletetaan se vektoriin.
// Toteutuksessa käytetty viikkoharkka03 hyväksi ideassa.
vector<string> Pilkopaivamaara(string syote) {
    vector<string> rivi_tekstina;
    string::size_type alkukohta = 0;
    string kentta;

    while (true) {
        string::size_type loppukohta;
        loppukohta = syote.find("-", alkukohta);

        // Jos erotinmerkkiä ei löytynyt poistutaan silmukasta.
        if (loppukohta == string::npos) {
            break;
        }

        kentta = syote.substr(alkukohta, loppukohta - alkukohta);

        if (!(kentta.empty())) {
            rivi_tekstina.push_back(kentta);
        }
        alkukohta = loppukohta + 1;
    }
    // Viimeisen '-' -merkin jälkeen jäi vielä jotain, otetaan se talteen.
    kentta = syote.substr(alkukohta);
    if (!(kentta.empty())) {
        rivi_tekstina.push_back(kentta);
    }
    return rivi_tekstina;
}

// Rivivektorin muuntaminen integer muotoon.
// Samalla hoituu virhesyötteistä teksti ja muut merkit.
vector<unsigned int> string2int(vector<string> rivi) {
    vector<unsigned int> rivi_numeroina;

    // Käydään vektori läpi ja muunnetaan jokainen sting kenttä int:ksi
    for (string i : rivi) {
        unsigned int temppi;
        stringstream stream(i);

        // Jos käännös onnistuu työnnetään se vektoriin.
        // Jos ei onnistu, on syötteessä muuta kuin numeroita.
        // Virhetarkastus hoidetaan myöhemmin.
        if (stream >> temppi) {
            rivi_numeroina.push_back(temppi);

            // Jos kentässä oli numeroiden jälkeen jotain merkkejä vielä
            // niin tyhjennetään vektori, koska myöhemmin tarkistetaan
            // että vektorin koko joka oltava 3.
            if ( stream.peek() != EOF ) {
                rivi_numeroina.empty();
                return rivi_numeroina;
            }
        }
    }
    return rivi_numeroina;
}


// Projektin vaatimat tulostusmuodot paivaykselle.
void Projekti01Tulostus(Paivamaara paivays) {

    cout << "The date is a valid date." << endl;
    cout << "Day is " << paivays.AnnaPaiva() << endl;
    cout << "Month is " << paivays.AnnaKuukausi() << endl;
    cout << "Year is " << paivays.AnnaVuosi() << endl;
    cout << "Weekday is ";
    paivays.TulostaViikonpaiva();
    cout << endl;

    paivays.AsetaEdellinenPaiva();
    cout << "The previous date was: ";
    paivays.TulostaViikonpaiva();
    cout << " " << paivays.AnnaPaiva() << "." << paivays.AnnaKuukausi()
         << "." << paivays.AnnaVuosi() << endl;

    paivays.AsetaSeuraavaPaiva();
    paivays.AsetaSeuraavaPaiva();
    cout << "The next date will be: ";
    paivays.TulostaViikonpaiva();
    cout << " " << paivays.AnnaPaiva() << "." << paivays.AnnaKuukausi()
         << "." << paivays.AnnaVuosi() << endl;
}


// Pääohjelma käyttöliittymää ja luokan testausta varten.
int main() {

    Paivamaara paivamaara;

    cout << string(32, '-') << endl;
    cout << "Welcome to date testing program!" << endl;
    cout << string(32, '-') << endl << endl;

    while(true) {
        string rivi;
        cout << "Input a date in day-month-year format: ";
        getline(cin, rivi);

        if(rivi == "quit") {
            cout << "Test program ending, goodbye!" << endl << endl;
            break;

        } else {
            cout << "--- TEST OUTPUT BEGIN" << endl;

            vector<unsigned int> paivays = string2int(Pilkopaivamaara(rivi));

            // Jos pilkkoja ja muunnos ovat menneet oikein niin
            // vektorin pituus pitää olla == 3.
            if (paivays.size() == 3) {
                unsigned int pp = paivays.at(0);
                unsigned int kk = paivays.at(1);
                unsigned int vvvv = paivays.at(2);

                paivamaara.AsetaPaivamaara(pp, kk, vvvv);

                if (!paivamaara.OnkoPaivamaaraLaillinen()) {
                    cout << "Error: this is not a valid date!" << endl;
                } else {
                    Projekti01Tulostus(paivamaara);
                }

            } else {
                cout << "Error: this is not a valid date!" << endl;
            }
            cout << "--- TEST OUTPUT END" << endl << endl;
        }
    }
}


// - - -
// Luokan jäsenfunktiot
// - - -

// Oletusrakentaja, 1.1.1800 on keskiviikko
Paivamaara::Paivamaara():
    paiva_(1), kuukausi_(1), vuosi_(1800) {
}

Paivamaara::Paivamaara(unsigned int paiva, unsigned int kuukausi, unsigned int vuosi):
    paiva_(paiva), kuukausi_(kuukausi), vuosi_(vuosi) {
}

void Paivamaara::AsetaPaivamaara(unsigned int paiva, unsigned int kuukausi, unsigned int vuosi) {
    paiva_ = paiva;
    kuukausi_ = kuukausi;
    vuosi_ = vuosi;
}

unsigned int Paivamaara::AnnaPaiva() const {
    return paiva_;
}

unsigned int Paivamaara::AnnaKuukausi() const {
    return kuukausi_;
}

unsigned int Paivamaara::AnnaVuosi() const {
    return vuosi_;
}

void Paivamaara::TulostaViikonpaiva() const {
    unsigned int viikonpaivanumero = LaskeViikonpaivaNumero();

    if (viikonpaivanumero == MAANANTAI) {
        cout << "Monday";
    } else if (viikonpaivanumero == TIISTAI) {
        cout << "Tuesday";
    } else if (viikonpaivanumero == KESKIVIIKKO) {
        cout << "Wednesday";
    } else if (viikonpaivanumero == TORSTAI ) {
        cout << "Thursday";
    } else if (viikonpaivanumero == PERJANTAI ) {
        cout << "Friday";
    } else if (viikonpaivanumero == LAUANTAI ) {
        cout << "Saturday";
    } else {
        cout << "Sunday";
    }
}

// Lasketaan kertyneet päivät 1.1.1800 alkaen joka oli keskiviikko.
// Referenssipäivänä käytetään 1.1.1799 joka oli tiistai, jolloin saadaan
// myös edellinen päivä laskettua päivästä 1.1.1800.
unsigned int Paivamaara::LaskeViikonpaivaNumero() const {
    Paivamaara referenssipaiva(1, 1, 1799);
    unsigned int paivia_kertynyt = 0;

    // Vuosista kertyneet päivät
    while (referenssipaiva.vuosi_ < vuosi_) {
        if (referenssipaiva.OnkoKarkausvuosi()) {
            paivia_kertynyt = paivia_kertynyt + KARKAUSVUODEN_PITUUS;
        } else {
            paivia_kertynyt = paivia_kertynyt + NORMAALIVUODEN_PITUUS;
        }
        ++referenssipaiva.vuosi_;
    }

    // Kuukausista kertyneet päivät
    while (referenssipaiva.kuukausi_ < kuukausi_) {
        if (referenssipaiva.OnkoPitkaKuukausi()) {
            paivia_kertynyt = paivia_kertynyt + PITKAN_KUUN_PITUUS;
        } else if (referenssipaiva.OnkoLyhytKuukausi()) {
            paivia_kertynyt = paivia_kertynyt + LYHYEN_KUUN_PITUUS;
        } else if (referenssipaiva.OnkoHelmikuu() && referenssipaiva.OnkoKarkausvuosi()) {
            paivia_kertynyt = paivia_kertynyt + KARKAUSHELMIKUUSSA;
        } else {
            paivia_kertynyt = paivia_kertynyt + HELMIKUUSSA;
        }
        ++referenssipaiva.kuukausi_;
    }

    // Päivistä kertyneet päivät + jakojäännös
    paivia_kertynyt = (paivia_kertynyt + paiva_) % PAIVIA_VIIKOSSA;

    return paivia_kertynyt;
}


bool Paivamaara::OnkoPaivamaaraLaillinen() const {

    if (paiva_ < 1) {
        return false;
    } else if (kuukausi_ < TAMMI || kuukausi_ > JOULU) {
        return false;
    } else if (vuosi_ < ALOITUSVUOSI) {
        return false;
    } else if (OnkoPitkaKuukausi() && paiva_ > PITKAN_KUUN_PITUUS) {
        return false;
    } else if (OnkoLyhytKuukausi() && paiva_ > LYHYEN_KUUN_PITUUS) {
        return false;
    } else if (OnkoHelmikuu() && OnkoKarkausvuosi() && paiva_ > KARKAUSHELMIKUUSSA) {
        return false;
    } else if (OnkoHelmikuu() && !OnkoKarkausvuosi() && paiva_ > HELMIKUUSSA) {
        return false;
    } else {
        return true;
    }
}

bool Paivamaara::OnkoHelmikuu() const {
    if (kuukausi_ == HELMI) {
        return true;
    } else {
        return false;
    }
}

bool Paivamaara::OnkoLyhytKuukausi() const {
    if (kuukausi_ == HUHTI || kuukausi_ == KESA
            || kuukausi_ == SYYS || kuukausi_ == MARRAS) {
        return true;
    } else {
        return false;
    }
}

bool Paivamaara::OnkoPitkaKuukausi() const {
    return (!OnkoHelmikuu() && !OnkoLyhytKuukausi());
}

bool Paivamaara::OnkoKarkausvuosi() const {
    if ((vuosi_ % 4 == 0 && vuosi_ % 100 != 0) || vuosi_ % 400 == 0) {
        return true;
    } else {
        return false;
    }
}

void Paivamaara::AsetaSeuraavaPaiva() {
    ++paiva_;

    if ((paiva_ > PITKAN_KUUN_PITUUS && OnkoPitkaKuukausi())
            || (paiva_ > LYHYEN_KUUN_PITUUS && OnkoLyhytKuukausi())
            || (paiva_ > KARKAUSHELMIKUUSSA && OnkoHelmikuu() && OnkoKarkausvuosi())
            || (paiva_ > HELMIKUUSSA && OnkoHelmikuu() && !OnkoKarkausvuosi())) {
        paiva_ = 1;
        ++kuukausi_;
    }

    if (kuukausi_ > JOULU) {
        kuukausi_ = TAMMI;
        ++vuosi_;
    }
}

void Paivamaara::AsetaEdellinenPaiva() {
    --paiva_;

    if (paiva_ < 1) {
        --kuukausi_;

        if (kuukausi_ < TAMMI) {
            kuukausi_ = JOULU;
            --vuosi_;
        }

        if (OnkoPitkaKuukausi()) {
            paiva_ = PITKAN_KUUN_PITUUS;
        } else if (OnkoLyhytKuukausi()) {
            paiva_ = LYHYEN_KUUN_PITUUS;
        } else if (OnkoHelmikuu() && OnkoKarkausvuosi()) {
            paiva_ = KARKAUSHELMIKUUSSA;
        } else {
            paiva_ = HELMIKUUSSA;
        }
    }
}
