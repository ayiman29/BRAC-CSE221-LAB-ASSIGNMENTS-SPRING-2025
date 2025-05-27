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
int N;
int X1, Y1, X2, Y2;
int res;
int weight[] = { 0, 5, 5, 5, 5, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8};
int nTest[] =  { 0, 1, 1, 1, 1, 40, 40, 40, 40, 20, 20, 10, 10, 5, 5};
extern int solve(int N, int X1, int Y1, int X2, int Y2);

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
inline void printCase(string& verdict, int test, int N, int X1, int Y1, int X2, int Y2) {
    if (ifstream(verdict + ".txt").peek() == ifstream::traits_type::eof()) {
        ofstream fout(verdict + ".txt");
        fout << "batch = " << to_string(batch) << "\ntest = " << to_string(test) << "\n";
        fout << "N = " << to_string(N) << "\n";
        fout << "X1 = " << to_string(X1) << "\n";
        fout << "Y1 = " << to_string(Y1) << "\n";
        fout << "X2 = " << to_string(X2) << "\n";
        fout << "Y2 = " << to_string(Y2) << "\n";
    }
    cout << verdict << " on Batch " << batch << "\n";
}
inline void exitCase(string verdict) {
    printCase(verdict, test, N, X1, Y1, X2, Y2), exit(1);
}
inline void checkSoln() {
    start = chrono::high_resolution_clock::now();
    res = solve(N, X1, Y1, X2, Y2);
    finish = chrono::high_resolution_clock::now();
    elapsed += chrono::duration_cast<chrono::nanoseconds>(finish - start);
    if (std::chrono::seconds(timeLimit) < elapsed)
        exitCase("TimeLimitExceeded");
    
    ofstream fout("_A6C_output.txt");
    //Write output
    fout << res << "\n";

    //Write output done
    fout.close();
    int stat = system("_A6C_Judge.out  _A6C_input.txt _A6C_output.txt");
    if(stat != 0)
        exitCase("WrongAnswer");
}
inline void processBatch() {
    for (test = 1; test <= nTest[batch]; ++test) {
        string cmd = "_A6C_Gen.out " + to_string(batch) + " " + to_string(test) + " > _A6C_input.txt";
        system(cmd.c_str());
        ifstream fin("_A6C_input.txt");
        
        //READ INPUT
        fin >> N;
        fin >> X1 >> Y1 >> X2 >> Y2;
            
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
    if (ifstream("_A6C_" + ID + ".cpp"))
        ifstream("_A6C_" + ID + ".cpp").ignore(12) >> best;
    ofstream("WrongAnswer.txt").close();
    ofstream("TimeLimitExceeded.txt").close();
    for (batch = 1; batch <= nBatch; total += weight[batch], ++batch)
        if (!system((".\\a.exe " + to_string(batch)).c_str()))
            score += weight[batch];
    if (best <= score) {
        ofstream("_A6C_" + ID + ".cpp") << "// " << ID << " " << score << "\n";
        system(("echo // %COMPUTERNAME% %USERNAME%>>_A6C_" + ID + ".cpp").c_str());
        ifstream fin("_A6C_Solution.cpp");
        ofstream("_A6C_" + ID + ".cpp", ios::app) << string("").assign(istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>());
    }
    cout << "Tentative score = " << double(score) / total << "/1\n", exit(0);
}
