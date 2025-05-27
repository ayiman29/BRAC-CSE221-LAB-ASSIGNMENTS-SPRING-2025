#include<bits/extc++.h>
using namespace std;
mt19937 rng;
inline int randInt(int x, int y) { return uniform_int_distribution<int>(x, y)(rng); }
inline string to_string(vector<int>& x) {
    string y = "[";
    if (!x.empty()) y += to_string(x[0]);
    for (int i = 1; i < x.size(); ++i)
        y += ", " + to_string(x[i]);
    return y + "]";
}
int test = 0, best = 0, score = 0, batch = 0, total = 0;
int timeLimit = 1, nBatch = 10;
int weight[] = { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
int nTest[] = { 0, 10, 100, 100, 100, 100, 100, 100, 10, 10, 10 };
int maxN[] = { 0, 10, 10, 100, 100, 1000, 1000, 10000, 100000, 1000000, 1000000 };
int maxS[] = { 0, 1'000, 1'000'000, 1'000'000, 1'000'000'000, 1'000'000, 1'000'000'000, 1'000'000, 1'000'000'000, 1'000'000, 1'000'000'000 };
vector<int> A;
int N, S;
pair<int, int> res;
extern pair<int, int> solve(int N, int S, vector<int> A);
inline void printCase(string& verdict, int test, int N, int S, vector<int> A) {
    if (ifstream(verdict + ".txt").peek() == ifstream::traits_type::eof()) {
        ofstream fout(verdict + ".txt");
        fout << "batch = " << to_string(batch) << "\ntest = " << to_string(test) << "\n";
        fout << "N = " << to_string(N) << "\n";
        fout << "S = " << to_string(S) << "\n";
        fout << "A = " << to_string(A) << "\n";
    }
    cout << verdict << " on Batch " << batch << "\n";
}
inline void exitCase(string verdict) {
    printCase(verdict, test, N, S, A), exit(1);
}
bool validIndex(int i) {
    return i > 0 && i <= N;
}
inline void checkSoln() {
    if (res.first != -1) {
        if (!validIndex(res.first) || !validIndex(res.second) || res.first == res.second)
            exitCase("WrongAnswer");
        if (A[res.first - 1] + A[res.second - 1] != S)
            exitCase("WrongAnswer");
    }
    else {
        for (int i = 0, j = N - 1; i < j; i += (A[i] + A[j] > S ? (j -= 1, 0) : 1))
            if (A[i] + A[j] == S)
                exitCase("WrongAnswer");
    }
}
inline void processBatch() {
    for (test = 1; test <= nTest[batch]; ++test) {
        A.assign(N = randInt(2, maxN[batch]), 0);
        int D = maxS[batch] / N;
        for (int i = 0; i < N; ++i)
            A[i] = (randInt((i == 0 ? 1 : A[i - 1]), maxS[batch] - (N - i - 1) * D));
        bool OK = randInt(0, 1);
        if (OK) {
            int i = randInt(0, N - 1);
            int j = i;
            while (i == j)j = randInt(0, N - 1);
            S = A[i] + A[j];
        }
        else {
            S = randInt(1, maxS[batch]);
        }
        res = solve(N, S, A), checkSoln();
    }
}
inline void limitTime() {
    this_thread::sleep_for(chrono::seconds(timeLimit));
    exitCase("TimeLimitExceeded");
}
int main(int argc, char** argv) {
    if (argc == 2) rng.seed(batch = stoi(argv[1]));
    if (1 <= batch && batch <= nBatch) {
        cout << "Running on Batch " << batch << endl;
        chrono::_V2::system_clock::time_point start = chrono::high_resolution_clock::now();
        thread(limitTime).detach(), processBatch();
        chrono::_V2::system_clock::time_point finish = chrono::high_resolution_clock::now();
        chrono::_V2::system_clock::duration elapsed = chrono::duration_cast<chrono::nanoseconds>(finish - start);
        cout << fixed << setprecision(9) << "Passed Batch " << batch << " in " << (elapsed.count() * 1e-9) << "s\n", exit(0);
    }
    string ID;
    ifstream("EnterIDandLanguage.txt") >> ID;
    if (ifstream("_A2A_" + ID + ".cpp"))
        ifstream("_A2A_" + ID + ".cpp").ignore(12) >> best;
    ofstream("WrongAnswer.txt").close();
    ofstream("TimeLimitExceeded.txt").close();
    for (batch = 1; batch <= nBatch; total += weight[batch], ++batch)
        if (!system((".\\a.exe " + to_string(batch)).c_str()))
            score += weight[batch];
    if (best <= score) {
        ofstream("_A2A_" + ID + ".cpp") << "// " << ID << " " << score << "\n";
        system(("echo // %COMPUTERNAME% %USERNAME%>>_A2A_" + ID + ".cpp").c_str());
        ifstream fin("_A2A_Solution.cpp");
        ofstream("_A2A_" + ID + ".cpp", ios::app) << string("").assign(istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>());
    }
    cout << "Tentative score = " << double(score) / total << "/1\n", exit(0);
}
