#include<bits/extc++.h>
using namespace std;
const int MAXN = 1e5 + 9;
//vector<pair<int, int> > adj[MAXN];
vector<pair<pair<int, int>, int > > edges;
// // Compile and run: c++ _712_Testing.cpp && .\a.exe

int solve(int N, int M, int S, int D, int K, vector< pair< pair<int, int>, int > > edges) {
    int res = 0;
    //your code here

    return res;
}


inline string to_string(vector<int>& x) {
    string y = "[";
    if (!x.empty()) y += to_string(x[0]);
    for (int i = 1; i < x.size(); ++i)
        y += ", " + to_string(x[i]);
    return y + "]";
}

inline string to_string(vector<pair<int, int>>& x) {
    string y = "";
    if (!x.empty()) y += to_string(x[0].first) + " " + to_string(x[0].second) + "\n";
    for (int i = 1; i < x.size(); ++i)
        y += to_string(x[i].first) + " " + to_string(x[i].second) + "\n";
    return y ;
}
int main() {
    /*
    stdin
    7 10 3 7 5
    2 3 1
    2 4 1
    4 3 6
    4 1 2
    1 7 2
    4 5 3
    5 7 8
    4 7 1
    5 6 4
    6 7 2
    */

    int N, M, S, D, K;
    cin >> N >> M >> S >> D >> K;

    for(int i=0; i<M; i++){
        int u, v, w;
        cin >> u >> v >> w;
        pair<int, int> ed = make_pair(u, v);
        edges.push_back(make_pair(ed, w));
    }

    chrono::_V2::system_clock::time_point start = chrono::high_resolution_clock::now();
    int res = solve(N, M, S, D, K, edges);
    chrono::_V2::system_clock::time_point finish = chrono::high_resolution_clock::now();
    chrono::_V2::system_clock::duration elapsed = chrono::duration_cast<chrono::nanoseconds>(finish - start);

    // ofstream fout("OutputOfYourCode.txt");
    // fout << to_string(res);
    // fout.close();


    // stdout
    cout << res << "\n";

    cout << fixed << setprecision(9) << "Execution time for the targeted one test is " << (elapsed.count() * 1e-9) << "s\n";
    exit(0);
}
