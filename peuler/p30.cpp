#include <iostream>
#include <cmath>

using namespace std;

int sum_digits(int n);

int main(int argc, char* argv[]){

  int s = 0;
  for(int i = 2; i < 1000000; i++)
    if (i == sum_digits(i))
      s = s + i;

  cout << s << endl;

  return 0;
}

int sum_digits(int n){

  int s = 0;
  while (n > 0){
    s = s + pow((n % 10),5);
    n = n / 10;
  }
  return s;
}
