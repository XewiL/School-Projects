// TIE-02206 Basic Course on Programming
// Viikkoharkka07, rekursiivinen funktio palindromille
//
// Petri Leppänen, 160280

#include <iostream>
#include <string>


using namespace std;

//bool is_palindrome(const string& str) {

//    if (str.empty()) {
//        return true;
//    }

//    string::size_type i = 0;

//    while (i <= str.size() / 2) {
//        if (str.at(i) != str.at(str.size() - 1 - i)) {
//            return false;
//        }
//        ++i;
//    }
//    return true;
//}


// Sama funktio tehty nyt rekursiolla.
// Funktio on tehty normaalilla rekurssiolla.
bool is_palindrome_recursive(const string& str, string::size_type i = 0) {
    if (str.empty()) {
        return true;
    }

    if (str.size() > i) {

        if (str.at(i) != str.at(str.size() - 1 - i)) {
            return false;
        } else {
            return (is_palindrome_recursive(str, i+1));
        }
    }
    return true;
}


// Main funktio, jossa tehty käyttöliittymä
// funktion toiminnallisuutta varten.
int main() {
    string line;

    while (line != "quit") {
        cout << "Anna sana: ";
        getline(cin, line);

        if (line == "quit") {
            break;
        }

        if (is_palindrome_recursive(line)) {
            cout << "Sana on palindromi" << endl;
        } else {
            cout << "Sana ei ole palindromi" << endl;
        }
    }
}
