#include "tiedostonluku.hh"
#include "tuotantoketju.hh"
#include <fstream>
#include <string>
#include <regex>
#include <iostream>

using namespace std;

//Toteutettu tiedostonluku rekursiivisesti
bool lue_tiedosto(ifstream& virta, Tuotantoketju& reseptit){
    string rivi;

    if ( getline(virta,rivi) ){        
        regex tyhjakentta ("[/n[:space:]]*");
        // Kommenttikenttä on muotoa <spc><#><kommentti> kommentti ja space
        // voivat kyllä puuttuakin
        regex kommenttikentta("^[[:space:]]*[#]");
        smatch tulos;
        regex reseptirivi(
            "[[:space:]]*"   // 0-n kpl sanaväimerkkejä (space, tab)
            "([[:alpha:]_]+)"// kenttä: yksi tai useampi aakkosta tai alaviivaa
            "[[:space:]]*"
            "[:]"
            "[[:space:]]*"
            "([[:alpha:]_]+)"
            "[[:space:]]*"
        );
        // Mikäli kenttä on tyhjä niin luetaan uusi rivi eli
        // kutsutaan lue_tiedostoa uusiksi
        if (rivi.empty() or regex_match (rivi,tyhjakentta) ){
            return lue_tiedosto(virta,reseptit);

        // Kommettikentän kohdalla toimitaan samoin
        }else if ( regex_search(rivi, kommenttikentta ) ){
            return lue_tiedosto(virta,reseptit);

        // Reseptirivin kohdalla varmistetaan,
        // että lisääminen rakenteeseen onnistui
        }else if ( regex_match( rivi,tulos,reseptirivi ) ){
            if ( not reseptit.lisaa(tulos.str(1),tulos.str(2))){
                return false;
            }
            return lue_tiedosto(virta,reseptit);

        // Jos rivi ei täsmännyt mihinkään aiempaan se tulkitaan
        // virheelliseksi ja palautetaan false
        }else{
            return false;
        }

    }else{
        return true;
    }
}

