#include "hakufunktiot.hh"
//Huom! kaikissa tulostuksissa ei ole tarvinnut huolehtia erikseen aakkosjärjestyksestä
//sillä set/map tekee sen automaattisesti

//Tulostaa iteraattorien avulla kauppaketjujen nimet
void tulosta_kauppaketjut(const map <string,map<string,set<Tuote>>>& kauppaketjut){
    map <string,map<string,set<Tuote>>>::const_iterator iter;
    iter = kauppaketjut.begin();
    while ( iter != kauppaketjut.end() ) {
        cout << iter->first <<endl;
        ++iter;
    }
}

//Tulostaa myymälöiden nimet. Nyt käydään iteraattorien avulla sisempää mappia läpi
void tulosta_myymalat(const map <string,map<string,set<Tuote>>>& kauppaketjut,string kauppaketju){
    map<string,set<Tuote>>::const_iterator iter;
    iter = (kauppaketjut.at(kauppaketju)).begin();
    while ( iter != (kauppaketjut.at(kauppaketju)).end() ) {
        cout << iter->first <<endl;
        ++iter;
    }
}

//Tulostaa tuotevalikoiman käyden läpi sisintä set-rakennetta
void tulosta_valikoima(const map <string,map<string,set<Tuote>>>& kauppaketjut,string kauppaketju,string myymala){
    set<Tuote>::const_iterator iter;
    iter = (kauppaketjut.at(kauppaketju).at(myymala)).begin();

    //Mikäli tuotteen hinta on 0 niin tulostetaan sana "loppu", muulloin tulostetaan
    //tuotteen hinta kahden desimaalin tarkkuudella.
    while ( iter != (kauppaketjut.at(kauppaketju).at(myymala)).end() ) {
        if (iter->hinta == 0){
            cout << iter->tuotteen_nimi << " loppu" <<endl;
        }
        else{
            cout << fixed;
            cout << iter->tuotteen_nimi << " " << setprecision(2) <<iter->hinta << endl;
        }
        ++iter;
    }
}

//Etsii halutun tuotteen halvinta hintaa. Alussa luodaan set niille tuotteille, joita löytyy kaupasta. Luodaan samalla myös bool-muuttuja, joka
//kertoo, että onko tuote löydetty, mutta se on loppu.

void tulosta_halvin(const map <string,map<string,set<Tuote>>>& kauppaketjut,string tuote){
    set<string> kaupat_joissa_tuotetta_on;
    bool tuotetta_loytyy_mutta_on_loppunut = false;
    double halvin_hinta;
    map <string,map<string,set<Tuote>>>::const_iterator kauppaketjuiter;
    kauppaketjuiter = kauppaketjut.begin();

    //Jokainen kauppaketju käydään läpi tässä while-silmukassa
    while ( kauppaketjuiter != kauppaketjut.end() ) {
        string kauppaketjun_nimi = kauppaketjuiter->first;
        map<string,set<Tuote>>::const_iterator myymalaiter;
        myymalaiter = (kauppaketjut.at(kauppaketjun_nimi)).begin();

        //Jokaisen kauppaketjun myymälä käydään läpi tässä while-silmukassa
        while ( myymalaiter != (kauppaketjut.at(kauppaketjun_nimi)).end() ) {
            set<Tuote>::const_iterator tuoteiter;
            tuoteiter = (kauppaketjut.at(kauppaketjun_nimi).at(myymalaiter->first)).begin();

            //Jokaisen myymälän tuotevalikoima käydään läpi tässä while-silmukassa. Tarkistetaan että löytyykö kyseistä
            //tuotetta, jos tuote löytyi ekaa kertaa sen hinta on halvin hinta ja sitä verrataan jatkossa mahdollisesti
            //löytyvien tuotteiden hintoihin. Mikäli jatkossa löytyy halvempi tuote niin set tyhjennetään ennen uuden
            //tuotteen lisäämistä. Jokaisella kerralla, kun tuotetta löytyy myymälästä niin se lisätään
            //kaupat_joissa_tuotetta_on settiin muodossa: kauppaketjun_nimi_myymälän_nimi (esim. Prisma Lielahti).
            //Tämä helpottaa huomattavasti tulosten tulostamista aakkosjärjestyksessä.
            while ( tuoteiter != (kauppaketjut.at(kauppaketjun_nimi).at(myymalaiter->first)).end() ) {
                if(tuoteiter->tuotteen_nimi == tuote){
                    if(kaupat_joissa_tuotetta_on.empty() and tuoteiter->hinta != 0){
                        halvin_hinta = tuoteiter->hinta;
                        kaupat_joissa_tuotetta_on.insert(kauppaketjun_nimi + " " + myymalaiter->first);
                    }
                    else{
                        if(tuoteiter->hinta == 0){
                            tuotetta_loytyy_mutta_on_loppunut = true;
                        }
                        else if(tuoteiter->hinta == halvin_hinta){
                            kaupat_joissa_tuotetta_on.insert(kauppaketjun_nimi + " " + myymalaiter->first);
                        }
                        else if(tuoteiter->hinta < halvin_hinta){
                            halvin_hinta = tuoteiter->hinta;
                            kaupat_joissa_tuotetta_on.clear();
                            kaupat_joissa_tuotetta_on.insert(kauppaketjun_nimi + " " + myymalaiter->first);

                        }

                    }
                }
                ++tuoteiter;
            }
            ++myymalaiter;
        }
        ++kauppaketjuiter;
    }

    //Tulostetaan tulokset mikäli niitä löytyi. Muulloin tarkistetaan,että löytyikö tuote, mutta se on loppu
    set<string>::iterator iter;
    if (not kaupat_joissa_tuotetta_on.empty()){
        cout << fixed;
        cout << setprecision(2) << halvin_hinta << " euroa" << endl;
        iter = kaupat_joissa_tuotetta_on.begin();
        while (iter != kaupat_joissa_tuotetta_on.end()){
            cout << *iter <<endl;
            ++iter;
        }
    }
    else if (tuotetta_loytyy_mutta_on_loppunut){
        cout << "Tuote on tilapäisesti loppu kaikkialta." <<endl;
    }
    else{
        cout << "Tuote ei kuulu valikoimiin." <<endl;
        }
}


//Käy läpi kaikkien kauppaketjujen tuotteiden nimet ja lisää ne tuotteet-settiin
void tulosta_tuotenimet(const map <string,map<string,set<Tuote>>>& kauppaketjut){
    set<string> tuotteet;
    map <string,map<string,set<Tuote>>>::const_iterator kauppaketjuiter;
    kauppaketjuiter = kauppaketjut.begin();

    //Jokainen kauppaketju käydään läpi tässä while-silmukassa
    while ( kauppaketjuiter != kauppaketjut.end() ) {
        string kaupan_nimi = kauppaketjuiter->first;
        map<string,set<Tuote>>::const_iterator myymalaiter;
        myymalaiter = (kauppaketjut.at(kaupan_nimi)).begin();

        //Jokaisen kauppaketjun myymälä käydään läpi tässä while-silmukassa
        while ( myymalaiter != (kauppaketjut.at(kaupan_nimi)).end() ) {
            set<Tuote>::const_iterator tuoteiter;
            tuoteiter = (kauppaketjut.at(kaupan_nimi).at(myymalaiter->first)).begin();

            //Jokaisen myymälän tuotevalikoima käydään läpi tässä while-silmukassa ja
            //jokainen tuote lisätään settiin. Set-rakenne varmistaa, että vaikka sama
            //tuote lisätään settiin niin se on siellä vain kerran
            while ( tuoteiter != (kauppaketjut.at(kaupan_nimi).at(myymalaiter->first)).end() ) {
                tuotteet.insert(tuoteiter->tuotteen_nimi);
                ++tuoteiter;
            }
            ++myymalaiter;
        }
        ++kauppaketjuiter;
    }
    //Tulostetaan tuotteet-settiin tallennetut tuotteiden nimet
    set<string>::iterator iter;
    iter = tuotteet.begin();
    //Koska set on valmiiksi aakkosjärjestyksessä niin riittää, että tulostaa setin alusta
    //loppuun
    while (iter != tuotteet.end()){
        cout << *iter <<endl;
        ++iter;
    }

}
