#ifndef APUFUNKTIOT_HH
#define APUFUNKTIOT_HH
#include <iostream>
#include <string>
#include "splitter.hh"

using namespace std;

//apufunktioissa on määritelty struct-rakenne, testaa_kentta ja testaa_hinta
struct Tuote {
    string tuotteen_nimi;
    double hinta;
    };
    //set-rakenteen vaatima vertailufunktio toteutettiin inline bool operatorin avulla
    //jonka löysin pienen googlailun jälkeen netistä
    inline bool operator<(const Tuote& eka, const Tuote& toka){
    return eka.tuotteen_nimi < toka.tuotteen_nimi;
    }

//Funktiota käytetään tiedoston luvussa tarkistamaan rivin oikea muoto
bool testaa_kentta(Splitter& paloittelija);

//Funktiota käytetään tarkistamaan,että onko hinta mahdollista muuttaa double-muuttujaksi
bool testaa_hinta(string testattava);

#endif // APUFUNKTIOT_HH
