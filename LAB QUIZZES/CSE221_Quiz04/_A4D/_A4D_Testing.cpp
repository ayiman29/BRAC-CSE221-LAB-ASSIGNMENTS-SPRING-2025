#include<bits/extc++.h>
using namespace std;
// // Compile and run: c++ _A4D_Testing.cpp && .\a.exe
bool solve(int N, vector<pair<int, int>> edges) {
    bool res = true;
    //your code here
    

    return res;
}
template<class T>
inline string to_string(pair<T, T> &x) {
    return "{" + to_string(x.first) + ", " + to_string(x.second) + "}";
}
template<class T>
inline string to_string(vector<T>& x) {
    string y = "[";
    if (!x.empty()) y += to_string(x[0]);
    for (int i = 1; i < x.size(); ++i)
        y += ", " + to_string(x[i]);
    return y + "]";
}
int main() {
    // stdin
    // 3 2
    // 0 1
    // 1 2
    // int N, M;
    // cin >> N >> M;
    // vector<pair<int, int>> edges;
    // for(int i = 0; i < M; i++){
    //     int u, v;
    //     cin >> u >> v;
    //     edges.emplace_back(u, v);
    // }

    // // hardcoded input
    int N = 5;
    vector<pair<int, int>> edges = {{0, 1}, {0, 2}, {0, 3}, {2, 3}, {2, 4}, {3, 4}};

    
    chrono::_V2::system_clock::time_point start = chrono::high_resolution_clock::now();
    bool res = solve(N, edges);
    chrono::_V2::system_clock::time_point finish = chrono::high_resolution_clock::now();
    chrono::_V2::system_clock::duration elapsed = chrono::duration_cast<chrono::nanoseconds>(finish - start);

    // // file output
    // ofstream fout("OutputOfYourCode.txt");
    // fout << to_string(res);
    // fout.close();

    // stdout
    cout << to_string(res) << "\n";

    cout << fixed << setprecision(9) << "Execution time for the targeted one test is " << (elapsed.count() * 1e-9) << "s\n";
    exit(0);
}
