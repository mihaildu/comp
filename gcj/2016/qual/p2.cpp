#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <cstdlib>
#include <cstring>

using namespace std;


void solve(void);
long long _solve(char* line);

int main(int argc, char* argv[]){
  solve();
  return 0;
}

#define LINESIZE 2000
ofstream of;

void solve(){

  ifstream fl;
  fl.open("f2.in");
  of.open("f2.out");

  int n, i;
  long long flips;
  fl >> n;

  char tmp[LINESIZE];
  memset(tmp,0,LINESIZE);
  fl.getline(tmp,LINESIZE);

  for (i = 0; i < n; i++){
    fl.getline(tmp,LINESIZE);
    flips = _solve(tmp);
    of << "Case #" << (i+1) << ": " << flips << endl;
  }

  fl.close();
  of.close();
}


long long _solve(char* line){

  string s(line);
  int sz = s.size(), i;
  long long flips = 0;
  
  for (i = 0; i < sz; i++)
    if (s[i] == '-'){
      while ((s[i] == '-') && (i < sz))
	i = i + 1;
      flips = flips + 2;
    }

  if (s[0] == '-')
    flips = flips - 1;

  return flips;
}
