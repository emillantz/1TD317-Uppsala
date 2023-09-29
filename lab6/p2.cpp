// TODO TESTFALL

#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

class Transaktion
{
private:
    string datum;
    string typ;
    string namn;
    double belopp;
    int antal_kompisar;
    string *kompisar;

public:
    Transaktion();
    ~Transaktion();
    Transaktion &operator=(const Transaktion &t);
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
    Person *personer;

public:
    PersonLista();
    ~PersonLista();
    PersonLista &operator=(const PersonLista &pl);
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
    Transaktion *transaktioner;

public:
    TransaktionsLista();
    ~TransaktionsLista();
    TransaktionsLista &operator=(const TransaktionsLista &tl);
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
    kompisar = nullptr;
}

Transaktion::~Transaktion()
{
    delete[] kompisar;
    kompisar = nullptr;
}

Transaktion &Transaktion::operator=(const Transaktion &t)
{
    if (this != &t)
    {
        delete[] kompisar;
        datum = t.datum;
        typ = t.typ;
        namn = t.namn;
        belopp = t.belopp;
        antal_kompisar = t.antal_kompisar;
        kompisar = new string[antal_kompisar];
        for (int i = 0; i < antal_kompisar; i++)
        {
            kompisar[i] = t.kompisar[i];
        }
    }
    return *this;
}

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
    for (int i = 0; i < antal_kompisar; i++)
    {
        if (kompisar[i] == namn)
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
    for (int i = 0; i < antal_kompisar; i++)
    {
        os << kompisar[i] << "\t";
    }
    os << endl;
}

bool Transaktion::lasIn(istream &is)
{
    delete[] kompisar;

    is >> datum >> typ >> namn >> belopp >> antal_kompisar;

    kompisar = new string[antal_kompisar];

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
    transaktioner = nullptr;
}

TransaktionsLista::~TransaktionsLista()
{
    delete[] transaktioner;
    transaktioner = nullptr;
}

TransaktionsLista &TransaktionsLista::operator=(const TransaktionsLista &tl)
{
    if (this != &tl)
    {
        delete[] transaktioner;
        antal_transaktioner = tl.antal_transaktioner;
        transaktioner = new Transaktion[antal_transaktioner];

        for (int i = 0; i < antal_transaktioner; i++)
        {
            transaktioner[i] = tl.transaktioner[i];
        }
    }
    return *this;
}

// Will only comment this method since the others are the same
void TransaktionsLista::laggTill(Transaktion &t)
{
    Transaktion *newTrans = nullptr;

    // Init new array with size+1
    newTrans = new Transaktion[antal_transaktioner + 1];

    // Copy everything over
    for (int i = 0; i < antal_transaktioner; i++)
    {
        newTrans[i] = transaktioner[i];
    }
    // Push t to new array and increment antal_transaktioner
    newTrans[antal_transaktioner] = t;
    antal_transaktioner++;

    // Delete and move pointer to new address
    delete[] transaktioner;
    transaktioner = newTrans;
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
    for (int i = 0; i < antal_transaktioner; i++)
    {
        total_kostnad += transaktioner[i].hamtaBelopp();
    }
    return total_kostnad;
}

double TransaktionsLista::liggerUteMed(const string &namn)
{
    double summa = 0.0;
    for (int i = 0; i < antal_transaktioner; i++)
        if (transaktioner[i].hamtaNamn() == namn)
        {
            int antal = transaktioner[i].hamtaAntalKompisar();
            double belopp = transaktioner[i].hamtaBelopp();

            summa += belopp * (1.0 - 1.0 / (antal + 1));
        }
    return summa;
}

double TransaktionsLista::arSkyldig(const string &namn)
{
    double summa = 0.0;
    for (int i = 0; i < antal_transaktioner; i++)
    {
        if (transaktioner[i].finnsKompis(namn))
        {
            int antal = transaktioner[i].hamtaAntalKompisar();
            double belopp = transaktioner[i].hamtaBelopp();

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

    for (int i = 0; i < antal_transaktioner; i++)
    {
        if (!personer.finnsPerson(transaktioner[i].hamtaNamn()))
        {
            namn = transaktioner[i].hamtaNamn();
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
    personer = nullptr;
}

PersonLista::~PersonLista()
{
    delete[] personer;
    personer = nullptr;
}

PersonLista &PersonLista::operator=(const PersonLista &pl)
{
    if (this != &pl)
    {
        delete[] personer;
        antal_personer = pl.antal_personer;
        personer = new Person[antal_personer];

        for (int i = 0; i < antal_personer; i++)
        {
            personer[i] = pl.personer[i];
        }
    }
    return *this;
}

void PersonLista::laggTill(Person ny_person)
{
    Person *nyPers = nullptr;
    nyPers = new Person[antal_personer + 1];

    for (int i = 0; i < antal_personer; i++)
    {
        nyPers[i] = personer[i];
    }

    nyPers[antal_personer] = ny_person;
    antal_personer++;

    delete[] personer;

    personer = nyPers;
}

double PersonLista::summaSkyldig()
{
    double summa = 0.0;
    for (int i = 0; i < antal_personer; i++)
    {
        summa += personer[i].hamtaSkyldig();
    }
    return summa;
}

double PersonLista::summaBetalat()
{
    double summa = 0.0;
    for (int i = 0; i < antal_personer; i++)
    {
        summa += personer[i].hamtaBetalat();
    }
    return summa;
}

bool PersonLista::finnsPerson(const string &namn)
{
    for (int i = 0; i < antal_personer; i++)
    {
        if (personer[i].hamtaNamn() == namn)
        {
            return true;
        }
    }
    return false;
}

void PersonLista::skrivUtOchFixa(ostream &os)
{
    for (int i = 0; i < antal_personer; i++)
    {
        personer[i].skrivUt(os);
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