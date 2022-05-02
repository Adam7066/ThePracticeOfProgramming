#include <iostream>
#include <vector>
#include <utility>
#include <numeric>
#include <limits>
#include <algorithm>
#include <cmath>
#include <iomanip>
using namespace std;
#define USE_CPPIO() ios_base::sync_with_stdio(0); cin.tie(0)

int main() {
    USE_CPPIO();
    int n, ca = 1;
    while(cin >> n && n) {
        cout << "**********************************************************\n";
        cout << "Network #" << ca++ << "\n";
        vector<pair<int, int>> v(n);
        vector<int> tmp(n), ans(n);
        for(int i = 0; i < n; ++i)
            cin >> v[i].first >> v[i].second;
        iota(tmp.begin(), tmp.end(), 0);
        double m = numeric_limits<double>::max();
        do {
            double s = 0.0;
            for(int i = 1; i < n; ++i) {
                int x = v[tmp[i]].first - v[tmp[i - 1]].first;
                int y = v[tmp[i]].second - v[tmp[i - 1]].second;
                s += sqrt(x * x + y * y) + 16;
            }
            if(s < m) {
                copy(tmp.begin(), tmp.end(), ans.begin());
                m = s;
            }
        }
        while(next_permutation(tmp.begin(), tmp.end()));
        for(int i = 1; i < n; ++i) {
            int x = v[ans[i]].first - v[ans[i - 1]].first;
            int y = v[ans[i]].second - v[ans[i - 1]].second;
            double d = sqrt(x * x + y * y) + 16;
            cout << "Cable requirement to connect (";
            cout << v[ans[i - 1]].first << "," << v[ans[i - 1]].second << ") to (";
            cout << v[ans[i]].first << "," << v[ans[i]].second << ") is ";
            cout << fixed << setprecision(2) << d << " feet.\n";
        }
        cout << "Number of feet of cable required is ";
        cout << fixed << setprecision(2) << m << ".\n";
    }
    return 0;
}