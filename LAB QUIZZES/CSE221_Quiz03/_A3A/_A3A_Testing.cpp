#include<bits/extc++.h>
using namespace std;
int N = 0, M = 0;
vector<int> A;
long long res;
// // Compile and run: c++ _A3A_Testing.cpp && .\a.exe
long long solve(vector<int> A) {
    int N = A.size();
    long long res = 0;
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
    // fin >> temp >> temp >> N;
    // A.resize(N);
    // fin.ignore(6), getline(fin, temp);
    // istringstream sin(temp);
    // for (int i = 0, j; i < N; sin >> temp, A[i] = stoi(temp.substr(0, temp.size() - 1)), ++i);
    // fin.close();

    // stdin
    // 5
    // 1 2 5 4 3
    cin >> N;
    A.resize(N);
    for (int i = 0; i < N; ++i) cin >> A[i];

    // // hardcoded input
    // A = vector<int>({ 1, 2, 5, 4, 3 });

    chrono::_V2::system_clock::time_point start = chrono::high_resolution_clock::now();
    res = solve(A);
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
