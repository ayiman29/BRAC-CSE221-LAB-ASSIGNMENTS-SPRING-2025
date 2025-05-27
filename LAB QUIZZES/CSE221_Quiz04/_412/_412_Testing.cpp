#include<bits/extc++.h>
using namespace std;
int N = 0, M = 0, res = -1, initX = -1, initY = -1;
vector<pair<int, int> > arr;
// // Compile and run: c++ _412_Solution.cpp _412_Testing.cpp && .\a.exe
// extern vector<int> solve(vector<int> list1, vector<int> list2);
inline int solve(int N, int initX, int initY, vector<pair<int, int> > arr) {
    int M = arr.size();
    int res = -1;
    // Place your code here
    return res;
}


inline string to_string(vector<int>& x) {
    string y = "[";
    if (!x.empty()) y += to_string(x[0]);
    for (int i = 1; i < x.size(); ++i)
        y += ", " + to_string(x[i]);
    return y + "]";
}
int main() {
    // // file input
    // // ifstream fin("TimeLimitExceeded.txt");
    // // ifstream fin("CustomTest.txt");
    // ifstream fin("WrongAnswer.txt");
    // string temp;
    // for (int i = 1; i <= 2; ++i) getline(fin, temp);
    // fin >> temp >> temp >> N;
    // fin >> temp >> temp >> M;
    // list1.resize(N);
    // list2.resize(M);
    // fin.ignore(10), getline(fin, temp);
    // istringstream sin(temp);
    // for (int i = 0, j; i < N; sin >> temp, list1[i] = stoi(temp.substr(0, temp.size() - 1)), ++i);
    // fin.ignore(9), getline(fin, temp);
    // sin = istringstream(temp);
    // for (int i = 0, j; i < M; sin >> temp, list2[i] = stoi(temp.substr(0, temp.size() - 1)), ++i);
    // fin.close();

    // stdin
    // 4 3
    // 1 3
    // 2 3
    // 1 1
    // 3 4 
    cin >> N >> M;
    arr.resize(N);
    cin >> initX >> initY;
    int bx, by;
    for (int i = 0; i < M; ++i) 
    {
        cin >> bx >> by;
        arr.push_back(make_pair(bx,by));
    }

    // // hardcoded input
    // list1 = vector<int>({ 1, 2, 2, 3, 4 });
    // list2 = vector<int>({ 2, 2, 3, 3, 5, 6 });

    chrono::_V2::system_clock::time_point start = chrono::high_resolution_clock::now();
    res = solve(N, initX, initY, arr);
    chrono::_V2::system_clock::time_point finish = chrono::high_resolution_clock::now();
    chrono::_V2::system_clock::duration elapsed = chrono::duration_cast<chrono::nanoseconds>(finish - start);

    // // file output
    // ofstream fout("OutputOfYourCode.txt");
    // fout << to_string(res);
    // fout.close();

    // stdout
    cout << to_string(res) << "\n";

    cout << fixed << setprecision(9) << "Execution time for the targeted one test is " << (elapsed.count() * 1e-9) << "s\n";
    exit(0);
}
