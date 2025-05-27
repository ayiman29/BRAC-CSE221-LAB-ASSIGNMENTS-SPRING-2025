#include<bits/extc++.h>
using namespace std;
mt19937 rng;
inline int randInt(int x, int y) { return uniform_int_distribution<int>(x, y)(rng); }
chrono::_V2::system_clock::time_point start, finish;
chrono::_V2::system_clock::duration elapsed = std::chrono::system_clock::duration::zero();
int test = 0, best = 0, score = 0, batch = 0, total = 0;
int timeLimit = 1, nBatch = 10, nSample = 2, N = 0, M = 0;
int weight[] = { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
int nTest[] = { 0, 1, 1, 100, 10,  1000, 10, 1,   100,    1000, 100 };
int maxNM[] = { 0, 10, 100, 10, 500,  50,  5000, 10000,   1000,   1000, 5000 };
vector<pair<int, int>> arr;
vector<vector<pair<int, int> > > sampleArr = {
    {},
    {{7,7}},
    {{1,1},{1,2}}
};
vector<int> sampleN = {0, 10, 2};
vector<int> sampleinitX = {0, 6, 2};
vector<int> sampleinitY = {0, 7, 2};
vector<int> sampleAns = {0, 7, 1};
vector< vector<int> > samples = { {}, {4, 2, 1, 5, 3}, {1, 4, 3, 10}, {9, 6, 400000, 2, 12, 5, 300000, 7, 1, 15, 13}, {23, 11, 5, 2} };
int res;
int initX = -1, initY = -1;
extern int solve(int N, int initX, int initY, vector<pair<int, int> > arr);
inline string to_string(vector<int>& x) {
    string y = "[";
    if (!x.empty()) y += to_string(x[0]);
    for (int i = 1; i < x.size(); ++i)
        y += ", " + to_string(x[i]);
    return y + "]";
}
inline string to_string(vector<pair<int, int> > &x)
{
    string y = "[";
    if(!x.empty()) y+="(" + to_string(x[0].first) + ", " + to_string(x[0].second) + ")";
    for (int i = 1; i<x.size(); ++i)
    {
        y+= ", (" + to_string(x[i].first) + ", " + to_string(x[i].second) + ")";
    }  
    return y + "]";
}
inline void printCase(string& verdict, int test, int N, int initX, int initY, vector<pair<int, int> > arr) {
    if (ifstream(verdict + ".txt").peek() == ifstream::traits_type::eof()) {
        ofstream fout(verdict + ".txt");
        fout << "batch = " << to_string(batch) << "\ntest = " << to_string(test) << "\n";
        fout << "N = " << N << "\n";
        fout << "M = " << to_string(arr.size()) << "\n";
        fout << "arr = " << to_string(arr) << "\n";
        fout << "initX = " << initX << "\n";
        fout << "initY = " << initY << "\n";
    }
    cout << verdict << " on Batch " << batch << "\n";
}
inline void exitCase(string verdict) {
    printCase(verdict, test, N, initX, initY, arr), exit(1);
}

inline void checkSoln(int val) {
    start = chrono::high_resolution_clock::now();
    res = solve(N, initX, initY, arr);
    finish = chrono::high_resolution_clock::now();
    elapsed += chrono::duration_cast<chrono::nanoseconds>(finish - start);
    if (std::chrono::seconds(timeLimit) < elapsed)
        exitCase("TimeLimitExceeded");
    
    if (val != res) exitCase("WrongAnswer");
}
inline void processBatch() {
    
    if (batch <= nSample) {
        test = 1;
        arr = sampleArr[batch];
        N = sampleN[batch];
        initX = sampleinitX[batch];
        initY = sampleinitY[batch];
        checkSoln(sampleAns[batch]);
        return;
    }
    
    for (test = 1; test <= nTest[batch]; ++test) { 
        int tot = 0;
        set<pair<int, int> > block;
        set<pair <int, int> > st2;
        N = randInt(2, maxNM[batch]);
        M = randInt(1, min(100, N * N - 1));
        initX = randInt(1, N);
        initY = randInt(1, N);
        while((int)st2.size() < M){
            int x = randInt(1, N);
            int y = randInt(1, N);
            if(x == initX and y == initY)
                continue;
            st2.insert(make_pair(x, y));
            if(abs(x - initX) < 2 and abs(y - initY) < 2){
                int dx = x - initX;
                int dy = y - initY;
                pair<int, int> p = make_pair(dx,dy);
                if(block.find(p)==block.end()){ 
                    tot+=1;
                    block.insert(p);
                }
            }    
        }
        arr = vector<pair<int, int> >(st2.begin(),st2.end());
        int ans = 8;
        if ((initX == 1 or initX == N) and (initY == 1 or initY == N))
            ans -= 5;
        else if(initX == 1 or initX == N)
            ans -= 3;
        else if(initY == 1 or initY == N)
            ans -= 3;
        checkSoln(ans - tot);
        
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
    if (ifstream("_412_" + ID + ".cpp"))
        ifstream("_412_" + ID + ".cpp").ignore(12) >> best;
    ofstream("WrongAnswer.txt").close();
    ofstream("TimeLimitExceeded.txt").close();
    for (batch = 1; batch <= nBatch; total += weight[batch], ++batch)
        if (!system((".\\a.exe " + to_string(batch)).c_str()))
            score += weight[batch];
    if (best <= score) {
        ofstream("_412_" + ID + ".cpp") << "// " << ID << " " << score << "\n";
        system(("echo // %COMPUTERNAME% %USERNAME%>>_412_" + ID + ".cpp").c_str());
        ifstream fin("_412_Solution.cpp");
        ofstream("_412_" + ID + ".cpp", ios::app) << string("").assign(istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>());
    }
    cout << "Tentative score = " << double(score) / total << "/1\n", exit(0);
}
