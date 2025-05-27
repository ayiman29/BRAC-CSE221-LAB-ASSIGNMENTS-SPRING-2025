#include<bits/extc++.h>
using namespace std;
inline int rng(int x) { return abs(rand() << 30LL | rand() << 15LL | rand()) % x; }
inline string to_string(vector<int>& x) {
    string y = "[";
    if (!x.empty()) y += to_string(x[0]);
    for (int i = 1; i < x.size(); ++i)
        y += ", " + to_string(x[i]);
    return y + "]";
}

// Compile and run: c++ _A1E_Testing.cpp && .\a.exe
vector<int> solve(vector<int> arr) {
    // Change the given code
    for (int i = 0; i < arr.size(); ++i)
        for (int j = 0; j < arr.size() - i - 1; ++j)
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
    return arr;
}
int N = 0;
vector<int> arr, res;
int main() {
    // stdin
    // 5
    // 3 2 1 4 5
    cin >> N;
    for (int i = 1, j; i <= N; ++i)
        cin >> j, arr.push_back(j);


    chrono::_V2::system_clock::time_point start = chrono::high_resolution_clock::now();
    res = solve(arr);
    chrono::_V2::system_clock::time_point finish = chrono::high_resolution_clock::now();
    chrono::_V2::system_clock::duration elapsed = chrono::duration_cast<chrono::nanoseconds>(finish - start);

    // // stdout
    // cout << to_string(res) << "\n";

    cout << fixed << setprecision(9) << "Execution time for the targeted one test is " << (elapsed.count() * 1e-9) << "s\n";
    exit(0);

    
    // // file input
    // ifstream fin("TimeLimitExceeded.txt");
    // ifstream fin("CustomTest.txt");
    // ifstream fin("WrongAnswer.txt");
    // string temp;
    // for (int i = 1; i <= 11; ++i) fin >> temp;
    // for (fin.ignore(2); fin >> temp; arr.push_back(stoi(temp)))
    //     temp.pop_back();
    // fin.close();

    // // hardcoded input
    // arr = vector<int>({ 3, 2, 1, 4, 5 });

    
    // // file output
    // ofstream fout("OutputOfYourCode.txt");
    // fout << to_string(res);
    // fout.close();
}
