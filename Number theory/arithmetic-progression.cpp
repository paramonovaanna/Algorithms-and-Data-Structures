#pragma GCC optimize("O3")

#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <random>
#include <set>

using namespace std;

#define ll long long 
#define fr first 
#define sc second 
#define umap unordered_map


const int N = 100100 * 2;
mt19937 gen(12345);

umap<int, int> used;
int a[N];
int n0, n, lim;

void input(){
    cin >> n0;
    n = 2 * n0;
    for (int i = 0; i < n; ++i){
        cin >> a[i]; 
    }
    sort(a, a + n);
    lim = (a[n - 1] - a[0]) / n0;
}


void process(int dx){
    if (used[dx]){
        return;
    }
    used[dx] = 1;

    umap<int, int> dp;
    int mx = 0;
    int id = 0;
    for (int i = 0; i < n; ++i){
        dp[a[i]] = dp[a[i] - dx] + 1;
        if (mx < dp[a[i]]){
            mx = dp[a[i]];
            id = i;
        }
    }
    if (mx >= n0){
        cout << a[id] - dx * (n0 - 1) << ' ' << dx;
        exit(0);
    }
}

void sample(){
    umap<int, int> divs;
    for (int i = 2; i < n; ++i){
        ++divs[a[i] - a[i - 1]];
        ++divs[a[i] - a[i - 2]];
    }
    vector<pair<int, int> > dvs;
    for (auto elem : divs){
        if (elem.sc * 13 >= n){
            dvs.push_back({-elem.sc, elem.fr});
        }
    }
    sort(dvs.begin(), dvs.end());
    
    for (auto elem : dvs){
        process(elem.sc);
    }
}


int main(){
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    input();
    if (n0 == 1){
        cout << a[0] << ' ' << 0 << '\n';
        return 0;
    }
    sample();
    
}
