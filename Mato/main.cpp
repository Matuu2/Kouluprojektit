#include "kuljetut.hh"
#include <iostream>
#include <string>
#include <vector>

bool ratkaisunhaku(const vector<int>& madon_tiedot, Kuljetut &kuutio, vector<string>& suunnat, unsigned int indeksi);
using namespace std;
//Snakecube nimisen pulmapelin ratkontaohjelma. 

//Oman kuutioni "koodi" 2,2,2,2,1,1,1,2,2,1,1,2,1,2,1,1,2
int main(){
    //Avatun kuution tiedot.Ensimmäistä palikkaa ei oteta
    //mukaan laskuihin eikä mitään palikkaa lasketa kahdesti
    vector<int> madon_tiedot;
    vector<string> suunnat; //Mihin suuntaan ollaan menty
    suunnat.push_back("+y"); //Aloitetaan menemällä "ylös"
    Kuljetut kuutio;
    string syote;
    int luku = 1;
    cout << "Anna madon tiedot" <<endl;
    while(luku > 0 and luku < 3){
        getline(cin,syote);
        luku = stoi(syote);
        if( luku > 0 and luku < 3 ){
            madon_tiedot.push_back(luku);
        }
    }
    for (unsigned int i = 0; i < madon_tiedot.size(); ++i){
        cout << madon_tiedot.at(i) <<endl;
    }
    kuutio.anna_aloituspiste(0,0,0);
    if ( not ratkaisunhaku(madon_tiedot,kuutio,suunnat,0) ){
        cout<<"byhyy"<<endl;
    }else{
        cout << "juhuu?" << endl;
        for (unsigned int i = 1; i < suunnat.size(); ++i )
            cout << i << ". = " << suunnat.at(i) <<endl;
    }
}

bool ratkaisunhaku(const vector<int>& madon_tiedot,Kuljetut& kuutio, vector<string>& suunnat, unsigned int indeksi){
    if ( suunnat.back() == "+x" or suunnat.back() == "-x"){
        if( indeksi == madon_tiedot.size() ){
            return true;
        }
        if ( kuutio.liikuta_matoa("y",madon_tiedot.at(indeksi),false) ){
            suunnat.push_back("+y");
            if ( ratkaisunhaku(madon_tiedot,kuutio,suunnat,indeksi + 1) ){
                return true;
            }
        }if( kuutio.liikuta_matoa("z",madon_tiedot.at(indeksi),false) ){
            suunnat.push_back("+z");
            if ( ratkaisunhaku(madon_tiedot,kuutio,suunnat,indeksi + 1) ){
                return true;
            }

        }if( kuutio.liikuta_matoa("y",-madon_tiedot.at(indeksi),false) ){
            suunnat.push_back("-y");
            if ( ratkaisunhaku(madon_tiedot,kuutio,suunnat,indeksi + 1) ){
                return true;
            }

        }if( kuutio.liikuta_matoa("z",-madon_tiedot.at(indeksi),false) ){
            suunnat.push_back("-z");
            if ( ratkaisunhaku(madon_tiedot,kuutio,suunnat,indeksi + 1) ){
                return true;
            }
        }

        if ( suunnat.back() == "+x"){
            kuutio.liikuta_matoa("x",-madon_tiedot.at(indeksi-1),true);
            suunnat.pop_back();
        }else {
            kuutio.liikuta_matoa("x",madon_tiedot.at(indeksi-1),true);
            suunnat.pop_back();
        }
        return false;


    }else if ( suunnat.back() == "+y" or suunnat.back() == "-y"){

        if( indeksi == madon_tiedot.size() ){
            return true;
        }
        if ( kuutio.liikuta_matoa("x",-madon_tiedot.at(indeksi),false) ){
            suunnat.push_back("-x");
            if ( ratkaisunhaku(madon_tiedot,kuutio,suunnat,indeksi + 1) ){
                return true;
            }

        }if( kuutio.liikuta_matoa("z",madon_tiedot.at(indeksi),false) ){
            suunnat.push_back("+z");
            if ( ratkaisunhaku(madon_tiedot,kuutio,suunnat,indeksi + 1) ){
                return true;
            }

        }if( kuutio.liikuta_matoa("x",madon_tiedot.at(indeksi),false) ){
            suunnat.push_back("+x");
            if ( ratkaisunhaku(madon_tiedot,kuutio,suunnat,indeksi + 1) ){
                return true;
            }

        }if( kuutio.liikuta_matoa("z",-madon_tiedot.at(indeksi),false) ){
            suunnat.push_back("-z");
            if ( ratkaisunhaku(madon_tiedot,kuutio,suunnat,indeksi + 1) ){
                return true;
            }
        }

        if ( suunnat.back() == "+y"){
            kuutio.liikuta_matoa("y",-madon_tiedot.at(indeksi-1),true);
            suunnat.pop_back();
        }else {
            kuutio.liikuta_matoa("y",madon_tiedot.at(indeksi-1),true);
            suunnat.pop_back();
        }
        return false;


    }else{
        if( indeksi == madon_tiedot.size() ){
            return true;
        }
        if ( kuutio.liikuta_matoa("x",-madon_tiedot.at(indeksi),false) ){
            suunnat.push_back("-x");
            if ( ratkaisunhaku(madon_tiedot,kuutio,suunnat,indeksi + 1) ){
                return true;
            }

        }if( kuutio.liikuta_matoa("y",madon_tiedot.at(indeksi),false) ){
            suunnat.push_back("+y");
            if ( ratkaisunhaku(madon_tiedot,kuutio,suunnat,indeksi + 1) ){
                return true;
            }

        }if( kuutio.liikuta_matoa("x",madon_tiedot.at(indeksi),false) ){
            suunnat.push_back("+x");
            if ( ratkaisunhaku(madon_tiedot,kuutio,suunnat,indeksi + 1) ){
                return true;
            }

        }if( kuutio.liikuta_matoa("y",-madon_tiedot.at(indeksi),false) ){
            suunnat.push_back("-y");
            if ( ratkaisunhaku(madon_tiedot,kuutio,suunnat,indeksi + 1) ){
                return true;
            }
        }

        if ( suunnat.back() == "+z"){
            kuutio.liikuta_matoa("z",-madon_tiedot.at(indeksi-1),true);
            suunnat.pop_back();
        }else {
            kuutio.liikuta_matoa("z",madon_tiedot.at(indeksi-1),true);
            suunnat.pop_back();
        }
        return false;

    }

}
