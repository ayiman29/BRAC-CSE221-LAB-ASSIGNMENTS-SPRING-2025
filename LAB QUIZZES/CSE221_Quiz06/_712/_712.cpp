#include<bits/extc++.h>
using namespace std;
mt19937_64 rng;
inline int randInt(int x, int y) { return uniform_int_distribution<int>(x, y)(rng); }
inline long long randLong(long long x, long long y) { return uniform_int_distribution<long long>(x, y)(rng); }
chrono::_V2::system_clock::time_point start, finish;
chrono::_V2::system_clock::duration elapsed = std::chrono::system_clock::duration::zero();
int test = 0, best = 0, score = 0, batch = 0, total = 0;
int timeLimit = 1, nBatch = 10;
using LL = long long;
using pii = pair<int, int>;
int N, M, X, Y, Z, S, D, K;
vector<int> arr;
vector<int> edj[200009];
vector<pair<pii, int> > edges;
vector<int> u, v, w;
int res;
int weight[] = { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
int nTest[] =  { 0, 1, 50, 100, 100, 50, 20, 50, 50, 20, 50};
extern int solve(int N, int M, int S, int D, int K, vector< pair< pair<int, int>, int > > edges);
vector<pair<int, int> > vv = {make_pair(2,2), make_pair(3,1)};

inline string to_string(pair<int, int> p)
{
    string y = "";
    y += to_string(p.first) + " " + to_string(p.second) + "\n";
    return y;
}
inline string to_string(vector<pair<int, int> > vp)
{
    string y = "";
    for(pair<int, int> p : vp)
    {
        y += to_string(p.first) + " " + to_string(p.second) + "\n";
    }
    return y;
}
inline string to_string(vector<pair<pii, int> > vp)
{
    string y = "";
    for(pair<pii, int> p : vp)
    {
        y += to_string(p.first.first) + " " + to_string(p.first.second) + " " + to_string(p.second) +"\n";
    }
    return y;
}
template<class T>
inline string to_string(vector<T>& x) {
    string y = "[";
    if (!x.empty()) y += to_string(x[0]);
    for (int i = 1; i < x.size(); ++i)
        y += ", " + to_string(x[i]);
    return y + "]";
}

inline void printCase(string& verdict, int test, int N, int M, int S, int D, int K, vector<pair<pii, int> > edges) {
    if (ifstream(verdict + ".txt").peek() == ifstream::traits_type::eof()) {
        ofstream fout(verdict + ".txt");
        fout << "batch = " << to_string(batch) << "\ntest = " << to_string(test) << "\n";
        fout << "N = " << to_string(N) << "\n";
        fout << "M = " << to_string(M) << "\n";
        fout << "S = " << to_string(S) << "\n";
        fout << "D = " << to_string(D) << "\n";
        fout << "K = " << to_string(K) << "\n";
        fout << "edges = " << "\n" << to_string(edges) << "\n";
    }
    cout << verdict << " on Batch " << batch << "\n";
}
inline void exitCase(string verdict) {
    printCase(verdict, test, N, M, S, D, K, edges), exit(1);
}
inline void checkSoln() {
    start = chrono::high_resolution_clock::now();
    res = solve(N, M, S, D, K, edges);
    finish = chrono::high_resolution_clock::now();
    elapsed += chrono::duration_cast<chrono::nanoseconds>(finish - start);
    if (std::chrono::seconds(timeLimit) < elapsed)
        exitCase("TimeLimitExceeded");
    
    ofstream fout("_712_output.txt");
    //Write output
    fout << res << "\n";
    //Write output done
    fout.close();
    int stat = system("_712_Judge.out  _712_input.txt _712_output.txt");
    if(stat != 0)
        exitCase("WrongAnswer");
}
inline void processBatch() {
    for (test = 1; test <= nTest[batch]; ++test) {
        string cmd = "_712_Gen.out " + to_string(batch) + " " + to_string(test) + " > _712_input.txt";
        system(cmd.c_str());
        ifstream fin("_712_input.txt");
        edges.clear();
        //READ INPUT
        u.clear();
        v.clear();
        w.clear();
        fin >> N >> M >> S >> D >> K;
        
        for(int i = 0; i<M; i++)
        {
            X;
            fin >> X;
            u.push_back(X);
        }
        for(int i = 0; i<M; i++)
        {
            Y;
            fin >> Y;
            v.push_back(Y);
        }
        for(int i = 0; i<M; i++)
        {
            Z;
            fin >> Z;
            w.push_back(Z);
        }    

        for(int i = 0; i<M; i++)
        {
            pii p = make_pair(u[i],v[i]);
            edges.push_back(make_pair(p,w[i]));
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
    if (ifstream("_712_" + ID + ".cpp"))
        ifstream("_712_" + ID + ".cpp").ignore(12) >> best;
    ofstream("WrongAnswer.txt").close();
    ofstream("TimeLimitExceeded.txt").close();
    for (batch = 1; batch <= nBatch; total += weight[batch], ++batch)
        if (!system((".\\a.exe " + to_string(batch)).c_str()))
            score += weight[batch];
    if (best <= score) {
        ofstream("_712_" + ID + ".cpp") << "// " << ID << " " << score << "\n";
        system(("echo // %COMPUTERNAME% %USERNAME%>>_712_" + ID + ".cpp").c_str());
        ifstream fin("_712_Solution.cpp");
        ofstream("_712_" + ID + ".cpp", ios::app) << string("").assign(istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>());
    }
    cout << "Tentative score = " << double(score) / total << "/1\n", exit(0);
}
