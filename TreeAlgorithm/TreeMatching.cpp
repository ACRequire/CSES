
You are given a tree consisting of n nodes.

A matching is a set of edges where each node is an endpoint of at most one edge. What is the maximum number of edges in a matching?

Input

The first input line contains an integer n: the number of nodes. The nodes are numbered 1,2,.,n.

Then there are n-1 lines describing the edges. Each line contains two integers a and b: there is an edge between nodes a and b.

Output

Print one integer: the maximum number of pairs.

Constraints
1髇�2�105
1骯,b髇
Example

Input:
5
1 2
1 3
3 4
3 5

Output:
2

Explanation: One possible matching is (1,2) and (3,4).

Code
#include <bits/stdc++.h>
using namespace std;
 
#define hey(x) cerr << #x << " : " << x << "\n";
#define int long long int
#define ll long long
#define vi vector<int>
#define vvi vector<vector<int> >
#define vpi vector<pair<int, int> >
#define vvpi vector<vector<pair<int, int> > >
#define all(v) (v).begin(), (v).end()   
#define rall(v) (v).rbegin(), (v).rend()
#define pii pair<int, int>
#define pb push_back
#define SZ(x) (int)(x).size()
#define inf 1e12
#define F first
#define S second
#define PI 3.1415926535897932384626
#define out cout << fixed << setprecision(12)
#define fill(v, val) memset((v), val, sizeof(v))
#define fast ios::sync_with_stdio(false); cin.tie(0);
#define hey2(x, y) cerr << #x << " : " << x << "," << #y << " : " << y << '\n';
 
const int N = 1e6 + 10;
const int mod = 1e9 + 7;
const double pi = acos(-1);
 
void print(vi &a) {
    for(int i : a) cerr << i << ' ';
    cerr << "\n";
}
 
vvi g;
int dp[N][2];
 
void dfs(int u, int par) {
    dp[u][0] = dp[u][1] = 0;
    for(int v : g[u]) {
        if(v != par) {
            dfs(v, u);
        }
    }
    int sum = 0;
    for(int v : g[u]) {
        if(v != par) {
            sum += max(dp[v][0], dp[v][1]);
        }
    }
    dp[u][0] = sum;
    for(int v : g[u]) {
        if(v != par) {
            int answer = 1 + dp[v][0] + (sum - max(dp[v][0], dp[v][1]));
            dp[u][1] = max(dp[u][1], answer);
        }
    }
}
 
 
int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    g = vvi(n + 1);
    for(int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].pb(v), g[v].pb(u);
    }    
    dfs(1, 0);
    cout << max(dp[1][1], dp[1][0]) << "\n";
    return 0;
}

Link to this code: https://cses.fi/paste/669e86c875c15174c79cb/
