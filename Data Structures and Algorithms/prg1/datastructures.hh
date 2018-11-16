// Datastructures.hh

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>

struct TownData
{
    std::string name;
    int x;
    int y;
};

struct fromcoordinate
{
    int x;
    int y;
};

class Datastructures
{
public:
    Datastructures();
    ~Datastructures();

    // Estimate of performance: Vakio aika
    // Short rationale for estimate: Tietorakenteet ovat vektorissa,
    // joten sen pituuden saa .size() komennolla.
    unsigned int size();

    // Estimate of performance: Lineaarinen
    // Short rationale for estimate: Tietorakenne on vektorissa,
    // joten sen tyhjentäminen käydään lineaarisesti läpi (muistin vapautus).
    void clear();

    // Estimate of performance: Vakio aika
    // Short rationale for estimate: Palauttaa vektorin, jossa kaikki kaupungit
    // satunnaisessa järjestyksessä.
    std::vector<TownData*> all_towns();

    // Estimate of performance: Vakio aika
    // Short rationale for estimate: Lisätään kaupunki suoraan vektorin perälle
    // .push_back() komennolla.
    TownData* add_town(std::string const& name, int x, int y);

    // Estimate of performance: n log n
    // Short rationale for estimate: Palautetaan vektori heti, jos se on järjestyksessä.
    // Muuten järjestetään Random-Quick-Sortilla, vektori järjestykseen.
    std::vector<TownData*> towns_alphabetically();

    // Estimate of performance: n log n
    // Short rationale for estimate: Palautetaan vektori heti, jos se on järjestyksessä.
    // Muuten järjestetään Random-Quick-Sortilla, vektori järjestykseen.
    std::vector<TownData*> towns_distance_increasing();

    // Estimate of performance: Pahimmassa tapauksessa lineaarinen.
    // Short rationale for estimate: Kaupungin hakuun käytetään puolitushakua
    // jos se on jo järjestyksessä, muuten haetaan lineaarisesti käymällä koko vektori läpi.
    TownData* find_town(std::string const& name);

    // Estimate of performance: Lineaarinen
    // Short rationale for estimate: Pienin etäisyys saadaan vakioajalla, jos kaupungit
    // ovat valmiiksi järjestyksessä. Muuten tulos haetaan lineaarisesti koko vektori läpi
    // käymällä.
    TownData* min_distance();

    // Estimate of performance: Lineaarinen
    // Short rationale for estimate: Suurin etäisyys saadaan vakioajalla, jos kaupungit
    // ovat valmiiksi järjestyksessä. Muuten tulos haetaan lineaarisesti koko vektori läpi
    // käymällä.
    TownData* max_distance();

    // Estimate of performance: n Log n
    // Short rationale for estimate: n. alkio saadaan vakioajalla, jos kaupungit ovat
    // valmiiksi järjestyksessä. Muuten järjestetään Random-Quick-Sortilla, vektori järjestykseen.
    TownData* nth_distance(unsigned int n);


    // Estimate of performance: N^2
    // Short rationale for estimate: Käydään vektorit lineearisesti läpi ja poistetaan
    // osoitin. Pahimmassa tapauksessa .erase() komennon takia vektori joutuu siirtämään
    // muita alkioita n-kertaa.
    void remove_town(std::string const& town_name);

    // Estimate of performance: n log n
    // Short rationale for estimate: Palautetaan vektori heti, jos se on järjestyksessä.
    // Muuten järjestetään Random-Quick-Sortilla, vektori järjestykseen.
    std::vector<TownData*> towns_distance_increasing_from(int x, int y);

private:
    // Randomized-QuickSort funktiot
    void randomizedQuicksort (std::vector<TownData*>& A, int left, int right);
    int randomizedPartition (std::vector<TownData*>& A, int left, int right);
    int partition (std::vector<TownData*>& A, int left, int right);

    // Vektorin kahden alkion vaihto
    void swap(TownData*& left, TownData*& right);
    // Kaupunkien etäisyyden laskeminen tehtävänannon mukaan
    unsigned int distance(int x1, int x2, int y1, int y2);

    // Puolitushaku kaupungin etsintään, jos vektori on aakkosjärjestyksessä
    TownData* binarySearch(std::vector<TownData*>& A, unsigned int n, std::string const& key);

    bool isalphaorder_;
    bool isorigoorder_;
    bool iscoordorder_;

    // Etsitäänkö nimen vai koordinaattien mukaan.
    // True = name, False = coordinate.
    bool flag_;

    // Pidetään kirjaa mistä koordinaatista halutaan etäisyyttä mitata
    fromcoordinate from_;

    // Database -vektorit
    std::vector<TownData*> alphaorder_;
    std::vector<TownData*> origoorder_;
    std::vector<TownData*> coordorder_;
};

#endif // DATASTRUCTURES_HH
