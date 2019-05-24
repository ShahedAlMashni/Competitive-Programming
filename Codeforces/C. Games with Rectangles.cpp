// problem link : https://codeforces.com/problemset/problem/128/C

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 7, M = 1000000007;
int n, m, k;
int pp(int n, int p) { // fast power
	if (!p)return 1;
	int ret = pp(n, p / 2);
	if (p & 1) return ((ret * 1LL * ret) % M * 1LL * n) % M;
	return (ret * 1LL * ret) % M;
}
int nCr(int n, int r) { //N choose R
	int f1 = 1, f2 = 1;
	for (int i = 1; i <= r; i++) {
		f1 = (f1 * 1LL * i) % M;
	}
	for (int i = n; i > n - r; i--) {
		f2 = (f2 * 1LL * i) % M;
	}
	return (f2 * 1LL * pp(f1, M - 2)) % M;
}
int main() {
	cin >> n >> m >> k;
	if ((n - 1 < 2 * k) || (m - 1 < 2 * k))return puts("0"), 0;
	/*  _______
       |_|_|_|_|
       |_|_|_|_|
       |_|_|_|_|
      solve each dimension independently
      for m=4
      we can define a sequence of pairs
      [0,4],[1,3]..
      each pair represents the lower and upper boundaries of a rectangle's width
      write all numbers in the sequence in sorted order 0,1,2,3,4
      a sequence of k pairs has 2*k unique numbers,so to form a valid sequence, choose 2*k 
      elements from 1,,,m-1 , every possible combination of chosen elements forms only 
      one valid sequence

	*/
	cout << (nCr(n - 1, 2 * k) * 1LL * nCr(m - 1, 2 * k)) % M << endl;


}