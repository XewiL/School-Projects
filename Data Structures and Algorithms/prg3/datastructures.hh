// Datastructures.hh

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
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

// Type for a coordinate (x, y)
using Coord = std::pair<int, int>;

// Return value for cases where coordinates were not found
Coord const NO_COORD{NO_VALUE, NO_VALUE};

// Type for distance
using Dist = int;

// Return value for cases where distance is unknown
Dist const NO_DIST = NO_VALUE;

// Käytetään lyhennettä kaupunki pointteriin
using Townptr = std::shared_ptr<struct TownData>;

// Kaupungin data kokonaisuudessaan
struct TownData
{
    TownID id;
    std::string name;
    Coord coordinates;
    // Tiedot verusta varten
    int tax;
    Townptr mastertown;
    std::vector<Townptr> vassaltowns;
    // Tiedot teitä varten
    std::unordered_map<TownID, Townptr> roads; // Kaupungista lähtevät tiet
    bool marked; // Hakualgoritmeja varten onko etsitty jo tästä kaupungista
    Townptr from; // Hakualgoritmeja varten mitä reittiä päädyttiin tähän kaupunkiin
};

// Binäärihaulle minkä mukaan etsitään
struct CompareNames
{
    bool operator() (Townptr town, std::string name ) const { return town->name < name;}
    bool operator() (std::string name, Townptr town ) const { return name < town->name; }
};


class Datastructures
{
public:
    Datastructures();
    ~Datastructures();

    // Estimate of performance: O(1)
    // Short rationale for estimate: saadaan helposti std::size()
    unsigned int size();

    // Estimate of performance: O(n)
    // Short rationale for estimate: std::clear()
    void clear();

    // Estimate of performance: O(n) ~O(1)
    // Short rationale for estimate: unordered mapin etsintä, find()
    std::string get_name(TownID id);

    // Estimate of performance: O(n) ~O(1)
    // Short rationale for estimate: unordered mapin etsintä, find()
    Coord get_coordinates(TownID id);

    // Estimate of performance: O(n) ~O(1)
    // Short rationale for estimate: unordered mapin etsintä, find()
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

    // Estimate of performance: O(n) ~O(1)
    // Short rationale for estimate: unordered mapin etsintä, find()
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

    // Estimate of performance: O(n) ~O(1)
    // Short rationale for estimate: unordered mapin etsintä, find()
    bool add_vassalship(TownID vassalid, TownID masterid);

    // Estimate of performance: O(1) / O(n)
    // Short rationale for estimate: Jos verokaupunkeja paljon (pointer ketju pitkä)
    std::vector<TownID> taxer_path(TownID id);

    // Estimate of performance: O(n) ~O(1)
    // Short rationale for estimate: unordered mapin etsintä, find()
    bool add_road(TownID town1, TownID town2);

    // Estimate of performance: O(n log n)
    // Short rationale for estimate: ID sorttaus
    std::vector<TownID> get_roads_from(TownID id);

    // Estimate of performance: O(n²)
    // Short rationale for estimate: Kaksi silmukkaa sisäkkäin missä etsitään kaikki tiet
    std::vector<std::pair<TownID, TownID>> all_roads();

    // Estimate of performance: O(n) ~O(1)
    // Short rationale for estimate: unordered mapin etsintä ja poisto, find(), erase()
    bool remove_road(TownID town1, TownID town2);

    // Estimate of performance: O(n²)
    // Short rationale for estimate: Kaupunkien läpikäyminen + unordered mapin tyhjentäminen, clear()
    void clear_roads();

    // Estimate of performance: O(kaupunkien määrä + teiden määrä)
    // Short rationale for estimate: BFS-hakualgoritmi
    std::vector<TownID> any_route(TownID fromid, TownID toid);


    // - - - - - - - - - - - - - -
    // Non-compulsory operations
    // - - - - - - - - - - - - - -

    // Estimate of performance: O(n)
    // Short rationale for estimate: Joutuu pahimmillaan etsimään poistettavan kaupungin lineaarisesti
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

    // New ones!

    // Estimate of performance: O(kaupunkien määrä + teiden määrä)
    // Short rationale for estimate: BFS-hakualgoritmi, O(towns+roads)
    std::vector<TownID> least_towns_route(TownID fromid, TownID toid);

    // Estimate of performance: O(kaupunkien määrä + teiden määrä)
    // Short rationale for estimate: DFS-hakualgoritmi, O(towns+roads)
    // Tosin oma tyhmä loop toteutus -> O(n²)
    std::vector<TownID> road_cycle_route(TownID startid);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> shortest_route(TownID fromid, TownID toid);

    // Estimate of performance:
    // Short rationale for estimate:
    Dist trim_road_network();

private:
    unsigned int distance(int x1, int x2, int y1, int y2);
    // Tietorakenteet
    std::unordered_map<TownID, Townptr> towns_;

    std::vector<Townptr> alphaorder_;
    std::vector<Townptr> origoorder_;
    std::vector<Townptr> coordorder_;

    // Liput onko vektorit järjestyksessä
    bool isalphaorder_;
    bool isorigoorder_;
    bool iscoordorder_;

    // Indeksi johon asti vektorit on järjestyksessä
    std::vector<Townptr>::iterator index_alpha_;
    std::vector<Townptr>::iterator index_origo_;

    // Pidetään kirjaa mistä koordinaatista halutaan etäisyyttä mitata
    Coord from_;
};

#endif // DATASTRUCTURES_HH
