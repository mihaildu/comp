#include <iostream>
#include <map>

using namespace std;

map<unsigned long long, unsigned long long>::iterator it;
map<unsigned long long, unsigned long long> _map;
unsigned long long gen(unsigned long long n);

unsigned long long _mmax;

int main(int argc, char* argv[]){

  unsigned long long i, _max = 0, res, mnr;
  _map[1] = 1;
  _mmax = 0;
  for (i = 2; i < 1000000; i++) {
    res = gen(i);
    if (res > _max) {
      _max = res;
      mnr = i;
    }
  }
  cout << mnr << ' ' << _max << endl;
  cout << _mmax << endl;
  return 0;
}

unsigned long long gen(unsigned long long n) {

  if (n == 1)
    return 1;

  unsigned long long nn = (unsigned long long) n;
  unsigned long long s = 1;
  while (nn > 1){

    if (nn > _mmax)
      _mmax = nn;

    if (nn % 2 == 0)
      nn = nn / 2;
    else
      nn = 3 * nn + 1;
    it = _map.find(nn);
    if (it != _map.end()){
      s = s + it->second;
      _map[n] = s;
      return s;
    }
    s = s + 1;
  }
  
  return 0;
}
