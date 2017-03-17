// TIE-02200 Ohjelmoinnin perusteet Harjoitustyö 4
// Matias Ala-Sunila 246417
// matias.ala-sunila@student.tut.fi


#ifndef PAINOINDEKSILASKIN_HH
#define PAINOINDEKSILASKIN_HH

#include <QMainWindow>
#include <QActionGroup>
#include <QAction>
#include <QMenu>

namespace Ui {
class Painoindeksilaskin;
}

class Painoindeksilaskin : public QMainWindow
{
    Q_OBJECT

//Määritellään rakentaja ja purkaja
public:
    explicit Painoindeksilaskin(QWidget *parent = 0);
    ~Painoindeksilaskin();


public slots:
    // Laskee painoindeksin ja kutsuu tulkintafunktiota
    void laske_painoindeksi();
    // Hoitaa toiminnallisuuden, kun valitaan nainen valikosta
    void nainen_valittu();
    // Hoitaa toiminnallisuuden, kun valitaan mies valikosta
    void mies_valittu();
    // Asettaa painoindeksilaskimen alkutilaan
    void slot_alkutila();
    // Ottaa argumenttinaan bmi:n, jonka avulla kirjoitetaan sanallinen tulkinta bmi:stä labeliin
    void tulkinta(double bmi);

//Private-osassa on lähinnä sukupuolivalikkoa varten luodut asiat.
//Qactiongroup avulla tehdään rakenne, jossa voi valita vain yhden vaihtoehdon kerrallaan.
//Samalla täytyy käsin luoda myös menu ja sinne toiminnot mies ja nainen
private:
    Ui::Painoindeksilaskin *ui;
    QActionGroup *sukupuoliActiongroup;
    QAction *nainen;
    QAction *mies;
    QMenu *sukupuolimenu;
    bool Onko_nainen_valittu = true;

};

#endif // PAINOINDEKSILASKIN_HH
