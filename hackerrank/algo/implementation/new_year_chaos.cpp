#include <iostream>
#include <vector>

using namespace std;

void printv(vector<int> v){
  int sz = v.size();
  for (int i = 0; i < sz; i++)
    cout << v[i] << ' ';
  cout << endl;
}

bool check_chaotic(int* a, int n);
void solve_slow(int* a, int n);
int solve_fast(int* a, int n);

int main(int argc, char* argv[]){

  int a[] = {1, 2, 5, 4, 3}, n = 5;
  if (check_chaotic(a,n) == true)
    return 0;
  
  cout << solve_fast(a,n) << endl;
  return 0;
}

bool check_chaotic(int* a, int n){
  for (int i = 0; i < n; i++){
    if ((a[i] - i - 1) > 2){
      cout << "Too chaotic" << endl;
      return true;
    }
  }
  return false;
}

int solve_fast(int* a, int n){

  int tmp, sz, inv;
  
  if (n == 1)
    return 0;

  if (n == 2){
    if (a[0] > a[1]){
      tmp = a[0];
      a[0] = a[1];
      a[1] = tmp;
      return 1;
    }
    return 0;
  }
  
  sz = n / 2;
  inv = solve_fast(a,sz);
  inv = inv + solve_fast(a+sz,(n+1)/2);

  int il = 0, ir = sz;
  vector<int> new_a(n);
  for (int i = 0; i < n; i++){
    if (il == sz){
      new_a[i] = a[ir];
      ir = ir + 1;
      continue;
    }
    if (ir >= n){
      new_a[i] = a[il];
      il = il + 1;
      continue;      
    }
    if (a[il] <= a[ir]){
      new_a[i] = a[il];
      il = il + 1;
    }
    else{
      inv = inv + (sz - il);
      new_a[i] = a[ir];
      ir = ir + 1;
    }
  }
  
  for (int i = 0; i < n; i++)
    a[i] = new_a[i];

  return inv;
}

void solve_slow(int* a, int n){

  int s = 0, val;
  vector<int> bribes(n);
  for (int i = 0; i < n; i++)
    for (int j = (i+1); j < n; j++)
      if (a[i] > a[j]){
	s = s + 1;
        val = a[i] - 1;
	bribes[val] += 1;
	if (bribes[val] > 2){
	  cout << "Too chaotic" << endl;
	  return;
	}
      }

  cout << s << endl;
}
