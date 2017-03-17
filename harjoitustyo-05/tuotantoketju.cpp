#include "tuotantoketju.hh"
#include "reppu.hh"
#include <memory>
#include <string>
#include <iostream>

using namespace std;

Tuotantoketju::Tuotantoketju():
    ensimmaisen_osoite_(nullptr),
    viimeisen_osoite_(nullptr){
}

// Riittää että vapautetaan vain jokaiset Ketjun_alkiot, sillä
// shared_ptr huolehtii materiaalialkioiden poistamisesta
Tuotantoketju::~Tuotantoketju() {
    Ketjun_alkio* vapautettavan_osoite;

    while ( ensimmaisen_osoite_ != nullptr ) {
        vapautettavan_osoite = ensimmaisen_osoite_;
        ensimmaisen_osoite_ = ensimmaisen_osoite_->seuraavan_osoite;
        delete vapautettavan_osoite;
    }
}

//Mikäli ensimmäisen osoite on nullptr niin rakenne on tyhjä
bool Tuotantoketju::onko_tyhja() const{
    return ensimmaisen_osoite_ == nullptr;
}

// Tarkistetaan, että löytyykö kysytty tavara
// tuotettavista_esineistä tai materiaaleista käymällä läpi
// jokainen Ketjun_alko ja sitä vastaava Materiaali_alkioiden linkitetty lista
bool Tuotantoketju::onko_ketjussa(const string& etsittava) const{

    Ketjun_alkio* tutkittava_esine = ensimmaisen_osoite_;
    shared_ptr<Materiaali_alkio> tutkittava_materiaali =
            tutkittava_esine->ensimmainen_materiaali;

    while (tutkittava_esine != nullptr){
        tutkittava_materiaali = tutkittava_esine->ensimmainen_materiaali;
        if( tutkittava_esine->tuotettava_esine == etsittava){
            return true;
        }
        while ( tutkittava_materiaali != nullptr){
            if (tutkittava_materiaali->materiaali == etsittava){
                return true;
            }
            tutkittava_materiaali = tutkittava_materiaali->seuraavan_osoite;
        }
        tutkittava_esine = tutkittava_esine->seuraavan_osoite;
    }
    return false;

}
// Lisätään tietorakenteeseen tuotettava esine ja siihen tarvittava materiaali
bool Tuotantoketju::lisaa(const string& tuotettava_esine,
                          const string& tarvittava_materiaali) {

    shared_ptr<Materiaali_alkio> materiaalin_osoite(new Materiaali_alkio);
    materiaalin_osoite->materiaali = tarvittava_materiaali;
    materiaalin_osoite->edellisen_osoite = nullptr;
    materiaalin_osoite->seuraavan_osoite = nullptr;

    // Jos lista on tyhjä niin lisääminen tapahtuu helposti vain varaamalla
    // muistista tilaa Ketjun_alkiolle. Samalla pistetään sen muistiosoite
    // talteen sekä tallennetaan Materiaali_alkion osoite Ketjun_alkioon
    if( onko_tyhja() ){
        Ketjun_alkio* esineen_osoite = new Ketjun_alkio;
        esineen_osoite->tuotettava_esine = tuotettava_esine;
        ensimmaisen_osoite_ = esineen_osoite;
        viimeisen_osoite_ = esineen_osoite;
        esineen_osoite->seuraavan_osoite = nullptr;
        esineen_osoite->ensimmainen_materiaali = materiaalin_osoite;
        esineen_osoite->viimeinen_materiaali = materiaalin_osoite.get();

    // Nyt tiedetään, ettei rakenne ole tyhjä, joten tutkitaan löytyykö
    // tuotettava_esine jo valmiiksi listasta.
    }else{
        Ketjun_alkio* tutkittava = ensimmaisen_osoite_;
        kohta_ketjussa(tutkittava,tuotettava_esine);

        // Tuotettavaa_esinettä ei löytynyt. Tilanne on melkein sama kuin
        // tyhjään listaan lisäämisessä. Nyt kuitenkin täytyy huolehtia,
        // että toiseksi viimeinen alkio tietää lisättävän osoitteen
        if ( tutkittava == nullptr ){
            Ketjun_alkio* esineen_osoite = new Ketjun_alkio;
            esineen_osoite->tuotettava_esine = tuotettava_esine;
            viimeisen_osoite_->seuraavan_osoite = esineen_osoite;
            viimeisen_osoite_ = esineen_osoite;
            esineen_osoite->seuraavan_osoite = nullptr;
            esineen_osoite->ensimmainen_materiaali = materiaalin_osoite;
            esineen_osoite->viimeinen_materiaali = materiaalin_osoite.get();

        // Tuotettava_esine löytyi listasta, joten täytyy lisätä vain
        // uusi materiaali olemassa olevaan Materiaali_alkioiden ketjuun.
        // Myöhempää tulostamista ajatellen lisätään materiaali valmiiksi
        // aakkosjärjestystä ajatellen oikeaan kohtaaan

        }else{
            //Sijoitetaan materiaali materiaaliketjun alkuun mikäli se tulee
            //aakkosissa ennen jo olemassa olevaa ensimmäistä alkiota
            if ( tutkittava->ensimmainen_materiaali->materiaali
                    > tarvittava_materiaali ){
                tutkittava->ensimmainen_materiaali->edellisen_osoite =
                        materiaalin_osoite.get();
                materiaalin_osoite->seuraavan_osoite =
                        tutkittava->ensimmainen_materiaali;
                tutkittava->ensimmainen_materiaali = materiaalin_osoite;

            //Vastaavasti tutkitaan, että tuleeko se aakkosissa viimeisen
            //alkion jälkeen ja lisätään se sinne
            }else if ( tutkittava->viimeinen_materiaali->materiaali
                       < tarvittava_materiaali ){
                tutkittava->viimeinen_materiaali->seuraavan_osoite =
                        materiaalin_osoite;
                materiaalin_osoite->edellisen_osoite =
                        tutkittava->viimeinen_materiaali;
                tutkittava->viimeinen_materiaali = materiaalin_osoite.get();

            //Jos edelliset kohdat eivät täyttyneet niin materiaali lisätään,
            //jonnekin ketjun keskelle ja varmistetaan ettei kyseistä
            //materiaalia jo löydy listasta. Tällöin pitää ensiksi selvittää
            //se alkio, joka on ennen lisättävää materiaalia.
            }else{
                shared_ptr<Materiaali_alkio> lisayksen_kohta =
                        tutkittava->ensimmainen_materiaali;
                while ( lisayksen_kohta->materiaali <= tarvittava_materiaali ){
                    if (lisayksen_kohta->materiaali == tarvittava_materiaali){
                        return false;
                    }
                    lisayksen_kohta = lisayksen_kohta->seuraavan_osoite;
                }
                lisayksen_kohta->edellisen_osoite->seuraavan_osoite =
                        materiaalin_osoite;
                materiaalin_osoite->seuraavan_osoite = lisayksen_kohta;
                materiaalin_osoite->edellisen_osoite =
                        lisayksen_kohta->edellisen_osoite;
                lisayksen_kohta->edellisen_osoite = materiaalin_osoite.get();
                lisayksen_kohta = nullptr;
            }
        }
    }
    return true;
}
// Etsitään ensin kohta_ketjussa funktion avulla se Ketjun_alkio,
// joka vastaa haluttua esinettä. Tämän jälkeen tulostetaan kyseistä
// Ketjun_alkiota vastaavat Materiaali_alkiot
void Tuotantoketju::tulosta_materiaalit(const string& haluttu_esine) const{
    Ketjun_alkio* tulostettava = ensimmaisen_osoite_;
    kohta_ketjussa(tulostettava,haluttu_esine);

    if ( tulostettava != nullptr ){
        shared_ptr<Materiaali_alkio> tulostettava_materiaali =
                tulostettava->ensimmainen_materiaali;
        while ( tulostettava_materiaali != nullptr){
            cout << tulostettava_materiaali->materiaali << endl;
            tulostettava_materiaali =
                    tulostettava_materiaali->seuraavan_osoite;
        }
    }
}
// Tutkitaan ensin, että löytyykö esine repusta eli se on askarreltavissa.
// Tämän jälkeen etsitään oikea Ketjun_alkio, jos sen osoite on nullptr eli
// sitä ei voi askarrella (esim Puuta tai Rautamalmia). Muulloin esineelle
// löytyy askartelumateriaalit, joista jokaisen täytyy löytyä repusta,
// jotta esineen voi askarrella
bool Tuotantoketju::askarteltavissa (const string& esine,
                                     const Reppu& reppu) const{

    if ( reppu.onko_repussa(esine) ){
        return true;
    }
    Ketjun_alkio* tutkittava_esine = ensimmaisen_osoite_;
    kohta_ketjussa(tutkittava_esine,esine);

    if (tutkittava_esine == nullptr ){
        return false;
    }else {
        shared_ptr<Materiaali_alkio> tutkittava_materiaali =
                tutkittava_esine->ensimmainen_materiaali;
        while ( tutkittava_materiaali != nullptr){
            if ( not reppu.onko_repussa(tutkittava_materiaali->materiaali) ){
                return false;
            }
            tutkittava_materiaali = tutkittava_materiaali->seuraavan_osoite;
        }
    return true;
    }
}
// Etsii esinettä vastaavan Ketjun_alkion ja tallentaa sen osoitteen
// tutkittava_esine viiteparametriin
void Tuotantoketju::kohta_ketjussa(Ketjun_alkio*& tutkittava_esine,
                                   const string& esine) const{

    while ( tutkittava_esine != nullptr){
        if ( tutkittava_esine->tuotettava_esine == esine){
            break;
        }
        tutkittava_esine = tutkittava_esine->seuraavan_osoite;
    }
}
// Etsitään taas oikea Ketjun_alkio, jonka jälkeen tutkitaan sen
// materiaaleja yksitellen läpi.
bool Tuotantoketju::askarreltavissa_bonus(const string& esine,
                                          const Reppu& reppu) const{

    if ( askarteltavissa(esine,reppu) ){
        return true;
    }
    Ketjun_alkio* tutkittava_esine = ensimmaisen_osoite_;
    kohta_ketjussa(tutkittava_esine,esine);

    if ( tutkittava_esine == nullptr ){
        return false;
    }
    shared_ptr<Materiaali_alkio> tutkittava_materiaali =
        tutkittava_esine->ensimmainen_materiaali;

    // Tätä aiemmin on edetty samalla tavalla kuin askarreltavissa funktiossa.
    // Nyt Mikäli materiaalia ei löytynyt repusta niin tutkitaan, että onko
    // kyseiselle materiaalille olemassa omat materiaalinsa. Mikäli ei ole
    // ja sitä ei löydy repusta niin alkuperäistä esinettä ei voi askarrella.
    // Mikäli kuitenkin materiaalille löytyy materiaaleja niin kutsutaan uusiksi
    // funktiota itseään erona se, että nyt tutkitaan, että onko materiaalia
    // mahdollista askarrella
    while ( tutkittava_materiaali != nullptr){

        if ( not reppu.onko_repussa(tutkittava_materiaali->materiaali) ){
            Ketjun_alkio* etsittava = ensimmaisen_osoite_;
            kohta_ketjussa(etsittava,tutkittava_materiaali->materiaali);

            if ( etsittava == nullptr && not
                reppu.onko_repussa(tutkittava_materiaali->materiaali) ){
                return false;
            }else{
                if ( not askarreltavissa_bonus(
                         tutkittava_materiaali->materiaali,reppu) ){
                    return false;
                }
            }

        }
        tutkittava_materiaali = tutkittava_materiaali->seuraavan_osoite;
    }
    return true;
}
