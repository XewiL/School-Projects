// Datastructures.hh

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <utility>
#include <limits>



// Type for town IDs
using TownID = std::string;

// Return value for cases where required town was not found
TownID const NO_ID = "----------";

// Return value for cases where integer values were not found
int const NO_VALUE = std::numeric_limits<int>::min();

// Return value for cases where name values were not found
std::string const NO_NAME = "-- unknown --";

struct TownData
{
    TownID id;
    std::string name;
    int x;
    int y;
    int tax;
    TownData* mastertown;
    std::vector<TownData*> vassaltowns;
};


// Binäärihaulle minkä mukaan etsitään
struct CompareNames
{
    bool operator() (TownData* town, std::string name ) const { return town->name < name;}
    bool operator() (std::string name, TownData* town ) const { return name < town->name; }
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

    // Estimate of performance: O(n)
    // Short rationale for estimate: saadaan helposti std::size()
    unsigned int size();

    // Estimate of performance: O(n)
    // Short rationale for estimate: Tyhjennetään kaikki tietorakenteet lineaarisesti
    void clear();

    // Estimate of performance: O(n) ~O(1)
    // Short rationale for estimate: unordered mapin etsintä
    std::string get_name(TownID id);

    // Estimate of performance: O(n) ~O(1)
    // Short rationale for estimate: unordered mapin etsintä
    std::pair<int, int> get_coordinates(TownID id);

    // Estimate of performance: O(n) ~O(1)
    // Short rationale for estimate: unordered mapin etsintä
    int get_tax(TownID id);

    // Estimate of performance: O(n log n)
    // Short rationale for estimate: unordered mapin etsintä + vassalkaupunkien sorttaus
    std::vector<TownID> get_vassals(TownID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Haetaan lineaarisesti kaikkien kaupunkien ID:t
    std::vector<TownID> all_towns();

    // Estimate of performance: O(1)
    // Short rationale for estimate: map:n ja vectorin perään lisäys
    bool add_town(TownID id, std::string const& name, int x, int y, int tax);

    // Estimate of performance: O(1)
    // Short rationale for estimate: Kaupungin etsintä mapista
    bool change_town_name(TownID id, std::string const& newname);

    // Estimate of performance: O(n log n)
    // Short rationale for estimate: Vektorin sorttaus + merge
    std::vector<TownID> towns_alphabetically();

    // Estimate of performance: O(n log n)
    // Short rationale for estimate: Vektorin sorttaus + merge
    std::vector<TownID> towns_distance_increasing();

    // Estimate of performance: O(log n) / O(n)
    // Short rationale for estimate: Riippuen paljolti onko kaupungit järjestyksessä
    std::vector<TownID> find_towns(std::string const& name);

    // Estimate of performance: O(1) / O(n)
    // Short rationale for estimate: Riippuen paljolti onko kaupungit järjestyksessä
    TownID min_distance();

    // Estimate of performance: O(1) / O(n)
    // Short rationale for estimate: Riippuen paljolti onko kaupungit järjestyksessä
    TownID max_distance();

    // Estimate of performance: O(1) / O(n log n)
    // Short rationale for estimate: Riippuen paljolti onko kaupungit järjestyksessä
    TownID nth_distance(unsigned int n);

    // Estimate of performance: O(1)
    // Short rationale for estimate: Kaupunkien etsintä mapista
    bool add_vassalship(TownID vassalid, TownID masterid);

    // Estimate of performance: O(1) / O(n)
    // Short rationale for estimate: Jos verokaupunkeja paljon (pointer ketju pitkä)
    std::vector<TownID> taxer_path(TownID id);

    // - - - - - - - - - - - - -
    //
    // Non-compulsory operations
    //
    // - - - - - - - - - - - - -

    // Estimate of performance: O(n)
    // Short rationale for estimate: Joutuu poistettavan kaupungin etsimään lineaarisesti
    bool remove_town(TownID id);

    // Estimate of performance: O(n log n)
    // Short rationale for estimate: Todennäköisesti aina halutaa etäisyys eri pisteestä
    //                               niin joutuu sorttaamaan.
    std::vector<TownID> towns_distance_increasing_from(int x, int y);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> longest_vassal_path(TownID id);

    // Estimate of performance:
    // Short rationale for estimate:
    int total_net_tax(TownID id);

private:
    unsigned int distance(int x1, int x2, int y1, int y2);
    std::vector<std::vector<TownID> > vassalTravel();

    // Tietorakenteet
    std::unordered_map<TownID, TownData*> towns_;

    std::vector<TownData*> alphaorder_;
    std::vector<TownData*> origoorder_;
    std::vector<TownData*> coordorder_;

    // Liput onko vektorit järjestyksessä
    bool isalphaorder_;
    bool isorigoorder_;
    bool iscoordorder_;

    // Indeksi johon asti vektorit on järjestyksessä
    std::vector<TownData*>::iterator index_alpha_;
    std::vector<TownData*>::iterator index_origo_;

    // Pidetään kirjaa mistä koordinaatista halutaan etäisyyttä mitata
    fromcoordinate from_;
};

#endif // DATASTRUCTURES_HH
