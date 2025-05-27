#include<bits/extc++.h>
using namespace std;
vector<int> solve(vector<int> arr) {
    // Change the given code
    for (int i = 0; i < arr.size(); ++i)
        for (int j = 0; j < arr.size() - i - 1; ++j)
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
    return arr;
}