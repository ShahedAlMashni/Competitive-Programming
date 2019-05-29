//problem link: https://codeforces.com/contest/1167/problem/E

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 7;
int n, x, a[N];
vector<int>v[N];
int maxL, minR;
int b[N], lst[N];
int ch(int pref, int suf) {
	pref = lst[pref];
	if (!pref)return 1;
	return suf > b[v[pref].back()];
}
int main() {
	scanf("%d%d", &n, &x);
	int mx = -1;
	for (int i = 0; i < n; ++i) {
		scanf("%d", &a[i]);
		v[a[i]].push_back(i);
		mx = max(mx, a[i]);
		b[i] = mx;
	}
	maxL = x;
	mx = -1;
	lst[0] = 0;
	for (int i = 1; i <= x; ++i) {
		lst[i] = lst[i - 1];
		if (v[i].size())lst[i] = i;
	}
	for (int i = 1; i <= x; ++i) {

		if (!v[i].size())continue;

		if (mx > v[i][0]) {
			maxL = i;
			break;
		}
		mx = v[i].back();
	}
	int mn = n;
	minR = 1;
	for (int i = x; i >= 1; i--) {
		if (!v[i].size())continue;
		if (mn < v[i].back()) {
			minR = i;
			break;
		}
		mn = v[i][0];
	}
	ll ans = 0;
	for (int i = 1; i <= maxL; ++i) {
		int l = max(i, minR), r = x, md, bst = -1;
		while (l <= r) {
			md = (l + r) / 2;
			if (ch(i - 1, md + 1)) {
				r = md - 1;
				bst = md;
			}
			else l = md + 1;
		}
		ans += (x - bst + 1);
	}
	cout << ans << endl;
}