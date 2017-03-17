// TIE-02200 Ohjelmoinnin perusteet Harjoitustyö 4
// Matias Ala-Sunila 246417
// matias.ala-sunila@student.tut.fi

#include "painoindeksilaskin.hh"
#include "ui_painoindeksilaskin.h"

#include <QMainWindow>
#include <QActionGroup>
#include <QAction>
#include <QMenu>


Painoindeksilaskin::Painoindeksilaskin(QWidget *parent):
    // Luodaan Painoindeksilaskin ja sukupuoliactiongroup
    QMainWindow(parent),
    ui(new Ui::Painoindeksilaskin),
    sukupuoliActiongroup(new QActionGroup(this))
{
    ui->setupUi(this);
    // Tehdään tarvittavat yhdistämiset
    connect(ui->spinBox_paino,SIGNAL(valueChanged(int)),this,SLOT(laske_painoindeksi()));
    connect(ui->spinBox_pituus,SIGNAL(valueChanged(int)),this,SLOT(laske_painoindeksi()));
    connect(ui->actionAlkutila,SIGNAL(triggered()),this,SLOT(slot_alkutila()));

    // Määritellään sukupuolivalikko tekemällä käsin sukupuolimenu, joka lisätään
    // desingerilla tehtyyn menubariin. Tehdään vaihtoehdot käsin ja lisätään ne
    // actiongrouppiin, joka hoitaa sen että voidaan valita nainen tai mies. Yhdistetään
    // vielä toiminnot vastaaviin slotteihin
    sukupuolimenu = ui->menuBar->addMenu("Sukupuoli");
    nainen = sukupuolimenu->addAction("Nainen");
    nainen->setCheckable(true);
    nainen->setChecked(true);
    sukupuoliActiongroup->addAction(nainen);
    connect(nainen,SIGNAL(triggered()),this,SLOT(nainen_valittu()));
    mies = sukupuolimenu->addAction("Mies");
    mies->setCheckable(true);
    sukupuoliActiongroup->addAction(mies);
    connect(mies,SIGNAL(triggered()),this,SLOT(mies_valittu()));

}

//Luodaan purkaja
Painoindeksilaskin::~Painoindeksilaskin()
{
    delete ui;
}


//Laskee painoindeksin ja kutsuu tulkintafunktiota
void Painoindeksilaskin::laske_painoindeksi(){
    // Haetaan arvot spinboxeista ja tarkistetaan, ettei kumpikaan ole nolla.
    // Muulloin lasketaan bmi ja asetetaan sen arvo labeliin ja kutsutaan tulkintafunktiota bmi:n arvolla
    double paino = ui->spinBox_paino->value();
    double pituus = ui->spinBox_pituus->value();

    if ( pituus == 0 or paino == 0 ){
        ui->label_bmi-> setText("-");
        ui->label_tulkinta->setText("-");

    } else{
        double bmi = ( paino * 10000) / (pituus * pituus );
        ui->label_bmi->setNum(bmi);
        tulkinta(bmi);
    }
}


// Kun valitaan nainen niin tallennetaan tieto totuusarvoon ja labeliin sekä lasketaan mahdollisesti uusi tulkinta
void Painoindeksilaskin::nainen_valittu(){
    Onko_nainen_valittu = true;
    ui->label_sukupuoli->setText("Nainen");
    laske_painoindeksi();
}


// Kun valitaan mies niin tallennetaan tieto totuusarvoon ja labeliin sekä lasketaan mahdollisesti uusi tulkinta
void Painoindeksilaskin::mies_valittu(){
    Onko_nainen_valittu = false;
    ui->label_sukupuoli->setText("Mies");
    laske_painoindeksi();
}


//Alkutila asettaa spinboxit nollaan (spinboxin muutos muuttaa myös sliderit nollaksi) ja labelit alkuarvoon "-"
//Sekä varmistaa että nainen on valittuna
void Painoindeksilaskin::slot_alkutila(){
    ui->spinBox_paino->setValue(0);
    ui->spinBox_pituus->setValue(0);
    ui->label_bmi->setText("-");
    ui->label_tulkinta->setText("-");
    if (not Onko_nainen_valittu){
        nainen->trigger();
    }

}


// Tulkinta funktio hoitaa, että argumenttia otettua bmi:tä vastaava tulkinta laitetaan label_tulkinta kohtaan oikein
void Painoindeksilaskin::tulkinta(double bmi){
    if( Onko_nainen_valittu ){
        if ( bmi <= 19.1){
            ui->label_tulkinta->setText("alipainoa");
        } else if ( bmi > 19.1 and bmi <= 25.8 ){
            ui->label_tulkinta->setText("normaali");
        } else if ( bmi > 25.8 and bmi <= 27.3 ){
            ui->label_tulkinta->setText("lievää ylipainoa");
        } else if ( bmi > 27.3 and bmi <= 32.2 ){
            ui->label_tulkinta->setText("ylipainoa");
        } else {
            ui->label_tulkinta->setText("paljon ylipainoa");
        }
    } else {
        if ( bmi <= 20.7){
            ui->label_tulkinta->setText("alipainoa");
        } else if ( bmi > 20.7 and bmi <= 26.4 ){
            ui->label_tulkinta->setText("normaali");
        } else if ( bmi > 26.4 and bmi <= 27.8 ){
            ui->label_tulkinta->setText("lievää ylipainoa");
        } else if ( bmi > 27.8 and bmi <= 31.1 ){
            ui->label_tulkinta->setText("ylipainoa");
        } else {
            ui->label_tulkinta->setText("paljon ylipainoa");
        }
    }
}
