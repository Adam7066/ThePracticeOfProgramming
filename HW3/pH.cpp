#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;
#define USE_CPPIO() ios_base::sync_with_stdio(0); cin.tie(0)

int main() {
    USE_CPPIO();
    int T;
    cin >> T;
    while(T--) {
        int n;
        cin >> n;
        vector<int> v(n);
        for(int i = 0; i < n; ++i)
            cin >> v[i];
        nth_element(v.begin(), v.begin() + (n / 2), v.end());
        cout << accumulate(v.begin(), v.end(), 0, [&](int x, int y) {
            return x + abs(y - v[n / 2]);
        }) << "\n";
    }
    return 0;
}