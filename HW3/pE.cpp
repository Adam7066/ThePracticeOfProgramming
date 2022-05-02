#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
#define USE_CPPIO() ios_base::sync_with_stdio(0); cin.tie(0)

int main() {
    USE_CPPIO();
    int n;
    while(cin >> n && n) {
        string s;
        cin >> s;
        int t = s.size() / n;
        for(int i = 0; i < s.size(); i += t)
            reverse(s.begin() + i, s.begin() + i + t);
        cout << s << "\n";
    }
    return 0;
}