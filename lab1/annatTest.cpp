#include <iostream>
using namespace std;

int main()
{
  int a;
  int b = 12;
  a = 0; // Missing semicolon on ln8 => error: expected ';' after expression

  cout << "a = " << a << endl;
  cout << a + b << '\n'
       << "a-b = " << a - b << endl;

  return 0;
}
