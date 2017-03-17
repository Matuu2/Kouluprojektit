#ifndef TIEDOSTONLUKU_HH
#define TIEDOSTONLUKU_HH
#include "tuotantoketju.hh"
#include <fstream>

using namespace std;

bool lue_tiedosto(ifstream& virta, Tuotantoketju& reseptit);

#endif // TIEDOSTONLUKU_HH
