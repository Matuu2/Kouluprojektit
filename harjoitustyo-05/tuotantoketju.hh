#ifndef TUOTANTOKETJU_HH
#define TUOTANTOKETJU_HH
#include "reppu.hh"
#include <memory>
#include <string>

using namespace std;

//Tuotantoketju koostuu kahdesta linkitetystä listasta.
//Ketjun_alkiot sisältävät tuotettavat_esineet ja
//Materiaali_alkiot niihin suorat edeltäjät.
class Tuotantoketju
{
public:
    Tuotantoketju();
    ~Tuotantoketju();
    bool onko_ketjussa(const string& etsittava) const;
    bool lisaa(const string& valmistettava_esine,
               const string& tarvittava_materiaali);
    void tulosta_materiaalit(const string& haluttu_esine) const;
    bool askarteltavissa (const string& esine, const Reppu& reppu) const;
    bool askarreltavissa_bonus(const string& esine, const Reppu& reppu) const;



private:

    bool onko_tyhja() const;

    struct Materiaali_alkio{
        string materiaali;
        shared_ptr<Materiaali_alkio> seuraavan_osoite;
        Materiaali_alkio* edellisen_osoite;
    };

    struct Ketjun_alkio{
        string tuotettava_esine;
        shared_ptr<Materiaali_alkio> ensimmainen_materiaali;
        Materiaali_alkio* viimeinen_materiaali;
        Ketjun_alkio* seuraavan_osoite;
    };
    void kohta_ketjussa(Ketjun_alkio*& tutkittava_esine, const string& esine) const;

    Ketjun_alkio* ensimmaisen_osoite_;
    Ketjun_alkio* viimeisen_osoite_;

};
#endif // TUOTANTOKETJU_HH
