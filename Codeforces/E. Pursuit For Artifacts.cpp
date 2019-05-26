#include<iostream>
#include<stdio.h>
#include<vector>
#include<queue>
#include<string>
#include<stack>
#include<algorithm>
#include<memory.h>
#include<set>
#include<map>
#include<cmath>
#include<time.h>
#include<iomanip>
#include<time.h>
using namespace std;
typedef long long ll;
#define se second
#define fi first
#define pb push_back
const int N = 1e6 + 5, M = 1e9 + 7;
const double PI = acos(-1);
int n, m, a, b,t,has[N],cc[N];
vector<pair<int,int>>v[N],g[N];
int l[N], d[N], vis[N];
map<pair<int, int>, int>mp;
void dfs(int u, int p) {
	l[u] = d[u] = ++t;
	vis[u] = 1;
	for (int i = 0; i < v[u].size(); i++) {
		int x = v[u][i].fi;
		if (!vis[x]) {
			dfs(x, u);
			l[u] = min(l[u], l[x]);
			if (l[x] > d[u])
				mp[{ min(u, x), max(u, x) }] = 1;
		}
		else if (x != p) {
			l[u] = min(l[u], d[x]);
		}
	}
}
void go(int u, int p,int c) {
	vis[u] = 1;
	cc[u] = c;
	for (int i = 0;i < v[u].size();i++) {
		int x = v[u][i].first;
		if (!mp[{min(u, x), max(u, x)}]) {
			if(!vis[x])
			go(x, u,c);
			has[c] += v[u][i].second;
		}
	}
}
int find(int u, int p, int fe) {
	if (u == cc[b])return fe;
	for (int i = 0;i < g[u].size();i++) {
		int x = g[u][i].first;
		int y = g[u][i].second;
		if (x!=p && find(x, u,fe+has[x] + has[u] + y))return 1;
	}
	
	return 0;
}
int main() {
	scanf("%d%d", &n, &m);
	for (int x,y,z,i = 0;i < m;i++) {
		scanf("%d%d%d", &x, &y, &z);
		v[x].pb({ y,z });
		v[y].pb({ x,z });
	}
	scanf("%d%d", &a, &b);
	dfs(1, -1);
	memset(vis, 0, sizeof vis);
	t = 0;
	for (int i = 1;i <= n;i++) 
		if (!vis[i]) {
			go(i, -1,++t);
		}
	

	for(int i=1;i<=n;i++)
		for (int j = 0;j < v[i].size();j++) {
			int x = v[i][j].first;
			if (cc[i] != cc[x])g[cc[i]].pb({ cc[x],v[i][j].second });
		}
	if (find(cc[a], -1, has[cc[a]])) puts("YES");
	else puts("NO");
	
	

}