#ifndef HAKUFUNKTIOT_HH
#define HAKUFUNKTIOT_HH
#include <iostream>
#include "apufunktiot.hh"
#include <string>
#include <map>
#include <set>
#include <iomanip>

using namespace std;

//Jokainen hakufunktio ottaa parametrinään tietorakenteen ja tarvittaessa muita
//parametrejä
//Tulostaa kauppaketjujen nimet
void tulosta_kauppaketjut(const map <string,map<string,set<Tuote>>>& kauppaketjut);

//Tulostaa käyttäjän antaman kauppaketjun myymälät
void tulosta_myymalat(const map <string,map<string,set<Tuote>>>& kauppaketjut,string kauppaketju);

//Ottaa parametrinään kauppaketjun ja myymälän nimen ja tulostaa sen myymälän tuotteet
void tulosta_valikoima(const map <string,map<string,set<Tuote>>>& kauppaketjut,string kauppaketju,string myymala);

//Ottaa parametrinään tuotteen nimen ja etsii mistä tuote löytyy halvimmalla
void tulosta_halvin(const map <string,map<string,set<Tuote>>>& kauppaketjut,string tuote);

//Tulostaa kaikkien kauppojen tuotteet
void tulosta_tuotenimet(const map <string,map<string,set<Tuote>>>& kauppaketjut);

#endif // HAKUFUNKTIOT_HH
