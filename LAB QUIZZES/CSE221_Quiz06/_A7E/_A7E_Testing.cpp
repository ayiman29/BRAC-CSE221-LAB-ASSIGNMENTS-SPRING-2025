#include<bits/extc++.h>
using namespace std;
// // Compile and run: c++ _A7E_Testing.cpp && .\a.exe

long long solve(int N, int M, vector<int> &Us, vector<int> &Vs, vector<int> &Ws){ 
    long long res = -1;
    //your code here

    return res;
}
template<typename K, typename V>
inline string to_string(pair<K, V>& x) {
    return "(" + to_string(x.first) + ", " + to_string(x.second) + ")";
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
    // 4 3
    // 1 4 3
    // 3 4 4
    // 2 3 5
    
    // int N, M;
    // cin >> N >> M;
    // vector<int> Us(M), Vs(M), Ws(M);
    // for (int i = 0; i < M; ++i) {
    //     cin >> Us[i] >> Vs[i] >> Ws[i];
    // }

    // // hardcoded input
    int N = 4, M = 3;
    vector<int> Us = {1, 3, 2};
    vector<int> Vs = {4, 4, 3};
    vector<int> Ws = {3, 4, 5};
    
    chrono::_V2::system_clock::time_point start = chrono::high_resolution_clock::now();
    long long res = solve(N, M, Us, Vs, Ws);
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
