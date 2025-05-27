#include <bits/stdc++.h>
using namespace std;

// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt")

using ll = long long int;
using ull = unsigned long long int;
using vi = vector<ll>;
using ii = pair<ll,ll>;
using vii = vector<ii>;
using ld = long double;
using Ti = array<int, 3>;

#define eb emplace_back
#define fi first
#define se second


mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

template<class T, class V> 
ostream& operator << (ostream &s, pair<T, V> a){
	s << a.fi << ' ' << a.se; return s;
}

template<class T, class V> 
istream& operator >> (istream &s, pair<T, V> &a){
	s >> a.fi >> a.se; return s;
}

template<class T> 
ostream& operator << (ostream &s, vector<T> a){
	for(int i = 0; i < (int)a.size(); i++){
		if(i > 0)s << ' ' ; 
		s << a[i];
	} return s;
}

template<class T> 
istream& operator >> (istream &s, vector<T> &a){
	for(T &x : a)s >> x; 
	return s;
}

template<class T> 
void input(T a[], int l, int r, istream &s = cin){
	while(l <= r)s >> a[l++];
}

template<class T> 
void output(T a[], int l, int r, bool en = true, ostream &s = cout){
	while(l <= r){ s << a[l++];
		if(l <= r) s << ' ';
	} if(en)s << "\n";
}

const double PI = acos(-1);



//====================================================================//
template<class T>
T getRandInt(T l, T r){
	std::uniform_int_distribution<T> distrib(l, r);
	return distrib(rng);
}
ld getRandDouble(ld l, ld r){
	std::uniform_real_distribution<> distrib(l, r);
	return distrib(rng);
}
template<class T>
vector<T> getIntArray(int n, T l, T r){
	vector<T> v(n);
	for(int i = 0; i < n; i++){
		v[i] = getRandInt(l, r);
	}
	return v;
}
vector<ld> getDoubleArray(int n, ld l, ld r){
	vector<ld> v(n);
	for(int i = 0; i < n; i++){
		v[i] = getRandDouble(l, r);
	}
	return v;
}
template<class T>
pair<T, T> getPair(T l, T r){
	T L = getRandInt(l, r);
	T R = getRandInt(l, r);
	if(L > R)swap(L, R);
	return {L, R};
}
string getString(int n, int l = 'a', int r = 'z'){
	string ans;
	for(int i = 0; i < n; i++)ans += (char)(getRandInt(l, r));
	return ans;
}
vector<int> getPermutation(int n){
	vector<int> v(n);
	for(int i = 0; i < n; i++){
		v[i] = i + 1;
	}
	shuffle(v.begin(), v.end(), rng);
	return v;
}

const ll INFL = 2e18;
const int INF = 1e9;
const ll mod = 1e9+7;
const int N = 2e5, K = 1e9, M = 3e5, logK = 30, W = 1e9;
const int oldK = 1e6, oldLogK = 20;


vector<ii> decode(vector<int> &code, int n){
	vector<ii> edges;
	vector<int> deg(n + 1);
	for(auto x : code)	deg[x]++;
	priority_queue<int> baki;
	for(int i = 1; i <= n; i++)if(deg[i] == 0)baki.push(-i);
	while(!code.empty()){
		int u = -baki.top();
		baki.pop();
		int v = code.back();
		code.pop_back();
		edges.push_back({u, v});
		if(--deg[v] == 0)baki.push(-v);
	}
	int u = -baki.top();
	baki.pop();
	int v = -baki.top();
	edges.push_back({u, v});
	return edges;
}
//random
vector<ii> randomTree(int n){
	vector<int> code(n - 2);
	for(int i = 0; i < code.size(); i++)code[i] = getRandInt(1, n);
	return decode(code, n);
}

vector<ii> lineTree(int n){
	vector<ii> edges;
	for(int i = 1; i < n; i++)edges.push_back({i, i + 1});
	return edges;
}

vector<ii> starTree(int n){
	vector<ii> edges;
	for(int i = 1; i < n; i++)edges.push_back({i, n});
	return edges;
}

vector<ii> stretchTree(int n, int k){
	vector<ii> edges;
	for(int i = 2; i <= n; i++)edges.push_back({getRandInt(max(1, i - k), i - 1), i});
	return edges;
}

vector<ii> highdegTree(int n, int k){
	vector<ii> edges;
	for(int i = 2; i <= n; i++)edges.push_back({getRandInt(1, min(k, i - 1)), i});
	return edges;
}

vector<ii> kTree(int n, int k){
	vector<ii> edges;
	int cur = 1, t = 0;
	for(int i = 2; i <= n; i++){
		if(t == k)cur++, t = 0;
		edges.push_back({cur, i});
		t++;
	}
	return edges;
}

vector<ii> caterpillarTree(int n, int k){
	int len = (n + k) / (k + 1);
	auto edges = lineTree(len);
	int cur = 1, t = 0;
	for(int i = len + 1; i <= n; i++){
		if(t == k)t = 0, cur++;
		edges.push_back({cur, i});
		t++;
	}
	return edges;
}

vector<ii> starlineTree(int n, int k){
	vector<ii> edges;
	int len = n - k;
	edges = lineTree(len);
	for(int i = len + 1; i <= n; i++){
		edges.push_back({len / 2 + 1, i});
	}
	return edges;
}

vector<ii> modify(int n, vector<ii> &e){
	vector<ii> ret;
	vector<int> perm = getPermutation(n);
	for(auto& [u, v] : e){
		ret.emplace_back(perm[u - 1], perm[v - 1]);
	}
	return ret;
}

vector<Ti> addWeight(vector<ii> &e, int wlo, int whi){
	vector<Ti> ret;
	for(auto& [u, v] : e){
		ret.push_back({u, v, getRandInt(wlo, whi)});
	}
	return ret;
}

vector<ii> addExtraEdge(vector<ii> &e, int n, int m){
	m = max(m, n - 1);
	m = min((ll)m, (ll)n * (n - 1) / 2);
	int iter = 0;
	set<ii> edge;
	for(auto [u, v] : e){
		if(u > v)swap(u, v);
		edge.emplace(u, v);
	}
	while(edge.size() < m and iter < 1000000){
		int a = getRandInt(2, n);
		int b = getRandInt(1, a - 1);
		edge.insert(ii(b, a));
		iter++;
	}
	if(edge.size() != m){
		set<ii> all;
		for(int i = 0; i < n; ++i)for(int j = 0; j < i; ++j)all.emplace(j + 1, i + 1);
		for(auto x : edge)all.erase(x);
		while(edge.size() < m){
			int cnt = getRandInt(0, (int)all.size() - 1);
			auto it = all.begin();
			advance(it, cnt);
			edge.insert(*it);
			all.erase(it);
		}
	}

	vector<ii> edges;
	for(auto x : edge)edges.emplace_back(x);
	return edges;
}

vector<ii> addExtraBipartiteEdge(vector<ii> &e, int n, int m){
	set<ii> edge;
	vector<int> clr(n + 1, -1);
	vector<vector<int>> adj(n + 1);
	for(auto [u, v] : e){
		if(u > v)swap(u, v);
		edge.emplace(u, v);
		adj[u].eb(v);
		adj[v].eb(u);
	}
	
	auto dfs = [&](auto&& dfs, int x, int c) -> void {
		clr[x] = c;
		for(auto y : adj[x]){
			if(clr[y] == -1)
				dfs(dfs, y, c ^ 1);
		}
		return;
	};
	
	for(int i = 1; i <= n; i++){
		if(clr[i] == -1)dfs(dfs, i, 0);
	}
	
	vector<int> S[2];
	for(int i = 1; i <= n; i++)
		S[clr[i]].eb(i);
	
	m = max(m, n - 1);
	m = min((ll)m, (ll)S[0].size() * (ll)S[1].size());
	int iter = 0;
	while(edge.size() < m and iter < 1000000){
		int a = S[0][getRandInt(0, (int)S[0].size() - 1)];
		int b = S[1][getRandInt(0, (int)S[1].size() - 1)];
		if(a > b)
			swap(a, b);
		edge.insert(ii(a, b));
		iter++;
	}
	if(edge.size() != m){
		set<ii> all;
		for(int i = 0; i < S[0].size(); ++i)for(int j = 0; j < S[1].size(); ++j)all.emplace(min(S[0][i], S[1][j]), max(S[0][i], S[1][j]));
		for(auto x : edge)all.erase(x);
		while(edge.size() < m){
			int cnt = getRandInt(0, (int)all.size() - 1);
			auto it = all.begin();
			advance(it, cnt);
			edge.insert(*it);
			all.erase(it);
		}
	}

	vector<ii> edges;
	for(auto x : edge)edges.emplace_back(x);
	return edges;
}
bool farthest_destination = false;
tuple<int, vector<Ti>> postProcess(int n, vector<ii> e, int wlo, int whi){
	e = modify(n, e);
	for(auto& [x, y] : e){
		if(getRandInt(0, 1) == 1)swap(x, y);
	}
	auto E = addWeight(e, wlo, whi);
	
	auto getFarthestDestination = [&](){
		vector<vector<ii>> adj(n + 1);
		for(auto [u, v, w] : E){
			adj[u].emplace_back(v, w);
		}
			
		vector<ll> dist[2];
		dist[0] = vector<ll>(n + 1, LLONG_MAX);
		dist[1] = vector<ll>(n + 1, LLONG_MAX);
		dist[0][1] = dist[1][1] = 0;
		priority_queue<pair<ii, int>, vector<pair<ii, int>>, greater<pair<ii, int>>> pq;
		pq.push({ii(0, 0), 1});
		pq.push({ii(0, 1), 1});
		while(!pq.empty()){
			auto [di, u] = pq.top();
			auto [d, p] = di;
			pq.pop();
			if(d != dist[p][u])continue;
			for(auto [x, w] : adj[u]){
				if(p != w % 2 && dist[w % 2][x] > d + w){
					dist[w % 2][x] = d + w;
					pq.push({ii(d + w, p ^ 1), x});
				}
			}
		}
		int mx = 1;
		for(int i = 1; i <= n; i++){
			if(min(dist[0][i], dist[1][i]) != LLONG_MAX and min(dist[0][i], dist[1][i]) >= min(dist[0][mx], dist[1][mx]))
				mx = i;
		}
		return mx;
	};
	if(farthest_destination){
		int d = getFarthestDestination();
		if(d != 1){
			for(auto& [u, v, w] : E){
				if(u == d) u = n;
				else if(u == n) u = d;

				if(v == d) v = n;
				else if(v == n) v = d;
			}
		}
	}
	return {n, E};
}

void print(const tuple<int, vector<Ti>> &t){
	auto [n, e] = t;
	cout << n << " " << e.size() << "\n";
	for(auto x : e)
		cout << x[0] << ' ' << x[1] << ' ' << x[2] << "\n";
	
}

const int BATCH_COUNT = 14;
const string types[] = {"randomGraph", "bipartiteGraph", "lineGraph", "starGraph", "stretchGraph", "highdegGraph", "kGraph", "caterpillarGraph", "starlineGraph", "randomTree", "lineTree", "starTree", "stretchTree", "highdegTree", "kTree", "caterpillarTree", "starlineTree"};
const int TOTAL_TYPES = sizeof(types) / sizeof(types[0]);
const ii Nrange[BATCH_COUNT] = {
	ii(4, 4),
	ii(6, 6),
	ii(2, 2),
	ii(5, 5),
	ii(2, 20),
	ii(20, 20),
	ii(2, 200),
	ii(200, 200),
	ii(2, 2000),
	ii(2000, 2000),
	ii(2, 20000),
	ii(20000, 20000),
	ii(2, 200000),
	ii(200000, 200000),
};

const ii Mrange[BATCH_COUNT] = {
	ii(3, 6),
	ii(2, 3),
	ii(1, 1),
	ii(7, 9),
	ii(2, 40),
	ii(20, 40),
	ii(2, 400),
	ii(200, 400),
	ii(2, 4000),
	ii(2000, 4000),
	ii(2, 40000),
	ii(20000, 40000),
	ii(2, 300000),
	ii(200000, 300000)
};

const ii Wrange[BATCH_COUNT] = {
	ii(1, 5),
	ii(1, 5),
	ii(1, 10),
	ii(1, 8),
	ii(1, 1000000),
	ii(1, 1000000),
	ii(1, 1000000),
	ii(1, 1000000),
	ii(1, 1000000),
	ii(1, 1000000),
	ii(1, 1000000),
	ii(1, 1000000),
	ii(1, 1000000),
	ii(1, 1000000)
};


int main(int argc, char* argv[]){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	// cout << argc << endl;
	int batch = atoi(argv[1]);
	int test = atoi(argv[2]);
	int seed = batch * 786786 + test;
	batch--;
	rng.seed(seed); 
	int nlo = Nrange[batch].first;
	int nhi = Nrange[batch].second;
	int mlo = Mrange[batch].first;
	int mhi = Mrange[batch].second;
	int wlo = Wrange[batch].first;
	int whi = Wrange[batch].second;
	string type = types[test / 2 % TOTAL_TYPES];
	if(test % 2 == 0)
		type = types[0];
	if(test % 3 == 1)
		farthest_destination = true;
	if(batch == 1)
		farthest_destination = false;

	if(type == "randomGraph"){
		int n = getRandInt(nlo, nhi);
		int m = getRandInt(mlo, mhi);
		auto e = randomTree(n);
		e.clear();
		e = addExtraEdge(e, n, m);
		print(postProcess(n, e, wlo, whi));
	}else if(type == "bipartiteGraph"){
		int n = getRandInt(nlo, nhi);
		int m = getRandInt(mlo, mhi);
		auto e = randomTree(n);
		e = addExtraBipartiteEdge(e, n, m);
		print(postProcess(n, e, wlo, whi));
	}else if(type == "lineGraph"){
		int n = getRandInt(nlo, nhi);
		int m = getRandInt(mlo, mhi);
		auto e = lineTree(n);
		e = addExtraEdge(e, n, m);
		print(postProcess(n, e, wlo, whi));
	}else if(type == "starGraph"){
		int n = getRandInt(nlo, nhi);
		int m = getRandInt(mlo, mhi);
		auto e = starTree(n);
		e = addExtraEdge(e, n, m);
		print(postProcess(n, e, wlo, whi));
	}else if(type == "stretchGraph"){
		int n = getRandInt(nlo, nhi);
		int m = getRandInt(mlo, mhi);
		int k = getRandInt(1, n / 2 - 1);
		auto e = stretchTree(n, k);
		e = addExtraEdge(e, n, m);
		print(postProcess(n, e, wlo, whi));
	}else if(type == "highdegGraph"){
		int n = getRandInt(nlo, nhi);
		int m = getRandInt(mlo, mhi);
		int k = getRandInt(1, n / 2 - 1);
		auto e = highdegTree(n, k);
		e = addExtraEdge(e, n, m);
		print(postProcess(n, e, wlo, whi));
	}else if(type == "kGraph"){
		int n = getRandInt(nlo, nhi);
		int m = getRandInt(mlo, mhi);
		int k = getRandInt(1, n / 2 - 1);
		auto e = kTree(n, k);
		e = addExtraEdge(e, n, m);
		print(postProcess(n, e, wlo, whi));
	}else if(type == "caterpillarGraph"){
		int n = getRandInt(nlo, nhi);
		int m = getRandInt(mlo, mhi);
		int k = getRandInt(1, n / 2 - 1);
		auto e = caterpillarTree(n, k);
		e = addExtraEdge(e, n, m);
		print(postProcess(n, e, wlo, whi));
	}else if(type == "starlineGraph"){
		int n = getRandInt(nlo, nhi);
		int m = getRandInt(mlo, mhi);
		int k = getRandInt(1, n / 2 - 1);
		auto e = starlineTree(n, k);
		e = addExtraEdge(e, n, m);
		print(postProcess(n, e, wlo, whi));
	}else if(type == "randomTree"){
		int n = getRandInt(nlo, nhi);
		auto e = randomTree(n);
		print(postProcess(n, e, wlo, whi));
	}else if(type == "lineTree"){
		int n = getRandInt(nlo, nhi);
		auto e = lineTree(n);
		print(postProcess(n, e, wlo, whi));
	}else if(type == "starTree"){
		int n = getRandInt(nlo, nhi);
		auto e = starTree(n);
		print(postProcess(n, e, wlo, whi));
	}else if(type == "stretchTree"){
		int n = getRandInt(nlo, nhi);
		int k = getRandInt(1, n / 2 - 1);
		auto e = stretchTree(n, k);
		print(postProcess(n, e, wlo, whi));
	}else if(type == "highdegTree"){
		int n = getRandInt(nlo, nhi);
		int k = getRandInt(1, n / 2 - 1);
		auto e = highdegTree(n, k);
		print(postProcess(n, e, wlo, whi));
	}else if(type == "kTree"){
		int n = getRandInt(nlo, nhi);
		int k = getRandInt(1, n / 2 - 1);
		auto e = kTree(n, k);
		print(postProcess(n, e, wlo, whi));
	}else if(type == "caterpillarTree"){
		int n = getRandInt(nlo, nhi);
		int k = getRandInt(1, n / 2 - 1);
		auto e = caterpillarTree(n, k);
		print(postProcess(n, e, wlo, whi));
	}else if(type == "starlineTree"){
		int n = getRandInt(nlo, nhi);
		int k = getRandInt(1, n / 2 - 1);
		auto e = starlineTree(n, k);
		print(postProcess(n, e, wlo, whi));
	}else{
		cout << "Invalid argument\n";
	}
	
	return 0;
}

