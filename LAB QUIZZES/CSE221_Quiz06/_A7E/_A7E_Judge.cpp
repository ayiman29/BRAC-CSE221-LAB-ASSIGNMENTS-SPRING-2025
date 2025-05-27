#include<bits/stdc++.h>
using namespace std;

using ll = long long int;
using ii = pair<ll,ll>;
template<class T> 
istream& operator >> (istream &s, vector<T> &a){
	for(T &x : a)s >> x; 
	return s;
}

const int N = 200005;
vector<ii> adj[N];
int main(int argc, char* argv[1]){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    assert(argc == 3);

    string input_file_name = string(argv[1]);
    string output_file_name = string(argv[2]);

    ifstream fin(input_file_name);
    ifstream fout(output_file_name);
    
    int n, m;
    fin >> n >> m;
    for(int i = 0; i < m; i++){
        int u, v, w;
        fin >> u >> v >> w;
        adj[u].emplace_back(v, w);
    }
    fin.close();
    auto distance = [&](int s){
        vector<vector<ll>> dist = {vector<ll>(n + 1, LLONG_MAX), vector<ll>(n + 1, LLONG_MAX)};
        dist[0][s] = dist[1][s] = 0;
        priority_queue<tuple<ll, int, int>, vector<tuple<ll, int, int>>, greater<tuple<ll, int, int>>> pq;
        pq.emplace(0, 0, s);
        pq.emplace(0, 1, s);
        while(!pq.empty()){
            auto [di, p, u] = pq.top();
            pq.pop();
            if(di != dist[p][u])continue;
            for(auto [x, w] : adj[u]){
                if(p != w % 2 && dist[w % 2][x] > di + w){
                    dist[w % 2][x] = di + w;
                    pq.emplace(di + w, p ^ 1, x);
                }
            }
        }
        
        return dist;
    };
    
    auto d1 = distance(1);
    ll ans = min(d1[0][n], d1[1][n]);
    if(ans == LLONG_MAX)
        ans = -1;
    
    ll res;
    fout >> res;
    fout.close();
    if(res != ans ){
        exit(1);
    }
    exit(0);
}
