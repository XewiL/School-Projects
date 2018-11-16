// Datastructures.cc

#include "datastructures.hh"

#include <random>
#include <algorithm>

#include <QTextStream>

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


unsigned int Datastructures::size()
{
    return alphaorder_.size();
}

void Datastructures::clear()
{
    // Muistin putsaaminen
    unsigned int size = alphaorder_.size();
    for (unsigned int i = 0; i < size; ++i) {
        delete alphaorder_[i];
    }

    // Tyhjennetään tietorakenteet
    towns_.clear();
    alphaorder_.clear();
    origoorder_.clear();
    coordorder_.clear();

    isalphaorder_ = isorigoorder_ =  iscoordorder_ = true;
    index_alpha_ = alphaorder_.begin();
    index_origo_ = origoorder_.begin();
}

std::string Datastructures::get_name(TownID id)
{
    auto search = towns_.find(id);
    if (search != towns_.end()) return search->second->name;
    else return NO_NAME;
}

std::pair<int, int> Datastructures::get_coordinates(TownID id)
{
    auto search = towns_.find(id);
    if (search != towns_.end()) return {search->second->x, search->second->y};
    else return {NO_VALUE, NO_VALUE};
}

int Datastructures::get_tax(TownID id)
{
    auto search = towns_.find(id);
    if (search != towns_.end()) return search->second->tax;
    else return NO_VALUE;
}

// Etsittävän kaupungin ensimmäiset vassallikaupungit
std::vector<TownID> Datastructures::get_vassals(TownID id)
{
    auto search = towns_.find(id);
    if (search != towns_.end()) {
        std::vector<TownData*> vassals = search->second->vassaltowns;
        std::vector<TownID> ids;

        // Kopioidaan kaupunkien id:t ja sortataan järjestykseen
        for (auto towns : vassals) ids.push_back(towns->id);
        std::sort(ids.begin(), ids.end());
        return ids;
    }
    else return {NO_ID};
}

// Kaikki kaupunkien ID:t satunnaisessa järjestyksessä
std::vector<TownID> Datastructures::all_towns()
{
    // Silmukka jossa käydään tietorakenne läpi ja lisätään id:t vectoriin
    std::vector<TownID> ids;
    for (TownData* town : alphaorder_) ids.push_back(town->id);
    return ids;
}


bool Datastructures::add_town(TownID id, const std::string& name, int x, int y, int tax)
{
    auto search = towns_.find(id);
    if (search == towns_.end()) {
        TownData newtown = {id, name, x, y, tax, nullptr, {}};
        TownData* townptr = new TownData(newtown);

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


bool Datastructures::change_town_name(TownID id, const std::string& newname)
{
    auto change = towns_.find(id);
    if (change != towns_.end()) {
        change->second->name = newname;
        return true;
    } else return false;
}

std::vector<TownID> Datastructures::towns_alphabetically()
{
    std::vector<TownID> ids;
    if (!isalphaorder_) {
        // Sort - Merge
        // Sortataan vain vektorin loppu pää joka ei ole vielä järjestyksessä
        // ja sen jälkeen mergetään alkupää ja loppu pää.
        if(unsigned(std::distance(alphaorder_.begin(), index_alpha_)) < alphaorder_.size() - 1
                && index_alpha_ != alphaorder_.begin()) {

            std::sort(index_alpha_+ 1, alphaorder_.end(),
                      [](TownData* a, TownData* b) { return a->name < b->name; });

            std::inplace_merge(alphaorder_.begin(), index_alpha_, alphaorder_.end(),
                               [](TownData* a, TownData* b) { return a->name < b->name; });

            index_alpha_ = alphaorder_.end();

        } else {
            // Sortataan koko vektori, kun se tehdään ensimmäistä kertaa
            std::sort(alphaorder_.begin(), alphaorder_.end(),
                      [](TownData* a, TownData* b) { return a->name < b->name; });
        }
    }
    // Palautetaan ID vektori
    for (TownData* town : alphaorder_) {
        ids.push_back(town->id);
    }
    isalphaorder_ = true;
    return ids;
}

std::vector<TownID> Datastructures::towns_distance_increasing()
{
    std::vector<TownID> ids;
    if (!isorigoorder_) {
        // Sort - Merge
        // Sortataan vain vektorin loppu pää joka ei ole vielä järjestyksessä
        // ja sen jälkeen mergetään alkupää ja loppu pää.
        if (unsigned(std::distance(origoorder_.begin(), index_origo_)) < origoorder_.size() - 1
                && index_origo_ != origoorder_.begin()) {
            std::sort(index_origo_ + 1, origoorder_.end(), [](TownData* a, TownData* b) {
                return abs(a->x - 0) + abs(a->y - 0) < abs(b->x - 0) + abs(b->y - 0); // Etäisyys origosta
            });
            std::inplace_merge(origoorder_.begin(), index_origo_, origoorder_.end(),
                    [](TownData* a, TownData* b) {
                return abs(a->x - 0) + abs(a->y - 0) < abs(b->x - 0) + abs(b->y - 0);
            });
        } else {
            // Sortataan koko vektori, kun se tehdään ensimmäistä kertaa
            std::sort(origoorder_.begin(), origoorder_.end(), [](TownData* a, TownData* b) {
                return abs(a->x - 0) + abs(a->y - 0) < abs(b->x - 0) + abs(b->y - 0);
            });
        }
    }
    for (TownData* town : origoorder_) {
        ids.push_back(town->id);
    }
    isorigoorder_ = true;
    return ids;
}


// Palauttaa kaupungit, joilla on annettu nimi tai tyhjän
// vektorin, jos sellaisia ei ole. Paluuarvo on järjestettävä
// nousevan ID:n mukaiseen järjestykseen.
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
        std::sort(ids.begin(), ids.end());
    }
    return ids;
}


TownID Datastructures::min_distance()
{
    unsigned int size = origoorder_.size();
    if (size == 0) return NO_ID;

    // Jos järjestyksessä -> ensimmäinen alkio, muuten etsitään lineaarisesti
    // koska ei ole järkeä maksaa suurempaa tehokkuuttaa järjestämisestä
    TownData* mdtown = origoorder_.front();

    if (isorigoorder_) return mdtown->id;
    else {
        unsigned int shortest = distance(mdtown -> x, 0, mdtown -> y, 0);

        for (unsigned int i = 1; i < size; ++i) {
            unsigned int dist = distance(origoorder_[i] -> x, 0, origoorder_[i] -> y, 0);
            if (dist < shortest) {
                mdtown = origoorder_[i];
                shortest = dist;
            }
        }
    }
    return mdtown->id;
}


TownID Datastructures::max_distance()
{
    unsigned int size = origoorder_.size();
    if (size == 0) return NO_ID;

    // Jos järjestyksessä -> viimeinen alkio, muuten etsitään lineaarisesti
    TownData* mdtown = origoorder_.back();

    if (isorigoorder_) return mdtown->id;
    else {
        unsigned int longest = distance(origoorder_[0] -> x, 0, origoorder_[0] -> y, 0);
        mdtown = origoorder_[0];

        for (unsigned int i = 1; i < size; ++i) {
            unsigned int dist = distance(origoorder_[i] -> x, 0, origoorder_[i] -> y, 0);
            if (dist > longest) {
                mdtown = origoorder_[i];
                longest = dist;
            }
        }
    }
    return mdtown->id;
}


// Jos kaupungit ovat jo etäisyysjärjestyksessä origosta saadaan n. alkio helposti.
// Muuten järjestetään kaupungit etäisyysjärjestykseen origosta.
TownID Datastructures::nth_distance(unsigned int n)
{
    unsigned int size = origoorder_.size();

    if (size == 0 || n > size) return NO_ID;
    else if (size == 1) return origoorder_.front()->id;
    else if (isorigoorder_) return origoorder_[n - 1]->id;
    else return towns_distance_increasing()[n - 1];
}


// Jos jompaa kumpaa kaupunkia ei löydy tai vasallilla on jo isäntä, ei tehdä
// mitään ja palautetaan false. Muuten palautetaan true.
bool Datastructures::add_vassalship(TownID vassalid, TownID masterid)
{
    auto vassal = towns_.find(vassalid);
    auto master = towns_.find(masterid);

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

        TownData* townptr = town->second->mastertown;

        while (townptr != nullptr) {
            ids.push_back(townptr->id);
            townptr = townptr->mastertown;
        }
        return ids;
    } else return {};
}


// - - - - - - - - - - - - -
//
// EI PAKOLLISET
//
// - - - - - - - - - - - - -


// Funktiossa on bugi. Jos poistetaan kaupunki jolla verosuhteita niin ohjelma
// kaatuu (example-data.txt, datassa kun poistetaan Kuopio tai Oulu niin osoitin
// jää osoittamaan silti master kaupunkiin).
// En tajua missä vika. Siksi pointterin deletointi kommenteissa.
bool Datastructures::remove_town(TownID id)
{
    auto remove = towns_.find(id);
    if (remove != towns_.end()) {
        TownData* mastertown = remove->second->mastertown;
        std::vector<TownData*> vassals = remove->second->vassaltowns;

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
            std::vector<TownData*> mastervassals = mastertown->vassaltowns;
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
//                delete coordorder_[i]; // Ennen viimeistä osoitinta vapautetaan myös muisti
                coordorder_.erase(coordorder_.begin() + i);
                break;
            }
        }
        return true;
    }
    return false; // Jos poistettavaa kaupunkia ei löytynyt
}


std::vector<TownID> Datastructures::towns_distance_increasing_from(int x, int y)
{
    std::vector<TownID> ids;

    // Jos vektori on jo järjestyksessä annetusta (x ,y):stä palautetaan id:t
    // suoraan, muuten vektori on järjestettävä ensin järjestykseen.
    if(iscoordorder_ && from_.x == x && from_.y == y) {
        for (TownData* town : coordorder_) {
            ids.push_back(town->id);
        }
        return ids;
    } else {
        // Tallennetaan annettu (x, y) talteen
        from_.x = x;
        from_.y = y;
        std::sort(coordorder_.begin(), coordorder_.end(),
                  [x, y](const TownData* a, const TownData* b) {
            return abs(a->x - x) + abs(a->y - y) < abs(b->x - x) + abs(b->y - y); // Etäisyys (x,y):stä
        });
        iscoordorder_ = true;

        for (TownData* town : coordorder_) {
            ids.push_back(town->id);
        }
        return ids;
    }
}

std::vector<TownID> Datastructures::longest_vassal_path(TownID id)
{
    std::vector<TownID> ids;
    auto town = towns_.find(id);
    if (town != towns_.end()) {
        // Rekursiivisesti käytäisiin puu vassalvektorista alaspäin

//        std::vector<std::vector<TownID>> vassals = vassalTravel();
    }

    //return ids;
    return {};
}

int Datastructures::total_net_tax(TownID id)
{
    return NO_VALUE; // Replace with actual implementation
}


std::vector<std::vector<TownID>> Datastructures::vassalTravel()
{
    return {{}};

}

// Etäisyyden mittaus kahden kordinaatin välillä tehtäväannon mukaan
unsigned int Datastructures::distance(int x1, int x2, int y1, int y2)
{
    return abs(x1 - x2) + abs(y1 - y2);
}
