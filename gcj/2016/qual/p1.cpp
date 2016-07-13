#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <cstdlib>
#include <cstring>
#include <map>

using namespace std;

map<int,bool> _map;

void solve(void);
long long _solve(long long nr);

int main(int argc, char* argv[]){
  solve();
  return 0;
}

#define LINESIZE 2000
ofstream of;

void solve(){

  ifstream fl;
  fl.open("f2.in");
  of.open("f3.out");

  int i, nr;
  long long n, res;
  fl >> n;

  for (i = 0; i < n; i++){
    _map.clear();
    fl >> nr;
    res = _solve(nr);
    if (res < 0)
      of << "Case #" << (i+1) << ": INSOMNIA" << endl;
    else
      of << "Case #" << (i+1) << ": " << res << endl;
  }

  fl.close();
  of.close();
}


void print_map(void){
  int i;
  map<int,bool>::iterator it;
  for (i = 0; i < 10; i++){
    it = _map.find(i);
    if (it != _map.end()){
      cout << i << ' ';
    }
    cout << endl;
  }
}

long long _solve(long long nr){

  if (nr == 0)
    return -1;

  bool stop;
  map<int,bool>::iterator it;
  int dig, m = 2, i, cnt = 0;
  long long nr_cpy1, nr_cpy2 = nr;
  while (true){
    stop = true;
    nr_cpy1 = nr_cpy2;
    while (nr_cpy1 > 0){
      dig = nr_cpy1 % 10;
      _map[dig] = true;
      nr_cpy1 = nr_cpy1 / 10;
    }

    // check for completion
    for (i = 0; i < 10; i++){
      it = _map.find(i);
      if (it == _map.end()){
	stop = false;
	break;
      }
    }

    if (stop == true)
      return nr_cpy2;
    nr_cpy2 = nr * m;
    m = m + 1;
  }
  return -1;
}
