#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]){

  int N;
  ifstream fl;
  fl.open("p018_triangle.txt");

  N = 15;
  int a[N][N];

  // make it 0
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      a[i][j] = 0;

  for (int i = 0; i < N; i++){
    for (int j = 0; j < (i+1); j++)
      fl >> a[i][j];
  }

  for (int i = 1; i < N; i++){
    for (int j = 0; j < (i+1); j++){
      if (j == 0)
	a[i][j] = a[i][j] + a[i-1][j];
      else if (j == i)
	a[i][j] = a[i][j] + a[i-1][j-1];
      else if (a[i-1][j-1] > a[i-1][j])
	a[i][j] = a[i][j] + a[i-1][j-1];
      else
	a[i][j] = a[i][j] + a[i-1][j];
    }
  }

  int max = -1;
  for (int i = 0; i < N; i++)
    if (a[N-1][i] > max)
      max = a[N-1][i];

  cout << max << endl;
  fl.close();
  return 0;
}
