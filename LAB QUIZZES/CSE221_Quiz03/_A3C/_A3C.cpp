#include<bits/extc++.h>
using namespace std;
mt19937_64 rng;
inline int randInt(int x, int y) { return uniform_int_distribution<int>(x, y)(rng); }
inline long long randLong(long long x, long long y) { return uniform_int_distribution<long long>(x, y)(rng); }
chrono::_V2::system_clock::time_point start, finish;
chrono::_V2::system_clock::duration elapsed = std::chrono::system_clock::duration::zero();
int test = 0, best = 0, score = 0, batch = 0, total = 0;
int timeLimit = 1, nBatch = 14;
using LL = long long;
LL N = 0, A = 0, ten_9 = 1000000000, MOD = 1000003;
int weight[] = { 0, 5, 5, 5, 5, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8};
int nTest[] =  { 0, 1, 1, 1, 1, 1000, 1000, 10000, 1000, 10000, 10, 1000, 1000, 10000, 10000};
LL maxN[] =   { 0, 0, 0, 0, 0,  10,  100, 100, 1000, 1000, 1000000, 1000000, ten_9, ten_9 * 1000, ten_9 * ten_9};
LL res, ans;
extern LL solve(LL A, LL N);
inline string to_string(vector<int>& x) {
    string y = "[";
    if (!x.empty()) y += to_string(x[0]);
    for (int i = 1; i < x.size(); ++i)
        y += ", " + to_string(x[i]);
    return y + "]";
}
inline void printCase(string& verdict, int test, LL A, LL N) {
    if (ifstream(verdict + ".txt").peek() == ifstream::traits_type::eof()) {
        ofstream fout(verdict + ".txt");
        fout << "batch = " << to_string(batch) << "\ntest = " << to_string(test) << "\n";
        fout << "A = " << to_string(A) << "\n";
        fout << "N = " << to_string(N) << "\n";
    }
    cout << verdict << " on Batch " << batch << "\n";
}
inline void exitCase(string verdict) {
    printCase(verdict, test, A, N), exit(1);
}
inline void checkSoln() {
    start = chrono::high_resolution_clock::now();
    res = solve(A, N);
    finish = chrono::high_resolution_clock::now();
    elapsed += chrono::duration_cast<chrono::nanoseconds>(finish - start);
    if (std::chrono::seconds(timeLimit) < elapsed)
        exitCase("TimeLimitExceeded");
    if(res < 0 or res >= MOD)
        exitCase("WrongAnswer");
    LL tempN=N;
    for(ans=1;N;ans=(N&1?ans*A%MOD:ans),N>>=1,A=A*A%MOD);
    N=tempN;
    if(res != ans)
        exitCase("WrongAnswer");
        
}
inline void processBatch() {
    if (batch == 1) {
        test = 1;
        A = 100;
        N = 3;
        checkSoln();
        return;
    }
    if (batch == 2) {
        test = 1;
        A = 100;
        N = 7;
        checkSoln();
        return;
    }
    if (batch == 3) {
        test = 1;
        A = 1000000;
        N = ten_9 * ten_9;
        checkSoln();
        return;
    }
    if (batch == 4) {
        test = 1;
        A = 1;
        N = ten_9;
        checkSoln();
        return;
    }
    for (test = 1; test <= nTest[batch]; ++test) {
        A = randInt(1, 1000000);
        N = randLong(1, maxN[batch]);
        checkSoln();
    }
}
inline void limitTime() {
    for (chrono::_V2::system_clock::duration recall = std::chrono::system_clock::duration::max();
        elapsed < std::chrono::seconds(timeLimit) && recall != elapsed;)
        recall = elapsed, this_thread::sleep_for(chrono::seconds(timeLimit << 1));
    exitCase("TimeLimitExceeded");
}
int main(int argc, char** argv) {
    if (argc == 2) rng.seed(batch = stoi(argv[1]));
    if (1 <= batch && batch <= nBatch) {
        cout << "Running on Batch " << batch << endl;
        thread(limitTime).detach(), processBatch();
        cout << fixed << setprecision(9) << "Accepted on Batch " << batch << " in " << (elapsed.count() * 1e-9) << "s\n", exit(0);
    }
    string ID;
    ifstream("EnterIDandLanguage.txt") >> ID;
    if (ifstream("_A3C_" + ID + ".cpp"))
        ifstream("_A3C_" + ID + ".cpp").ignore(12) >> best;
    ofstream("WrongAnswer.txt").close();
    ofstream("TimeLimitExceeded.txt").close();
    for (batch = 1; batch <= nBatch; total += weight[batch], ++batch)
        if (!system((".\\a.exe " + to_string(batch)).c_str()))
            score += weight[batch];
    if (best <= score) {
        ofstream("_A3C_" + ID + ".cpp") << "// " << ID << " " << score << "\n";
        system(("echo // %COMPUTERNAME% %USERNAME%>>_A3C_" + ID + ".cpp").c_str());
        ifstream fin("_A3C_Solution.cpp");
        ofstream("_A3C_" + ID + ".cpp", ios::app) << string("").assign(istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>());
    }
    cout << "Tentative score = " << double(score) / total << "/1\n", exit(0);
}
