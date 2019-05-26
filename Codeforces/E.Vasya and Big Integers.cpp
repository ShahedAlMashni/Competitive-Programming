//problem link: https://codeforces.com/contest/1051/problem/E

#include <bits/stdc++.h>
using namespace std;
const int N = 3e6 + 7, M = 998244353;
string l, a, r, tmp;
int ll, rr, n;
int to[N], mx[N], dp[N], arr1[N], arr2[N];
int sm[N];
void Z_function(int *z) {
//z[i] is the length of the longest substring starting at tmp[i]
//which is also a prefix of tmp[i]
	int n = tmp.size();
	int L = 0, R = 0;
	for (int i = 1; i < n; i++) {
		if (i > R) {
			L = R = i;
			while (R < n && tmp[R - L] == tmp[R]) R++;
			z[i] = R - L; R--;
		}
		else {
			int k = i - L;
			if (z[k] < R - i + 1) z[i] = z[k];
			else {
				L = i;
				while (R < n && tmp[R - L] == tmp[R]) R++;
				z[i] = R - L; R--;
			}
		}
	}
}
int check_if_greater(int st, int ed) {
	//return 1 if a[st-ed]>=l
	if (ed - st + 1 < l.size())return 0; //smaller size
	if (ed - st + 1 > l.size())return 1;
	//size is equal
	int x = arr1[st + l.size() + 1];
	// x is the length of the longest prefix of a[st] that matches prefix of L
	if (x == l.size())return 1; //equals to L
	if (a[st + x] < l[x])return 0;
	return 1;
}
int check_if_smaller(int st, int ed) {
	//similar to above
	if (ed - st + 1 > r.size())return 0;
	if (ed - st + 1 < r.size())return 1;
	int x = arr2[st + r.size() + 1];
	if (x == r.size())return 1;
	if (a[st + x] > r[x])return 0;
	return 1;

}
int main() {
	cin >> a >> l >> r;
	tmp = l + '#' + a;
	Z_function(arr1); //generate array Z for prefix L
	tmp = r + '#' + a;
	Z_function(arr2); //generate array Z for prefix R
	n = a.size();
	memset(to, -1, sizeof to);
	memset(mx, -1, sizeof mx);
//to[i] minimum position where a[i-to[i]] will be >= L
//mx[i] maximum position where a[i-mx[i]] will be <= R
	for (int i = 0; i < n; i++) {
		if (a[i] == '0') {
			// dont want leading zeros
			if (l == "0") {
				//will only accept partition "0" if L="0"
				to[i] = i, mx[i] = i;
			}
			continue;
		}
		int l = i, r = n - 1, md;

		//binary search on the right positions
		while (l <= r) {
			md = (l + r) / 2;
			if (check_if_greater(i, md)) {
				r = md - 1;
				to[i] = md;
			}
			else l = md + 1;
		}
		l = i, r = n - 1, md;
		while (l <= r) {
			md = (l + r) / 2;
			if (check_if_smaller(i, md)) {
				l = md + 1;
				mx[i] = md;
			}
			else r = md - 1;
		}
	}
	dp[n] = 1;
	sm[n] = 1; // suffix summation of dp[i]
	// let dp[i] be the number of correct partitions for the long integer a[i-n]
	for (int i = n - 1; i >= 0; i--) {
		if (to[i] == -1 || mx[i] == -1 || to[i] > mx[i]) {
			sm[i] = sm[i + 1];
			continue;
		}
		// we can divide a new partition starting at i, and ending [to[i],mx[i]]
		// dp[i] equals the sum of of dp[to[i]+1] till dp[mx[i]+1]
		dp[i] = (sm[to[i] + 1] - sm[mx[i] + 2] + M) % M;
		sm[i] = (dp[i] + sm[i + 1]) % M;
	}
	cout << dp[0] << endl;
}