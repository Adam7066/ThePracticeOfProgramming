#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <iomanip>
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
        double avg = accumulate(v.begin(), v.end(), 0) * 1.0 / n;
        double ans = count_if(v.begin(), v.end(), [&](int a) {
            return a > avg;
        }) * 1.0 / n * 100;
        cout << fixed << setprecision(3) << ans << "%\n";
    }
    return 0;
}