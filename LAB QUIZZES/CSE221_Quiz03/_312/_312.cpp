#include<bits/extc++.h>
using namespace std;
mt19937 rng;
inline int randInt(int x, int y) { return uniform_int_distribution<int>(x, y)(rng); }
chrono::_V2::system_clock::time_point start, finish;
chrono::_V2::system_clock::duration elapsed = std::chrono::system_clock::duration::zero();
int test = 0, best = 0, score = 0, batch = 0, total = 0;
int timeLimit = 1, sBatch = 2, nBatch = 10, N = 0;
int weight[] = { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
int nTest[] = { 0, 1, 1, 1, 1, 100, 10000, 1, 100, 10000, 1000000 };
int maxNM[] = { 0, 5, 10, 100, 1000, 100, 10, 10000, 1000, 100, 10 };
vector<int> preOrderSample[3] = { vector<int>(), vector<int>({3, 9, 20, 15, 7}), vector<int>({1, 2, 3, 4, 5, 6, 7, 8, 9, 500000}) };
vector<int> postOrderSample[3] = { vector<int>(), vector<int>({9, 15, 7, 20, 3}), vector<int>({500000, 9, 8, 7, 6, 5, 4, 3, 2, 1}) };
vector<int> preOrder, postOrder, result, newOrder;
extern vector<int> solve(vector<int> preOrder, vector<int> postOrder);
inline string to_string(vector<int>& x) {
    string y = "[";
    if (!x.empty()) y += to_string(x[0]);
    for (int i = 1; i < x.size(); ++i)
        y += ", " + to_string(x[i]);
    return y + "]";
}
inline void printCase(string& verdict, int test, vector<int> preOrder, vector<int> postOrder) {
    if (ifstream(verdict + ".txt").peek() == ifstream::traits_type::eof()) {
        ofstream fout(verdict + ".txt");
        fout << "batch = " << to_string(batch) << "\ntest = " << to_string(test) << "\n";
        fout << "N = " << to_string(preOrder.size()) << "\n";
        fout << "preOrder = " << to_string(preOrder) << "\n";
        fout << "postOrder = " << to_string(postOrder) << "\n";
    }
    cout << verdict << " on Batch " << batch << "\n";
}
inline void exitCase(string verdict) {
    printCase(verdict, test, preOrder, postOrder), exit(1);
}
void build2(int preLeft, int resLeft, int span) {
    if (span < 1) return;
    for (int i = 0; ; ++i) if (preOrder[preLeft] == result[resLeft + i]) {
        build2(preLeft + 1, resLeft, i);
        build2(preLeft + 1 + i, resLeft + i + 1, span - 1 - i);
        break;
    }
    newOrder.push_back(preOrder[preLeft]);
}
inline void checkSoln() {
    start = chrono::high_resolution_clock::now();
    result = solve(preOrder, postOrder);
    finish = chrono::high_resolution_clock::now();
    elapsed += chrono::duration_cast<chrono::nanoseconds>(finish - start);
    if (std::chrono::seconds(timeLimit) < elapsed)
        exitCase("TimeLimitExceeded");
    if (result.size() != N) exitCase("WrongAnswer");
    newOrder.clear(), newOrder.reserve(N), build2(0, 0, N);
    if (postOrder != newOrder) exitCase("WrongAnswer");
}
void build(int left, int right) {
    if (right < left) return;
    if (left < right) {
        int mid = randInt(left + 1, right);
        build(left + 1, mid);
        build(mid + 1, right);
    }
    postOrder.push_back(preOrder[left]);
}
inline void processBatch() {
    if (batch <= sBatch) {
        test = 1;
        preOrder = preOrderSample[batch];
        postOrder = postOrderSample[batch];
        N = preOrder.size();
        checkSoln();
        return;
    }
    for (test = 1; test <= nTest[batch]; ++test) {
        N = randInt(1, maxNM[batch]);
        preOrder.clear();
        postOrder.clear();
        preOrder.reserve(N);
        postOrder.reserve(N);
        __gnu_pbds::gp_hash_table<int, __gnu_pbds::null_type> hashTable;
        for (int i = 0, j; i < N; ++i) {
            while (hashTable.find(j = randInt(1, 500000)) != hashTable.end());
            hashTable.insert(j), preOrder.push_back(j);
        }
        build(0, N - 1), checkSoln();
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
    if (ifstream("_312_" + ID + ".cpp"))
        ifstream("_312_" + ID + ".cpp").ignore(12) >> best;
    ofstream("WrongAnswer.txt").close();
    ofstream("TimeLimitExceeded.txt").close();
    for (batch = 1; batch <= nBatch; total += weight[batch], ++batch)
        if (!system((".\\a.exe " + to_string(batch)).c_str()))
            score += weight[batch];
    if (best <= score) {
        ofstream("_312_" + ID + ".cpp") << "// " << ID << " " << score << "\n";
        system(("echo // %COMPUTERNAME% %USERNAME%>>_312_" + ID + ".cpp").c_str());
        ifstream fin("_312_Solution.cpp");
        ofstream("_312_" + ID + ".cpp", ios::app) << string("").assign(istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>());
    }
    cout << "Tentative score = " << double(score) / total << "/1\n", exit(0);
}