// problem link: https://codeforces.com/contest/1033/problem/F

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 7, M =  998244353;
int w, n, m, x, p[N], f[N];
int mp[N];
string s;
ll ans;
char a[N];
void go(int idx, int s = 0) {
	if (idx == w) {
		mp[s] += f[x];
		return;
	}
	int b = (x & (1 << (w - 1 - idx))) != 0;
	go(idx + 1, s + 2 * p[w - 1 - idx]);
	if (b)go(idx + 1, s + p[w - 1 - idx]);
	else go(idx + 1, s );
}
void calc(int idx, int a = 0, int b = 0) {
	if (idx == w) {
		ans += mp[a] * mp[b];
		return;
	}
	if (s[idx] == 'A') {
		calc(idx + 1, a + 2 * p[w - 1 - idx], b );
		calc(idx + 1, a , b + p[w - 1 - idx]);
	} else if (s[idx] == 'O')calc(idx + 1, a , b );
	else if (s[idx] == 'X') {
		calc(idx + 1, a , b );
		calc(idx + 1, a + p[w - 1 - idx], b + p[w - 1 - idx]);
	}
	else if (s[idx] == 'a') {
		calc(idx + 1, a + p[w - 1 - idx], b + p[w - 1 - idx]);
	}
	else if (s[idx] == 'o') {
		calc(idx + 1, a + 2 * p[w - 1 - idx], b + p[w - 1 - idx]);
		calc(idx + 1, a + p[w - 1 - idx], b );
	}
	else {
		calc(idx + 1, a , b + p[w - 1 - idx]);
		calc(idx + 1, a + p[w - 1 - idx], b );
	}
}
int main() {
	scanf("%d%d%d", &w, &n, &m);
	p[0] = 1;
	for (int i = 1; i <= w; i++)p[i] = p[i - 1] * 3;
	for (int  i = 0; i < n; i++) {
		scanf("%d", &x);
		f[x]++;
	}
	for (x = 0; x < (1 << w); x++) {
		if (!f[x])continue;
		go(0);
	}
	for (int i = 0; i < m; i++) {
		scanf("%s", a);
		s = a;
		ans = 0;
		calc(0);
		printf("%lld\n", ans);
	}
}