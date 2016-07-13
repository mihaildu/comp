#include <iostream>
#include <cmath>
#include <map>

using namespace std;

map<int,bool> map_abun;
map<int,bool>::iterator it1, it2;

int sum_div(int n);

int main(int argc, char* argv[]){

  int tmp, s = 0, count = 0, c2 = 0;
  for (int i = 12; i < 28123; i++){
    tmp = sum_div(i);
    if (tmp > i){
      map_abun[i] = true;
      c2 = c2 + 1;
    }
  }

  bool flag;
  for (int i = 1; i < 28123; i++){
    flag = false;
    for (int j = 12; j < i; j++){
      it1 = map_abun.find(j);
      it2 = map_abun.find(i-j);
      if ((it1 != map_abun.end()) && (it2 != map_abun.end())){
	flag = true;
	break;
      }
    }
    if (flag == false){
      s = s + i;
      count = count + 1;
    }
  }

  cout << s << endl;
  cout << count << endl;
  return 0;
}

int sum_div(int n){

  int s = 1, l = sqrt(n);

  for (int i = 2; i <= l; i++)
    if ((n % i) == 0)
      s = s + i + (n / i);

  if ((l*l) == n)
    s = s - l;

  return s;
}
