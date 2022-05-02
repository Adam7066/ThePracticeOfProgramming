#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
#define USE_CPPIO() ios_base::sync_with_stdio(0); cin.tie(0)

int main() {
    USE_CPPIO();
    string s, t;
    while(cin >> s >> t) {
        int pos = 0;
        bool flag = true;
        for(auto it : s) {
            auto f = find(t.begin() + pos, t.end(), it);
            if(f == t.end()) {
                flag = false;
                break;
            }
            pos = f - t.begin() + 1;
        }
        if(flag) cout << "Yes\n";
        else cout << "No\n";
    }
    return 0;
}