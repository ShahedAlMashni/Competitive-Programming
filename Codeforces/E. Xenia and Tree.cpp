#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define se second
#define fi first
#define pb push_back
const int N = 1e6;
vector<vector<int>> v;
int n, m;
int dis[N], red[N], vis[N], dep[N], dp[N][20];
void bfs() {
	queue<int> q;
	memset(dis, 0, sizeof dis);
	memset(vis, 0, sizeof vis);
	for (int i = 1; i <= n; i++)
		if (red[i])
			q.push(i),vis[i]=1;
	while (q.size()) {
		int u = q.front();

		q.pop();
		for (int i = 0; i < v[u].size(); i++) {
			if (!vis[v[u][i]]) {
				q.push(v[u][i]);
				dis[v[u][i]] = dis[u] + 1;
				vis[v[u][i]]=1;
			}
		}
	}

}

void dfs(int u, int p) {
	dp[u][0] = p;
	for (int i = 0; i < v[u].size(); i++) {
		int x = v[u][i];
		if (x != p)
			dep[x] = dep[u] + 1, dfs(x, u);
	}
}
pair<int, int> qu[N];
int lca(int a, int b) {
	if (dep[a] < dep[b])
		swap(a, b);
	for (int i = 17; i >= 0; i--) {
		if (dep[a] - (1 << i) >= dep[b])
			a = dp[a][i];
	}
	if (a == b)
		return a;
	for (int k = 17; k >= 0; --k)
		if (dp[a][k] != dp[b][k])
			a = dp[a][k], b = dp[b][k];
	return dp[a][0];
}
int main() {
//	freopen("input.txt", "r", stdin);
	scanf("%d%d", &n, &m);
	v.resize(n + 1);
	red[1] = 1;
	for (int a, b, i = 0; i < n - 1; i++) {
		scanf("%d%d", &a, &b);
		v[a].pb(b), v[b].pb(a);
	}
	dfs(1, -1);
	for (int k = 1; k <= 17; k++)
		for (int i = 1; i <= n; i++)
			if (dp[i][k - 1] == -1)
				dp[i][k] = -1;
			else
				dp[i][k] = dp[dp[i][k - 1]][k - 1];
	int sz = sqrt(m);
	vector<int> r;
	for (int t, vv, i = 0; i < m; i++) {
		scanf("%d%d", &t, &vv);
		if (i % sz == 0)
			bfs(),r.clear();
		if (t == 1)
			red[vv] = 1, r.pb(vv);
		else {
			int mn = dis[vv];

			for (int j = 0; j < r.size(); j++)
				mn = min(mn, dep[vv] + dep[r[j]] - 2 * dep[lca(r[j], vv)]);
			printf("%d\n", mn);

		}
	}

	return 0;
}