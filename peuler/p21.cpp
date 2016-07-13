#include <iostream>
#include <cmath>

using namespace std;

int sum_div(int n);

int main(int argc, char* argv[]){

  int tmp, s = 0;
  for (int i = 2; i < 10000; i++){
    tmp = sum_div(i);
    if (tmp == i)
      continue;
    if (i == sum_div(tmp)){
      cout << i << ' ' << tmp << endl;
      s = s + i;
    }
  }

  cout << s << endl;

  return 0;
}

int sum_div(int n){

  int s = 1, l = sqrt(n);

  for (int i = 2; i < l; i++)
    if ((n % i) == 0)
      s = s + i + (n / i);

  return s;
}
