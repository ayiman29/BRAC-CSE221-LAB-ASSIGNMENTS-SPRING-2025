#include<bits/extc++.h>
using namespace std;
int N = 0;
vector<int> preOrder, postOrder, result;
// // Compile and run: c++ _312_Solution.cpp _312_Testing.cpp && .\a.exe
// extern vector<int> solve(vector<int> preOrder, vector<int> postOrder);
inline vector<int> solve(vector<int> preOrder, vector<int> postOrder) {
    int N = preOrder.size();
    vector<int> result;
    // Place your code here
    return result;
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
    // preOrder.resize(N);
    // postOrder.resize(N);
    // fin >> temp >> temp, fin.ignore(2), getline(fin, temp);
    // istringstream sin(temp);
    // for (int i = 0, j; i < N; sin >> temp, preOrder[i] = stoi(temp.substr(0, temp.size() - 1)), ++i);
    // fin >> temp >> temp, fin.ignore(2), getline(fin, temp);
    // sin = istringstream(temp);
    // for (int i = 0, j; i < N; sin >> temp, postOrder[i] = stoi(temp.substr(0, temp.size() - 1)), ++i);
    // fin.close();

    // stdin
    // 5
    // 3 9 20 15 7
    // 9 15 7 20 3
    cin >> N;
    preOrder.reserve(N);
    postOrder.reserve(N);
    for (int i = 0; i < N; ++i) cin >> preOrder[i];
    for (int i = 0; i < N; ++i) cin >> postOrder[i];

    // // hardcoded input
    // preOrder = vector<int>({ 3, 9, 20, 15, 7 });
    // postOrder = vector<int>({ 9, 15, 7, 20, 3 });

    chrono::_V2::system_clock::time_point start = chrono::high_resolution_clock::now();
    result = solve(preOrder, postOrder);
    chrono::_V2::system_clock::time_point finish = chrono::high_resolution_clock::now();
    chrono::_V2::system_clock::duration elapsed = chrono::duration_cast<chrono::nanoseconds>(finish - start);

    // // file output
    // ofstream fout("OutputOfYourCode.txt");
    // fout << to_string(result);
    // fout.close();

    // stdout
    cout << to_string(result) << "\n";

    cout << fixed << setprecision(9) << "Execution time for the targeted one test is " << (elapsed.count() * 1e-9) << "s\n";
    exit(0);
}