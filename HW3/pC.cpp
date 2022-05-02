#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;
#define USE_CPPIO() ios_base::sync_with_stdio(0); cin.tie(0)

int main() {
    USE_CPPIO();
    int n;
    while(cin >> n) {
        vector<int> v(n);
        int dif[n];
        for(int i = 0; i < n; ++i)
            cin >> v[i];
        adjacent_difference(v.begin(), v.end(), dif, [](int x, int y) {
            return abs(x - y);
        });
        dif[0] = 0;
        sort(dif, dif + n);
        int cnt = -1;
        if(all_of(dif, dif + n, [&](int a) {
            ++cnt;
            return a == cnt;
        })) cout << "Jolly\n";
        else cout << "Not jolly\n";
    }
    return 0;
}