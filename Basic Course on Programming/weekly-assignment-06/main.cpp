// TIE-02206 Basic Course on Programming
//
// Viikkoharkka06, Petri Leppänen 160280


#include <iostream>
#include <map>

using namespace std;


int count_names(map<string, string>::const_iterator iter,
                map<string, string>::const_iterator end, char letter) {

    if (iter == end) {
        return 0;

    } else if (iter->first.at(0) == letter) {
        ++iter;
        return 1 + count_names(iter, end, letter);

    } else {
        ++iter;
        return count_names(iter, end, letter);
    }
}


int main() {
    // {nimi, puhelinnumero}
    map<string, string> phonebook = {
        {"Pekka", "123456789"},
        {"Antti", "987654321"},
        {"Seppo", "123645575"},
        {"Teppo", "325344565"},
        {"Tapio", "123213452"},
        {"Kalle", "239082354"},
        {"Anni", "198734582"},
        {"Tiina", "123098345"},
    };


//    string name, number;
//    cout << "Puhelinluetteloon lisääminen. Lopeta sanalla quit" << endl;
//    while (true) {
//        cout << "Anna nimi: ";
//        getline(cin, name);
//        cout << "Anna numero: ";
//        getline(cin, number);

//        if (nimi == "quit" || number == "quit") {
//            break;
//        }
//        phonebook.insert(name, number);
//    }

    char initial_letter = 'T';

    cout << "Puhelinluettolasta löytyi "
         << count_names(phonebook.begin(), phonebook.end(), initial_letter )
         << " " << initial_letter << "-alkukirjaimella olevaa nimeä." << endl;
}
