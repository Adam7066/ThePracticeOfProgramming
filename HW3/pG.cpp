#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define USE_CPPIO() ios_base::sync_with_stdio(0); cin.tie(0)

int main() {
    USE_CPPIO();
    int n, q, ca = 1;
    while(cin >> n >> q && n && q) {
        cout << "CASE# " << ca++ << ":\n";
        vector<int> v(n);
        for(int i = 0; i < n; ++i)
            cin >> v[i];
        sort(v.begin(), v.end());
        while(q--) {
            int t;
            cin >> t;
            auto find = lower_bound(v.begin(), v.end(), t);
            if(find != v.end() && *find == t)
                cout << t << " found at " << find - v.begin() + 1 << "\n";
            else cout << t << " not found\n";
        }
    }
    return 0;
}