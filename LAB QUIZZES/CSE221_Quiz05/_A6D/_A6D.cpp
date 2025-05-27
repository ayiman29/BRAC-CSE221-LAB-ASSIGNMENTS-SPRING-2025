#include<bits/extc++.h>
using namespace std;
mt19937_64 rng;
inline int randInt(int x, int y) { return uniform_int_distribution<int>(x, y)(rng); }
inline long long randLong(long long x, long long y) { return uniform_int_distribution<long long>(x, y)(rng); }
chrono::_V2::system_clock::time_point start, finish;
chrono::_V2::system_clock::duration elapsed = std::chrono::system_clock::duration::zero();
int test = 0, best = 0, score = 0, batch = 0, total = 0;
int timeLimit = 2, nBatch = 14;
using LL = long long;
int N, R;
vector<pair<int, int>> edges;
vector<int> res;
int weight[] = { 0, 5, 5, 5, 5, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8};
int nTest[] =  { 0, 1, 1, 1, 1, 40, 40, 40, 40, 20, 20, 10, 10, 5, 5};
extern vector<int> solve(int N, int R, vector<pair<int, int>> edges);

template<class K, class V>
inline string to_string(const pair<K, V> &x){
    return "{" + to_string(x.first) + ", " + to_string(x.second) + "}";
}
template<class T>
inline string to_string(vector<T>& x) {
    string y = "[";
    if (!x.empty()) y += to_string(x[0]);
    for (int i = 1; i < x.size(); ++i)
        y += ", " + to_string(x[i]);
    return y + "]";
}
inline void printCase(string& verdict, int test, int N, int R, vector<pair<int, int>> edges) {
    if (ifstream(verdict + ".txt").peek() == ifstream::traits_type::eof()) {
        ofstream fout(verdict + ".txt");
        fout << "batch = " << to_string(batch) << "\ntest = " << to_string(test) << "\n";
        fout << "N = " << to_string(N) << "\n";
        fout << "R = " << to_string(R) << "\n";
        fout << "edges = " << to_string(edges) << "\n";
    }
    cout << verdict << " on Batch " << batch << "\n";
}

inline void exitCase(string verdict) {
    printCase(verdict, test, N, R, edges), exit(1);
}
inline void checkSoln() {
    start = chrono::high_resolution_clock::now();
    res = solve(N, R, edges);
    finish = chrono::high_resolution_clock::now();
    elapsed += chrono::duration_cast<chrono::nanoseconds>(finish - start);
    if (std::chrono::seconds(timeLimit) < elapsed)
        exitCase("TimeLimitExceeded");
    if (res.size() != N + 1)
        exitCase("WrongAnswer");

    ofstream fout("_A6D_output.txt");
    //Write output
    res[0] = 0;
    for(int i = 0; i <= N; ++i) {
        fout << res[i] << " \n"[i == N];
    }

    //Write output done
    fout.close();
    int stat = system("_A6D_Judge.out  _A6D_input.txt _A6D_output.txt");
    if(stat != 0)
        exitCase("WrongAnswer");
}
inline void processBatch() {
    for (test = 1; test <= nTest[batch]; ++test) {
        string cmd = "_A6D_Gen.out " + to_string(batch) + " " + to_string(test) + " > _A6D_input.txt";
        system(cmd.c_str());
        ifstream fin("_A6D_input.txt");
        
        //READ INPUT
        fin >> N >> R;
        edges.resize(N - 1);
        for(auto &[x, y] : edges)
            fin >> x >> y;
            
        //INPUT READING DONE
        
        fin.close();
        
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
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    if (argc == 2) rng.seed(batch = stoi(argv[1]));
    if (1 <= batch && batch <= nBatch) {
        cout << "Running on Batch " << batch << endl;
        thread(limitTime).detach(), processBatch();
        cout << fixed << setprecision(9) << "Accepted on Batch " << batch << " in " << (elapsed.count() * 1e-9) << "s\n", exit(0);
    }
    string ID;
    ifstream("EnterIDandLanguage.txt") >> ID;
    if (ifstream("_A6D_" + ID + ".cpp"))
        ifstream("_A6D_" + ID + ".cpp").ignore(12) >> best;
    ofstream("WrongAnswer.txt").close();
    ofstream("TimeLimitExceeded.txt").close();
    for (batch = 1; batch <= nBatch; total += weight[batch], ++batch)
        if (!system((".\\a.exe " + to_string(batch)).c_str()))
            score += weight[batch];
    if (best <= score) {
        ofstream("_A6D_" + ID + ".cpp") << "// " << ID << " " << score << "\n";
        system(("echo // %COMPUTERNAME% %USERNAME%>>_A6D_" + ID + ".cpp").c_str());
        ifstream fin("_A6D_Solution.cpp");
        ofstream("_A6D_" + ID + ".cpp", ios::app) << string("").assign(istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>());
    }
    cout << "Tentative score = " << double(score) / total << "/1\n", exit(0);
}
