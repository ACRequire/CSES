You are given a tree consisting of n nodes, and m paths in the tree.

Your task is to calculate for each node the number of paths containing that node.

Input

The first input line contains integers n and m: the number of nodes and paths. The nodes are numbered 1,2,…,n.

Then there are n−1 lines describing the edges. Each line contains two integers a and b: there is an edge between nodes a and b.

Finally, there are m lines describing the paths. Each line contains two integers a and b: there is a path between nodes a and b.

Output

Print n integers: for each node 1,2,…,n, the number of paths containing that node.

Constraints
1≤n,m≤2⋅105
1≤a,b≤n
Example

Input:
5 3
1 2
1 3
3 4
3 5
1 3
2 5
1 4

Output:
3 1 3 1 1

Solution:

#include <bits/stdc++.h>
using namespace std;
 
#define print(x) cerr << #x << " is " << x << endl;
#define int long long int
#define ll long long
#define vi vector<int>
#define vvi vector<vector<int>>
#define vpi vector<pair<int, int>>
#define all(v) (v).begin(), (v).end()
#define pii pair<int, int>
#define pb push_back
 
const int N = 5e5 + 10;
const int mod = 1e9 + 7;
 
vi g[N];
int u, v;
 
int dp[N][31];
int lvl[N];
 
void dfs(int u, int par){
    dp[u][0] = par;
    lvl[u] = lvl[par] + 1;
    
    for(int i = 1; i <= 30; ++i)
        if(dp[u][i-1] != -1)
            dp[u][i] = dp[dp[u][i-1]][i-1];
    
    for(int v: g[u]){
        if(v != par){
            dfs(v, u);
        }
    }
}
 
int lca(int u, int v){
    
    if(lvl[u] < lvl[v])
        swap(u, v);
    
    for(int i = 30; ~i; --i)
        if(lvl[u] - (1 << i) >= lvl[v])
            u = dp[u][i];
    
    if(u == v)
        return u;
    
    for(int i = 30; ~i; --i)
        if(dp[u][i] ^ dp[v][i])
            u = dp[u][i],v = dp[v][i];
        
    return dp[u][0];
}
 
int Parent(int u, int k) {
    k = lvl[u] - k;
    for(int i = 30; ~i; --i) {
        if(lvl[u] - (1 << i) >= k) {
            u = dp[u][i];
        }
    }
    return u == 0 ? -1 : u;
}
 
int distance(int u, int v) {
    return lvl[u] + lvl[v] - 2 * lvl[lca(u, v)];    
}
 
int32_t main()
{    
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    for(int i = 1; i < n ; ++i){
        int u, v;
        cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }
    memset(dp, -1, sizeof(dp));
    lvl[0] = -1;
    dfs(1, 0);
    
    /* ---------------write code below---------------------------- */
    
    vi prefix(n + 2, 0);
    while(q--) {
        int a, b;
        cin >> a >> b;
        int LCA = lca(a, b);
        prefix[a]++; // add flow to a;
        prefix[b]++; // add flow to b;
        prefix[LCA]--; // removing one of flow;
        prefix[dp[LCA][0]]--; // removing other flow; from parent of lca;
    }
    function<void(int, int)> go = [&](int u, int par) {
        for(int v : g[u]) {
            if(v != par) {
                go(v, u);
                prefix[u] += prefix[v];
            }
        }
    };
    go(1, 0);
    for(int i = 1; i <= n; ++i) {
        cout << prefix[i] << ' ';
    }
    cout << '\n';
    return 0;
}
