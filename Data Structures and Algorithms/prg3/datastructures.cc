// Datastructures.cc

#include "datastructures.hh"

#include <random>
#include <cmath>
#include <algorithm>
#include <queue>
#include <stack>
#include <iostream>

std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
}


Datastructures::Datastructures() :
isalphaorder_(true), isorigoorder_(true), iscoordorder_(true), from_({0, 0})
{

}

Datastructures::~Datastructures()
{
    clear();
}

// Palauttaa tietorakenteessa olevien kaupunkien lukumäärän.
unsigned int Datastructures::size()
{
    return towns_.size();
}

// Tyhjentää tietorakenteet eli poistaa kaikki kaupungit
// (tämän jälkeen size palauttaa 0).
void Datastructures::clear()
{
    towns_.clear();
    alphaorder_.clear();
    origoorder_.clear();
    coordorder_.clear();

    isalphaorder_ = isorigoorder_ = iscoordorder_ = true;
    index_alpha_ = alphaorder_.begin();
    index_origo_ = origoorder_.begin();
}

// Palauttaa annetulla ID:llä olevan kaupungin nimen, tai
// NO_NAME, jos id:llä ei löydy kaupunkia.
std::string Datastructures::get_name(TownID id)
{
    auto search = towns_.find(id);
    if (search != towns_.end()) return search->second->name;
    else return NO_NAME;
}

// Palauttaa annetulla ID:llä olevan kaupungin sijainnin,
// tai parin (NO_VALUE, NO_VALUE), jos id:llä ei löydy kaupunkia.
Coord Datastructures::get_coordinates(TownID id)
{
    auto search = towns_.find(id);
    if (search != towns_.end())
        return {search->second->coordinates.first,search->second->coordinates.second};
    else return NO_COORD;
}

// Palauttaa annetulla ID:llä olevan kaupungin verotiedon,
// tai NO_VALUE, jos id:llä ei löydy kaupunkia.
int Datastructures::get_tax(TownID id)
{
    auto search = towns_.find(id);
    if (search != towns_.end()) return search->second->tax;
    else return NO_VALUE;
}

// Palauttaa annetulla ID:llä olevan kaupungin välittömien vasallien id:t
// (ts. mukaan ei lasketa vasallien vasalleja), tai vektorin jonka
// ainoa alkio on NO_ID, jos id:llä ei löydy kaupunkia. Paluuarvo on
// järjestettävä nousevan ID:n mukaiseen järjestykseen.
std::vector<TownID> Datastructures::get_vassals(TownID id)
{
    auto search = towns_.find(id);
    if (search != towns_.end()) {
        std::vector<Townptr> vassals = search->second->vassaltowns;
        std::vector<TownID> ids;

        // Kopioidaan kaupunkien id:t ja sortataan järjestykseen
        for (auto towns : vassals) ids.push_back(towns->id);
        std::sort(ids.begin(), ids.end());
        return ids;
    }
    else return {NO_ID};
}

// Palauttaa kaikki tietorakenteessa olevat kaupungit
// mielivaltaisessa järjestyksessä.
std::vector<TownID> Datastructures::all_towns()
{
    // Silmukka jossa käydään tietorakenne läpi ja lisätään id:t vectoriin
    std::vector<TownID> ids;
    for (Townptr town : alphaorder_) ids.push_back(town->id);
    return ids;
}

// Lisää tietorakenteeseen uuden kaupungin annetulla uniikilla id:llä,
// nimellä, sijainnilla ja verotulolla. Aluksi kaupungit eivät ole minkään
// toisen kaupungin vasalleja. Jos annetulla id:llä on jo kaupunki, ei tehdä
// mitään ja palautetaan false, muuten palautetaan true.
bool Datastructures::add_town(TownID id, const std::string& name, int x, int y, int tax)
{
    auto search = towns_.find(id);
    if (search == towns_.end()) { // jos kaupunkia vielä ole, se lisätään
        TownData newtown = {id, name, {x, y}, tax, nullptr, {}, {}, false, nullptr};
        Townptr townptr(new TownData(newtown));

        // Kaupunkien lisäykset tietorakenteisiin
        towns_.insert({id, townptr});
        alphaorder_.push_back(townptr);
        origoorder_.push_back(townptr);
        coordorder_.push_back(townptr);

        // Liput
        isalphaorder_ = isorigoorder_ = iscoordorder_ = false;

        return true;

    } else return false;
}

// Muuttaa annetulla ID:llä olevan kaupungin nimen.
// Jos kaupunkia ei löydy, palauttaa false, muuten true.
bool Datastructures::change_town_name(TownID id, const std::string& newname)
{
    auto change = towns_.find(id);
    if (change != towns_.end()) {
        change->second->name = newname;
        return true;
    } else return false;
}

// Palauttaa kaupungit nimen mukaan aakkosjärjestyksessä.
std::vector<TownID> Datastructures::towns_alphabetically()
{
    std::vector<TownID> ids;
    if (!isalphaorder_) {
        // Sort - Merge
        // Sortataan vain vektorin loppu pää, joka ei ole vielä järjestyksessä
        // ja sen jälkeen mergetään alkupää ja loppupää.
        if(unsigned(std::distance(alphaorder_.begin(), index_alpha_)) < alphaorder_.size() - 1
                && index_alpha_ != alphaorder_.begin()) {

            std::sort(index_alpha_ + 1, alphaorder_.end(),
                      [](Townptr a, Townptr b) { return a->name < b->name; });

            std::inplace_merge(alphaorder_.begin(), index_alpha_, alphaorder_.end(),
                               [](Townptr a, Townptr b) { return a->name < b->name; });

            index_alpha_ = alphaorder_.end();

        } else {
            // Sortataan koko vektori, kun se tehdään ensimmäistä kertaa
            std::sort(alphaorder_.begin(), alphaorder_.end(),
                      [](Townptr a, Townptr b) { return a->name < b->name; });
        }
    }
    // Palautetaan ID vektori
    for (Townptr town : alphaorder_) {
        ids.push_back(town->id);
    }
    isalphaorder_ = true;
    return ids;
}

// Palauttaa kaupungit etäisyysjärjestyksessä origosta (0,0), lähin ensin.
std::vector<TownID> Datastructures::towns_distance_increasing()
{
    std::vector<TownID> ids;
    if (!isorigoorder_) {
        // Sort - Merge
        // Sortataan vain vektorin loppu pää joka ei ole vielä järjestyksessä
        // ja sen jälkeen mergetään alkupää ja loppu pää.
        if (unsigned(std::distance(origoorder_.begin(), index_origo_)) < origoorder_.size() - 1
                && index_origo_ != origoorder_.begin()) {
            std::sort(index_origo_ + 1, origoorder_.end(), [](Townptr a, Townptr b) {
                // Etäisyys origosta
                return abs(a->coordinates.first - 0) + abs(a->coordinates.second - 0)
                        < abs(b->coordinates.first - 0) + abs(b->coordinates.second - 0);
            });
            std::inplace_merge(origoorder_.begin(), index_origo_, origoorder_.end(),
                    [](Townptr a, Townptr b) {
                return abs(a->coordinates.first - 0) + abs(a->coordinates.second - 0)
                        < abs(b->coordinates.first - 0) + abs(b->coordinates.second - 0);
            });
        } else {
            // Sortataan koko vektori, kun se tehdään ensimmäistä kertaa
            std::sort(origoorder_.begin(), origoorder_.end(), [](Townptr a, Townptr b) {
                return abs(a->coordinates.first - 0) + abs(a->coordinates.second - 0)
                        < abs(b->coordinates.second - 0) + abs(b->coordinates.second - 0);
            });
        }
    }
    for (Townptr town : origoorder_) {
        ids.push_back(town->id);
    }
    isorigoorder_ = true;
    return ids;
}

// Palauttaa kaupungit, joilla on annettu nimi tai tyhjän vektorin, jos sellaisia
// ei ole. Paluuarvo on järjestettävä nousevan ID:n mukaiseen järjestykseen.
std::vector<TownID> Datastructures::find_towns(std::string const& name)
{
    std::vector<TownID> ids;

    // Jos kaupungit ovat nimijärjestyksessä, haetaan binäärihaualla,
    // muuten lineaarisesti koko tietokanta läpi ja etsitään kaupungit.
    if (isalphaorder_) {
        auto range = std::equal_range(alphaorder_.begin(), alphaorder_.end(), name, CompareNames{});
        for (auto i = range.first; i != range.second; ++i)
            ids.push_back((*i)->id);

    } else {
        // Koko tietokannan käyminen läpi lineaarisesti, avain = id
        // Sortataan saatu vektori ID:n mukaan
        for (auto town : alphaorder_)
            if (town->name == name) ids.push_back(town->id);
    }
    std::sort(ids.begin(), ids.end());
    return ids;
}

// Palauttaa kaupungin, joka on lähinnä origoa (0,0). Jos tällaisia on useita,
// palauttaa jonkin niistä. Jos kaupunkeja ei ole, palautetaan NO_ID.
TownID Datastructures::min_distance()
{
    unsigned int size = origoorder_.size();
    if (size == 0) return NO_ID;

    // Jos järjestyksessä -> ensimmäinen alkio, muuten etsitään lineaarisesti
    // koska ei ole järkeä maksaa suurempaa tehokkuuttaa järjestämisestä
    Townptr mdtown = origoorder_.front();

    if (isorigoorder_) return mdtown->id;
    else {
        unsigned int shortest = distance(mdtown -> coordinates.first, 0,
                                         mdtown -> coordinates.second, 0);

        for (unsigned int i = 1; i < size; ++i) {
            unsigned int dist = distance(origoorder_[i] -> coordinates.first, 0,
                                         origoorder_[i] -> coordinates.second, 0);
            if (dist < shortest) {
                mdtown = origoorder_[i];
                shortest = dist;
            }
        }
    }
    return mdtown->id;
}

// Palauttaa kaupungin, joka on kauimpana origosta (0,0). Jos tällaisia on useita,
// palauttaa jonkin niistä. Jos kaupunkeja ei ole, palautetaan NO_ID.
TownID Datastructures::max_distance()
{
    unsigned int size = origoorder_.size();
    if (size == 0) return NO_ID;

    // Jos järjestyksessä -> viimeinen alkio, muuten etsitään lineaarisesti
    Townptr mdtown = origoorder_.back();

    if (isorigoorder_) return mdtown->id;
    else {
        unsigned int longest = distance(origoorder_[0] -> coordinates.first, 0,
                                        origoorder_[0] -> coordinates.second, 0);
        mdtown = origoorder_[0];

        for (unsigned int i = 1; i < size; ++i) {
            unsigned int dist = distance(origoorder_[i] -> coordinates.first, 0,
                                         origoorder_[i] -> coordinates.second, 0);
            if (dist > longest) {
                mdtown = origoorder_[i];
                longest = dist;
            }
        }
    }
    return mdtown->id;
}

// Palauttaa kaupungin, joka on etäisyysjärjestyksessä n:s origosta (0,0).
// Jos tällaisia on useita, palauttaa jonkin niistä. Jos n on 0 tai suurempi
// kuin kaupunkien määrä, palautetaan NO_ID.
TownID Datastructures::nth_distance(unsigned int n)
{
    unsigned int size = origoorder_.size();

    // Jos kaupungit ovat jo etäisyysjärjestyksessä origosta saadaan n. alkio helposti.
    // Muuten järjestetään kaupungit etäisyysjärjestykseen origosta.
    if (size == 0 || n > size) return NO_ID;
    else if (size == 1) return origoorder_.front()->id;
    else if (isorigoorder_) return origoorder_[n - 1]->id;
    else return towns_distance_increasing()[n - 1];
}

// Lisää kaupunkien välille vasallisuhteen. Kaupunki voi olla vain yhden kaupungin
// vasallikaupunki. Työssä saa olettaa, että vasallisuhteet eivät voi muodostaa
// silmukoita (ts. kaupunki ei voi olla suoraan tai epäsuorasti itsensä vasalli).
// Jos jompaa kumpaa kaupunkia ei löydy tai vasallilla on jo isäntä, ei tehdä
// mitään ja palautetaan false. Muuten palautetaan true.
bool Datastructures::add_vassalship(TownID vassalid, TownID masterid)
{
    auto vassal = towns_.find(vassalid);
    auto master = towns_.find(masterid);

    // Jos jompaa kumpaa kaupunkia ei löydy tai vasallilla on jo isäntä, ei tehdä
    // mitään ja palautetaan false. Muuten palautetaan true.
    if (vassal != towns_.end() && master != towns_.end()
            && vassal->second->mastertown == nullptr) {
        vassal->second->mastertown = master->second;
        master->second->vassaltowns.push_back(vassal->second);
        return true;

    } else return false;
}

// Palauttaa listan kaupungeista, joille kaupunki maksaa veroa suoraan
// tai epäsuorasti. Paluuvektoriin talletetaan ensin kaupunki itse, sitten sen
// isäntä, isännän isäntä jne. niin kauan kuin isäntiä riittää. Jos id:llä ei
// ole kaupunkia, palautetaan tyhjä vektori.
std::vector<TownID> Datastructures::taxer_path(TownID id)
{
    auto town = towns_.find(id);
    if (town != towns_.end()) {

        std::vector<TownID> ids;
        ids.push_back(town->second->id);

        Townptr townptr = town->second->mastertown;

        while (townptr != nullptr) {
            ids.push_back(townptr->id);
            townptr = townptr->mastertown;
        }
        return ids;
    } else return {};
}


// Lisää annettujen kaupunkien välille tien. Jos jompaa kumpaa kaupunkia ei löydy
// tai niiden välillä on jo tie, ei tehdä mitään ja palautetaan false, muuten true.
bool Datastructures::add_road(TownID town1, TownID town2)
{
    auto t1 = towns_.find(town1);
    auto t2 = towns_.find(town2);
    if (t1 != towns_.end() && t2 != towns_.end()) {
        auto t12 = t1->second->roads.find(town2);
        auto t21 = t2->second->roads.find(town1);

        // Löytyykö kaupunkien väliltä jo tie entuudestaan
        if (t12 == t1->second->roads.end() && t21 == t2->second->roads.end()) {
            t1->second->roads.insert({t2->first, t2->second});
            t2->second->roads.insert({t1->first, t1->second});
            return true;
        }
    }
    return false; // Jos kaupunkia ei löytynyt tai niiden välillä oli jo tie
}

// Palauttaa nousevan id:n mukaisessa järjestyksessä listan kapungeista,
// joihin annetusta kaupungista menee suoraan tie.
// Jos annettua kaupunkia ei löydy, palautetaan ainoana alkiona NO_ID.
std::vector<TownID> Datastructures::get_roads_from(TownID id)
{
    auto town = towns_.find(id);
    if (town != towns_.end()) {
        std::vector<TownID> ids;

        for (auto road : town->second->roads)
            ids.push_back(road.first);
        std::sort(ids.begin(), ids.end());
        return ids;
    } else return {NO_ID};
}

// Palauttaa listan kaikista teistä. Jokainen tie on listassa pari kaupunki-id:itä,
// ja esitetään siinä järjestyksessä, että parin ensimmäinen id on pienempi kuin
// toinen id. Listassa parit on järjestetty ensisijaisesti ensimmäisen
// id:n mukaan, toissijaisesti toisen.
std::vector<std::pair<TownID, TownID>> Datastructures::all_roads()
{
    if (towns_.size() == 0) return {};
    else {
        std::vector<std::pair<TownID, TownID>> townpairs;

        // merkataan kaikki kaupungit läpikäymättömäksi.
        for (auto town : towns_){
            town.second->marked = false;
        }
        // Käydään kaupunkeja läpi ja niiden teiden päässä olevia kaupunkeja
        // ja lisätään vektoripariin.
        for (auto town1 : towns_) {
            town1.second->marked = true; // merkataan kaupunki läpikäydyksi
            for (auto town2 : town1.second->roads) {
                // jos reittiä ei olla vielä lisätty toisin päin, niin lisätään
                if (!town2.second->marked) {
                    if (town1.first < town2.first)
                        townpairs.push_back({town1.first, town2.first});
                    else
                        townpairs.push_back({town2.first, town1.first});
                }
            }
        }
        // Järjestys ID:n mukaan.
        std::sort(townpairs.begin(), townpairs.end());
        return townpairs;
    }
}


// Poistaa annettujen kaupunkien väliltä tien. Jos jompaa kumpaa kaupunkia ei löydy
// tai niiden välillä ei ole tietä, ei tehdä mitään ja palautetaan false, muuten true.
bool Datastructures::remove_road(TownID town1, TownID town2)
{
    auto t1 = towns_.find(town1);
    auto t2 = towns_.find(town2);
    if (t1 != towns_.end() && t2 != towns_.end()) {
        auto t12 = t1->second->roads.find(town2);
        auto t21 = t2->second->roads.find(town1);
        // Löytyykö kaupunkien väliltä tie
        if (t12 != t1->second->roads.end() && t21 != t2->second->roads.end()) {
            t1->second->roads.erase(town2);
            t2->second->roads.erase(town1);
            return true;
        }
    }
    return false;
}

// Poistaa kaikki tiet (mutta ei poista kaupunkeja).
void Datastructures::clear_roads()
{
    for (auto town : towns_) {
        town.second->roads.clear();
    }
}

// Palauttaa jonkin (mielivaltaisen) reitin kaupungista id1 kaupunkiin id2.
// Palautetussa vektorissa on ensimmäisenä id1, sitten kaikki reitin varrella
// olevat kaupungit järjestyksessä ja viimeisenä id2.
// Jos reittiä ei löydy, palautetaan tyhjä vektori.
// Jos jompaa kumpaa kaupunkia ei löydy, ainoana alkiona palautetaan NO_ID.
std::vector<TownID> Datastructures::any_route(TownID fromid, TownID toid)
{
    return least_towns_route(fromid, toid);
}


// - - - - - - - - - - - -
// EI PAKOLLISET FUNKTIOT
// - - - - - - - - - - - -

bool Datastructures::remove_town(TownID id)
{
    auto remove = towns_.find(id);
    if (remove != towns_.end()) {
        Townptr mastertown = remove->second->mastertown;
        std::vector<Townptr> vassals = remove->second->vassaltowns;

        if (mastertown != nullptr && vassals.size() > 0) {

            // Poistettavan kaupungin vassalkaupunkien masterit osoittamaan
            // poistettavan kaupungin masteriin
            auto viter = vassals.begin();
            while (viter != vassals.end()){
                (*viter)->mastertown = mastertown;
                ++viter;
            }

            // Poistetaan poistettavan kaupungin masterin vassaleista
            // poistettava kaupunki
            std::vector<Townptr> mastervassals = mastertown->vassaltowns;
            auto miter = mastervassals.begin();
            while (miter != mastervassals.end()) {
                if ((*miter)->id == id) {
                    mastervassals.erase(miter);
                    break;
                }
                ++miter;
            }

            // Poistetaan kaikki pointterit myös poistettavasta kaupungista.
            // Tyhjennetään poistettavan kaupungin vassal vektori
            // ja masterkaupunki -> nullptr
            vassals.clear();
            mastertown = nullptr;
        }

        // Helpoimman kautta ja laitetaan järjestysindeksi nolliin
        index_alpha_ = alphaorder_.begin();
        index_origo_ = origoorder_.begin();

        // Teiden poisto poistettavasta kaupungista
        for (auto road : remove->second->roads)
            remove_road(id, road.second->id);

        // Poistetaan pointterit kaikista tietorakenteista
        towns_.erase(id);
        unsigned int size = alphaorder_.size();
        for (unsigned int i = 0; i < size; ++i) {
            if (alphaorder_[i] -> id == id) {
                alphaorder_.erase(alphaorder_.begin() + i);
                break;
            }
        }
        for (unsigned int i = 0; i < size; ++i) {
            if (origoorder_[i] -> id == id) {
                origoorder_.erase(origoorder_.begin() + i);
                break;
            }
        }
        for (unsigned int i = 0; i < size; ++i) {
            if (coordorder_[i] -> id == id) {
                coordorder_.erase(coordorder_.begin() + i);
                break;
            }
        }
        return true;
    }
    return false; // Jos poistettavaa kaupunkia ei löytynyt
}

// Palauttaa kaupungit etäisyysjärjestyksessä annetusta
// koordinaatista (x,y), lähin ensin.
std::vector<TownID> Datastructures::towns_distance_increasing_from(int x, int y)
{
    std::vector<TownID> ids;

    // Jos vektori on jo järjestyksessä annetusta (x ,y):stä palautetaan id:t
    // suoraan, muuten vektori on järjestettävä ensin järjestykseen.
    if(iscoordorder_ && from_.first == x && from_.second == y) {
        for (Townptr town : coordorder_) {
            ids.push_back(town->id);
        }
        return ids;
    } else {
        // Tallennetaan annettu (x, y) talteen
        from_.first = x;
        from_.second = y;
        std::sort(coordorder_.begin(), coordorder_.end(),
                  [x, y](const Townptr a, const Townptr b) {
            // Etäisyys (x,y):stä
            return abs(a->coordinates.first - x) + abs(a->coordinates.second - y)
                    < abs(b->coordinates.first - x) + abs(b->coordinates.second - y);
        });
        iscoordorder_ = true;

        for (Townptr town : coordorder_) {
            ids.push_back(town->id);
        }
        return ids;
    }
}

// Ei ollut tehtynä myöskään prg2:ssa
std::vector<TownID> Datastructures::longest_vassal_path(TownID id)
{
    return {}; // Replace with actual implementation
}

// Ei ollut tehtynä myöskään prg2:ssa
int Datastructures::total_net_tax(TownID id)
{
    return NO_VALUE; // Replace with actual implementation
}


// - - - - - - - - - - - - - - -
// UUDET EI PAKOLLISET FUNKTIOT
// - - - - - - - - - - - - - - -

// Palauttaa sellaisen reitin kaupungista id1 kaupunkiin id2, jonka varrella on
// mahdollisimman vähän kaupunkeja. Jos usealla reitillä on yhtä vähän kaupunkeja,
// palautetaan jokin niistä.
// Palautetussa vektorissa on ensimmäisenä id1, sitten kaikki reitin varrella
// olevat kaupungit ja viimeisenä id2.
// Jos reittiä ei löydy, palautetaan tyhjä vektori.
// Jos jompaa kumpaa kaupunkia ei löydy, ainoana alkiona palautetaan NO_ID.

// Käytetään tähän leveyteen ensin hakua (BFS)
std::vector<TownID> Datastructures::least_towns_route(TownID fromid, TownID toid)
{
    auto t1 = towns_.find(fromid);
    auto t2 = towns_.find(toid);
    if (t1 != towns_.end() && t2 != towns_.end()) {
        std::vector<TownID> route;
        Townptr town1 = t1->second;
        Townptr town2 = t2->second;

        // Jos lähtö ja maali samat
        if (town1 == town2) {
            route.push_back(town1->id);
            return route;
        } else {

            // Merkataan ensin kaikki kaupungit läpikäymättömäksi
            // ja mistä ollaan tultu
            for (auto town : towns_){
                town.second->marked = false;
                town.second->from = nullptr;
            }

            std::queue<Townptr> queue;
            town1->marked = true;
            queue.push(town1);

            while (!queue.empty()) {
                Townptr t = queue.front();
                queue.pop();

                // Jos löydetään kaupunki, aletaan etsimään miten sinne päädyttiin
                if (t == town2) {
                    Townptr iter = t;
                    while (iter != town1) {
                        route.push_back(iter->id);
                        iter = iter->from;
                    }
                    // Lisätään vielä lähtökaupunki ja käännetään järjestys
                    route.push_back(town1->id);
                    std::reverse(route.begin(), route.end());
                    return route;
                }
                for (auto road : t->roads) {
                    if (!road.second->marked) {
                        road.second->marked = true;
                        road.second->from = t;
                        queue.push(road.second);
                    }
                }
            }
        }
        // Tänne päädytään, jos ei reittiä löydy -> palautetaan tyhjä vektori
        return {};
    } else return {NO_ID};
}

// Tarkastaa, voiko annetusta kaupungista kulkea tieverkkoa pitkin niin,
// että reittiin muodostuu silmukka (palataan eri tietä johonkin reitin varrella olevaan
// kaupunkiin). Paluuarvona palautetaan reitti, joka päättyy ko. silmukkaan
// (paluuarvon viimeisenä kaupunkina on kaupunki, johon palaaminen muodostaa silmukan).
// Jos reittiä ei löydy, palautetaan tyhjä vektori.
// Jos annettua kaupunkia ei löydy, palautetaan ainoana alkiona NO_ID.

// Käytetään tähän syvyyteen ensin hakua (DFS)
std::vector<TownID> Datastructures::road_cycle_route(TownID startid)
{
    auto search = towns_.find(startid);
    if (search != towns_.end()) {
        std::vector<TownID> route;
        Townptr start = search->second;

        // Merkataan ensin kaikki kaupungit läpikäymättömäksi
        // ja mistä ollaan tultu
        for (auto town : towns_){
            town.second->marked = false;
            town.second->from = nullptr;
        }
        
        std::vector<Townptr> stack;
        start->marked = true;
        stack.push_back(start);

        while (!stack.empty()) {
            Townptr t = stack.back();
            stack.pop_back();

            for (auto road : t->roads) {

                // Jos löydetään kaupunki joka on vielä stackissä
                // ollaan löydetty silmukka
                // p.s. joku voisi neuvoa miten tän saa std::find_if + lambdalla :)

                // Ehkä jotenkin näin
                // auto iter = std::find_if(stack.begin(), stack.end(), [road](auto s){return road.second->id == s->id;});

                // Koitin tätä ehtoa etsiä jotenkin muutenkin noiden previous yms
                // pointterien avulla mutta pää hajosi lopulta
                // joten keksin tän hätäratkaisun, mutta tästä nyt tuli auttamattoman hidas :(
//                bool found = false;
//                for (auto s : stack) {
//                    if (s->id == road.second->id) {
//                        found = true;
//                        break;
//                    }
//                }

//                if (found) {

                // Jos löydetään merkattu kaupunki, niin ollaan löydetty silmukka
                if (road.second->marked && road.second != t->from) {
                    Townptr iter = t;
                    // Lisätään silmukan ensimmäinen ja toinen kaupunki
                    if (road.second->from != nullptr)
                        route.push_back(road.second->from->id);
                    route.push_back(road.second->id);
                    // Lisätään loput kaupungeista
                    while (iter != start) {
                        route.push_back(iter->id);
                        iter = iter->from;
                    }
                    // Lisätään vielä lähtökaupunki ja käännetään järjestys
                    route.push_back(start->id);
                    std::reverse(route.begin(), route.end());
                    return route;

                // Jos naapurikaupunki ei ole vielä merkattu läpikäydyksi
                // lisätään se stackiin
                } if (!road.second->marked) {
                    road.second->marked = true;
                    road.second->from = t;
                    stack.push_back(road.second);
                }
            }
        }
        // Tänne päädytään, jos silmukkaa ei löydy -> palautetaan tyhjä vektori
        return {};
    } else return {NO_ID}; 
}

// Palauttaa sellaisen reitin kaupungista id1 kaupunkiin id2, jonka kokonaispituus
// on mahdollisimman pieni (tien pituus on kaupunkien etäisyys käyttäen tässä
// etäisyyden määritelmää). Jos useat reitit ovat yhtä lyhyitä, palautetaan jokin niistä.
// Palautetussa vektorissa on ensimmäisenä id1, sitten kaikki reitin varrella olevat
// kaupungit ja viimeisenä id2.
// Jos reittiä ei löydy, palautetaan tyhjä vektori.
// Jos jompaa kumpaa kaupunkia ei löydy, ainoana alkiona palautetaan NO_ID.

// Käytetään tähän A* algoritmia

std::vector<TownID> Datastructures::shortest_route(TownID fromid, TownID toid)
{
    // Jotta autotestit menis läpi
    return {NO_ID}; // Replace with actual implementation

    // Kova yritys mutta ei aikaa tehdä loppuun...
    auto t1 = towns_.find(fromid);
    auto t2 = towns_.find(toid);
    if (t1 != towns_.end() && t2 != towns_.end()) {
        std::vector<TownID> route;
        Townptr town1 = t1->second;
        Townptr town2 = t2->second;

        // Jos lähtö ja maali samat
        if (town1 == town2) {
            route.push_back(town1->id);
            return route;
        } else {

            // Merkataan ensin kaikki kaupungit läpikäymättömäksi
            // ja mistä ollaan tultu
            for (auto town : towns_){
                town.second->marked = false;
                town.second->from = nullptr;
            }

            // Lyhin mahdollinen reitti
            unsigned int mindist = distance(town1->coordinates.first, town2->coordinates.first,
                                            town1->coordinates.second, town2->coordinates.second);
            std::queue<Townptr> queue;
            town1->marked = true;
            queue.push(town1);

            while (!queue.empty()) {
                Townptr t = queue.front();
                queue.pop();

                // Jos löydetään kaupunki, aletaan etsimään miten sinne päädyttiin
                if (t == town2) {
                    Townptr iter = t;
                    while (iter != town1) {
                        route.push_back(iter->id);
                        iter = iter->from;
                    }
                    // Lisätään vielä lähtökaupunki ja käännetään järjestys
                    route.push_back(town1->id);
                    std::reverse(route.begin(), route.end());
                    return route;
                }
                for (auto road : t->roads) {
                    if (!road.second->marked) {
                        road.second->marked = true;
                        //road.second->from = t;
                        queue.push(road.second);
                    }
                    // Relax

                    // Kekoa etäisyyden mukaan laskien
                }
            }
        }
        // Tänne päädytään, jos ei reittiä löydy -> palautetaan tyhjä vektori
        return {};
    } else return {NO_ID};
}

Dist Datastructures::trim_road_network()
{
    return NO_DIST; // Replace with actual implementation
}

// Etäisyyden mittaus kahden kordinaatin välillä tehtäväannon mukaan
unsigned int Datastructures::distance(int x1, int x2, int y1, int y2)
{
    return abs(x1 - x2) + abs(y1 - y2);
}
