#include "apufunktiot.hh"
#include "kayttoliittyma.hh"
#include "reppu.hh"
#include "tuotantoketju.hh"
#include <string>
#include <iostream>
#include <regex>

using namespace std;
bool lisaa_reppuun(const Tuotantoketju& reseptit, const string& syoterivi,
                   Reppu &reppu);


void kayttoliittyma(Tuotantoketju& reseptit){
    cout << "Tuotantoketjut luettu onnistuneesti." << endl;

    Reppu reppu;
    regex koko_rivi_regex(
        "[[:space:]]*"      // 0-n kpl sanaväimerkkejä (space, tab)
        "([[:alpha:]_]+)"  // kenttä: yksi tai useampi aakkosta tai alaviivaa
        "[[:space:]]*"
        "("
        "[[:space:]]*"
        "[[:alpha:]_]+"
        "[[:space:]]*"
        ")*"
    );
    regex kaksi_sanaa_regex(
         "[[:space:]]*"
         "([[:alpha:]_]+)"
         "[[:space:]]*"
         "([[:alpha:]_]+)"
         "[[:space:]]*"
    );
    regex yksi_sana_regex(
         "[[:space:]]*"
         "([[:alpha:]_]+)"
         "[[:space:]]*"
    );


    smatch tulos;
    smatch tulos2;
    smatch tulos3;

    string syoterivi;
    cout << "testikayttoliittyma> ";
    while ( getline(cin, syoterivi) ) {


        // Tutkitaan, että rivi on muodoltaan halutun kaltainen.
        if ( regex_match(syoterivi,tulos,koko_rivi_regex) ) {

            // Tutkitaan, että onko rivissä vain yksi sana
            if ( regex_match(syoterivi,tulos3,yksi_sana_regex) ){


                if ( tulos3.str(1) == "loppu" ){
                    break;

                }else if ( tulos3.str(1) == "reppu" ){
                    reppu.tyhjenna();
                    cout << "Reppu tyhjennetty." <<endl;

                }else if ( tulos3.str(1) == "tulostareppu" ){
                    reppu.tulosta();

                }else{
                    virheilmoitus("Virheellinen syote");
                }

            }else if ( tulos.str(1) == "reppu"){
                if ( lisaa_reppuun(reseptit,syoterivi,reppu) ){
                    cout << "Repun sisalto asetettu." << endl;
                }

            // Tutkitaan, että onko rivissä täsmälleen kaksi sanaa.
            // Tutkitaan sen jälkeen, että löytyykö sieltä tunnettu käsky
            // ja sen perässä tavara, joka esiintyi syötetiedostossa
            }else if ( regex_match(syoterivi,tulos2,kaksi_sanaa_regex) ){

                if( tulos2.str(1) == "materiaalit" &&
                            reseptit.onko_ketjussa(tulos2.str(2))){
                    reseptit.tulosta_materiaalit(tulos2.str(2));

                }else if ( tulos2.str(1) == "askarreltavissa" &&
                            reseptit.onko_ketjussa(tulos2.str(2))){                    
                   if ( reseptit.askarteltavissa(tulos2.str(2),reppu)
                           && not reppu.onko_tyhja() ){
                       cout << "On askarreltavissa." <<endl;
                   }else{
                       cout << "Ei ole askarreltavissa." <<endl;
                   }

                }else if ( tulos2.str(1) == "askarreltavissa_bonus" &&
                            reseptit.onko_ketjussa(tulos2.str(2))){
                   if ( reseptit.askarreltavissa_bonus(tulos2.str(2),reppu)
                           && not reppu.onko_tyhja() ){
                       cout << "On askarreltavissa." <<endl;
                   }else{
                       cout << "Ei ole askarreltavissa." <<endl;
                   }
                }else{
                    virheilmoitus("Virheellinen syote");
                }

            }else{
                virheilmoitus("Virheellinen syote");
            }


        } else {
            virheilmoitus("Virheellinen syote");
        }
        cout << "testikayttoliittyma> ";
    }
}

// Toteutettu erikseeen funktio reppuun lisäämistä varten. Funktio ottaa
// parametrinaan tuotantoketjun, annetun syötteen ja itse Reppu-rakenteen
bool lisaa_reppuun(const Tuotantoketju& reseptit, const string& syoterivi,
                   Reppu& reppu){

    // Käydään iteraattorin avulla kaikki kentät läpi ja lisätään jokainen
    //ei-reppu sana erikseen reppuun mikäli se on mahdollista.
    //Muulloin reppu tyhjennetään ja tulostetaan virheilmoitus
    regex kentta_regex("[[:alpha:]_]+");
    sregex_iterator iter(syoterivi.begin(), syoterivi.end(),
                         kentta_regex);
    sregex_iterator end;

    while ( iter != end ) {
        if ( iter->str() != "reppu" ){
            if ( not reseptit.onko_ketjussa(iter->str())
                            or not reppu.lisaa(iter->str())){
                virheilmoitus("lisääminen reppuuun ei onnistunut");
                reppu.tyhjenna();
                return false;
            }
        }
        ++iter;
    }
    return true;
}

