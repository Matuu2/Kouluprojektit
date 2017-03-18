#ifndef SPLITTER_HH
#define SPLITTER_HH
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Tämän luokan julkista rajapintaa voisi parantaa huomattavasti,
// jos miettisi asiaa hiukankaan pidemmälle.  Yksinkertaisena
// esimerkkinä STL-säiliön käytöstä luokan private-osassa tämä
// kuitenkin on riittävä.

class Splitter {
  public:
    Splitter();

    // Asetetaan merkkijono, joka halutaan paloitella.
    void aseta_paloiteltavava_merkkijono(const string& mjono);

    // Paloitellaan merkkijono parametrina annetun erotinmerkin
    // kohdalta osiin. Paluuarvona tieto siitä, montako kenttää
    // rivillä oli.  Parametri ohita_tyhjat on lisäys
    // tehtävänantoon. Jos ohita_tyhjat- parametrin arvo on true,
    // paloittelun tuloksena mahdollisesti syntyvät tyhjät kentät
    // jätetään pois lopputuloksesta.  Tämä on hyödyllinen ominaisuus,
    // jos halutaan jakaa merkkijono sanoiksi, mutta ei olla täysin
    // varmoja siitä, onko sanojen välissä yksi vai useampia
    // välilyöntejä:  paloittelijaolio.paloittele(' ', true);
    int paloittele(char erotinmerkki, bool ohita_tyhjat = false);

    // Kun merkkijono on paloiteltu, tällä metodilla
    // voidaan pyytää Splitter-oliolta tietty kenttä.
    // Oletetaan että kentät on numeroitu vasemmalta
    // oikealle alkaen nollasta.
    string hae_kentta(int kentan_numero) const;

  private:
    // Lähtötieto: tätä merkkijonoa paloittele-metodi pätkiin osiin.
    string paloiteltava_;

    // onko_paloittelu_suoritettu_-muuttujan arvo on true, mikäli
    // paloittele-metodia on kutsuttu sen jälkeen, kun uusi
    // paloiteltava merkkijono viimeksi asetettiin
    // aseta_paloiteltavava_merkkijono-metodilla.
    bool onko_paloittelu_suoritettu_;

    // paloittele-metodi tallentaa tuloksen tähän vektoriin, niin
    // että kun merkkijono on kerran paloiteltu, sen kenttiin päästään
    // käsiksi nopeasti.
    vector<string> kentat_;
};

#endif // SPLITTER_HH

