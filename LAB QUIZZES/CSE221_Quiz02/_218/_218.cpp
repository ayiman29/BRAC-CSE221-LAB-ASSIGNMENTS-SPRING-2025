#include<bits/extc++.h>
using namespace std;
mt19937 rng;
inline int randInt(int x, int y) { return uniform_int_distribution<int>(x, y)(rng); }
chrono::_V2::system_clock::time_point start, finish;
chrono::_V2::system_clock::duration elapsed = std::chrono::system_clock::duration::zero();
int test = 0, best = 0, score = 0, batch = 0, total = 0;
int timeLimit = 1, nBatch = 25, N = 0, M = 0;
int weight[] = { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
int nTest[] = { 0, 2, 10, 1, 100, 10, 1, 1000, 100, 10, 1, 10000, 1000, 100, 10, 1, 100000, 10000, 1000, 100, 10, 100000, 10000, 1000, 100, 10 };
int maxNM[] = { 0, 10, 10, 100, 10, 100, 1000, 10, 100, 1000, 10000, 10, 100, 1000, 10000, 100000, 10, 100, 1000, 10000, 100000, 100, 1000, 10000, 100000, 1000000 };
vector<int> list1, list2, res;
extern vector<int> solve(vector<int> list1, vector<int> list2);
inline string to_string(vector<int>& x) {
    string y = "[";
    if (!x.empty()) y += to_string(x[0]);
    for (int i = 1; i < x.size(); ++i)
        y += ", " + to_string(x[i]);
    return y + "]";
}
inline void printCase(string& verdict, int test, vector<int> list1, vector<int> list2) {
    if (ifstream(verdict + ".txt").peek() == ifstream::traits_type::eof()) {
        ofstream fout(verdict + ".txt");
        fout << "batch = " << to_string(batch) << "\ntest = " << to_string(test) << "\n";
        fout << "N = " << to_string(list1.size()) << "\n";
        fout << "M = " << to_string(list2.size()) << "\n";
        fout << "list1 = " << to_string(list1) << "\n";
        fout << "list2 = " << to_string(list2) << "\n";
    }
    cout << verdict << " on Batch " << batch << "\n";
}
inline void exitCase(string verdict) {
    printCase(verdict, test, list1, list2), exit(1);
}
inline void checkSoln() {
    start = chrono::high_resolution_clock::now();
    res = solve(list1, list2);
    finish = chrono::high_resolution_clock::now();
    elapsed += chrono::duration_cast<chrono::nanoseconds>(finish - start);
    if (std::chrono::seconds(timeLimit) < elapsed)
        exitCase("TimeLimitExceeded");
    int k = 0;
    for (int i = list1.size() - 1, j = list2.size() - 1; 0 <= i || 0 <= j; ++k) {
        if (k == res.size() || ((0 <= i && res[k] != list1[i]) && (0 <= j && res[k] != list2[j])))
            exitCase("WrongAnswer");
        for (; 0 <= i && list1[i] == res[k]; --i);
        for (; 0 <= j && list2[j] == res[k]; --j);
    }
    if (k != res.size() || !is_sorted(res.rbegin(), res.rend())) exitCase("WrongAnswer");
}
inline void processBatch() {
    if (batch == 1) {
        test = 1;
        list1 = vector<int>({ 1, 2, 2, 3, 4 });
        list2 = vector<int>({ 2, 2, 3, 3, 5, 6 });
        N = list1.size();
        M = list2.size();
        checkSoln();
        test = 2;
        list1 = vector<int>({ 2, 4, 5, 5, 8, 9, 9, 12, 15 });
        list2 = vector<int>({ 1, 1, 5, 6, 7, 12, 12, 20 });
        N = list1.size();
        M = list2.size();
        checkSoln();
        return;
    }
    for (test = 1; test <= nTest[batch]; ++test) {
        list1.clear();
        list2.clear();
        list1.reserve(N = randInt(1, maxNM[batch]));
        list2.reserve(M = randInt(1, maxNM[batch]));
        for (int i = 0; i < N; ++i) {
            if (i && randInt(0, 1)) list1.push_back(0);
            else list1.push_back(randInt(1, 1000000000 / N));
            if (i) list1[i] = min(1000000000, list1[i] + list1[i - 1]);
        }
        for (int i = 0; i < M; ++i) {
            if (i && randInt(0, 1)) list2.push_back(0);
            else list2.push_back(randInt(1, 1000000000 / M));
            if (i) list2[i] = min(1000000000, list2[i] + list2[i - 1]);
        }
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
    if (ifstream("_218_" + ID + ".cpp"))
        ifstream("_218_" + ID + ".cpp").ignore(12) >> best;
    ofstream("WrongAnswer.txt").close();
    ofstream("TimeLimitExceeded.txt").close();
    for (batch = 1; batch <= nBatch; total += weight[batch], ++batch)
        if (!system((".\\a.exe " + to_string(batch)).c_str()))
            score += weight[batch];
    if (best <= score) {
        ofstream("_218_" + ID + ".cpp") << "// " << ID << " " << score << "\n";
        system(("echo // %COMPUTERNAME% %USERNAME%>>_218_" + ID + ".cpp").c_str());
        ifstream fin("_218_Solution.cpp");
        ofstream("_218_" + ID + ".cpp", ios::app) << string("").assign(istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>());
    }
    cout << "Tentative score = " << double(score) / total << "/1\n", exit(0);
}