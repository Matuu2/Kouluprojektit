#ifndef REPPU_HH
#define REPPU_HH
#include <string>

using namespace std;

// Reppua toteutettaessa on hyödynnetty ennakkotehtävän 11 mallikoodia
class Reppu
{
public:

    Reppu();
    ~Reppu();
    void tyhjenna();
    bool lisaa(string syote);
    void tulosta() const;
    bool onko_repussa(const string &etsittava) const;
    bool onko_tyhja() const;

private:

    int  koko() const;

    string* taulukko_;      // Osoitin dynaamisesti varatun taulukon alkuun.
    int  kokonaistila_ ; // Minkä kokoinen dynaamisesti varattu taulukko on.
    int  kaytetty_tila_; // Montako alkiota taulukosta on käytetty.

};

#endif // REPPU_HH
