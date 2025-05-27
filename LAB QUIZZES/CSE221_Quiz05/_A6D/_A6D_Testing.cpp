#include<bits/extc++.h>
using namespace std;
// // Compile and run: c++ _A6D_Testing.cpp && .\a.exe

vector<int> solve(int N, int R, vector<pair<int, int>> edges) {
    vector<int> res(N + 1, 0);
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
int main() {
    // stdin
    // 4 1
    // 3 1
    // 4 1
    // 1 2
    // int N, R;
    // cin >> N >> R;
    // vector<pair<int, int>> edges(N-1);
    // for(int i = 0; i < N-1; i++){
    //     int u, v;
    //     cin >> u >> v;
    //     edges[i] = {u, v};
    // }

    // // hardcoded input
    int N = 4, R = 1;
    vector<pair<int, int>> edges = {
        {3, 1},
        {4, 1},
        {1, 2}
    };

    
    chrono::_V2::system_clock::time_point start = chrono::high_resolution_clock::now();
    vector<int> res = solve(N, R, edges);
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
