#include<bits/extc++.h>
using namespace std;
mt19937_64 rng;
inline int randInt(int x, int y) { return uniform_int_distribution<int>(x, y)(rng); }
inline long long randLong(long long x, long long y) { return uniform_int_distribution<long long>(x, y)(rng); }
chrono::_V2::system_clock::time_point start, finish;
chrono::_V2::system_clock::duration elapsed = std::chrono::system_clock::duration::zero();
int test = 0, best = 0, score = 0, batch = 0, total = 0;
int timeLimit = 1, nBatch = 13;
using LL = long long;
int N;
vector<pair<int, int>> edges;
vector<int> perm, par;
int res, o = 0;
int weight[] = { 0, 6, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8};
int nTest[] =  { 0, 1, 1, 1, 10000, 10000, 1000, 1000, 100, 100, 50, 50, 20, 20};
int maxN[] =   { 0, 5, 5, 8, 10,  10, 100, 100, 1000, 1000, 10000, 10000, 100000, 100000};
extern bool solve(int N, vector<pair<int, int>> edges);
template<class T>
inline string to_string(pair<T, T> &x) {
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
inline void printCase(string& verdict, int test, int N, vector<pair<int, int>> edges) {
    if (ifstream(verdict + ".txt").peek() == ifstream::traits_type::eof()) {
        ofstream fout(verdict + ".txt");
        fout << "batch = " << to_string(batch) << "\ntest = " << to_string(test) << "\n";
        fout << "N = " << to_string(N) << "\n";
        fout << "edges = " << to_string(edges) << "\n";
    }
    cout << verdict << " on Batch " << batch << "\n";
}
inline void exitCase(string verdict) {
    printCase(verdict, test, N, edges), exit(1);
}
inline void checkSoln() {
    start = chrono::high_resolution_clock::now();
    res = solve(N, edges);
    finish = chrono::high_resolution_clock::now();
    elapsed += chrono::duration_cast<chrono::nanoseconds>(finish - start);
    if (std::chrono::seconds(timeLimit) < elapsed)
        exitCase("TimeLimitExceeded");
    o = (o == 0 || o == 2);
    if(res != o)
        exitCase("WrongAnswer");
}
inline void processBatch() {
    if(batch == 1){
        N = 5;
        edges = {{0, 1}, {0, 2}, {0, 3}, {0, 4}, {1, 2}, {1, 3}, {2, 3}, {2, 4}, {3, 4}};
        o = 0;
        checkSoln();
        return;
    }else if(batch == 2){
        N = 5;
        edges = {{0, 1}, {0, 2}, {0, 3}, {2, 3}, {2, 4}, {3, 4}};
        o = 1;
        checkSoln();
        return;
    }else if(batch == 3){
        N = 8;
        edges = {{0, 2}, {0, 4}, {1, 0}, {1, 4}, {1, 6}, {1, 5}, {2, 4}, {2, 5}, {3, 2}, {4, 3}, {4, 7}, {5, 3}, {6, 4}, {6, 2}, {6, 5}, {7, 0}};
        o = 0;
        checkSoln();
        return;
    }
    for (test = 1; test <= nTest[batch]; ++test) {
        N = randInt(1, maxN[batch]);
        int M = randInt(N - 1, 2 * maxN[batch]);
        perm.resize(N);
        par.assign(N, 0);
        edges.clear();
        o = 0;
        for(int i = 0; i < N; i++)perm[i] = i;
        shuffle(perm.begin(), perm.end(), rng);
        for(int i = 1; i < N; i++){
            int u = perm[randInt(0, i - 1)];
            int v = perm[i];
            par[u]^=1, par[v]^=1;
            if(par[u] == par[v])o += 4 * par[u] - 2;
            edges.emplace_back(u, v);
            M--;
        }
        int A = randInt(0, 2);
        if(N <= 3 or A == 2){
            while(M > N / 2){
                int u = randInt(0, N - 1);
                int v = randInt(0, N - 1);
                par[u]^=1, par[v]^=1;
                if(u != v and par[u] == par[v])o += 4 * par[u] - 2;
                edges.emplace_back(u, v);
                M--;
            }
            vector<int> oo;
            for(int i = 0; i < N; i++)if(par[i])oo.push_back(i);
            shuffle(oo.begin(), oo.end(), rng);
            while(oo.size() > 2){
                int u = oo.back();
                oo.pop_back();
                int v = oo.back();
                oo.pop_back();
                par[u]^=1, par[v]^=1;
                if(u != v and par[u] == par[v])o += 4 * par[u] - 2;
                edges.emplace_back(u, v);
                M--;
            }
        }else{
            while(M > A){
                int u = randInt(0, N - 1);
                int v = randInt(0, N - 1);
                par[u]^=1, par[v]^=1;
                if(u != v and par[u] == par[v])o += 4 * par[u] - 2;
                edges.emplace_back(u, v);
                M--;
            }
            if(A == 1 and o <= 2){
                vector<int> ee;
                for(int i = 0; i < N; i++)if(!par[i])ee.push_back(i);
                int u = ee[0];
                int v = ee[1];
                par[u]^=1, par[v]^=1;
                if(u != v and par[u] == par[v])o += 4 * par[u] - 2;
                edges.emplace_back(u, v);
                M--;
            }
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
    if (ifstream("_A4D_" + ID + ".cpp"))
        ifstream("_A4D_" + ID + ".cpp").ignore(12) >> best;
    ofstream("WrongAnswer.txt").close();
    ofstream("TimeLimitExceeded.txt").close();
    for (batch = 1; batch <= nBatch; total += weight[batch], ++batch)
        if (!system((".\\a.exe " + to_string(batch)).c_str()))
            score += weight[batch];
    if (best <= score) {
        ofstream("_A4D_" + ID + ".cpp") << "// " << ID << " " << score << "\n";
        system(("echo // %COMPUTERNAME% %USERNAME%>>_A4D_" + ID + ".cpp").c_str());
        ifstream fin("_A4D_Solution.cpp");
        ofstream("_A4D_" + ID + ".cpp", ios::app) << string("").assign(istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>());
    }
    cout << "Tentative score = " << double(score) / total << "/1\n", exit(0);
}
