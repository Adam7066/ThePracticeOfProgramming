#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define USE_CPPIO() ios_base::sync_with_stdio(0); cin.tie(0)

int main() {
    USE_CPPIO();
    int T;
    cin >> T;
    for(int ca = 1; ca <= T; ++ca) {
        int n;
        cin >> n;
        vector<int> v(n);
        for(int i = 0; i < n; ++i)
            cin >> v[i];
        cout << "Case " << ca << ": " << *max_element(v.begin(), v.end()) << "\n";
    }
    return 0;
}