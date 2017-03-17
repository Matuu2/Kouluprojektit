// TIE-02200 Ohjelmoinnin perusteet Harjoitustyö 4
// Matias Ala-Sunila 246417
// matias.ala-sunila@student.tut.fi

#include "painoindeksilaskin.hh"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Painoindeksilaskin w;
    w.show();

    return a.exec();
}
