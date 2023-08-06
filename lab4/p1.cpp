//
// Programskal till inlämningsuppgift 4 - deluppgift A
//
// Hanterar fallet med 26 bokstäver A-Z

#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
using namespace std;

// Använd gärna denna globala konstant i programmet
// i stället för värdet 26
const int ANTAL_BOKSTAVER = 26; // A-Z
// Globala variabler är ej tillåtna

//--------------------------------------------------------
// Funktionsdeklarationer:
// Använd exakt de funktionsnamn som finns nedan

// Funktionen berakna_histogram_abs
int berakna_histogram_abs(string text, int freq[]);
// Funktionen skriv_histogram_abs
void skriv_histogram_abs(int freq[], int total);
//--------------------------------------------------------
// Huvudprogram:

int main()
{
  // Deklarera variabler
  string text;
  int freq[ANTAL_BOKSTAVER] = {0};
  int total;

  // Läs in en rad med text från tangentbordet
  cout << "Skriv in text: ";
  getline(cin, text);

  // Anropa funktionen berakna_histogram_abs som beräknar histogrammet
  // och antalet bokstäver.
  total = berakna_histogram_abs(text, freq);
  // Anropa funktionen skriv_histogram_abs som skriver ut histogrammet
  skriv_histogram_abs(freq, total);

  return 0;
}

//--------------------------------------------------------
// Returns total number of characters in string. Increments freq[] for each instance of a letter.
int berakna_histogram_abs(string text, int freq[])
{
  int total = 0;
  for (char c : text)
  {
    // Converts c to lowercase
    char lowercase = tolower(c);
    // Checks if c is a letter (not, i.e. a space or punctuation)
    if (isalpha(lowercase))
    {
      // Since c is converted to lowercase, index for letter is taken by subtracting 97 (ASCII value of 'a').
      freq[lowercase - 97]++;
      total++;
    }
  }
  return total;
}

void skriv_histogram_abs(int freq[], int total)
{
  cout << "Histogram:" << endl;
  for (int i = 0; i < ANTAL_BOKSTAVER; i++)
  {
    if (freq[i] > 0)
    {
      // 65 is ASCII value of 'A'
      cout << (char)(i + 65) << ": " << freq[i] << endl;
    }
  }
}
// Redovisning av uppgiften i ord.
/**
 * Jag har använt bokstävernas ASCII-värden för att räkna ut index för varje bokstav i en array (Hade även kunnat lösas med en Map där bokstaven är
 * key och antalet förekomster är value, men vet inte om maps är tillåtna). Jag valde även att inte ha med bokstäver som inte förekommer i strängen i
 * histogrammet, eftersom jag tycker att det blir lättare att läsa.
 **/