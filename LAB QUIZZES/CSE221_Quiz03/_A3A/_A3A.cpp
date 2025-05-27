#include<bits/extc++.h>
using namespace std;
mt19937 rng;
inline int randInt(int x, int y) { return uniform_int_distribution<int>(x, y)(rng); }
chrono::_V2::system_clock::time_point start, finish;
chrono::_V2::system_clock::duration elapsed = std::chrono::system_clock::duration::zero();
int test = 0, best = 0, score = 0, batch = 0, total = 0;
int timeLimit = 1, nBatch = 14, N = 0;
int weight[] = { 0, 5, 5, 5, 5,   8,   8,   8,   8,    8,    8,    8,     8,     8,       8 };
int nTest[] = { 0, 1, 1, 1, 1, 100, 100,  10, 100,   10,  100,  100,    10,    10,      10 };
int maxN[] = { 0, 5, 5, 5, 7,  10,  20, 100, 100, 1000, 1000, 1000, 10000, 100000, 100000 };
vector<int> A;
long long res;
extern long long solve(vector<int> A);
inline string to_string(vector<int>& x) {
    string y = "[";
    if (!x.empty()) y += to_string(x[0]);
    for (int i = 1; i < x.size(); ++i)
        y += ", " + to_string(x[i]);
    return y + "]";
}
inline void printCase(string& verdict, int test, vector<int> A) {
    if (ifstream(verdict + ".txt").peek() == ifstream::traits_type::eof()) {
        ofstream fout(verdict + ".txt");
        fout << "batch = " << to_string(batch) << "\ntest = " << to_string(test) << "\n";
        fout << "N = " << to_string(A.size()) << "\n";
        fout << "A = " << to_string(A) << "\n";
    }
    cout << verdict << " on Batch " << batch << "\n";
}
inline void exitCase(string verdict) {
    printCase(verdict, test, A), exit(1);
}
inline void checkSoln() {
    start = chrono::high_resolution_clock::now();
    res = solve(A);
    finish = chrono::high_resolution_clock::now();
    elapsed += chrono::duration_cast<chrono::nanoseconds>(finish - start);
    if (std::chrono::seconds(timeLimit) < elapsed)
        exitCase("TimeLimitExceeded");
    vector<pair<int, int>> st;
    st.emplace_back(0, A.size() - 1);
    vector<int> temp(A.size());
    while (!st.empty()) {
        auto [a, b] = st.back();
        st.pop_back();
        if (a == b)continue;
        if (b < 0) {
            b = -b;
            int m = a + b >> 1;
            int i = a, j = m + 1;
            while (i <= m || j <= b) {
                if (i > m || j <= b and A[j] < A[i])
                    temp[i + j - a - m - 1] = A[j], j++;
                else
                    res -= j - m - 1, temp[i + j - a - m - 1] = A[i], i++;

            }
            for (int i = a; i <= b; i++)A[i] = temp[i - a];
        }
        else {
            int m = a + b >> 1;
            st.emplace_back(a, -b);
            st.emplace_back(a, m);
            st.emplace_back(m + 1, b);
        }
    }
    if (res != 0)
        exitCase("WrongAnswer");
}
inline void processBatch() {
    if (batch == 1) {
        test = 1;
        A = vector<int>({ 1, 2, 5, 4, 3 });
        N = A.size();
        checkSoln();
        return;
    }
    if (batch == 2) {
        test = 1;
        A = vector<int>({ 1, 2, 3, 4, 5 });
        N = A.size();
        checkSoln();
        return;
    }
    if (batch == 3) {
        test = 1;
        A = vector<int>({ 5, 4, 3, 2, 1 });
        N = A.size();
        checkSoln();
        return;
    }
    if (batch == 4) {
        test = 1;
        A = vector<int>({ 6, 4, 2, 5, 7, 3, 1 });
        N = A.size();
        checkSoln();
        return;
    }
    for (test = 1; test <= nTest[batch]; ++test) {
        A.clear();
        A.assign(N = randInt(1, maxN[batch]), 0);
        vector<int> temp(N + 1, 0);
        for (int i = 0; i < N; ++i) {
            A[i] = randInt(1, N);
            temp[A[i]]++;
        }
        for (int i = 1; i <= N; i++)temp[i] += temp[i - 1];
        for (int i = 0; i < N; i++)A[i] = temp[A[i]]--;
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
    if (ifstream("_A3A_" + ID + ".cpp"))
        ifstream("_A3A_" + ID + ".cpp").ignore(12) >> best;
    ofstream("WrongAnswer.txt").close();
    ofstream("TimeLimitExceeded.txt").close();
    for (batch = 1; batch <= nBatch; total += weight[batch], ++batch)
        if (!system((".\\a.exe " + to_string(batch)).c_str()))
            score += weight[batch];
    if (best <= score) {
        ofstream("_A3A_" + ID + ".cpp") << "// " << ID << " " << score << "\n";
        system(("echo // %COMPUTERNAME% %USERNAME%>>_A3A_" + ID + ".cpp").c_str());
        ifstream fin("_A3A_Solution.cpp");
        ofstream("_A3A_" + ID + ".cpp", ios::app) << string("").assign(istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>());
    }
    cout << "Tentative score = " << double(score) / total << "/1\n", exit(0);
}
