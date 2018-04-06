/* Copyright (C) Redouane ELGHAZI
 * TBD
 */
#pragma GCC push_options
#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;
#define REP(i,a,b) for (int i = (a); i <= (b); ++i)
#define REPD(i,a,b) for (int i = (a); i >= (b); --i)
#define FORI(i,n) REP(i,1,n)
#define FOR(i,n) REP(i,0,(int)(n)-1)
#define mp make_pair
#define pb push_back
#define pii pair<int,int>
#define vi vector<int>
#define pll pair<ll, ll>
#define vl vector<ll>
#define ll long long
#define ld long double
#define SZ(x) (int)((x).size())
#define DBG(v) cerr << #v << " = " << (v) << endl;
#define FOREACH(i,t) for (auto i = t.begin(); i != t.end(); ++i)
#define fi first
#define se second
#define v(i,j) (0<=i and i<s and 0<=j and j<s)
#define INF -1

/* CONTRE-EXEMPLE
1
6
......
.####.
######
##..##
......
......
 */
#define MAXV 100005
int n,m; vi adj[MAXV]; int p[MAXV], dist[MAXV];
bool bfs() {
deque<int> q;
FORI(v,n) { if (!p[v]) { dist[v] = 0; q.pb(v); } else dist[v] = INF; }
dist[0] = INF;
while (!q.empty()) {
int v = q.front(); q.pop_front();
FOREACH(u,adj[v]) if (dist[p[*u]] == INF) {
dist[p[*u]] = dist[v]+1;
q.pb(p[*u]);
}
}
return dist[0] != INF;
} bool dfs (
int v) {
if (!v) return 1;
FOREACH(u,adj[v]) if (dist[p[*u]] == dist[v]+1) {
if (dfs(p[*u])) { p[*u] = v; p[v] = *u; return 1; }
}
dist[v] = INF;
return 0;
}
// vertices on the left should have numbers 1..n, on the right - n+1..n+m
// PRE: set n,m,adj (adj needs to be filled out only for vertices 1..n) (adj[0] must
// be empty), and the constant MAXV = maximum n+m
int matching () {
FOR(i,n+m+1) p[i] = 0;
int w = 0;
while (bfs()) FORI(v,n) if (!p[v]) if (dfs(v)) ++w;
return w;
}
// (i*n+j)/2
int main(){
    int T;
    cin >> T;
    FOR(t,T){
        int s;
        cin >> s;
        vector<string> M(s);
        vector<vi> ind(s, vi(s, 0));

        FOR(i,s){
            cin >> M[i];
        }

        n = 0;
        m = 0;
        FOR(i,s){
            FOR(j,s){
                if(M[i][j]=='#'){
                    if((i+j)%2==0){
                        ++n;
                        ind[i][j] = n;
                    }
                    else{
                        ++m;
                        ind[i][j] = -m;
                    }
                }
            }
        }

        FOR(i,s){
            FOR(j,s){
                if(ind[i][j]<0){
                    ind[i][j] = n-ind[i][j];
                }
            }
        }
        FOR(i,s){
            FOR(j,s){
                if(M[i][j]=='#'){
                    adj[ind[i][j]] = vi();
                    int k = i-1, l = j;
                    if(v(k,l) and M[k][l]=='#'){
                        adj[ind[i][j]].pb(ind[k][l]);
                    }
                    k = i+1, l = j;
                    if(v(k,l) and M[k][l]=='#'){
                        adj[ind[i][j]].pb(ind[k][l]);
                    }
                    k = i, l = j+1;
                    if(v(k,l) and M[k][l]=='#'){
                        adj[ind[i][j]].pb(ind[k][l]);
                    }
                    k = i, l = j-1;
                    if(v(k,l) and M[k][l]=='#'){
                        adj[ind[i][j]].pb(ind[k][l]);
                    }
                }
            }
        }
        /*FOR(i,s){
        FOR(j,s){
        cout << ind[i][j];
        }
        cout << endl;
        }
        FOR(i,n+m+1){
            cout << i << ": ";
            for(int j:adj[i]){
                cout << j << " ";
            }
            cout << endl;
        }*/
        cout << "Case " << t+1 << ": " << matching() << endl;
    }
	return 0;
}
