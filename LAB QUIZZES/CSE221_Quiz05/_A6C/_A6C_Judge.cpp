#include<bits/stdc++.h>
using namespace std;

using ll = long long int;


template<class T, class V> 
istream& operator >> (istream &s, pair<T, V> &a){
	s >> a.first >> a.second; return s;
}

int xi[] = {2, 2, -2, -2, 1, 1, -1, -1};
int yi[] = {1, -1, 1, -1, 2, -2, 2, -2};

int main(int argc, char* argv[1]){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    assert(argc == 3);

    string input_file_name = string(argv[1]);
    string output_file_name = string(argv[2]);

    ifstream fin(input_file_name);
    ifstream fout(output_file_name);
    
    queue<pair<int, int>> q;
    int n;
    pair<int, int> p1, p2;
    fin >> n >> p1 >> p2;
    vector<vector<int>> dis(n + 1, vector<int>(n + 1, -1));
    auto check = [&](int x, int y){
        return x < 1 || x > n || y < 1 || y > n || dis[x][y] != -1;
    };

    q.push(p1);
    dis[p1.first][p1.second] = 0;
    while(!q.empty()){
        auto [x, y] = q.front(); q.pop();
        for(int i = 0; i < 8; i++){
            int nx = x + xi[i], ny = y + yi[i];
            if(check(nx, ny))continue;
            dis[nx][ny] = dis[x][y] + 1;
            q.push({nx, ny});
        }
    }
    int res = dis[p2.first][p2.second];

    int ans;
    fout >> ans;
    if(res != ans){
        exit(1);
    }

    exit(0);
}
