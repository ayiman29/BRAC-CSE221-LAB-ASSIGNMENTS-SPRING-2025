#include<bits/extc++.h>
using namespace std;
mt19937 rng;
inline int randInt(int x, int y) { return uniform_int_distribution<int>(x, y + 1)(rng); }
inline string to_string(vector<int>& x) {
    string y = "[";
    if (!x.empty()) y += to_string(x[0]);
    for (int i = 1; i < x.size(); ++i)
        y += ", " + to_string(x[i]);
    return y + "]";
}
int test = 0, best = 0, score = 0, batch = 0, total = 0;
int timeLimit = 1, nBatch = 10, N = 0;
int weight[] = { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
int nTest[] = { 0, 10, 1000, 100000, 10, 100, 1000, 10000, 1, 10, 100 };
int maxN[] = { 0, 10, 10, 10, 100, 100, 100, 100, 1000, 1000, 1000 };
vector<int> sIDs, sMarks;
pair<int, vector<pair<int, int>>> res;
extern pair<int, vector<pair<int, int>>> solve(vector<int> sIDs, vector<int> sMarks);
inline void printCase(string& verdict, int test, vector<int> sIDs, vector<int> sMarks) {
    if (ifstream(verdict + ".txt").peek() == ifstream::traits_type::eof()) {
        ofstream fout(verdict + ".txt");
        fout << "batch = " << to_string(batch) << "\ntest = " << to_string(test) << "\n";
        fout << "N = " << to_string(sIDs.size()) << "\n";
        fout << "sIDs = " << to_string(sIDs) << "\n";
        fout << "sMarks = " << to_string(sMarks) << "\n";
    }
    cout << verdict << " on Batch " << batch << "\n";
}
inline void exitCase(string verdict) {
    printCase(verdict, test, sIDs, sMarks), exit(1);
}
inline void checkSoln() {
    vector<pair<int, int>> arr;
    arr.resize(N);
    for (int i = 0; i < N; ++i) arr[i] = make_pair(-sMarks[i], sIDs[i]);
    for (int i = 0, j; i < N; ++i) {
        j = min_element(arr.begin() + i, arr.end()) - arr.begin();
        if (i != j) swap(arr[i], arr[j]), --res.first;
    }
    for (int i = 0; i < N; ++i)
        arr[i] = make_pair(arr[i].second, -arr[i].first);
    if (res.first || arr != res.second) exitCase("WrongAnswer");
}
inline void processBatch() {
    for (test = 1; test <= nTest[batch]; ++test) {
        sIDs.clear(), sMarks.clear();
        sIDs.reserve(N = randInt(1, maxN[batch])), sMarks.reserve(N);
        for (int i = 1; i <= N; ++i)
            sIDs.push_back(i + 1000 - N), sMarks.push_back(randInt(1, 1000));
        shuffle(sIDs.begin(), sIDs.end(), rng);
        res = solve(sIDs, sMarks), checkSoln();
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
    if (ifstream("_A1F_" + ID + ".cpp"))
        ifstream("_A1F_" + ID + ".cpp").ignore(12) >> best;
    ofstream("WrongAnswer.txt").close();
    ofstream("TimeLimitExceeded.txt").close();
    for (batch = 1; batch <= nBatch; total += weight[batch], ++batch)
        if (!system((".\\a.exe " + to_string(batch)).c_str()))
            score += weight[batch];
    if (best <= score) {
        ofstream("_A1F_" + ID + ".cpp") << "// " << ID << " " << score << "\n";
        system(("echo // %COMPUTERNAME% %USERNAME%>>_A1F_" + ID + ".cpp").c_str());
        ifstream fin("_A1F_Solution.cpp");
        ofstream("_A1F_" + ID + ".cpp", ios::app) << string("").assign(istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>());
    }
    cout << "Tentative score = " << double(score) / total << "/1\n", exit(0);
}