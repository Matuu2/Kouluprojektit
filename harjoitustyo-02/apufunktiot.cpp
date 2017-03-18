#include "apufunktiot.hh"

//Ottaa parametrinään splitterin, jossa on sisällä sen hetkinen tiedoston rivi
bool testaa_kentta(Splitter& paloittelija){
    //rivejä pitää olla tasan neljä
    if (paloittelija.paloittele(';') != 4)
        return false;

    //Tarkistaa ettei kenttä ole tyhjä ja ettei se sisällä yhtää välilyöntejä
    for (int luku = 0;luku <= 3;++luku){
        if (paloittelija.hae_kentta(luku).empty()){
            return false;
        if ((paloittelija.hae_kentta(luku)).find(" ") != string::npos){
            return false;
            }
        }
    }
    return true;
}
//Tutkitaan,että muistuttaako testattava numeroa käymällä merkki merkiltä läpi. Mikäli merkki on piste tallenetaan ylös tieto, että
//piste on löytynyt, jotta jatkossa jos löytyy toinen piste niin tiedetään ettei testattavaa voi muuttaa luvuksi.
//isdigit() tarkistaa, että onko merkki numero(0,1...,9)
bool testaa_hinta(string testattava){
    bool piste_loytyi = false;
    for (string::size_type luku= 0;luku < testattava.size();++luku){
        if (testattava.at(luku) == '.'){
            if(piste_loytyi){
                return false;
            }
            else{
                piste_loytyi = true;
            }
        }
        else if(not isdigit(testattava.at(luku))){
            return false;
        }

    }
    return true;
}
