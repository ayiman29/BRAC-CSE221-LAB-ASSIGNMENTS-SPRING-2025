#include<bits/extc++.h>
using namespace std;
long long A, N;
long long res;
// // Compile and run: c++ _A3C_Testing.cpp && .\a.exe
long long solve(long long A, long long N) {
    long long res = 0;
    long long MOD = 1000003;
    // Place your code here

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
    // // file input
    // // ifstream fin("TimeLimitExceeded.txt");
    // // ifstream fin("CustomTest.txt");
    // ifstream fin("WrongAnswer.txt");
    // string temp;
    // for (int i = 1; i <= 2; ++i) getline(fin, temp);
    // fin >> temp >> temp >> A;
    // fin >> temp >> temp >> N;
    // fin.close();

    // stdin
    // 100
    // 7
    cin >> A >> N;
    
    // // hardcoded input
    // A = 100;
    // N = 7;

    chrono::_V2::system_clock::time_point start = chrono::high_resolution_clock::now();
    res = solve(A, N);
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
