#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <cstdlib>
#include <cstring>

using namespace std;


void solve(void);
void _solve(char* line);

int main(int argc, char* argv[]){
  solve();
  return 0;
}

#define LINESIZE 2000
ofstream of;

void solve(){

  ifstream fl;
  fl.open("f0.in");
  of.open("f0.out");

  int n, i;
  fl >> n;

  char tmp[LINESIZE];
  memset(tmp,0,LINESIZE);
  fl.getline(tmp,LINESIZE);

  for (i = 0; i < n; i++){
    //fl.getline(tmp,LINESIZE);
    //of << "Case #" << (i+1) << ": ";
    //_solve(tmp);
  }

  fl.close();
  of.close();
}


void _solve(char* line){

  string s(line);
  int sz = s.size();
}
