//------------------------------------------------
// TIE-02200 Ohjelmoinnin peruskurssi
// Harjoitustyö 5
// Matias Ala-Sunila
//------------------------------------------------
#include "apufunktiot.hh"
#include "kayttoliittyma.hh"
#include "tiedostonluku.hh"
#include "tuotantoketju.hh"
#include <iostream>
#include <string>

using namespace std;

// Totesin harjoitustyössä 3 annetun main-funktion erittäin toimivaksi, joten
// päätin käyttää tässä työssä samaa ratkaisua

int main() {
    Tuotantoketju reseptit;

    string tiedoston_nimi;
    cout << "Syotetiedosto: ";
    getline(cin, tiedoston_nimi);

    ifstream virta(tiedoston_nimi);
    if ( not virta ) {
        virheilmoitus("syötetiedostoa " + tiedoston_nimi + " ei voida lukea.");

        // main:in on palautettava nollasta eroava arvo, mikäli
        // ohjelman suoritus päättyi virhetilanteeseen.
        return 1;

    } else if ( not lue_tiedosto(virta, reseptit) ) {
        virheilmoitus("syötetiedosto " + tiedoston_nimi + " virheellinen.");

        return 1;

    } else {

        virta.close();

        kayttoliittyma(reseptit);
    }
}


