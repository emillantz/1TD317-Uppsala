// TODO TESTFALL

#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

const int MAX_PERSONER = 25;
const int MAX_TRANSAKTIONER = 25;

class Transaktion
{
private:
    string datum;
    string typ;
    string namn;
    double belopp;
    int antal_kompisar;
    string kompisar[MAX_PERSONER];

public:
    Transaktion();
    ~Transaktion();
    string hamtaNamn();
    double hamtaBelopp();
    int hamtaAntalKompisar();
    bool finnsKompis(const string &namn);
    bool lasIn(istream &is);
    void skrivUt(ostream &os);
    void skrivTitel(ostream &os);
};

class Person
{
private:
    string namn;
    double betalat_andras; // ligger ute med totalt
    double skyldig;        // skyldig totalt

public:
    Person();
    Person(const string &namn, double betalat_andras, double skyldig);
    string hamtaNamn();
    double hamtaBetalat();
    double hamtaSkyldig();
    void skrivUt(ostream &os);
};

class PersonLista
{
private:
    int antal_personer;
    Person personer[MAX_PERSONER];

public:
    PersonLista();
    ~PersonLista();
    void laggTill(Person ny_person);
    void skrivUtOchFixa(ostream &os);
    double summaSkyldig();
    double summaBetalat();
    bool finnsPerson(const string &namn);
};

class TransaktionsLista
{
private:
    int antal_transaktioner;
    Transaktion transaktioner[MAX_TRANSAKTIONER];

public:
    TransaktionsLista();
    ~TransaktionsLista();
    void lasIn(istream &is);
    void skrivUt(ostream &os);
    void laggTill(Transaktion &t);
    double totalKostnad();
    double liggerUteMed(const string &namn);
    double arSkyldig(const string &namn);
    PersonLista fixaPersoner();
};

int main()
{
    cout << "Startar med att läsa från en fil." << endl;

    TransaktionsLista transaktioner;
    ifstream is = ifstream("./tests/resa1.txt");
    transaktioner.lasIn(is);

    int operation = 1;
    while (operation != 0)
    {
        cout << endl;
        cout << "Välj i menyn nedan:" << endl;
        cout << "0. Avsluta. Alla transaktioner sparas på fil." << endl;
        cout << "1. Skriv ut information om alla transaktioner." << endl;
        cout << "2. Läs in en transaktion från tangentbordet." << endl;
        cout << "3. Beräkna totala kostnaden." << endl;
        cout << "4. Hur mycket är en viss person skyldig?" << endl;
        cout << "5. Hur mycket ligger en viss person ute med?" << endl;
        cout << "6. Lista alla personer mm och FIXA" << endl;

        cin >> operation;
        cout << endl;

        switch (operation)
        {
        case 1:
        {
            transaktioner.skrivUt(cout);
            break;
        }
        case 2:
        {
            Transaktion transaktion;
            cout << "Ange transaktion i följande format" << endl;
            transaktion.skrivTitel(cout);
            transaktion.lasIn(cin);
            transaktioner.laggTill(transaktion);
            break;
        }
        case 3:
        {
            cout << "Den totala kostnanden för resan var "
                 << transaktioner.totalKostnad() << endl;
            break;
        }
        case 4:
        {
            cout << "Ange personen: ";
            string namn;
            cin >> namn;
            double ar_skyldig = transaktioner.arSkyldig(namn);
            if (ar_skyldig == 0.)
                cout << "Kan inte hitta personen " << namn << endl;
            else
                cout << namn << " är skyldig " << ar_skyldig << endl;
            break;
        }
        case 5:
        {
            cout << "Ange personen: ";
            string namn;
            cin >> namn;
            double ligger_ute_med = transaktioner.liggerUteMed(namn);
            if (ligger_ute_med == 0.)
                cout << "Kan inte hitta personen " << namn << endl;
            else
                cout << namn << " ligger ute med " << ligger_ute_med << endl;
            break;
        }
        case 6:
        {
            cout << "Nu skapar vi en personarray och reder ut det hela!" << endl;
            PersonLista lista = transaktioner.fixaPersoner();
            lista.skrivUtOchFixa(cout);
            break;
        }
        }
    }
    cout << "Avslutar programmet och skriver alla transaktioner till filen ./tests/transaktioner.txt." << endl;
    ofstream os("./tests/transaktioner.txt");
    transaktioner.skrivUt(os);

    return 0;
}

// ==Transaktion== //
Transaktion::Transaktion()
{
    datum = "";
    typ = "";
    namn = "";
    belopp = 0;
    antal_kompisar = 0;
    for (int i = 0; i < MAX_PERSONER; i++)
    {
        kompisar[i] = "";
    }
}

Transaktion::~Transaktion() {}

string Transaktion::hamtaNamn()
{
    return this->namn;
}

double Transaktion::hamtaBelopp()
{
    return this->belopp;
}

int Transaktion::hamtaAntalKompisar()
{
    return this->antal_kompisar;
}

bool Transaktion::finnsKompis(const string &namn)
{
    for (string p : this->kompisar)
    {
        if (p == namn)
        {
            return true;
        }
    }
    return false;
}

void Transaktion::skrivTitel(ostream &os)
{
    os << "Datum \t Typ \t Namn \t Belopp \t Antal \t Lista över kompisar" << endl;
}

void Transaktion::skrivUt(ostream &os)
{
    // Not the prettiest thing i have done..
    os << datum << "\t" << typ << "\t" << namn << "\t" << belopp << "\t" << antal_kompisar << "\t";
    for (string name : kompisar)
    {
        os << name << "\t";
    }
    os << endl;
}

bool Transaktion::lasIn(istream &is)
{
    is >> datum >> typ >> namn >> belopp >> antal_kompisar;

    for (int i = 0; i < MAX_PERSONER; i++)
    {
        kompisar[i] = "";
    }

    for (int i = 0; i < antal_kompisar; i++)
    {
        is >> kompisar[i];
    }
    // Ensures Transaktionslista::lasIn() only stops at end-of-file
    return !is.eof();
}

// == TransaktionsLista == //
TransaktionsLista::TransaktionsLista()
{
    antal_transaktioner = 0;
}

TransaktionsLista::~TransaktionsLista() {}

void TransaktionsLista::laggTill(Transaktion &t)
{
    transaktioner[antal_transaktioner] = t;

    antal_transaktioner++;
}

void TransaktionsLista::lasIn(istream &is)
{
    Transaktion t;
    while (t.lasIn(is))
    {
        laggTill(t);
    }
}

void TransaktionsLista::skrivUt(ostream &os)
{
    for (int i = 0; i < antal_transaktioner; i++)
    {
        transaktioner[i].skrivUt(os);
    }
}

double TransaktionsLista::totalKostnad()
{
    double total_kostnad = 0;
    for (Transaktion t : transaktioner)
    {
        total_kostnad += t.hamtaBelopp();
    }
    return total_kostnad;
}

double TransaktionsLista::liggerUteMed(const string &namn)
{
    double summa = 0.0;
    for (Transaktion t : transaktioner)
        if (t.hamtaNamn() == namn)
        {
            int antal = t.hamtaAntalKompisar();
            double belopp = t.hamtaBelopp();

            summa += belopp * (1.0 - 1.0 / (antal + 1));
        }
    return summa;
}

double TransaktionsLista::arSkyldig(const string &namn)
{
    double summa = 0.0;
    for (Transaktion t : transaktioner)
    {
        if (t.finnsKompis(namn))
        {
            int antal = t.hamtaAntalKompisar();
            double belopp = t.hamtaBelopp();

            summa += (belopp / (antal + 1));
        }
    }
    return summa;
}

PersonLista TransaktionsLista::fixaPersoner()
{
    PersonLista personer;
    string namn;
    double betalat, skyldig;

    for (Transaktion t : transaktioner)
    {
        if (!personer.finnsPerson(t.hamtaNamn()))
        {
            namn = t.hamtaNamn();
            betalat = liggerUteMed(namn);
            skyldig = arSkyldig(namn);
            Person p(namn, betalat, skyldig);
            personer.laggTill(p);
        }
    }
    return personer;
}

// == Person == //
Person::Person()
{
    namn = "";
    betalat_andras = 0.0;
    skyldig = 0.0;
}

Person::Person(const string &namn, double betalat_andras, double skyldig)
{
    this->namn = namn;
    this->betalat_andras = betalat_andras;
    this->skyldig = skyldig;
}

string Person::hamtaNamn()
{
    return this->namn;
}

double Person::hamtaBetalat()
{
    return this->betalat_andras;
}

double Person::hamtaSkyldig()
{
    return this->skyldig;
}

void Person::skrivUt(ostream &os)
{
    os << namn << " ligger ute med " << betalat_andras << " och är skyldig " << skyldig;

    if (betalat_andras > skyldig)
    {
        os << ". Skall ha " << betalat_andras - skyldig << " från potten." << endl;
    }
    else if (betalat_andras < skyldig)
    {
        os << ". Skall lägga " << skyldig - betalat_andras << " till potten." << endl;
    }
    else
    {
        os << ". Skall varken lägga till eller ta från potten." << endl;
    }
}

// == PersonLista == //
PersonLista::PersonLista()
{
    antal_personer = 0;
}

PersonLista::~PersonLista() {}

void PersonLista::laggTill(Person ny_person)
{
    personer[antal_personer] = ny_person;
    antal_personer++;
}

double PersonLista::summaSkyldig()
{
    double summa = 0.0;
    for (Person p : personer)
    {
        summa += p.hamtaSkyldig();
    }
    return summa;
}

double PersonLista::summaBetalat()
{
    double summa = 0.0;
    for (Person p : personer)
    {
        summa += p.hamtaBetalat();
    }
    return summa;
}

bool PersonLista::finnsPerson(const string &namn)
{
    for (Person p : personer)
    {
        if (p.hamtaNamn() == namn)
        {
            return true;
        }
    }
    return false;
}

void PersonLista::skrivUtOchFixa(ostream &os)
{
    for (Person p : personer)
    {
        if (p.hamtaNamn() != "")
        {
            p.skrivUt(os);
        }
    }

    // Floats are dumb
    double epsilon = 1e-8;
    double abs = fabs(summaSkyldig() - summaBetalat());

    if (abs < epsilon)
    {
        os << "Allt stämmer!" << endl;
    }
    else
    {
        os << "Någon har fifflat med bokföringen!\n"
           << "Det skiljer " << abs << " kronor" << endl;
    }
}