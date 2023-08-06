//
// Programskal till inl�mningsuppgift 4 - deluppgift B
//
// Hanterar fallet med 26 bokst�ver A-Z

#include <string>
#include <cctype>
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

// Globala konstanter:

// Tips: Använd de globala konstanterna ANTAL_BOKSTAVER och ANTAL_SPRAK
// istället för värdena 26 och 4 i programmet.
const int ANTAL_BOKSTAVER = 26; // A-Z
const int ANTAL_SPRAK = 4;

// 2d-arrayen TOLK_HJALP innehåller bokstavsfrekvensen i %
// för fyra språk. TOLK_HJALP[0][0] är frekvensen av
// bokstaven a för engelska. TOLK_HJALP[0][25] är frekvensen av
// bokstaven z för engelska.
// Arrayen är en GLOBAL KONSTANT och skall alltså ej skickas
// som parameter till den funktion som behöver den.
const double TOLK_HJALP[ANTAL_SPRAK][ANTAL_BOKSTAVER] =
    {{8.27, 1.48, 2.94, 4.03, 11.78, 2.22, 1.72, 6.77, // engelska
      7.39, 0.12, 0.81, 3.76, 2.85, 6.71, 7.79, 1.54,
      0.05, 5.95, 6.69, 9.07, 2.66, 1.13, 2.14, 0.19,
      1.89, 0.03},
     {7.97, 1.40, 3.55, 3.79, 16.89, 1.02, 1.00, 0.75, // franska
      7.08, 0.38, 0.04, 5.51, 2.82, 8.11, 5.19, 2.78,
      1.01, 6.69, 8.35, 7.22, 6.09, 1.35, 0.02, 0.54,
      0.30, 0.15},
     {9.50, 1.11, 1.53, 5.30, 8.94, 1.74, 3.57, 3.94, // svenska
      3.98, 0.89, 3.26, 4.93, 3.41, 8.46, 5.01, 1.77,
      0.00, 6.73, 5.56, 9.20, 1.94, 2.42, 0.00, 0.05,
      0.45, 0.00},
     {5.12, 1.95, 3.57, 5.07, 16.87, 1.35, 3.00, 5.79, // tyska
      8.63, 0.19, 1.14, 3.68, 3.12, 10.64, 1.74, 0.42,
      0.01, 6.30, 6.99, 5.19, 3.92, 0.77, 1.79, 0.01,
      0.69, 1.24}};

// Globala variabler är ej tillåtna

//--------------------------------------------------------
// Funktionsdeklarationer:

// Deklarationer av dina egna funktioner
// Använd exakt de funktionsnamn som finns nedan

// Funktionen berakna_histogram_abs
// denna skrevs i A-uppgiften och kan klippas in här
int berakna_histogram_abs(string text, double histogram[]);
// Funktionen abs_till_rel
void abs_till_rel(double histogram[], int total);
// Funktionen plotta_histogram_rel
void plotta_histogram_rel(double histogram[]);
// Funktionen tolkning
void tolkning(double histogram[]);
// Funktionen namn_pa_fil
string namn_pa_fil();
// Funktionen inlasning
string inlasning(ifstream &buf);
//--------------------------------------------------------
// Huvudprogram:

int main()
{
  double histogram[ANTAL_BOKSTAVER] = {0};

  string filename = namn_pa_fil();
  ifstream buf = ifstream(filename);

  if (!buf)
  {
    cout << "Filen kunde inte öppnas" << endl;
    return 0;
  }

  string text = inlasning(buf);

  int total = berakna_histogram_abs(text, histogram);

  abs_till_rel(histogram, total);

  cout << endl;

  plotta_histogram_rel(histogram);

  cout << endl;

  tolkning(histogram);

  return 0;
}

//--------------------------------------------------------
// Funktionsdefinitioner:

// Same as part A
int berakna_histogram_abs(string text, double freq[])
{
  int total = 0;
  for (char c : text)
  {
    char lowercase = tolower(c);
    if (isalpha(lowercase))
    {
      freq[lowercase - 97]++;
      total++;
    }
  }
  return total;
}

string namn_pa_fil()
{
  string filename;
  cout << "Ange filnamn: ";
  getline(cin, filename);
  // Append .txt if it is not the last 4 characters of the file name.
  if (filename.length() - filename.rfind(".txt") != 4)
  {
    filename.append(".txt");
  }
  return filename;
}

string inlasning(ifstream &buf)
{
  string text;
  char c;
  while (buf.get(c))
  {
    text.push_back(c);
  }
  return text;
}

void abs_till_rel(double histogram[], int total)
{
  for (int i = 0; i < ANTAL_BOKSTAVER; i++)
  {
    histogram[i] = histogram[i] / total * 100;
  }
}

void plotta_histogram_rel(double histogram[])
{
  cout << "Bokstavsfördelning:" << endl;
  for (int i = 0; i < ANTAL_BOKSTAVER; i++)
  {
    cout << (char)(i + 97) << ": ";
    int trunc = histogram[i] / 0.5;
    for (int j = 0; j < trunc; j++)
    {
      cout << "*";
    }
    cout << endl;
  }
  return;
}

void tolkning(double histogram[])
{
  double quad[ANTAL_SPRAK];
  for (int i = 0; i < ANTAL_SPRAK; i++)
  {
    for (int j = 0; j < ANTAL_BOKSTAVER; j++)
    {
      quad[i] += (histogram[j] - TOLK_HJALP[i][j]) * (histogram[j] - TOLK_HJALP[i][j]);
    }
  }
  string langs[ANTAL_SPRAK] = {"engelska", "franska", "svenska", "tyska"};
  double min = __INT_MAX__;
  int minIndex = 0;

  for (int i = 0; i < ANTAL_SPRAK; i++)
  {
    cout << langs[i] << ": " << quad[i] << endl;

    if (quad[i] < min)
    {
      min = quad[i];
      minIndex = i;
    }
  }
  cout << "Det är mest troligt att språket är " << langs[minIndex] << "." << endl;
  return;
}
// -------------------------------------------------------
// Rapport om uppgiften
// Tolkningsfunktionen blev ganska rörig, hoppas att den inte gör allt för ont att läsa. Annars är det typ samma logik som i A-uppgiften, förutom att
// bokstäver med 0 frekvens skrivs ut i det plottade histogrammet (eftersom att det såg ut så i exemplena i canvas).
