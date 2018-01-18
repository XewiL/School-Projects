// TIE-02206 Basic Course on Programming - Viikkoharkka08
//
// Lajittelu osoittimien avulla
//
// Petri Leppänen, 160280


#include <iostream>
#include <iomanip>    // setw()
#include <vector>
#include <string>
#include <algorithm>  // sort()

using namespace std;


struct Student {
    string name;
    unsigned int id;
};

// sort -funktiota voidaan kuormittaa omalla funktiolla, jolla kerrotaan
// millä tavalla kahta ensimmäistä parametriä vertaillaan.
bool sortByName(const Student& first, const Student& second) {
    return first.name < second.name; // kasvava järjestys
}


// Tässä sama nyt tehty pointtereilla opiskelijanumeroille.
bool sortById(const Student* first, const Student* second) {
    return first->id < second->id; // kasvava järjestys
}


int main() {
    vector<Student> studentregistry = {
        { "Teekkari, Tiina",           52401 },
        { "Ylikuuskajaskari, Jaska",  186112 },
        { "Repolainen, Reijo",        117118 },
        { "Teekkari, Teemu",          196196 },
        { "Santaholma, Santtu",       173421 },
    };

    vector<Student*> studentpointers = { };

    // Let's initialize the pointer vector with the addresses of the
    // of the students in the studentregistry vector.
    for ( vector<Student>::size_type i = 0; i < studentregistry.size(); ++i ) {
        studentpointers.push_back( &studentregistry.at(i) );
    }

    // Järjestelyn jälkeen opiskelija-vektori on kasvavassa järjestyksessä nimen mukaan.
    sort(studentregistry.begin(), studentregistry.end(), sortByName);

    // Järjestelyn jälkeen osoitin-vektori on kasvavassa järjestyksessä numeron mukaan.
    sort(studentpointers.begin(), studentpointers.end(), sortById);


    // Test prints.  Did we actually succeed in
    // ordering the vectors as required?

    cout << "Students sorted in alphabetical order:" << endl
         << "--------------------------------------" << endl;
    for ( Student stu : studentregistry ) {
        cout << setw(24) << left << stu.name
             << setw(6) << right << stu.id << endl;
    }

    cout << endl;

    cout << "Students sorted by the student id:" << endl
         << "----------------------------------" << endl;
    for ( Student* stu_ptr : studentpointers ) {
        cout << setw(24) << left << stu_ptr->name
             << setw(6) << right << stu_ptr->id << endl;
    }
}
