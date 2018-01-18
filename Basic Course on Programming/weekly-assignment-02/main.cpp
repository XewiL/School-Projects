// TIE-02206 Viikkoharkka 02
// Luokka-tyypin harjoitus: kahden kellonajan erotus minuutteina
//
// Petri Leppänen, 160280


#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Luokka
class Clock {
  public:
    Clock(int hour, int minute);
    void tick_tock();
    void print() const;

    int fetch_hour() const;
    int fetch_minutes() const;

    // Lisäys luokan rajapintaan jolla lasketaan kahden kellonajan erotus
    int timediff(Clock latertime) const;


  private:
    // Minuutteja keskiyöstä
    int minutes_since_midnight_;
};

Clock::Clock(int hour, int minute):
    minutes_since_midnight_(60 * hour + minute) {
}

void Clock::tick_tock() {
    ++minutes_since_midnight_;

    if ( minutes_since_midnight_ >= 24 * 60 ) {
        minutes_since_midnight_ = 0;
    }
}

// Kokonaislukujen jakolaskun tulos on kokonaisluku (pyöristetään alaspäin)
int Clock::fetch_hour() const {
        return minutes_since_midnight_ / 60;
}

// Osamäärä saadaan %-merkillä eli mitä täysien tuntien jälkeen on minuutteja.
int Clock::fetch_minutes() const {
    return minutes_since_midnight_ % 60;
}

void Clock::print() const {
    cout << setfill('0') << setw(2) << fetch_hour()
         << "." << setw(2) << fetch_minutes() << endl;
}


// Lasketaan kahden kellonajan erotus minuutteina (aika jo valmiina minuutteina).
// Täytyy selvittää onko vuorokausi muuttunut aikojen välissä.
int Clock::timediff(Clock latertime) const {
    if (minutes_since_midnight_ > latertime.minutes_since_midnight_) {
        // Minuutteja on paivassa (24h * 60min)
        return 24 * 60 - minutes_since_midnight_ + latertime.minutes_since_midnight_;
    }
    else {
        return latertime.minutes_since_midnight_ - minutes_since_midnight_;
            }
}

// Funktiolla kysytään kellonaika.
// Virhesyötteitä ei olla huomioitu.
Clock asktime() {
    string row;
    cout << "Anna kellonaika (hh.mm) ";
    getline(cin, row);

    string hour,min;
    string::size_type dot = row.find("."); // Etsitään pisteen paikka
    hour = row.substr(0, dot);
    min = row.substr(dot+1);

    int hh = stoi(hour);
    int mm = stoi(min);

    Clock cl(hh, mm);
    return cl;
}

int main() {
    Clock time1(0, 0); // Kahden kellonajan alustus
    Clock time2(0, 0); // Miksi kääntäjä herjasi jos Clock time1; ??

    time1 = asktime();
    time2 = asktime();

    cout << "Kellonaikojen erotus minuutteina: " << time1.timediff(time2) << endl;
}
