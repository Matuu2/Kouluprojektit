#include "reppu.hh"
#include "apufunktiot.hh"
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

const int ALKUKOKO = 8;

Reppu::Reppu():
    taulukko_(new string[ALKUKOKO]),
    kokonaistila_(ALKUKOKO),
    kaytetty_tila_(0){
}

Reppu::~Reppu(){
    delete [] taulukko_;
}

bool Reppu::onko_tyhja() const{
    return koko() == 0;
}

int Reppu::koko() const{
    return kaytetty_tila_;
}
// Tyhjennä komento vapauttaa vanhan taulukon ja
// tekee uuden taulukon alkuperäisillä arvoilla
void Reppu::tyhjenna(){
    delete [] taulukko_;
    taulukko_ = new string[ALKUKOKO];
    kokonaistila_ = ALKUKOKO;
    kaytetty_tila_ = 0;
}

bool Reppu::lisaa(string syote){


    string* osoitin;
    osoitin = find(taulukko_,taulukko_+kaytetty_tila_,syote);

    //Varmistetaan ensin ettei arvoa löydy jo taulukosta
    if ( osoitin != taulukko_+kaytetty_tila_) {
        return false;
    }

    //Mikäli tila on loppumassa niin varataan uusi taulukko,joka
    //on kaksi kertaa vanhan ja kopioidaan vanhan taulukon arvot siihen
    if ( koko() == kokonaistila_ ) {
        string* uusi_taulukko = new string[2 * kokonaistila_];

        for ( int i = 0; i < koko(); ++i ) {
            uusi_taulukko[i] = taulukko_[i];
        }

        delete [] taulukko_;

        taulukko_ = uusi_taulukko;
        kokonaistila_ = 2 * kokonaistila_;


    }

    // Tässä kohdassa dynaamisessa taulukossa on tilaa.  Joko sitä
    // oli alunperin tai taulukon kokoa on kasvatattu edellisessä
    // if-rakenteessa.

    taulukko_[kaytetty_tila_] = syote;
    ++kaytetty_tila_;
    return true;


}
// Tutkitaan for-silmukan avulla, että löytyykö parametri etsittava taulukosta
bool Reppu::onko_repussa(const string& etsittava) const{

    for ( int i = 0; i < koko(); ++i ){
        if ( taulukko_[i] == etsittava){
           return true;
        }
    }
    return false;
}
//Tulostetaan listan alkiot siinä järjestyksessä, kun ne on lisätty taulukkoon
void Reppu::tulosta() const{

    for ( int i = 0; i < koko(); ++i ){
        cout << taulukko_[i] <<endl;
    }

}
