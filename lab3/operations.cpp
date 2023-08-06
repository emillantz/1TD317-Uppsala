#include <iostream>
using namespace std;

// Functions
void skrivInfo();
int lasEttTal();
char lasOp();
void ordna(int &n1, int &n2);
int berakna(int n1, int n2, char operation);
void skrivResultat(int result);

int main()
{
    skrivInfo();
    int nbr1 = lasEttTal();
    int nbr2 = lasEttTal();
    ordna(nbr1, nbr2);
    char operation = lasOp();
    int result = berakna(nbr1, nbr2, operation);
    skrivResultat(result);
    return 0;
}

void skrivInfo()
{
    cout << "Programmet läser 2 tal samt en bokstav som representerar"
         << " vad som ska göras med talen." << endl;
}
int lasEttTal()
{
    int nbr;
    cout << "Mata in ett tal: ";
    cin >> nbr;
    return nbr;
}

char lasOp()
{
    char op;
    cout << "a: Addition \n"
         << "m: Multiplikation \n"
         << "k: Kvadratsumma \n";
    cout << "Mata in en bokstav: ";
    cin >> op;
    return op;
}

void ordna(int &n1, int &n2)
{
    if (n1 > n2)
    {
        int temp = n1;
        n1 = n2;
        n2 = temp;
    }
}

int berakna(int n1, int n2, char op)
{
    switch (op)
    {
    case 'a':
    {
        int sum = 0;
        for (int i = n1; i <= n2; i++)
        {
            sum += i;
        }
        return sum;
    }
    case 'm':
    {
        int product = 1;
        for (int i = n1; i <= n2; i++)
        {
            product *= i;
        }
        return product;
    }
    case 'k':
    {
        int quadSum = 0;
        for (int i = n1; i <= n2; i++)
        {
            quadSum += i * i;
        }
        return quadSum;
    }
    default:
        return 0;
    }
}
void skrivResultat(int result)
{
    cout << "Resultatet av beräkningen: " << result << endl;
}