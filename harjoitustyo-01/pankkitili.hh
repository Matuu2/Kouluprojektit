#ifndef PANKKITILI_HH
#define PANKKITILI_HH
#include <iostream>
#include <string>
#include <random>
#include <iomanip>

using namespace std;


class pankkitili
{
public:
    pankkitili();
    void aseta(const string& tilinumero,const int& saldo,const int& asiakasnumero);
    void pano(const double& rahamaara);
    bool otto(const double& rahamaara);
    bool tilisiirto(const double& rahamaara,pankkitili& saaja);
    void tulosta();

private:
    string tilinumero_;
    double saldo_;
    int asiakasnumero_;
};

#endif // PANKKITILI_HH
