#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define USE_CPPIO() ios_base::sync_with_stdio(0); cin.tie(0)

int main() {
    USE_CPPIO();
    int T;
    cin >> T;
    cout << "Lumberjacks:\n";
    while(T--) {
        vector<int> v(10);
        for(int i = 0; i < 10; ++i)
            cin >> v[i];
        if(is_sorted(v.begin(), v.end(), less<int>()) || is_sorted(v.begin(), v.end(), greater<int>()))
            cout << "Ordered\n";
        else cout << "Unordered\n";
    }
    return 0;
}