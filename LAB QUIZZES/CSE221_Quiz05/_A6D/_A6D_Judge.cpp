#include<bits/stdc++.h>
using namespace std;

using ll = long long int;

template<class T> 
istream& operator >> (istream &s, vector<T> &a){
	for(T &x : a)s >> x; 
	return s;
}

const int N = 100005;
vector<int> adj[N];
int clr[N];
int main(int argc, char* argv[1]){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    assert(argc == 3);

    string input_file_name = string(argv[1]);
    string output_file_name = string(argv[2]);

    ifstream fin(input_file_name);
    ifstream fout(output_file_name);
    
    int n, r;
    fin >> n >> r;
    for(int i = 0; i < n - 1; ++i){
        int x, y;
        fin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    vector<int> cur;
    int id = 0;
    cur.push_back(r);
    vector<int> par(n + 1, -1);
    par[r] = 0;
    while(id < cur.size()){
        int u = cur[id];
        id++;
        for(int v : adj[u]){
            if(par[v] == -1){
                par[v] = u;
                cur.push_back(v);
            }
        }
    }

    vector<int> ans(n + 1, 1);
    while(cur.size() > 1){
        int u = cur.back();
        cur.pop_back();
        ans[par[u]] += ans[u];
    }
    ans[0] = 0;

    vector<int> res(n + 1);
    fout >> res;


    fin.close();
    fout.close();
    

    if(ans != res)
        exit(1);

    exit(0);
}
