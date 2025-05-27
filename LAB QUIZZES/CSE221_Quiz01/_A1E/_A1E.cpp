#include<bits/extc++.h>
using namespace std;
extern vector<int> solve(vector<int> arr);
inline int rng(int x) { return abs(rand() << 30LL | rand() << 15LL | rand()) % x; }
inline string to_string(vector<int>& x) {
    string y = "[";
    if (!x.empty()) y += to_string(x[0]);
    for (int i = 1; i < x.size(); ++i)
        y += ", " + to_string(x[i]);
    return y + "]";
}
int test = 0, best = 0, score = 0, batch = 0, total = 0;
int timeLimit = 2, nBatch = 5, N = 0;
int weight[] = { 0, 1, 2, 2, 2, 3 };
int nTest[] = { 0, 1000000, 10000, 100, 500, 50 };
int maxN[] = { 0, 10, 100, 1000, 10000, 100000 };
vector<int> arr, res;
inline void printCase(string verdict, int test, vector<int> arr) {
    if (ifstream(verdict + ".txt").peek() == ifstream::traits_type::eof()) {
        ofstream fout(verdict + ".txt");
        fout << "batch = " << to_string(batch) << "\ntest = " << to_string(test) << "\n";
        fout << "N = " << to_string(arr.size()) << "\n";
        fout << "arr = " << to_string(arr) << "\n";
    }
    cout << verdict << " on Batch " << batch << "\n", exit(1);
}
inline void checkSoln(vector<int>& res) {
    if (!is_sorted(res.begin(), res.end()))
        printCase("WrongAnswer", test, arr);
}
inline void limitTime() {
    this_thread::sleep_for(chrono::seconds(timeLimit));
    printCase("TimeLimitExceeded", test, arr);
}
int main(int argc, char** argv) {
    if (argc == 2) srand(batch = stoi(argv[1]));
    if (argc != 2 || batch < 1 || nBatch < batch) {
        string ID;
        ifstream("EnterIDandLanguage.txt") >> ID;
        if (ifstream("_A1E_" + ID + ".cpp"))
            ifstream("_A1E_" + ID + ".cpp").ignore(12) >> best;
        ofstream("WrongAnswer.txt").close();
        ofstream("TimeLimitExceeded.txt").close();
        for (batch = 1; batch <= nBatch; total += weight[batch], ++batch)
            if (!system((".\\a.exe " + to_string(batch)).c_str()))
                score += weight[batch];
        if (best <= score) {
            ofstream("_A1E_" + ID + ".cpp") << "// " << ID << " " << score << "\n";
            system(("echo // %COMPUTERNAME% %USERNAME%>>_A1E_" + ID + ".cpp").c_str());
            ifstream fin("_A1E_Solution.cpp");
            ofstream("_A1E_" + ID + ".cpp", ios::app) << string("").assign(istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>());
        }
        cout << "Tentative score = " << double(score) / total << "/1\n", exit(0);
    }
    cout << "Running on Batch " << batch << endl;
    chrono::_V2::system_clock::time_point start = chrono::high_resolution_clock::now();
    thread(limitTime).detach();
    if (1 <= batch && batch <= nBatch) {
        for (test = 1; test <= nTest[batch]; ++test) {
            res.clear(), arr.clear(), arr.reserve(N = 1 + rng(maxN[batch]));
            for (int i = 1; i <= N; arr.push_back(1 + rng(1000000000)), ++i);
            if (1000 < N) sort(arr.begin(), arr.end());
            res = solve(arr), checkSoln(res);
        }
    }
    chrono::_V2::system_clock::time_point finish = chrono::high_resolution_clock::now();
    chrono::_V2::system_clock::duration elapsed = chrono::duration_cast<chrono::nanoseconds>(finish - start);
    cout << fixed << setprecision(9) << "Passed Batch " << batch << " in " << (elapsed.count() * 1e-9) << "s\n", exit(0);
}