#include <iostream>
#include <gmpxx.h>

using namespace std;

int digits(mpz_class n);

int main(int argc, char* argv[]){

  int d, index = 2;
  mpz_class a = 1, b = 1, c;

  while (true){
    c = b;
    b = (a + b);
    a = c;
    d = digits(b);
    index = index + 1;
    if (d >= 1000){
      cout << index << endl;
      break;
    }
  }

  return 0;
}

int digits(mpz_class n){
  
  int s = 0;
  while (n > 0){
    n = n / 10;
    s = s + 1;
  }
  
  return s;
}
