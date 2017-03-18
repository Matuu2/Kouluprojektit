#include "kuljetut.hh"

Kuljetut::Kuljetut(){
    for (int x = 0; x < 3; ++x){
        for (int y = 0; y < 3; ++y){
            for (int z = 0; z < 3; ++z){
                kuutio_[x][y][z] = false;
            }
        }
    }
    nykyinen_xkoordinaatti_ = 0;
    nykyinen_ykoordinaatti_ = 0;
    nykyinen_zkoordinaatti_ = 0;
}

bool Kuljetut::anna_arvo(int x, int y, int z){
    return kuutio_[x][y][z];

}

bool Kuljetut::liikuta_matoa(string suunta, int maara,bool pakita){
    if ( suunta == "x"){
        return kulje_xsuunnassa(maara,pakita);
    }else if ( suunta == "y" ){
        return kulje_ysuunnassa(maara,pakita);
    }else{
        return kulje_zsuunnassa(maara,pakita);
    }
}

void Kuljetut::anna_aloituspiste(int x, int y, int z){
    for (int x = 0; x < 3; ++x){
        for (int y = 0; y < 3; ++y){
            for (int z = 0; z < 3; ++z){
                kuutio_[x][y][z] = false;
            }
        }
    }
    kuutio_[x][y][z] = true;
}

bool Kuljetut::kulje_xsuunnassa(int maara, bool pakita){
    int summa = nykyinen_xkoordinaatti_ + maara;
    if( summa < 0 || summa > 2 || anna_arvo(summa,nykyinen_ykoordinaatti_,nykyinen_zkoordinaatti_)){
        if ( !pakita ){
            return false;
        }
    }if ( maara > 0 ){
        for ( int i = 0; i <= maara; ++i){
            kuutio_[nykyinen_xkoordinaatti_+i][nykyinen_ykoordinaatti_][nykyinen_zkoordinaatti_] = !pakita;
        }
    }else{
        for ( int i = 0; i >= maara; --i){
            kuutio_[nykyinen_xkoordinaatti_+i][nykyinen_ykoordinaatti_][nykyinen_zkoordinaatti_] = !pakita;
        }
    }
    nykyinen_xkoordinaatti_ = summa;
    return true;
}

bool Kuljetut::kulje_ysuunnassa(int maara, bool pakita){
    int summa = nykyinen_ykoordinaatti_ + maara;
    if( summa < 0 || summa > 2 || anna_arvo(nykyinen_xkoordinaatti_,summa,nykyinen_zkoordinaatti_)){
        if ( !pakita ){
            return false;
        }
    }if ( maara > 0 ){
        for ( int i = 0; i <= maara; ++i){
            kuutio_[nykyinen_xkoordinaatti_][nykyinen_ykoordinaatti_+i][nykyinen_zkoordinaatti_] = !pakita;
        }
    }else{
        for ( int i = 0; i >= maara; --i){
            kuutio_[nykyinen_xkoordinaatti_][nykyinen_ykoordinaatti_+i][nykyinen_zkoordinaatti_] = !pakita;
        }
    }
    nykyinen_ykoordinaatti_ = summa;
    return true;
}

bool Kuljetut::kulje_zsuunnassa(int maara, bool pakita){
    int summa = nykyinen_zkoordinaatti_ + maara;
    if( summa < 0 || summa > 2 || anna_arvo(nykyinen_xkoordinaatti_,nykyinen_ykoordinaatti_,summa)){
        if ( !pakita ){
            return false;
        }
    }if ( maara > 0 ){
        for ( int i = 0; i <= maara; ++i){
            kuutio_[nykyinen_xkoordinaatti_][nykyinen_ykoordinaatti_][nykyinen_zkoordinaatti_+i] = !pakita;
        }
    }else{
        for ( int i = 0; i >= maara; --i){
            kuutio_[nykyinen_xkoordinaatti_][nykyinen_ykoordinaatti_][nykyinen_zkoordinaatti_+i] = !pakita;
        }
    }
    nykyinen_zkoordinaatti_ = summa;
    return true;
}
