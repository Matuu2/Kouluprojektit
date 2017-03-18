#ifndef TIEDOSTON_LUKU_HH
#define TIEDOSTON_LUKU_HH
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <fstream>
#include <cctype>
#include "splitter.hh"
#include "apufunktiot.hh"


using namespace std;

// Ottaa parametrinään tietorakenteen ja lukee tiedoston tallentaen rivit tietorakeenteeseen
bool lue_tiedosto(string tiedoston_nimi,map <string,map<string,set<Tuote>>>& kauppaketjut);

#endif // TIEDOSTON_LUKU_HH
