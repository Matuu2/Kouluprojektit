//Ohjelmoinnin peruskurssi  Harjoitustyö 2
//Matias Ala-Sunila 246417
//matias.ala-sunila@student.tut.fi
//Alkuhuomio: Koodissa on käytetty tekstitiedoston riveistä seuraavia termejä:
//ensimmäinen rivi on kauppaketju(Prisma,...) toinen rivi on myymälä(Lielahti,...)

#include <iostream>
#include "splitter.hh"
#include "tiedoston_luku.hh"
#include "apufunktiot.hh"
#include "hakufunktiot.hh"
#include <string>
#include <map>
#include <set>

using namespace std;

int main(){

    //Luodaan tarvittava tietorakenne tietojen tallentamiseksi
    //Valitsin mapin, josta kauppaketjun avulla löytyy uusi mappi.
    //Uudesta mapista löytyy myymälän nimen avulla set, jonka alkioina on tuote structeja.
    map <string,map<string,set<Tuote>>> kauppaketjut;
    string komento;
    Splitter paloittelija;

    //Ensin tarkistetaan, että onnistuiko tiedoston luku, jonka jälkeen mennään while-silmukan sisään
    if ( lue_tiedosto("tuotetiedot.txt",kauppaketjut) ){
        //While-silmukka loppuu, silloin käyttäjä syöttää "lopeta".
        //Käyttäjän antama syöte paloitellaan ja tutkitaan kenttien määrän mukaan, että
        //mikä kometo oli kyseessä
        while (true){
            cout << "tuotehaku> ";
            getline(cin,komento);
            paloittelija.aseta_paloiteltavava_merkkijono(komento);
            int kenttia = paloittelija.paloittele(' ');

            if (komento == "lopeta"){
                return false;
                }

            //Yhden kentän mittaisia komentoja on vain kaksi: "kauppaketjut" ja "tuotenimet"
            if (kenttia == 1){
                if(paloittelija.hae_kentta(0) == "kauppaketjut"){
                    tulosta_kauppaketjut(kauppaketjut);
                }
                else if(paloittelija.hae_kentta(0) == "tuotenimet"){
                    tulosta_tuotenimet(kauppaketjut);
                }
                else {
                    cout << "Virhe: Tuntematon komento" <<endl;
                }
            }
            //Kahden kentän mittaisia komentoja on myös kaksi: "myymalat" ja "halvin"
            //Komentoon "myymalat" liittyy virhetarkastelu, että myymälän on löytyttävä mapista
            else if (kenttia == 2){
                if (paloittelija.hae_kentta(0) == "myymalat"){
                    if (kauppaketjut.find(paloittelija.hae_kentta(1)) != kauppaketjut.end()){
                        tulosta_myymalat(kauppaketjut,paloittelija.hae_kentta(1));
                    }
                    else{
                        cout << "Virhe: Myymälää ei löytynyt" <<endl;
                    }
                }
                else if (paloittelija.hae_kentta(0) == "halvin"){
                    tulosta_halvin(kauppaketjut,paloittelija.hae_kentta(1));
                }
                else {
                    cout << "Virhe: Tuntematon komento" <<endl;
                }
            }
            //Kolmen kentän mittaisia komentoja on vain "tuotevalikoima".
            //Virhetarkastelussa täytyy tarkistaa, että annettu kauppaketju ja myymälä
            //löytyvät tietorakenteesta.
            else if (kenttia == 3){
                string kauppa = paloittelija.hae_kentta(1);
                string paikka = paloittelija.hae_kentta(2);
                if (paloittelija.hae_kentta(0) == "tuotevalikoima"){
                    if((kauppaketjut.find(kauppa) != kauppaketjut.end())){
                        if((kauppaketjut.at(kauppa)).find(paikka) != kauppaketjut.at(kauppa).end()){
                            tulosta_valikoima(kauppaketjut,kauppa,paikka);

                        }
                        else{
                            cout << "Virhe: Myymälää ei löytynyt" <<endl;
                        }
                    }
                    else{
                        cout << "Virhe: Kauppaketjua ei löytynyt" <<endl;

                    }
                }
                else {
                    cout << "Virhe: Tuntematon komento" <<endl;
                }

            }
            //Tämä tulostuu mikäli kenttiä oli väärä lukumäärä
            else {
                cout << "Virhe: Tuntematon komento" <<endl;
            }
            }
    }

}
