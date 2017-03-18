#ifndef KULJETUT_HH
#define KULJETUT_HH
#include <string>

using namespace std;

class Kuljetut
{
public:
    Kuljetut();
    bool anna_arvo(int x,int y, int z);
    bool liikuta_matoa(string suunta, int maara, bool pakita);
    void anna_aloituspiste(int x,int y, int z);

private:
    bool kulje_xsuunnassa(int maara, bool pakita);
    bool kulje_ysuunnassa(int maara, bool pakita);
    bool kulje_zsuunnassa(int maara, bool pakita);
    bool kuutio_ [3][3][3]; //x,y,z
    int nykyinen_xkoordinaatti_;
    int nykyinen_ykoordinaatti_;
    int nykyinen_zkoordinaatti_;

};

#endif // KULJETUT_HH
