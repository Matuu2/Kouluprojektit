#include "pankkitili.hh"

using namespace std;

//rakentaa pankkitiliolion, johon arvotaan tilin loppuosa rand()%-funktion avulla
pankkitili::pankkitili():

    tilinumero_{"FI112222333344"},
    saldo_{0},
    asiakasnumero_{rand()%1000000} {
    int luku = rand()% 10000;
    string loppuosa = to_string(luku);
    tilinumero_ += loppuosa;

}
//korvataan pankkitilin arvot käyttäjän haluamilla arvoilla
void pankkitili::aseta(const string& tilinumero,const int& saldo,const int& asiakasnumero){
    tilinumero_ = tilinumero;
    saldo_ = saldo;
    asiakasnumero_ = asiakasnumero;

}
//lisätään käyttäjän antaman määrän verran rahaa tilille
void pankkitili::pano(const double& rahamaara){
    saldo_ += rahamaara;
}
//Mikäli rahaa on tarpeeksi, tililtä otetaan haluttu määrä rahaa ja palautetaan true,
//muuten false, jonka avulla pääohjelmassa tiedetään,että onnistuiko otto
bool pankkitili::otto(const double& rahamaara){
    if (rahamaara > saldo_){
        return false;
    }
    else
        {saldo_ -= rahamaara;
        return true;
    }
}
//Mikäli rahaa on tarpeeksi, tililtä otetaan rahaa ja lisätään sen verran rahaa saajalle,
//jos siirto onnistui palautetaan true ja jos epäonnistui niin palautetaan false, jonka
//avulla pääohjelmassa tiedetään tilisiirron onnistuminen
bool pankkitili::tilisiirto(const double& rahamaara,pankkitili& saaja){
    if (rahamaara > saldo_){
        return false;
    }
    else
        {saaja.saldo_ += rahamaara;
        saldo_ -= rahamaara;
        return true;
    }
}
//tulostaa tilin tiedot
void pankkitili::tulosta(){
    cout << "Tilinumero: " << tilinumero_ << endl;
    cout << fixed << setprecision(2) << "Saldo: " << saldo_ << endl;
    cout << "Asiakasnumero: "<< asiakasnumero_ << endl;
}
