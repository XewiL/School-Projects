// Datastructures.cc

#include "datastructures.hh"

#include <random>


std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
}


// Rakentaja
Datastructures::Datastructures() :
    isalphaorder_(true), isorigoorder_(true), iscoordorder_(true), from_({0, 0})
{

}

// Purkaja
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
    for (unsigned int i = 0; i < alphaorder_.size(); ++i) {
        delete alphaorder_[i];
    }
    alphaorder_.clear();
    origoorder_.clear();
    coordorder_.clear();

    isalphaorder_ = true;
    isorigoorder_ = true;
    iscoordorder_ = true;
}

// Vaihtelun vuoksi palautetaan joku muu järjestys :)
std::vector<TownData*> Datastructures::all_towns()
{
    return coordorder_;
}

TownData* Datastructures::add_town(const std::string& name, int x, int y)
{
    TownData town = {name, x ,y};
    TownData* townptr = new TownData(town);

    alphaorder_.push_back(townptr);
    origoorder_.push_back(townptr);
    coordorder_.push_back(townptr);

    isalphaorder_ = false;
    isorigoorder_ = false;
    iscoordorder_ = false;

    return townptr;
}

// Jos kaupungit eivät ole valmiiksi jo aakkosjärjestyksesssä, niin sortataan
std::vector<TownData*> Datastructures::towns_alphabetically()
{
    if (!isalphaorder_) {
        flag_ = true;
        randomizedQuicksort(alphaorder_, 0, alphaorder_.size() - 1);
        isalphaorder_ = true;
    }
    return alphaorder_;
}

// Jos kaupungit eivät ole valmiiksi jo etäisyysjärjestyksestä origosta, niin sortataan
std::vector<TownData*> Datastructures::towns_distance_increasing()
{
    if (!isorigoorder_) {

        // Tallennetaan nykyiset koordinaatit talteen jota käytetään
        // kun mitataan etäisyyttä jostain muusta koordinaatista
        // kuin origosta.
        fromcoordinate temp = {from_.x, from_.y};

        // Etäisyys origosta
        from_.x = 0;
        from_.y = 0;

        flag_ = false;
        randomizedQuicksort(origoorder_, 0, origoorder_.size() - 1);
        isorigoorder_ = true;

        // Palautetaan koordinaatit talteen
        from_.x = temp.x;
        from_.y = temp.y;
    }
    return origoorder_;
}

// Jos kaupungit eivät ole aakkosjärjestyksessä, haetaan lineaarisesti, muuten puolitushaulla.
TownData* Datastructures::find_town(std::string const& name)
{
    unsigned int size = alphaorder_.size();
    if (size == 0) return nullptr;
    else if (isalphaorder_) return binarySearch(alphaorder_, size, name);
    else {
        for (TownData* town : alphaorder_) {
            if (town -> name == name) return town;
        }
    }
    // Kaupunkia ei löytynyt
    return nullptr;
}


TownData* Datastructures::min_distance()
{
    // Ohjeissa ei ollut tosin virhetarkasteluista mitään mainintaa mitä
    // pitää tehdä jos ei ole kaupunkeja lainkaan.
    unsigned int size = origoorder_.size();
    if (size == 0) return nullptr;

    // Jos järjestyksessä -> ensimmäinen alkio, muuten etsitään lineaarisesti
    // koska ei ole järkeä maksaa suurempaa tehokkuuttaa järjestämisestä
    TownData* mdtown = origoorder_.front();

    if (isorigoorder_) return mdtown;
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
    return mdtown;
}

TownData* Datastructures::max_distance()
{
    // Ohjeissa ei ollut tosin virhetarkasteluista mitään mainintaa mitä
    // pitää tehdä jos ei ole kaupunkeja lainkaan.
    unsigned int size = origoorder_.size();
    if (size == 0) return nullptr;

    // Jos järjestyksessä -> viimeinen alkio, muuten etsitään lineaarisesti
    TownData* mdtown = origoorder_.back();

    if (isorigoorder_) return mdtown;
    else {
        unsigned int longest = distance(origoorder_[0] -> x, 0, origoorder_[0] -> y, 0);

        for (unsigned int i = 1; i < size; ++i) {
            unsigned int dist = distance(origoorder_[i] -> x, 0, origoorder_[i] -> y, 0);
            if(dist > longest) {
                mdtown = origoorder_[i];
                longest = dist;
            }
        }
    }
    return mdtown;
}

// Jos kaupungit ovat jo etäisyysjärjestyksessä origosta saadaan n. alkio helposti.
// Muuten järjestetään kaupungit etäisyysjärjestykseen origosta.
TownData* Datastructures::nth_distance(unsigned int n)
{
    unsigned int size = origoorder_.size();

    if (size == 0 || n > size) return nullptr;
    else if (size == 1) return origoorder_.front();
    else if (isorigoorder_) return origoorder_[n - 1];
    else return towns_distance_increasing()[n - 1];
}

// Poistetaan jokaisesta vektorista osoitin erikseen
// ja viimeisessä loopissa vapautetaan myös muisti.
void Datastructures::remove_town(const std::string& town_name)
{
    unsigned int size = alphaorder_.size();
    for (unsigned int i = 0; i < size; ++i) {
        if (alphaorder_[i] -> name == town_name) {

            // .erase() -> TEHOKKUUS n² ??
            // Toinen vaihtoehto tähän kävi mielessä, että löydetty alkio
            // swapattaisiin vectorin viimeisimmän kanssa jonka jälkeen se poistetaan,
            // mutta sen jälkeen kaikki vektorit taas olisivat epäjärjestyksessä,
            // joiden järjestäminen on tehokkuudeltaan n log n.
            alphaorder_.erase(alphaorder_.begin() + i);
            break;
        }
    }
    for (unsigned int i = 0; i < size; ++i) {
        if (origoorder_[i] -> name == town_name) {
            origoorder_.erase(origoorder_.begin() + i);
            break;
        }
    }
    for (unsigned int i = 0; i < size; ++i) {
        if (coordorder_[i] -> name == town_name) {
            delete coordorder_[i];
            coordorder_.erase(coordorder_.begin() + i);
            break;
        }
    }
    return;
}

// Jos kaupungit eivät ole valmiiksi jo etäisyysjärjestyksestä annetusta
// kordinaatista, niin sortataan annetun koordinaattien mukaan
std::vector<TownData*> Datastructures::towns_distance_increasing_from(int x, int y)
{
    if(iscoordorder_ && from_.x == x && from_.y == y) return coordorder_;
    else {
        from_.x = x;
        from_.y = y;

        flag_ = false;
        randomizedQuicksort(coordorder_, 0, coordorder_.size() - 1);
        iscoordorder_ = true;

        return coordorder_;
    }
}



// - - - - - - - - - - - - - - -
//
// Algoritmit / Private funktiot
//
// - - - - - - - - - - - - - - -


// Randomized-QuickSort algoritmi luentokalvojen mukaan
void Datastructures::randomizedQuicksort(std::vector<TownData*>& A, int left, int right)
{
    if (left < right) {
        int p = randomizedPartition(A, left, right);
        randomizedQuicksort(A, left, p -1);
        randomizedQuicksort(A, p + 1, right);
    }
    return;
}

int Datastructures::randomizedPartition(std::vector<TownData*>& A, int left, int right)
{
    // Valitaan random alkio valmiiksi annetulla funktiolla
    int p = random_in_range(left, right);
    swap(A[right], A[p]);
    return partition(A, left, right);
}

int Datastructures::partition(std::vector<TownData*>& A, int left, int right)
{
    TownData* p = A[right];
    int i = left - 1;

    unsigned int pdist = distance(p -> x, from_.x, p -> y, from_.y);

    for (int j = left; j <= right - 1; ++j) {

        // Lajitellaan nimen mukaan
        if (flag_) {
            if (A[j] -> name <= p -> name) {
                ++i;
                swap(A[i], A[j]);
            }

        // Lajitellaan etäisyyden mukaan
        } else {
            unsigned int Adist = distance(A[j] -> x, from_.x, A[j] -> y, from_.y);
            if (Adist <= pdist) {
                ++i;
                swap(A[i], A[j]);
            }
        }
    }
    swap(A[i + 1], A[right]);
    return i + 1;
}


// Kahden alkion paikan vaihtaminen
void Datastructures::swap(TownData*& left, TownData*& right)
{
    TownData* temp = left;
    left = right;
    right = temp;
}

// Etäisyyden mittaus kahden kordinaatin välillä tehtäväannon mukaan
unsigned int Datastructures::distance(int x1, int x2, int y1, int y2)
{
    return abs(x1 - x2) + abs(y1 - y2);
}

// Puolitushaku
TownData* Datastructures::binarySearch(std::vector<TownData*>& A, unsigned int n, std::string const& key)
{
    unsigned int mid = 0;
    unsigned int left = 0;
    unsigned int right = n - 1;

    while (left <= right) {
        mid = (right + left) / 2;
        if (A[mid] -> name == key) return A[mid]; // Kaupunki löytyi
        else if (A[mid] -> name > key) right = mid - 1;
        else left = mid + 1;
    }
    // Kaupunkia ei löytynyt
    return nullptr;
}
