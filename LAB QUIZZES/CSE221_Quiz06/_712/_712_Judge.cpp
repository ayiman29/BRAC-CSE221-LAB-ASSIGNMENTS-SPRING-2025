#include<bits/stdc++.h>
using namespace std;

using ll = long long int;
using pii = pair<int, int>;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
inline int randInt(int x, int y) { return uniform_int_distribution<int>(x, y)(rng); }

const int N = 200005;
template<class T, class V> 
ostream& operator << (ostream &s, pair<T, V> a){
	s << a.first << ' ' << a.second; return s;
}

template<class T, class V> 
istream& operator >> (istream &s, pair<T, V> &a){
	s >> a.first >> a.second; return s;
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

vector<pii> adj[N];
const int INF = 1000000000;

int dijkstra(int n, int s, int k) {
    vector<int> d;
    d.assign(n+1, INF);

    d[s] = 0;
    using pii = pair<int, int>;
    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.push({0, s});
    while (!q.empty()) {
        int v = q.top().second;
        int d_v = q.top().first;
        q.pop();
        if (d_v != d[v])
            continue;

        for (auto edge : adj[v]) {
            int to = edge.first;
            int len = edge.second;

            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                q.push({d[to], to});
            }
        }
    }

    return d[k];
}



vector<int>  u, v, w;

vector<int> visited;



int main(int argc, char* argv[1]){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    assert(argc == 3);

    string input_file_name = string(argv[1]);
    string output_file_name = string(argv[2]);

    ifstream fin(input_file_name);
    ifstream fout(output_file_name);

    u.clear();
    v.clear();
    w.clear();

    int n, m, s, dest, k;
    fin >> n >> m >> s >> dest >> k; 
    
    for(int i = 0; i<=n; i++){
        adj[i].clear();
    }

    for(int i = 0; i < m; i++){
        int x;
        fin >> x;
        u.push_back(x);
    }

    for(int i = 0; i < m; i++){
        int x;
        fin >> x;
        v.push_back(x);
    }

    for(int i = 0; i < m; i++){
        int x;
        fin >> x;
        w.push_back(x);
    }

    for(int i = 0; i < m; i++){
        adj[u[i]].push_back(make_pair(v[i],w[i]));
        adj[v[i]].push_back(make_pair(u[i],w[i]));
    }

    int ans = -1;

    int d1 = dijkstra(n, s, k);
    int d2 = dijkstra(n, k, dest);

    if(d1!=INF and d2!=INF)
    {
        ans = d1 + d2;
    }
    
    int res;
    fout >> res; 
    
    if(res!=ans)
    {
        fin.close();
        fout.close();
        exit(1);
    }
    
    fin.close();
    fout.close();

    exit(0);
}
