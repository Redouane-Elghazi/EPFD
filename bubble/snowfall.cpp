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

int parc(int i, vector<vector<int> >& adj, vector<bool>& visited){
    int res = 0;
    if(!visited[i]){
        visited[i] = true;
        res = 1;
        for(int j:adj[i]){
            res += parc(j, adj, visited);
        }
    }
    return res;
}

int main(){
    int T;
    cin >> T;
    FOR(t,T){
        int n, m;
        cin >> n >> m;
        vector<vector<int> > adjo(n), adj(n);
        vi d(n,0);
        FOR(i,m){
            int u, v;
            cin >> u >> v;
            --u, --v;
            ++d[u];
            --d[v];
            adj[u].pb(v);
            adjo[u].pb(v);
            adj[v].pb(u);
        }
        int start = -1;
        bool poss = true, done = false;
        FOR(i,n){
            if(d[i] == 1 and start == -1){
                start = i;
            }
            else if(d[i]!=0 and d[i]!=-1){
                poss = false;
                break;
            }
        }
        if(poss){
            if(start == -1){
                FOR(i,n){
                    vector<bool> visited(n,false);
                    if(parc(i, adjo, visited)==n){
                        cout << "YES" << endl;
                        done = true;
                        break;
                    }
                }
            }
            else{
                vector<bool> visited(n,false);
                if(parc(start, adjo, visited)==n){
                    cout << "YES" << endl;
                    done = true;
                }
            }
        }
        if(!done){
            int start1 = -1, start2 = -1;
            poss = true;
            FOR(i,n){
                if((d[i]%2+2)%2 == 1 and start1 == -1){
                    start1 = i;
                    poss = false;
                }
                else if((d[i]%2+2)%2 == 1 and start2 == -1){
                    start2 = i;
                    poss = true;
                }
                else if(d[i]%2!=0){
                    poss = false;
                    break;
                }
            }
            vector<bool> visited(n,false);
            if(poss and parc(0, adj, visited) == n){
                cout << "TRAFFIC STOPPING NEEDED" << endl;
            }
            else{
                cout << "WAKE UP EARLIER" << endl;
            }
        }
    }
	return 0;
}
