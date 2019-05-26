#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 3e5 + 9;
double SIN[N], COS[N];
int n, m;
struct mat {
	double M[3][3];
	mat() {
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)M[i][j] = 0;
	}
	mat operator *(mat x) {
		mat ret;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++) {
				for (int k = 0; k < 3; k++)
					ret.M[i][j] += M[i][k] * x.M[k][j] ;
			}
		return ret;
	}
};
struct node {
	double m[3][1];
	node() {
		for (int i = 0; i < 3; i++)
			m[i][0] = 0;
	}
	node operator +(node x)const {
		node ret;
		for (int i = 0; i < 3; i++)
			ret.m[i][0] = m[i][0] + x.m[i][0];
		return ret;
	}
	node operator *(mat x) {
		node ret;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++) {
				ret.m[i][0] += x.M[i][j] * m[j][0] ;
			}
		return ret;
	}
};
node seg[4 * N], a[4 * N];
mat lazy[4 * N], I;
bool lazyf[4 * N];
node Z;
void build(int p, int s, int e) {
	if (s == e) {
		seg[p] = a[s];
		lazy[p] = I;
		return;
	}
	build(2 * p, s, (s + e) / 2);
	build(2 * p + 1, (s + e) / 2 + 1, e);
	lazy[p] = I;
}
void fix(int p, int s, int e) {
	if (!lazyf[p])return;
	seg[p] =  seg[p] * lazy[p] ;
	if (s != e)
	{
		lazy[p * 2 ] =  lazy[p] * lazy[p * 2]  ;
		lazy[p * 2 + 1] =  lazy[p] * lazy[p * 2 + 1];
		lazyf[2 * p] = lazyf[2 * p + 1] = 1;
	}

	lazy[p] = I;
	lazyf[p] = 0;
}
void update(int p, int s, int e, int l, int r, mat val)
{
	fix(p, s, e);
	if (s > r || e < l)
		return;
	if (s >= l && e <= r)
	{
		//cout<<s<<" "<<e<<endl;
		lazy[p] =   val * lazy[p];
		// for(int i=0;i<3;i++){
		// 	for(int j=0;j<3;j++)cout<<lazy[p].M[i][j]<<" ";
		// 	cout<<endl;
		// }
		lazyf[p]=1;
		fix(p, s, e);
		return;
	}
	update(p * 2 , s, (s + e) / 2, l, r, val);
	update(p * 2 + 1, (s + e) / 2 + 1, e, l, r, val);
}
node get(int p, int s, int e, int l, int r)
{
	fix(p, s, e);
	if (s > r || e < l)
		return Z;
	if (s >= l && e <= r)
		return seg[p];
	return get(p * 2 , s, (s + e) / 2, l, r) + get(p * 2 + 1, (s + e) / 2 + 1, e, l, r);
}
mat rot(int y) {
	mat x;
	x.M[0][0] = COS[y];
	x.M[0][1] = SIN[y];
	x.M[1][0] = -SIN[y];
	x.M[1][1] = COS[y];
	x.M[2][2] = 1;
	// for (int i = 0; i < 3; i++) {
	// 	for (int j = 0; j < 3; j++) {
	// 		cout << x.M[i][j] << " ";
	// 	}
	// 	puts("");
	// }
	// node s = get(1, 0, n, n, n);
	// s = s * x;
	// for (int i = 0; i < 3; i++) {
	// 	cout << s.m[i][0] << endl;
	// }
	return x;

}
double dis(double x1, double x2, double y1, double y2) {
	return sqrt((x1 - x2) * 1.0 * (x1 - x2) + (y1 - y2) * 1.0 * (y1 - y2));
}
mat trans(double tx, double ty) {
	mat x;

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)if (i == j)x.M[i][j] = 1;
	x.M[0][2] = tx;
	x.M[1][2] = ty;
	return x;

}
int main() {
	for (int i = 1; i <= 360; i++) {
		double ang = (i * acos(-1)) / 180.0;
		SIN[i] = sin(ang);
		COS[i] = cos(ang);
	}
	scanf("%d%d", &n, &m);
	for (int i = 0; i <= n; i++) {
		a[i].m[0][0] = i;
		a[i].m[2][0] = 1;
	}

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)if (i == j)I.M[i][j] = 1;
	build(1, 0, n);
	for (int t, x, y, i = 0; i < m; i++) {
		scanf("%d%d%d", &t, &x, &y);
		if (t == 2) {

			node ret = get(1, 0, n, x - 1, x - 1);
			mat Y = trans(-ret.m[0][0], -ret.m[1][0]);
			update(1, 0, n, x, n , Y);
			mat X = rot(y);
			update(1, 0, n, x, n , X);
			// node s = get(1, 0, n, n, n);
			// for (int i = 0; i < 3; i++) {
			// 	cout << s.m[i][0] << endl;
			// }
			Y = trans(ret.m[0][0], ret.m[1][0]);
			update(1, 0, n, x, n, Y);
		} else {
			node ret1 = get(1, 0, n , x - 1, x - 1);
			node ret2 = get(1, 0, n , x, x);
			//cout << ret1.m[0][0] << " " << ret1.m[1][0] << endl;
			//cout << ret2.m[0][0] << " " << ret2.m[1][0] << endl;

			double f = dis(ret1.m[0][0], ret2.m[0][0], ret1.m[1][0], ret2.m[1][0]);
			double ratio = (f + y) / f;
			double newX = ret1.m[0][0] + ratio * (ret2.m[0][0] - ret1.m[0][0]);
			double newY = ret1.m[1][0] + ratio * (ret2.m[1][0] - ret1.m[1][0]);
			mat X = trans(newX - ret2.m[0][0], newY - ret2.m[1][0]);
			update(1, 0, n, x, n , X);

		}
		node ret = get(1, 0, n, n, n);
		printf("%.7lf %.7lf\n", ret.m[0][0], ret.m[1][0]);
	}

	return 0;
}