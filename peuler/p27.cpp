#include <iostream>
#include <cmath>
#include <boost/multiprecision/miller_rabin.hpp>

using namespace std;

using namespace boost::multiprecision;
using namespace boost::random;

bool check_prime(int n);

int main(int argc, char* argv[]){

  mt19937 gen2(clock());

  int a, b, n, l, lmax = 0, val, p = 0;
  for (a = -999; a < 1000; a++)
    for (b = 2; b < 1000; b++){
      n = 0, l = 0;
      while (true){
	val = n*n + a*n + b;
	if (miller_rabin_test(val,25,gen2) == 0)
	  break;
	l = l + 1;
	n = n + 1;
      }
      if (l > lmax){
	lmax = l;
	p = a * b;
      }
    }

  cout << p << endl;

  return 0;
}
