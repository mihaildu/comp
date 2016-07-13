#include <iostream>

using namespace std;

int main(int argc, char* argv[]){

  int s = 1;
  for(int i = 3; i < 6; i = i + 2){
    s = s + 4*(i*i) - 6*(i-1);
  }
  
  cout << s << endl;

  return 0;
}
