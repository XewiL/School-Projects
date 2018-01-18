#include <iostream>
#include <string>
#include <map>

using namespace std;


void LisaaTulos(map<string, map<int, string>>& tulokset,
                const string& laji,
                const string& nimi) {

    map<string, map<int, string>>::iterator iter;
    iter = tulokset.find(laji);

    // Etsitään onko lajia jo listauksessa vielä entuudestaan.
    // Jos ei, lisätään laji.
    // Jos on sijoitetaan sijoituksena seuraavaksi.
    if (iter == tulokset.end()) {
        tulokset.insert({ laji, {{1, nimi}} });
    } else {
        map<int, string>::size_type sijoitus = iter->second.size() + 1;
        iter->second.insert( { sijoitus, nimi } );
    }
}


void Tulosta(const map<string, map<int, string>>& tulokset) {

    if (tulokset.size() != 0) {
        cout << endl;
        cout << "- - - - - TULOKSET - - - - - " << endl;
        cout << endl;
    }

    map<string, map<int, string>>::const_iterator laji;
    laji = tulokset.begin();

    while (laji != tulokset.end()) {
        cout << laji->first << endl;

        map<int, string>::const_iterator kilpailija;
        kilpailija = laji->second.begin();

        while ( kilpailija != laji->second.end() ) {
            cout << string(3, ' ') << kilpailija->first
                 << ". " << kilpailija->second << endl;

            ++kilpailija;
        }
        ++laji;
    }
}


int main() {
    // Luodaan rakenne jossa: {lajin nimi, {sijoitus, kilpailija nimi} }
    // Tulokset syötetään sijoitusjärjestyksessä joten sijoitusta
    // ei tarvitse erikseen kysyä.
    map<string, map<int, string>> tulokset;

    cout << "Listaa kilpailijan tulokset tulosjärjestyksessä voittajasta alkaen." << endl;
    cout << "Lopeta sanalla quit." << endl;

    while (true) {
        cout << "Laji: ";
        string laji;
        getline(cin, laji);

        if (laji == "quit") {
            break;
        }

        int i = 1;
        while (true) {
            cout << i << ". Nimi: ";
            string nimi;
            getline(cin, nimi);

            if (nimi == "quit" ) {
                break;
            }
            LisaaTulos(tulokset, laji, nimi);
            ++i;
        }

        string jatketaanko;
        while (jatketaanko != "k" || jatketaanko != "e") {
            cout << "Jatka (k/e)? ";
            getline(cin, jatketaanko);
            if (jatketaanko == "k" || jatketaanko == "e") {
                break;
            } else {
                jatketaanko = "";
                continue;
            }
        }
        if (jatketaanko == "e") {
            break;
        } else if (jatketaanko == "k") {
            continue;
        }
    }
    Tulosta(tulokset);
}
