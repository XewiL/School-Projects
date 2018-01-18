// Viikkoharjoitus 01
// Petri Leppänen, 160280

#include <iostream>
#include <cmath>

using namespace std;

double Laskehypotenuusa(double sivu1, double sivu2);

int main() {
    double sivu1, sivu2;

    cout << "Lasketaan suorakulmaisenkolmion hypotenuusa." << endl;
    cout << "Anna kolmion ensimmäisen sivun pituus: ";
    cin >> sivu1;
    cout << "Anna kolmion toisen sivun pituus: ";
    cin >> sivu2;
    cout << "Hypotenuusan pituus on: " << Laskehypotenuusa(sivu1, sivu2) << endl;
}

double Laskehypotenuusa(double sivu1, double sivu2) {
    return sqrt(sivu1*sivu1+sivu2*sivu2);
}
