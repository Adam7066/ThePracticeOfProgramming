#include <iostream>
#include <vector>
#include <numeric>
using namespace std;
#define USE_CPPIO() ios_base::sync_with_stdio(0); cin.tie(0)

int main() {
    USE_CPPIO();
    int n, ca = 1;
    while(cin >> n && n) {
        vector<int> v(n);
        for(int i = 0; i < n; ++i)
            cin >> v[i];
        int avg = accumulate(v.begin(), v.end(), 0) * 1.0 / n;
        int ans = 0;
        for(auto it : v)
            ans += abs(it - avg);
        cout << "Set #" << ca++ << "\nThe minimum number of moves is " << ans / 2 << ".\n\n";
    }
    return 0;
}