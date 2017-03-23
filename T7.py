#Johdatus ohjelmointiin Harjoitustyö 7 Yatzy
#Matias Ala-Sunila 246417 matias.ala-sunila@student.tut.fi

#Kerron ensin vähän yleistä työstäni, jotta siitä saisi helpommin jotain selvää
#Tein siis erikseen aloitusnäytön, jossa kerron lyhyesti mitä Yatzy on, mutta
#suosittelen lämpimästi tutustumaan Yatzyn sääntöihin ennen tarkastamista
#Aloitusnäytössä valitaan pelaajien määrä ja annetaan pelaajille nimet, jonka
#jälkeen peli voi alkaa

from tkinter import *
from tkinter import messagebox
import random, time

KUVATIEDOSTOT = ["1.gif", "2.gif", "3.gif", "4.gif", "5.gif", "6.gif",]


class aloitusnäyttö():
    """
    Luodaan aloitusnäyttö, josta kerroin aiemmin. Tilan takia pelaajien määrä
    on rajoitettu viiteen. Olen tässä vaiheessa myös tehnyt self.nimet listaan
    jo yhden nimen siltä varalta, että pelaaja sulkeekin aloitusnäytön
    painamatta "Aloita peli"-painiketta
    """
    def __init__(self):
        self.__ikkuna = Tk()
        self.__ikkuna.title("Tervetuloa pelaamaan Yatzya")
        self.__ikkuna.option_add("*Font","Verdana 10")
        self.__entrylista = []
        self.nimet = ["Pelaaja 1"]

        Label(self.__ikkuna,background="white",borderwidth=2, relief=GROOVE
              ,text="Pelin tarkoituksena on saavuttaa noppia heittämällä "
                    "mahdollisimman monta erilaista lukujen yhdistelmää.\n "
                    "Yhdistelmien tulos merkitään pöytäkirjaan.\n Pöytäkirjan "
                    "täytyttyä voittaja on se pelaaja, jolla on korkeimmat "
                    "lopputulospisteet.").grid(row=0, column=2,rowspan=2,
                                               columnspan=1, sticky=E+W+N+S)
        Label(self.__ikkuna,borderwidth=2,relief=GROOVE,text="Valitse "
                                                        "pelaajien määrä:")\
            .grid(row=4,column=2,columnspan=2,sticky=E+W)

        self.__valikko = Spinbox(self.__ikkuna,from_=1,to=5,
                          state = NORMAL)
        self.__valikko.grid(row=5,column=2)

        Button(self.__ikkuna,text="Anna pelaajien nimet",command=
        self.tee_entryt).grid(row=6,column=2)

        self.__ikkuna.mainloop()



    def tee_entryt(self):
        """
        Kun pelaajien määrä on valittu niin tehdään vastaava määrä entryjä ja
        niiden perään pelin aloittava painike
        """
        pelaajien_määrä = int(self.__valikko.get())

        for i in range(pelaajien_määrä):
            entry = Entry()
            entry.grid(row=7+i,column=2)
            self.__entrylista.append(entry)
        Button(self.__ikkuna,text="Aloita peli",command=lambda x=pelaajien_määrä : self.aloita_peli(x))\
                .grid(row=7+pelaajien_määrä,column=2)



    def aloita_peli(self,pelaajien_määrä):
        """
        Kun käyttäjä on painanut "Aloita peli"-painiketta niin käyttäjän antamat
        nimet kerätään talteen ja mikäli jossain ruudussa ei ole nimeä niin siihen
        kohtaan laitetaan "Pelaaja" ja sen ruudun numero mistä nimi puuttuu
        """
        self.nimet = []
        for i in range(pelaajien_määrä):
            if self.__entrylista[i].get() == "":
                self.nimet.append("Pelaaja "+str(i+1))
            else:
                self.nimet.append(self.__entrylista[i].get())

        self.__ikkuna.destroy()





class Yatzy():
    def __init__(self,nimet):
        """
        Tässä luodaan tarvittavat muuttujat. Pisteiden laskua varten on
        tarkoituksellisesti kolme muuttujaa johtuen bonuksesta, jonka saa yläosan
        pisteiden perusteella muutenkin selitän muuttujat tarkemmin niissä
        kohdissa missä niitä tarvitaan
        """
        self.__ikkuna = Tk()
        self.__ikkuna.title("Yatzy")
        self.__ikkuna.option_add("*Font", "Verdana 10")
        self.__pelaajien_määrä = len(nimet)
        self.__vuorossa = 1
        self.__vuoroja = 0
        self.__heittokertoja = 3
        self.__silmäluvut = [0] * 5
        self.__yläosanpisteet = [0] * self.__pelaajien_määrä
        self.__alaosanpisteet = [0] * self.__pelaajien_määrä
        self.__nopat_käytössä = [True] * 5
        self.__summa = [0] * self.__pelaajien_määrä
        self.__nimet = nimet

        # Muodostetaan gif-kuvista PhotoImage-tyyppisiä olioita,
        # joita voidaan käyttää kuvana käyttöliittymän Label-elementeissä.
        # Tämä on otettu suoraan noppapeliesimerkistä

        self.__noppakuvat = []
        for kuvatiedosto in KUVATIEDOSTOT:
            kuva = PhotoImage(file=kuvatiedosto)
            self.__noppakuvat.append(kuva)

#----------------------------------------------------------------------------
        # Kuvien teon jälkeen lisätään viisi paikkaa nopille ikkunan yläosaan
        # ja asetetaan niihin aluksi "Yatzylogo" kuva
        # Noppien perään tulevat lukitus- , heitä- ja lopeta-painikkeet

        self.__alkukuva = PhotoImage(file="Yatzylogo.png")
        self.__noppakuvalabelit = []

        for i in range(5):
            uusi_label = Label(self.__ikkuna)
            uusi_label.grid(row=0, column=self.__pelaajien_määrä+2+i)
            self.__noppakuvalabelit.append(uusi_label)
            uusi_label.configure(image=self.__alkukuva)


        self.__lukitusnappulat = []
        for i in  range(5):
            lukitusnappula = Button(self.__ikkuna,background = "green",
                                    state = DISABLED,text="lukitse",
                                    command= lambda x=i :self.lukitse_noppa(x))
            lukitusnappula.grid(row=0, column=self.__pelaajien_määrä+7+i, sticky=W+E)
            self.__lukitusnappulat.append(lukitusnappula)


        self.__heitänappula = Button(self.__ikkuna, text="HEITÄ", command=self.heitä)
        self.__heitänappula.grid(row=1, column=self.__pelaajien_määrä+9 , sticky=W+E)

        Button(self.__ikkuna, text="UUSI PELI", command=self.kysy_varmistus)\
            .grid(row=2, column=self.__pelaajien_määrä+9 , sticky=W+E)
        Button(self.__ikkuna, text="LOPETA",command=self.__ikkuna.destroy)\
            .grid(row=3, column=self.__pelaajien_määrä+9 , sticky=W+E)

#----------------------------------------------------------------------------
        # Kirjoitetaan nyt tekstitiedostoon tallennetut huipputulokset
        # ja luodaan niistä Labelit. Käytän apumuuttuja rivin_numero muuttujaa,
        # joka pitää kirjaa rivin järjestysnumerosta

        try:
            tiedosto = open("Huipputulokset.txt","r",encoding="utf-8")
            rivin_numero = 1
            Label(self.__ikkuna,background = "white",text="Huipputulokset").\
                grid(row=7, column=self.__pelaajien_määrä+9,sticky=W+E)
            for rivit in tiedosto:
                rivit = rivit.strip()
                Label(self.__ikkuna,background = "white",
                      text=str(rivin_numero)+". "+str(rivit)).\
                    grid(row=8+rivin_numero, column=self.__pelaajien_määrä+9
                         ,sticky=W+E)
                rivin_numero += 1

        except IOError:
            print("Virhe: tiedostoa ei saa luettua.")

#----------------------------------------------------------------------------
        #Nyt tehdään taulukko, joka sisältää heitettävät tavoitteet ja
        #selitykset niistä noppien alapuolella sekä lisätään pelaajien nimet

        Label(self.__ikkuna,background="white",borderwidth=2, relief=GROOVE
              ,text="YATZY")\
            .grid(row=0, column=0, columnspan=2, sticky=E+W+N+S)
        Label(self.__ikkuna,background="chartreuse" ,text="Ykköset")\
            .grid(row=1, column=0, columnspan=2, sticky=E+W+N+S)
        Label(self.__ikkuna,background="chartreuse" ,
              text="Tavoite on saada 1–5 kappaletta 1-silmälukuja")\
            .grid(row=1, column=self.__pelaajien_määrä+2, columnspan=5, sticky=E+W)
        Label(self.__ikkuna,background="white" ,text="Kakkoset")\
            .grid(row=2, column=0, columnspan=2, sticky=E+W+N+S)
        Label(self.__ikkuna,background="white" ,
              text="Tavoite on saada 1–5 kappaletta 2-silmälukuja")\
            .grid(row=2, column=self.__pelaajien_määrä+2, columnspan=5, sticky=E+W)
        Label(self.__ikkuna,background="chartreuse" ,text="Kolmoset")\
            .grid(row=3, column=0, columnspan=2, sticky=E+W+N+S)
        Label(self.__ikkuna,background="chartreuse" ,
              text="Tavoite on saada 1–5 kappaletta 3-silmälukuja")\
            .grid(row=3, column=self.__pelaajien_määrä+2, columnspan=5, sticky=E+W)
        Label(self.__ikkuna,background="white" ,text="Neloset")\
            .grid(row=4, column=0, columnspan=2, sticky=E+W+N+S)
        Label(self.__ikkuna,background="white" ,
              text="Tavoite on saada 1–5 kappaletta 4-silmälukuja")\
            .grid(row=4, column=self.__pelaajien_määrä+2, columnspan=5, sticky=E+W)
        Label(self.__ikkuna,background="chartreuse" ,text="Vitoset")\
            .grid(row=5, column=0, columnspan=2, sticky=E+W+N+S)
        Label(self.__ikkuna,background="chartreuse" ,
              text="Tavoite on saada 1–5 kappaletta 5-silmälukuja")\
            .grid(row=5, column=self.__pelaajien_määrä+2, columnspan=5, sticky=E+W)
        Label(self.__ikkuna,background="white" ,text="Kutoset")\
            .grid(row=6, column=0, columnspan=2, sticky=E+W+N+S)
        Label(self.__ikkuna,background="white" ,
              text="Tavoite on saada 1–5 kappaletta 6-silmälukuja")\
            .grid(row=6, column=self.__pelaajien_määrä+2, columnspan=5, sticky=E+W)
        Label(self.__ikkuna,background="lime green" ,relief=GROOVE,
              text="Välisumma")\
            .grid(row=7, column=0, columnspan=2, sticky=E+W+N+S)
        Label(self.__ikkuna,background="lime green",relief=GROOVE,
              text="Yläosan yhdistelmistä saadut pisteet yhteensä")\
            .grid(row=7, column=self.__pelaajien_määrä+2, columnspan=5, sticky=E+W)
        Label(self.__ikkuna,background="lime green" , relief=GROOVE,
              text="Bonus")\
            .grid(row=8, column=0, columnspan=2, sticky=E+W)
        Label(self.__ikkuna,background="lime green" , relief=GROOVE,
              text="Mikäli välisumma on vähintään 63p niin +50p")\
            .grid(row=8, column=self.__pelaajien_määrä+2, columnspan=5, sticky=E+W)
        Label(self.__ikkuna,background="white" ,text="Pari")\
            .grid(row=9, column=0, columnspan=2, sticky=E+W+N+S)
        Label(self.__ikkuna,background="white" ,
              text="Tavoite on saada kaksi samaa silmälukua")\
            .grid(row=9, column=self.__pelaajien_määrä+2, columnspan=5, sticky=E+W)
        Label(self.__ikkuna,background="chartreuse" ,text="Kaksi paria")\
            .grid(row=10, column=0, columnspan=2, sticky=E+W+N+S)
        Label(self.__ikkuna,background="chartreuse",
              text="Tavoite on saada kaksi eri paria")\
            .grid(row=10, column=self.__pelaajien_määrä+2, columnspan=5, sticky=E+W)
        Label(self.__ikkuna,background="white" ,text="Kolme samaa")\
            .grid(row=11, column=0, columnspan=2, sticky=E+W)
        Label(self.__ikkuna,background="white",
              text="Tavoite on saada kolme samaa silmälukua")\
            .grid(row=11, column=self.__pelaajien_määrä+2, columnspan=5, sticky=E+W)
        Label(self.__ikkuna,background="chartreuse" ,text="Neljä samaa")\
            .grid(row=12, column=0, columnspan=2, sticky=E+W+N+S)
        Label(self.__ikkuna,background="chartreuse",
              text="Tavoite on saada neljä samaa silmälukua")\
            .grid(row=12, column=self.__pelaajien_määrä+2, columnspan=5, sticky=E+W)
        Label(self.__ikkuna,background="white" ,text="Pikku suora")\
            .grid(row=13, column=0, columnspan=2, sticky=E+W+N+S)
        Label(self.__ikkuna,background="white",
              text="Tavoite on saada silmäluvut 1, 2, 3, 4 ja 5")\
            .grid(row=13, column=self.__pelaajien_määrä+2, columnspan=5, sticky=E+W)
        Label(self.__ikkuna,background="chartreuse" ,text="Iso suora")\
            .grid(row=14, column=0, columnspan=2, sticky=E+W+N+S)
        Label(self.__ikkuna,background="chartreuse",
              text="Tavoite on saada silmäluvut 2, 3, 4, 5 ja 6")\
            .grid(row=14, column=self.__pelaajien_määrä+2, columnspan=5, sticky=E+W)
        Label(self.__ikkuna,background="white" ,text="Täyskäsi")\
            .grid(row=15, column=0, columnspan=2, sticky=E+W+N+S)
        Label(self.__ikkuna,background="white",
              text="Tavoite on saada yksi pari ja yksi kolmoisluku")\
            .grid(row=15, column=self.__pelaajien_määrä+2, columnspan=5, sticky=E+W)
        Label(self.__ikkuna,background="chartreuse" ,text="Sattuma")\
            .grid(row=16, column=0, columnspan=2, sticky=E+W+N+S)
        Label(self.__ikkuna,background="chartreuse",
              text="Tähän kelpaa ihan mikä vain")\
            .grid(row=16, column=self.__pelaajien_määrä+2, columnspan=5, sticky=E+W)
        Label(self.__ikkuna,background="white" ,text="Yatzy")\
            .grid(row=17, column=0, columnspan=2, sticky=E+W+N+S)
        Label(self.__ikkuna,background="white",
              text="Yatzy eli viisi samaa")\
            .grid(row=17, column=self.__pelaajien_määrä+2, columnspan=5, sticky=E+W)
        Label(self.__ikkuna,background="lime green" ,text="Summa")\
            .grid(row=18, column=0, columnspan=2, sticky=E+W+N+S)
        Label(self.__ikkuna,background="lime green",
              text="Pelaajan kokonaispistemäärä")\
            .grid(row=18, column=self.__pelaajien_määrä+2, columnspan=5, sticky=E+W)


        for i in range(self.__pelaajien_määrä):
            Label(self.__ikkuna,background="white",borderwidth=2, relief=GROOVE
              ,text=" "+self.__nimet[i]+" ")\
            .grid(row=0, column=2+i, columnspan=1, sticky=E+W+N+S)

#-----------------------------------------------------------------------------
        # Nyt luodaan nappulat, joita painetaan, kun pelaaja valitsee ruudun
        # Nappuloiden määrä riippuu pelaajista ja siksi täytyy käyttää
        # for-silmukkaa. Nappulat tallennetaan ensin listaan, joka sen jälkeen
        # tallennetaan dictiin käyttäen pelaajan numeroa avaimena

        self.__pistenappulat = {}

        for i in range(self.__pelaajien_määrä):
            nappulat = []
            nappula0 = Button(self.__ikkuna,background="chartreuse",
                             command= lambda x=i: self.merkitsepisteet(0,x+1))
            nappula0.grid(row=1, column=2+i, sticky=W+E)
            nappulat.append(nappula0)
            nappula1 = Button(self.__ikkuna,background="white",
                              command= lambda x=i :self.merkitsepisteet(1,x+1))
            nappula1.grid(row=2, column=2+i, sticky=W+E)
            nappulat.append(nappula1)
            nappula2 = Button(self.__ikkuna,background="chartreuse",
                              command= lambda x=i: self.merkitsepisteet(2,x+1))
            nappula2.grid(row=3, column=2+i, sticky=W+E)
            nappulat.append(nappula2)
            nappula3 = Button(self.__ikkuna,background="white",
                              command= lambda x=i : self.merkitsepisteet(3,x+1))
            nappula3.grid(row=4, column=2+i, sticky=W+E)
            nappulat.append(nappula3)
            nappula4 = Button(self.__ikkuna,background="chartreuse",
                             command=lambda x=i : self.merkitsepisteet(4,x+1))
            nappula4.grid(row=5, column=2+i, sticky=W+E)
            nappulat.append(nappula4)
            nappula5 = Button(self.__ikkuna,background="white",
                              command =lambda x=i : self.merkitsepisteet(5,x+1))
            nappula5.grid(row=6, column=2+i, sticky=W+E)
            nappulat.append(nappula5)
            label6 = Label(self.__ikkuna,background="lime green",relief=GROOVE,
                           text="0")
            label6.grid(row=7, column=2+i, sticky=W+E)
            nappulat.append(label6)
            label7 = Label(self.__ikkuna,background="lime green", relief=GROOVE)
            label7.grid(row=8, column=2+i, sticky=W+E)
            nappulat.append(label7)
            nappula8 = Button(self.__ikkuna,background="white",
                   command =lambda x=i : self.merkitsepisteet(8,x+1))
            nappula8.grid(row=9, column=2+i, sticky=W+E)
            nappulat.append(nappula8)
            nappula9 = Button(self.__ikkuna,background="chartreuse",
                              command =lambda x=i : self.merkitsepisteet(9,x+1))
            nappula9.grid(row=10, column=2+i, sticky=W+E)
            nappulat.append(nappula9)
            nappula10 = Button(self.__ikkuna,background="white",
                   command =lambda x=i : self.merkitsepisteet(10,x+1))
            nappula10.grid(row=11, column=2+i, sticky=W+E)
            nappulat.append(nappula10)
            nappula11 = Button(self.__ikkuna,background="chartreuse",
                               command =lambda x=i : self.merkitsepisteet(11,x+1))
            nappula11.grid(row=12, column=2+i, sticky=W+E)
            nappulat.append(nappula11)
            nappula12 = Button(self.__ikkuna,background="white",
                               command =lambda x=i : self.merkitsepisteet(12,x+1))
            nappula12.grid(row=13, column=2+i, sticky=W+E)
            nappulat.append(nappula12)
            nappula13 = Button(self.__ikkuna,background="chartreuse",
                               command =lambda x=i : self.merkitsepisteet(13,x+1))
            nappula13.grid(row=14, column=2+i, sticky=W+E)
            nappulat.append(nappula13)
            nappula14 = Button(self.__ikkuna,background="white",
                               command =lambda x=i : self.merkitsepisteet(14,x+1))
            nappula14.grid(row=15, column=2+i, sticky=W+E)
            nappulat.append(nappula14)
            nappula15 = Button(self.__ikkuna,background="chartreuse",
                               command =lambda x=i : self.merkitsepisteet(15,x+1))
            nappula15.grid(row=16, column=2+i, sticky=W+E)
            nappulat.append(nappula15)
            nappula16 = Button(self.__ikkuna,background="white",
                               command =lambda x=i : self.merkitsepisteet(16,x+1))
            nappula16.grid(row=17, column=2+i, sticky=W+E)
            nappulat.append(nappula16)
            label17 = Label(self.__ikkuna,background="lime green",text="0",
                            relief=GROOVE)
            label17.grid(row=18, column=2+i, columnspan=1, sticky=E+W)
            nappulat.append(label17)

            self.__pistenappulat[i] = nappulat


        self.__ikkuna.mainloop()



    def alusta_peli(self):

        # Tehdään kaikki alkuvalmistelut uutta peliä varten
        self.__vuorossa = 1
        self.__heittokertoja = 3
        self.__silmäluvut = [0] * 5
        self.__vuoroja = 0
        self.__heitänappula.configure(state = NORMAL)


        # Nollataan pelaajien pisteet (ylä- ja alaosa erikseen
        # bonuksen laskemiseksi)

        self.__yläosanpisteet = [0] * self.__pelaajien_määrä
        self.__alaosanpisteet = [0] * self.__pelaajien_määrä
        self.__summa = [0] * self.__pelaajien_määrä

        # Lukitus-painikkeet ovat ennen ensimmäistä heittoa DISABLED, jottei
        # ensimmäinen pelaaja voi käyttää edellisen pelin silmälukuja uudessa
        # pelissä. Ensimmäisen heiton jälkeen lukitus-painikkeet ovat
        # normaalisti käytössä

        for i in range(5):
            if not self.__nopat_käytössä[i]:
                self.lukitse_noppa(i)
            self.__lukitusnappulat[i].configure(state = DISABLED)

        # Tyhjennetään ruudukko edellisen pelin pisteistä
        for i in range(self.__pelaajien_määrä):
            for j in range(18):
                self.__pistenappulat[i][j].configure(text = "")
                self.__pistenappulat[i][j].configure(state = NORMAL)



    def kysy_varmistus(self):
        """
        Varmistetaan, että pelaaja todella haluaa aloittaa uuden pelin, eikä
        esim. vahingossa painanut "UUSI PELI"-painiketta
        """
        uusi_peli = messagebox.askyesno("Uusi peli","      Oletko varma?")
        if uusi_peli:
            self.alusta_peli()



    def lukitse_noppa(self,nopan_numero):
        # Muutetaan nopan tilaa lukituksi tai vapautetaan se
        # Nopan tila tarkistetaan nopat_käytössä listasta
        # True = Noppa lukitsematon; False = Noppa lukittu

        muutettava_nappula = self.__lukitusnappulat[nopan_numero]
        if self.__nopat_käytössä[nopan_numero]:
            muutettava_nappula.configure(background = "red",
                                                       text = "lukittu")
            self.__nopat_käytössä[nopan_numero] = False
        else:
            muutettava_nappula.configure(background = "green",
                                                           text = "lukitse")
            self.__nopat_käytössä[nopan_numero] = True



    def heitä(self):
        """
        Ensiksi tarkistetaan, että pelaajalla on heittokertoja jäljellä
        Tämän jälkeen tarkistetaan, ettei noppaa ole lukittu ja samalla
        vapautetaan lukitse-painike, joka voi olla DISABLED (esim. kun on
        pelaajan ensimmäinen vuoro)
        Itse heittäminen tapahtuu niin, että arvotaan kymmenen lukua, jotka
        näytetään ruudulla 0,05 sekunnin välein luoden vaikutelman heitosta.
        Viimeiseksi arvottu luku jää näytölle ja se tallennetaan myös muistiin
        self.__silmäluvut listaan
        """
        silmäluku = 0
        if self.__heittokertoja > 0:
            for i in range(5):
                if self.__nopat_käytössä[i]:
                    self.__lukitusnappulat[i].configure(state = NORMAL)
                    noppaLabel = self.__noppakuvalabelit[i]
                    for j in range(0, 10):
                        silmäluku = random.randint(1, 6)
                        noppaLabel["image"] = self.__noppakuvat[silmäluku - 1]

                        self.__ikkuna.update_idletasks()
                        time.sleep(0.05)
                    self.__silmäluvut[i] = silmäluku
            self.__heittokertoja += -1

        else:
            messagebox.showerror("Virhe!","Heittosi loppuivat, "
                                          "valitse jokin kohta taulukosta")



    def merkitsepisteet(self,rivi,pelaajan_numero):
        """
        :param rivi: Se kohta taulukosta, josta painettiin (esim. pari)
        :param pelaajan_numero: Kenen taulukossa valittu painike sijaitsee

        Ensiksi tarkistetaan, että pelaaja valitsi tavoitteen omasta
        taulukostaan. Seuraavaksi tarkistetaan, että pelaaja on heittänyt
        noppia vähintään kerran. Tämä siksi että näin pelaaja ei voi käyttää
        toisen heittämiä silmälukuja omalla vuorollaan
        Tarkistusten jälkeen haetaan pistenappuloiden listasta se painike, jota
        painettiin ja lasketaan pisteet erillisen funktion avulla
        """

        if pelaajan_numero != self.__vuorossa:
            messagebox.showinfo("Huom!","On pelaajan {:d} vuoro".
                                format(self.__vuorossa))
        elif self.__heittokertoja == 3:
            messagebox.showinfo("Huom!","Sinun on heitettävä noppia vähintään "
                                     "yksi kerta ")
        else:
            nappula = self.__pistenappulat[pelaajan_numero-1][rivi]
            pisteet = laskepisteet(rivi,self.__silmäluvut)


            # Pisteet lisätään joko yläosan tai alaosan pisteisiin
            # Lisäksi pelaaja voi saada 50p lisää mikäli yläosan
            # pisteet ovat yhteensä vähintään 63p (bonuksen saa vain kerran ja
            # siksi tarkistetaan, ettei pelaaja ole jo ylittänyt aiemmin 63p)

            if rivi >= 0 and rivi <= 5:
                self.__yläosanpisteet[pelaajan_numero-1] += pisteet
                yläosalabel = self.__pistenappulat[pelaajan_numero-1][6]
                yläosalabel.configure(text=self.__yläosanpisteet[pelaajan_numero-1])

                if self.__yläosanpisteet[pelaajan_numero-1] > 62 and \
                            self.__yläosanpisteet[pelaajan_numero-1] - pisteet < 63:
                    bonuslabel = self.__pistenappulat[pelaajan_numero-1][7]
                    bonuslabel.configure(text="50")
                    self.__alaosanpisteet[pelaajan_numero-1] += 50

            else:
                self.__alaosanpisteet[pelaajan_numero-1] += pisteet


            # Pisteet ovat jo muistissa, mutta ne lisätään nyt näkyviin
            # ruudukkoon ja vaihdetaan samalla vuorossa olevaa pelaajaa.
            # Vaihdettaessa pelaajaa heittokerrat palautetaan kolmeen ja
            # lukitus-nappulat otetaan pois käytöstä ja ne palautuvat käyttöön
            # jälleen, kun seuraava pelaaja heittää ensimmäistä kertaa noppia

            nappula.configure(text=pisteet)
            nappula.configure(state=DISABLED)
            self.__heittokertoja = 3
            if self.__vuorossa != self.__pelaajien_määrä:
                self.__vuorossa += 1
            else:
                self.__vuorossa = 1
                self.__vuoroja += 1

            for i in range(5):
                if not self.__nopat_käytössä[i]:
                    self.lukitse_noppa(i)
                self.__lukitusnappulat[i].configure(state = DISABLED)


            # Merkitään summa taulukkoon ja tallennetaan se muistiin

            summalabel = self.__pistenappulat[pelaajan_numero-1][17]
            summalabel.configure(text=self.__yläosanpisteet[pelaajan_numero-1]
                                      + self.__alaosanpisteet[pelaajan_numero-1])
            self.__summa[pelaajan_numero-1] = self.__yläosanpisteet[pelaajan_numero-1] \
                    + self.__alaosanpisteet[pelaajan_numero-1]

            # Tarkistetaan, että  onko peli jo loppunut eli onko jo kaikissa
            # ruuduissa jo jokin tulos. Tämä tapahtuu tutkimalla erikseen
            # tätä varten luotua self._vuoroja muuttujaa, jota on kasvatettu
            # aina yhdellä, kun viimeisen pelaajan vuoro on päättynyt (rivi 489)
            # Mikäli peli on loppunut vertaillaan pelaajien pisteitä ja
            # etsitään korkeimman yhteispistemäärän saanut henkilö, joka
            # kerrotaan erillisessä pop-up ikkunassa


            if self.__vuoroja == 15:
                voittajan_pisteet = self.__summa[0]
                voittajan_numero = 0

                for i in range(self.__pelaajien_määrä):
                    if voittajan_pisteet < self.__summa[i]:
                        voittajan_pisteet = self.__summa[i]
                        voittajan_numero = i

                messagebox.showinfo("Peli Loppui","Voittaja on {:s} "
                        " {:d} pisteellä".format(self.__nimet[voittajan_numero],voittajan_pisteet))

                self.tarkista_huipputulokset()
                self.__heitänappula.configure(state = DISABLED)



    def tarkista_huipputulokset(self):
        """
        Tarkistetaan, että ylsikö joku pelaaja/pelaajat huipputuloksiin
        ja otetaan pelaajan nimi ja paras sijoitus muistiin
        Tallennetaan myös kaikki vanhat tulokset ylös
        """

        tiedosto = open("Huipputulokset.txt","r",encoding="utf-8")
        vanhat_tulokset = []
        uudet_tulokset = {}
        uuden_huipputuloksen_saavuttaneet_pelaajat = []
        rivien_lukumäärä = 0

        for rivit in tiedosto:
            rivit = rivit.strip()
            rivi = rivit.split(":")
            vanhat_tulokset.append(rivit)
            for i in range(len(self.__nimet)):
                if self.__summa[i] > int(rivi[1]) and i not \
                        in uuden_huipputuloksen_saavuttaneet_pelaajat:

                    uudet_tulokset[rivien_lukumäärä] = self.__nimet[i]+\
                                        ":"+str(self.__summa[i])
                    uuden_huipputuloksen_saavuttaneet_pelaajat.append(i)

            rivien_lukumäärä += 1

        tiedosto.close()

        # Nyt kirjoitetaan tiedostoon huipputulokset ylös, vaikkei lista
        # olisi muuttunutkaan. Mikäli joku ylsi uuteen huipputulokseen,
        # hän löytyy uudet_tulokset-sanakirjasta, jonka avaimena
        # toimii paras sijoitus


        tiedosto2 = open("Huipputulokset.txt","w",encoding="utf-8")
        rivien_lukumäärä = 0
        for i in range(5):

            if rivien_lukumäärä == 5:
                break
            if i in uudet_tulokset:
                tiedosto2.write(uudet_tulokset[i]+"\n")
                messagebox.showinfo("Onneksi olkoon","Uusi huipputulos  "
                                                     ""+uudet_tulokset[i])
                rivien_lukumäärä += 1
                if rivien_lukumäärä < 5:
                    tiedosto2.write(vanhat_tulokset[i]+"\n")
                    rivien_lukumäärä += 1
            else:
                tiedosto2.write(vanhat_tulokset[i]+"\n")
                rivien_lukumäärä += 1

        tiedosto2.close()




def laskepisteet(rivi,silmäluvut):
    """
    :param rivi: rivi: Se kohta taulukosta, josta painettiin (esim. pari)
    :param silmäluvut: Lista, johon on tallennettu heitetyt silmäluvut
    :return: saadut pisteet
    Riveillä 0-5 yritetään saada yksittäisiä silmälukuja eli pisteet ovat
    suoraan kyseisten silmälukujen määrä kerrottuna silmäluvulla.
    Riveillä 8-16 on yhdistelmiä ja niiden tarkistamisen helpottamiseksi
    silmäluvut lista on järjestetty.
    Rivillä 8 etsitään paria ja mikäli niitä on kaksi suurempi jää voimaan
    Rivillä 9 kaksi paria: Tarkistetaan, että silmälukujen joukosta
    löytyy kaksi ERI paria
    Rivit 10 ja 11 etsitään kolmea tai neljää samaa silmälukua
    Riveillä 12 ja 13 ovat suorat. Tarkistetaan ensin ettei mikään noppa
    esiinny useammin kuin kerran. Mikäli tämä toteutuu, niin katsotaan
    summan avulla kumpi suora on kyseessä
    Rivillä 14 on täyskäsi tai "mökki" : Tarkistetaan ensin, että silmälukujen
    joukossa on kolme samaa ja lisäksi pari
    Rivillä 15 on sattuma eli noppien silmäluvut ovat vain summattu yhteen
    Rivillä 16 on Yatzy eli viisi samaa
    Yhdistelmät tarkistetaan, sillä mikäli silmäluvut eivät sisällä kyseistä
    yhdistelmää, pelaaja ei saa yhtään pistettä kyseisestä kohdasta


    """
    pisteet = 0

    if 0 <= rivi <= 5:
        pisteet = silmäluvut.count(rivi+1)*(rivi+1)

    elif 8 <= rivi <= 16:
        tarkistettava_noppa = 1
        for nopat in sorted(silmäluvut):
            if rivi == 8 and silmäluvut.count(nopat) >= 2:
                pisteet = nopat*2
            elif rivi == 9 and silmäluvut.count(nopat) == 2:
                for noppa in silmäluvut:
                    if silmäluvut.count(noppa) >= 2 and noppa!=nopat:
                        pisteet = noppa*2 + nopat*2
            elif rivi == 10 and silmäluvut.count(nopat) >= 3:
                pisteet = nopat*3
            elif rivi == 11 and silmäluvut.count(nopat) >= 4:
                pisteet = nopat*4
            elif rivi == 12 or rivi == 13:
                if silmäluvut.count(nopat) != 1:
                    break
                elif tarkistettava_noppa == 5 and sum(silmäluvut)==15 and \
                                rivi == 12:
                    pisteet = 15
                elif tarkistettava_noppa == 5 and sum(silmäluvut)==20 and \
                                rivi==13:
                    pisteet = 20
            elif rivi == 14 and silmäluvut.count(nopat) == 3:
                for noppa in silmäluvut:
                    if silmäluvut.count(noppa) == 2:
                        pisteet = noppa*2 + nopat*3
            elif rivi == 15:
                pisteet = sum(silmäluvut)
            elif rivi == 16 and silmäluvut.count(nopat) == 5:
                pisteet = 50
            tarkistettava_noppa += 1

    return pisteet



def main():
    lista = aloitusnäyttö()
    Yatzy(lista.nimet)



main()