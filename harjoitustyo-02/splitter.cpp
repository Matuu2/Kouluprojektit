#include "splitter.hh"


Splitter::Splitter():
    paloiteltava_(""), onko_paloittelu_suoritettu_(false), kentat_( {} ) {
}


void Splitter::aseta_paloiteltavava_merkkijono(const string& mjono) {
    paloiteltava_ = mjono;

    // onko_paloittelu_suoritettu_-jäsenmuuttuja pitää kirjaa siitä,
    // onko paloittele-metodia kutsuttu sen jälkeen, kun paloiteltava
    // merkkijono on viimeksi asetettu.  Käytännössä tämä tarkoittaa sitä,
    // onko kentat_-vektorin arvo ajan tasalla.
    onko_paloittelu_suoritettu_ = false;
}


int Splitter::paloittele(char erotinmerkki, bool ohita_tyhjat) {
    // Tyhjennetään kentat_-vektori siltä varalta, että samaa oliota
    // on jo aiemmin käytetty jokin toisen merkkijonon paloitteluun,
    // minkä seurauksena vektorissa on jotain vanhaa tietoa.
    kentat_.clear();

    // alkukohta pitää kirjaa siitä, missä kohdassa merkkijonoa
    // on seuraava kenttä, jota ei vielä ole siirretty kentat_-vektoriin.
    string::size_type alkukohta = 0;
    string kentan_teksti;

    while ( true ) {
        // loppukohtaan etsitään find-metodilla, missä kohdassa
        // on ensimmäinen alkukohdan jälkeen tuleva erotinmerkki.
        string::size_type loppukohta;

        loppukohta = paloiteltava_.find(erotinmerkki, alkukohta);

        // Jos alkukohdan perästä ei löydy erotinmerkkiä, merkkojonossa
        // on enää yksi kenttä jäljellä (viimeinen kenttä, jonka perässä
        // ei ole erotinmerkkiä).  Käsitellään se erikseen silmukän perässä.
        if ( loppukohta == string::npos ) {
            break;
        }

        // Otetaan talteen kentän sisältö indeksien
        // alkukohta ja loppukohta välistä.
        kentan_teksti = paloiteltava_.substr(alkukohta, loppukohta - alkukohta);

        // Tyhjiä kenttiä ei tallenneta, mikäli parametri
        // ohita_tyhjat on true.
        if ( not (ohita_tyhjat and kentan_teksti.empty()) ) {
            kentat_.push_back(kentan_teksti);
        }

        // Siirretään alkukohta seuraavan käsittelemättömän
        // kentän ensimmäiseen merkkiin.
        alkukohta = loppukohta + 1;
    }

    // Otetaan viimeisen erotinmerkin perässä oleva teksti talteen.
    // koska se on rivin viimeinen kenttä.
    kentan_teksti = paloiteltava_.substr(alkukohta);

    if ( not (ohita_tyhjat and kentan_teksti.empty()) ) {
        kentat_.push_back(kentan_teksti);
    }

    // Kirjataan ylös, että paloittelu on suoritettu.
    onko_paloittelu_suoritettu_ = true;

    return kentat_.size();
}


string Splitter::hae_kentta(int kentan_numero) const {
    // Mitä tämän funktion pitäisi tehdä virhetilanteessa?
    // Eli jos esimerkiksi yritetään hakea kenttä ennen kuin
    // paloiteltava_ on pistetty osiin ja talletettu
    // kentat_-vektoriin. Periaatteessa funktio voisi aiheuttaa
    // poikkeuksen throw-käskyllä. Mutta koska se ei vielä ole tuttu,
    // kikkaillaan ja asetetaan kentan_numero käsin niin suureksi,
    // että vektoria indeksoiva at-operaatio tuottaa poikkeuksen.
    // Häpeämätöntä kikkailua.
    if ( not onko_paloittelu_suoritettu_ ) {
        // Alkioiden lukumäärä on yhtä suurempi kuin suurin
        // sallittu indeksin arvo.
        kentan_numero = kentat_.size();
    }

    // Jos poikkeusten käyttö olisi hanskassa, oikeaoppisesti edellinen menisi:
    //
    //    #include <stdexcept>  // Ohjelmakoodin alkuun
    //    ···
    //    if ( not onko_paloittelu_suoritettu_ ) {
    //        throw out_of_range("paloittelua ei ole suoritettu")
    //    }

    // Jos yritetään hakea kenttää, jota ei ole olemassa: siis
    // kentan_numero on suurempi tai yhtäsuuri kuin kentat_-vektorin
    // alkioiden määrä, seuraava at-operaatio tuottaa poikkeuksen.
    // Luokan käyttäjän vastuulle siis jää huolehtia siitä, että hän
    // yrittää käsitellä vain olemassa olevia kenttiä.  Kenttien
    // lukumäärä saadaan paloittele-metodin paluuarvona.
    return kentat_.at(kentan_numero);
}
