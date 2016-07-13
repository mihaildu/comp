#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]){

  vector<int> digits(10);
  for (int i = 0; i < 10; i++)
    digits[i] = i;

  char s[11];
  int n = 999999, dig, f = 1;

  for (int i = 2; i < 10; i++)
    f = f * i;

  s[10] = '\0';

  for (int i = 0; i < 10; i++){
    dig = (n / f);
    s[i] = digits[dig] + '0';
    digits.erase(digits.begin()+dig);
    n = n - (dig * f);
    if (i != 9)
      f = f / (9-i);
  }

  cout << s << endl;
  return 0;
}
