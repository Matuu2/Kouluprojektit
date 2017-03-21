#include <iostream>
#include <pankkitili.hh>
#include <string>
#include <iomanip>

using namespace std;
double kysy_rahamaaraa();
pankkitili& haluttu_tili(char tilin_numero, pankkitili& tili1, pankkitili& tili2,pankkitili& tili3);

//Harjoitustyö 1
//Matias Ala-Sunila

int main()
{
  //Määritellään alkuarvot ja luodaan kolme pankkitilioliot.Arvoa Nolla tarvitaan
  //komennon tutkimiseen
  string komento = "alkaa";
  pankkitili tili1;
  pankkitili tili2;
  pankkitili tili3;
  string::size_type nolla = 0;
  char tilin_numero = '0';

  // while-silmukassa tutkitaan, että onko annettu komento jokin tarkaan määrätyistä operaatioiden kutsuista
  // esim. tilin numero täytyy olla 1,2 tai 3, koska käytössä on vain kolme tiliä
  while (komento != "loppu"){
    cout << "pankkitilitesti> ";
    getline(cin,komento);

    //komento aseta kysyy käyttäjältä tilin tiedot ja asettaa ne halutun tilin tiedoiksi
    if (komento.length() == 7 and komento.substr(nolla,5) == "aseta"){
        tilin_numero = komento.at(6);

        if (tilin_numero == '1' or tilin_numero == '2' or tilin_numero == '3'){
            string tilinumero = "FI";
            cout << "Syötä tilinumero: ";
            getline(cin,tilinumero);
            double saldo = 0;
            string luku;
            cout << "Syötä saldo: ";
            getline(cin,luku);
            saldo = stod(luku);

            if (saldo < 0){
                cout << "Virhe: saldo ei voi olla negatiivinen" <<endl;
                }
            else {
                int asiakasnumero = 0;
                cout << "Syötä asiakasnumero: ";
                getline(cin,luku);
                asiakasnumero = stod(luku);
                (haluttu_tili(tilin_numero,tili1,tili2,tili3)).aseta(tilinumero,saldo,asiakasnumero);
                }
            }
        else{
            cout << "Virhe: Tilin numeron on oltava 1, 2 tai 3" << endl;
            }
        }

    //komento tulostaa halutun tilin tiedot
    else if (komento.length() == 9  and komento.substr(nolla,7) == "tulosta"){
        tilin_numero = komento.at(8);
        if (tilin_numero == '1' or tilin_numero == '2' or tilin_numero == '3'){
            pankkitili tulostettava_tili = haluttu_tili(tilin_numero,tili1,tili2,tili3);
            tulostettava_tili.tulosta();
            }
        else{
            cout << "Virhe: Tilin numeron on oltava 1, 2 tai 3" << endl;
            }
        }

    //pano lisää halutulle tilille rahaa samalla tehden virhetarkastuksen
    else if (komento.length() == 6  and komento.substr(nolla,4) == "pano"){
        tilin_numero = komento.at(5);

        if (tilin_numero == '1' or tilin_numero == '2' or tilin_numero == '3'){
            double rahamaara = kysy_rahamaaraa();

            if (rahamaara != -1){
                (haluttu_tili(tilin_numero,tili1,tili2,tili3)).pano(rahamaara);
                cout << "Pano suoritettu tilille " << tilin_numero << endl;
                }
            }

        else{
            cout << "Virhe: Tilin numeron on oltava 1, 2 tai 3" << endl;
            }
        }

    //ottaa halutulta tililtä rahaa. Hieman monimutkaisempi kuin pano, sillä pitää tarkistaa,
    //että tilillä on tarpeeksi rahaa
    else if(komento.length() == 6  and komento.substr(nolla,4) == "otto"){
        tilin_numero = komento.at(5);

        if (tilin_numero == '1' or tilin_numero == '2' or tilin_numero == '3'){
            double rahamaara = kysy_rahamaaraa();

            if (not(haluttu_tili(tilin_numero,tili1,tili2,tili3)).otto(rahamaara) and rahamaara != -1){
                cout << "Virhe: Tilillä ei ollut tarpeeksi rahaa" << endl;
               }
            else if (rahamaara != -1){
                    cout << "Otto suoritettu tililtä " << tilin_numero << "." << endl;
            }
        }
        else{
            cout << "Virhe: Tilin numeron on oltava 1, 2 tai 3" << endl;
            }
    }

    //siirtää rahaa tililtä toiselle jälleen tarkistaen,
    //että otettavalla tilillä on tarpeeksi rahaa
    else if (komento.length() == 14  and komento.substr(nolla,10) == "tilisiirto"){
        tilin_numero = komento.at(11);
        char saaja = '0';
        saaja = komento.at(13);

        if (tilin_numero == '1' or tilin_numero == '2' or tilin_numero == '3'){

            if (saaja == '1'){
                double rahamaara = kysy_rahamaaraa();
                if (not haluttu_tili(tilin_numero,tili1,tili2,tili3).tilisiirto(rahamaara,tili1)){
                    cout << "Virhe: tilisiirto epäonnistui." <<endl;
                    }
                }
            else if (saaja == '2'){
                double rahamaara = kysy_rahamaaraa();
                if (not haluttu_tili(tilin_numero,tili1,tili2,tili3).tilisiirto(rahamaara,tili2)){
                    cout << "Virhe: tilisiirto epäonnistui." <<endl;
                    }
              }
            else if (saaja == '3'){
               double rahamaara = kysy_rahamaaraa();
               if (not haluttu_tili(tilin_numero,tili1,tili2,tili3).tilisiirto(rahamaara,tili3)){
                    cout << "Virhe: tilisiirto epäonnistui." <<endl;
                  }
              }
            else{
                cout << "Virhe: Tilin numeron on oltava 1, 2 tai 3" << endl;
                }
        }
        else{
            cout << "Virhe: Tilin numeron on oltava 1, 2 tai 3" << endl;
            }

        }
  }

}
//palauttaa syötetyn tilin numeron perusteella oikean tiliolion
pankkitili& haluttu_tili(char tilin_numero, pankkitili& tili1, pankkitili& tili2,pankkitili& tili3){

    if (tilin_numero == '1'){
        return tili1;
        }
    else if (tilin_numero == '2'){
        return tili2;
        }
    else {
        return tili3;
        }

}
//Kysyy rahamäärää ja tekee samalla siihen virhetarkastelun. Palautettu arvo -1 kertoo pääohjelmalle, että syötetty rahamaara ei kelvannut
double kysy_rahamaaraa(){
    double rahamaara = 0;
    cout << "Syötä rahamäärä: ";
    string raha;
    getline (cin,raha);
    rahamaara = stod(raha);

    if (rahamaara < 0){
        cout << "Virhe: rahamäärä ei voi olla negatiivinen" <<endl;
        return -1;
    }
    else {return rahamaara;}
}
