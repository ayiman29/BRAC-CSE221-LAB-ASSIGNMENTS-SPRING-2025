#include<bits/extc++.h>
using namespace std;
// // Compile and run: c++ _A6C_Testing.cpp && .\a.exe
int solve(int N, int X1, int Y1, int X2, int Y2) {
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
int main() {
    // stdin
    // 4
    // 1 1
    // 3 4
    // int N;
    // cin >> N;
    // int X1, Y1;
    // cin >> X1 >> Y1;
    // int X2, Y2;
    // cin >> X2 >> Y2;

    // // hardcoded input
    int N = 4;
    int X1 = 1, Y1 = 1;
    int X2 = 3, Y2 = 4;

    
    chrono::_V2::system_clock::time_point start = chrono::high_resolution_clock::now();
    int res = solve(N, X1, Y1, X2, Y2);
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
