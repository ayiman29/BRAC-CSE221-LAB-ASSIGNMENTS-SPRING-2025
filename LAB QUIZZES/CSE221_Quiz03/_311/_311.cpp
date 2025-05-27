#include<bits/extc++.h>
using namespace std;
mt19937 rng;
inline int randInt(int x, int y) { return uniform_int_distribution<int>(x, y)(rng); }
chrono::_V2::system_clock::time_point start, finish;
chrono::_V2::system_clock::duration elapsed = std::chrono::system_clock::duration::zero();
int test = 0, best = 0, score = 0, batch = 0, total = 0;
int timeLimit = 1, nBatch = 20, nSample = 4, N = 0;
int weight[] = { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
int nTest[] = { 0, 1, 1, 1, 1, 100, 10, 1, 1000, 100, 10, 1, 10000, 1000, 100, 10, 100000, 10000, 1000, 100, 10 };
int maxNM[] = { 0, 10, 10, 50, 100, 10, 500, 1000, 50, 100, 5000, 10000, 10, 500, 1000, 50000, 50, 100, 1000, 50000, 500000 };
vector<int> arr;
vector< vector<int> > samples = { {}, {4, 2, 1, 5, 3}, {1, 4, 3, 10}, {9, 6, 400000, 2, 12, 5, 300000, 7, 1, 15, 13}, {23, 11, 5, 2} };
int res;
extern int solve(vector<int> arr);
inline string to_string(vector<int>& x) {
    string y = "[";
    if (!x.empty()) y += to_string(x[0]);
    for (int i = 1; i < x.size(); ++i)
        y += ", " + to_string(x[i]);
    return y + "]";
}
inline void printCase(string& verdict, int test, vector<int> arr) {
    if (ifstream(verdict + ".txt").peek() == ifstream::traits_type::eof()) {
        ofstream fout(verdict + ".txt");
        fout << "batch = " << to_string(batch) << "\ntest = " << to_string(test) << "\n";
        fout << "N = " << to_string(arr.size()) << "\n";
        fout << "arr = " << to_string(arr) << "\n";
    }
    cout << verdict << " on Batch " << batch << "\n";
}
inline void exitCase(string verdict) {
    printCase(verdict, test, arr), exit(1);
}

inline int count(vector<int>& nums, int st, int ed) {
    if (st >= ed) return 0;
    int mid = st + (ed - st) / 2;
    int tot = count(nums, st, mid) + count(nums, mid + 1, ed);
    
    int j = mid + 1;
    for (int i = st; i <= mid; i++) {
        while (j <= ed && nums[i] > 2LL * nums[j]) {
            j++;
        }
        tot += (j - (mid + 1));
    }

    vector<int> temp;
    int left = st, right = mid + 1;
    while (left <= mid && right <= ed) {
        if (nums[left] <= nums[right]) {
            temp.push_back(nums[left++]);
        } else {
            temp.push_back(nums[right++]);
        }
    }
    while (left <= mid) temp.push_back(nums[left++]);
    while (right <= ed) temp.push_back(nums[right++]);
    
    for (int i = st; i <= ed; i++) {
        nums[i] = temp[i - st];
    }

    return tot;
}
inline void checkSoln() {
    start = chrono::high_resolution_clock::now();
    res = solve(arr);
    finish = chrono::high_resolution_clock::now();
    elapsed += chrono::duration_cast<chrono::nanoseconds>(finish - start);
    if (std::chrono::seconds(timeLimit) < elapsed)
        exitCase("TimeLimitExceeded");
    int k = count(arr,0,arr.size()-1);
    if (k != res) exitCase("WrongAnswer");
}
inline void processBatch() {
    if (batch <= nSample) {
        test = 1;
        arr = samples[batch];
        N = arr.size();
        checkSoln();
        return;
    }
    for (test = 1; test <= nTest[batch]; ++test) {
        arr.clear();
        arr.reserve(N = randInt(1, maxNM[batch]));
        for (int i = 0; i < N; ++i) {
            arr.push_back(randInt(1, 500000));
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
    if (ifstream("_311_" + ID + ".cpp"))
        ifstream("_311_" + ID + ".cpp").ignore(12) >> best;
    ofstream("WrongAnswer.txt").close();
    ofstream("TimeLimitExceeded.txt").close();
    for (batch = 1; batch <= nBatch; total += weight[batch], ++batch)
        if (!system((".\\a.exe " + to_string(batch)).c_str()))
            score += weight[batch];
    if (best <= score) {
        ofstream("_311_" + ID + ".cpp") << "// " << ID << " " << score << "\n";
        system(("echo // %COMPUTERNAME% %USERNAME%>>_311_" + ID + ".cpp").c_str());
        ifstream fin("_311_Solution.cpp");
        ofstream("_311_" + ID + ".cpp", ios::app) << string("").assign(istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>());
    }
    cout << "Tentative score = " << double(score) / total << "/1\n", exit(0);
}
