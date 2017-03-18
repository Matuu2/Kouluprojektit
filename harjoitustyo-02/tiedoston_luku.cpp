#include "tiedoston_luku.hh"

bool lue_tiedosto(string tiedoston_nimi,map <string,map<string,set<Tuote>>>& kauppaketjut){

    //Kokeillaan ensin, että onnistuuko tiedoston lukeminen.
    ifstream tiedosto_olio(tiedoston_nimi);
        if ( not tiedosto_olio ) {
            cout << "Virhe: syötetiedostoa ei saatu luettua." << endl;
            return false;
            }

        else {
            //Luodaan paloittelija ja lisätään siihen joka kierros luettu rivi.
            Splitter paloittelija;
            string rivi;
            while ( getline(tiedosto_olio, rivi) ) {
                paloittelija.aseta_paloiteltavava_merkkijono(rivi);

                //testaa_kentta funktio varmistaa, että luettava rivi on oikeaa muotoa. Tiedoston rivit on erikseen nimetty
                //helpottamaan mahdollisesti koodin lukua. Lisäksi luodaan lopulliseen tietorakenteeseen(kauppaketjut)
                //lisättävät tietorakenteet(myymalat_tuotteineen,tuote_valikoima ja Tuote)

                if (testaa_kentta(paloittelija)){
                    string kauppaketju = paloittelija.hae_kentta(0);
                    string myymala = paloittelija.hae_kentta(1);
                    string tuotteen_nimi = paloittelija.hae_kentta(2);
                    map<string,set<Tuote>> myymalat_tuotteineen;
                    set<Tuote> tuote_valikoima;
                    Tuote tavara;

                    //Olen käyttänyt tuotteen hintana lukua 0, mikäli tuote on loppunut.
                    if (paloittelija.hae_kentta(3) == "loppu"){
                        tavara.hinta = 0;
                    }
                    //Testataan ennen muuttamista, että onko string mahdollista muuttaa double-muuttujaksi
                    else {
                        if (testaa_hinta(paloittelija.hae_kentta(3))){
                            tavara.hinta = stod(paloittelija.hae_kentta(3));
                        }
                        else{
                            cout << "Virhe: syötetiedostoa ei saatu luettua." <<endl;
                            return false;
                        }
                    }
                    //Lisätään tavarat strucktiin tuotteen_nimi.
                    //Tämän jälkeen tavara lisätään tuote_valikoimaan, joka lisätään myymalat_tuotteineen mappiin
                    tavara.tuotteen_nimi = tuotteen_nimi;
                    tuote_valikoima.insert(tavara);
                    myymalat_tuotteineen.insert({myymala,tuote_valikoima});

                    //Tutkitaan, että onko kauppaketju jo rakenteessa.
                    if (kauppaketjut.find(kauppaketju) == kauppaketjut.end()){
                        kauppaketjut.insert({kauppaketju,myymalat_tuotteineen});
                    }
                    else{
                        //Tutkitaan, että onko myymala jo rakenteessa
                        if ((kauppaketjut.at(kauppaketju)).find(myymala) == (kauppaketjut.at(kauppaketju)).end()){
                            (kauppaketjut.at(kauppaketju)).insert({myymala,tuote_valikoima});
                        }
                        //Nyt kun on jo tutkittu, että kauppaketju ja myymälä ovat rakenteessa niin tutkitaan,että
                        //löytyykö tuote jo valmiiksi myymälästä ja mikäli löytyi korvataan se uudella tuotteella,
                        //jolla on mahdollisesti uusi hinta.
                        bool loytyiko = false;
                        set<Tuote>::const_iterator iter;
                        iter = (kauppaketjut.at(kauppaketju).at(myymala)).begin();
                        while ( iter != (kauppaketjut.at(kauppaketju).at(myymala)).end() ) {
                            if (iter->tuotteen_nimi == tuotteen_nimi){
                                (kauppaketjut.at(kauppaketju).at(myymala)).erase(iter);
                                (kauppaketjut.at(kauppaketju).at(myymala)).insert(tavara);
                                loytyiko = true;
                            }
                            ++iter;

                        if ( not loytyiko){
                            ((kauppaketjut.at(kauppaketju)).at(myymala)).insert(tavara);
                            }
                        }

                    }
                }
                else {
                    cout << "Virhe: syötetiedostoa ei saatu luettua." <<endl;
                    return false;

                    }

                }
        //lopuksi suljetaan tiedosto ja kerrotaan pää-ohjelmalle, että luku onnistui
        tiedosto_olio.close();
        return true;
    }
}
