// TIE-02206 Viikkoharjoitukset 03
// String tekstin paloittelija -luokka
//
// Petri Leppänen, 160280

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>


using namespace std;

const unsigned int SPLIT_ERROR = 0;

class Splitter {
public:
    Splitter(const string& string_to_split = "");

    // Varsinainen splitteri, lisäehtona halutaanko myös tyhjät kentät
    unsigned int split(char separator, bool ignore_empty = false);

    // Asetetaan merkkijono paloittelijaan
    void set_string_to_split(const string& string_to_split);

    // Erona edelliseen että palauttaa SPLIT_ERROR jos yritetään tehdä jotain muuta
    // ennen kuin ollaan paloiteltu
    unsigned int number_of_fields() const;

    // Haetaan yhden kentän teksti.
    // Jos ei olla vielä splitattu tai kentän numero on liian suuri
    // => out_of_range
    string fetch_field(unsigned int field_index) const;

private:
    string line_;
    //int num_fields_; // ei tarvita koska saadaan vektorin koosta!
    vector<string> fields_;
};

// Rakentaja
Splitter::Splitter(const string& string_to_split):
    //fields_ voi jättää pois koska vektorit aina tyhjiä jos ei alusta, "nörttivinkki"
    line_(string_to_split), fields_({}) {
}

// Paloittelija: erotinmerkin avulla jaetaan stringi osiin ja
// talletetaan vektoriin jokainen osa
unsigned int Splitter::split(char separator, bool ignore_empty) { // HUOM! alustusarvo vain yhdessä kohtaa!
    string fieldtext;
    string::size_type pointer1 = 0; // Tekstin ensimmäinen pointteri (alkukohta)

    while (true) {
        string::size_type pointer2;
        // Etsitään seuraava erotinmerkin kohta kohdasta pointer1 eteenpäin
        pointer2 = line_.find(separator, pointer1);

        if (pointer2 == string::npos) { // jos ei löytynyt poistutaan loopista
            break;
        }

        fieldtext = line_.substr(pointer1, pointer2 - pointer1); // Tallennetaan osa vektoriin

        // Ei lisätä vektoriin jos tyhjä!
        if (fieldtext.length() != 0 || !ignore_empty) { // Sama kuin fieldtext.size(), hyvä kuitenkin stringeissä
            fields_.push_back(fieldtext);               // käyttää length koska size myös muilla esim vektoreilla
        }

        pointer1 = pointer2 + 1;
    }

    // nposin jälkeen jäi jotain! ainakin se yksi jos ei alkujaan löytynyt yhtään
    fieldtext = line_.substr(pointer1);
    if (fieldtext.length() != 0 || !ignore_empty) {
        fields_.push_back(fieldtext);
    }

    return fields_.size();
}


void Splitter::set_string_to_split(const string& string_to_split) {
    line_ = string_to_split;
    fields_ = {};
}


unsigned int Splitter::number_of_fields() const {
    if(fields_.size() == 0) {
        return SPLIT_ERROR;
    }
    else {
        return fields_.size();
    }
}


string Splitter::fetch_field(unsigned int field_index) const {
    if (fields_.empty() or field_index >= fields_.size()) {
        throw out_of_range("Väärä kenttä!");
    }
    else {
        return fields_.at(field_index);
    }
}

// Pääohjelma vain luokan testaamiseen
int main() {
    Splitter splitter_object("a::bc:def::hijlkm");

    splitter_object.split(':');  // char-tyyppi!

    cout << "fields: " << splitter_object.number_of_fields() << endl;  // 6

    cout << splitter_object.fetch_field(0) << endl; // a
    cout << splitter_object.fetch_field(1) << endl; // tyhjä
    cout << splitter_object.fetch_field(2) << endl; // bc
    cout << splitter_object.fetch_field(3) << endl; // def
    cout << splitter_object.fetch_field(4) << endl; // tyhjä
    cout << splitter_object.fetch_field(5) << endl; // hijlkm

    for ( unsigned int i = 0; i < splitter_object.number_of_fields(); ++i ) {
        string current_field_contents = splitter_object.fetch_field(i);
        cout << i << ": [" << current_field_contents << "]" << endl;
    }

    splitter_object.set_string_to_split(" A B  C   D    E     ");
    unsigned int fields = splitter_object.split(' ', true);

    cout << "fields: " << fields << endl;  // 5

    for ( unsigned int i = 0; i < fields; ++i ) {
        string current_field_contents = splitter_object.fetch_field(i);
        cout << i << ": [" << current_field_contents << "]" << endl;
    }

    cout << splitter_object.fetch_field(5) << endl;  // out_of_range exception
}
