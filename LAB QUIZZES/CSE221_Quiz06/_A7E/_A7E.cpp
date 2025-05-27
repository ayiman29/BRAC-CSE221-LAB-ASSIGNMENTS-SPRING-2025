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
int N, M;
vector<int> Us, Vs, Ws;
long long res;
int weight[] = { 0, 5, 5, 5, 5, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8};
int nTest[] =  { 0, 1, 1, 1, 1, 40, 40, 40, 40, 20, 20, 10, 10, 5, 5};
extern long long solve(int N, int M, vector<int> &Us, vector<int> &Vs, vector<int> &Ws);

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
inline void printCase(string& verdict, int test, int N, int M, vector<int>& Us, vector<int>& Vs, vector<int>& Ws) {
    if (ifstream(verdict + ".txt").peek() == ifstream::traits_type::eof()) {
        ofstream fout(verdict + ".txt");
        fout << "batch = " << to_string(batch) << "\ntest = " << to_string(test) << "\n";
        fout << "N = " << to_string(N) << "\n";
        fout << "M = " << to_string(M) << "\n";
        fout << "Us = " << to_string(Us) << "\n";
        fout << "Vs = " << to_string(Vs) << "\n";
        fout << "Ws = " << to_string(Ws) << "\n";
    }
    cout << verdict << " on Batch " << batch << "\n";
}

inline void exitCase(string verdict) {
    printCase(verdict, test, N, M, Us, Vs, Ws), exit(1);
}
inline void checkSoln() {
    start = chrono::high_resolution_clock::now();
    res = solve(N, M, Us, Vs, Ws);
    finish = chrono::high_resolution_clock::now();
    elapsed += chrono::duration_cast<chrono::nanoseconds>(finish - start);
    if (std::chrono::seconds(timeLimit) < elapsed)
        exitCase("TimeLimitExceeded");

    ofstream fout("_A7E_output.txt");
    //Write output
    fout << res << "\n";
    //Write output done
    fout.close();
    int stat = system("_A7E_Judge.out  _A7E_input.txt _A7E_output.txt");
    if(stat != 0)
        exitCase("WrongAnswer");
}
inline void processBatch() {
    for (test = 1; test <= nTest[batch]; ++test) {
        string cmd = "_A7E_Gen.out " + to_string(batch) + " " + to_string(test) + " > _A7E_input.txt";
        system(cmd.c_str());
        ifstream fin("_A7E_input.txt");
        
        //READ INPUT
        fin >> N >> M;
        Us.resize(M), Vs.resize(M), Ws.resize(M);
        for (int i = 0; i < M; ++i) {
            fin >> Us[i] >> Vs[i] >> Ws[i];
        }
            
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
    if (ifstream("_A7E_" + ID + ".cpp"))
        ifstream("_A7E_" + ID + ".cpp").ignore(12) >> best;
    ofstream("WrongAnswer.txt").close();
    ofstream("TimeLimitExceeded.txt").close();
    for (batch = 1; batch <= nBatch; total += weight[batch], ++batch)
        if (!system((".\\a.exe " + to_string(batch)).c_str()))
            score += weight[batch];
    if (best <= score) {
        ofstream("_A7E_" + ID + ".cpp") << "// " << ID << " " << score << "\n";
        system(("echo // %COMPUTERNAME% %USERNAME%>>_A7E_" + ID + ".cpp").c_str());
        ifstream fin("_A7E_Solution.cpp");
        ofstream("_A7E_" + ID + ".cpp", ios::app) << string("").assign(istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>());
    }
    cout << "Tentative score = " << double(score) / total << "/1\n", exit(0);
}
