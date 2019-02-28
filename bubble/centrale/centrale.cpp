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

vector<vi> D;
int n;

void solve(vi& res){
	vector<pii> succ (n, mp(-1,-1));
	set<pii> alive;
	FOR(u,n)
        alive.emplace(u,u);
	vi pote(n);
	FOR(u,n)
        pote[u]=u;
	FOR(i,n-1){
		int mini = INT_MAX;
		pii match(-1,-1);
		auto it(alive.begin());
		advance(it, rand()%alive.size());
		pii p = *it;
		int u = p.fi, v = p.se;
		for(pii p2:alive){
            int w = p2.fi, x = p2.se;
			if(u!=w){
				for(int i:{u,v}){
					for(int j:{w,x}){
						if(mini>D[i][j]){
							mini = D[i][j];
							match = mp(min(i,j), max(i,j));
						}
					}
				}
			}
		}
		u = match.fi, v = match.se;
		if(succ[u].fi == -1)
			succ[u].fi = v;
		else
			succ[u].se = v;
		if(succ[v].fi == -1)
			succ[v].fi = u;
		else
			succ[v].se = u;
		alive.erase(mp(min(pote[u], u), max(pote[u], u)));
		alive.erase(mp(min(pote[v], v), max(pote[v], v)));
		alive.insert(mp(min(pote[u],pote[v]),max(pote[u],pote[v])));
		int u2 = pote[u];
		int v2 = pote[v];
		pote[u2] = v2;
		pote[v2] = u2;
	}
	for(auto& p:alive){
        int u = p.fi;
        int v = p.se;
		succ[u] = mp(succ[u].fi, v);
		succ[v] = mp(succ[v].fi, u);
	}
	res = vi (n,1);
	int p = -1;
	int u = 0;
	FOR(i,n){
		int suiv = succ[u].fi;
		if(suiv == p)
			suiv = succ[u].se;
		res[i] = u;
		p = u;
		u = suiv;
	}
	return;
}


int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);


    auto clocker = clock();
    srand(42);
    cin >> n;
    D = vector<vi> (n, vi(n));
    FOR(i,n)
        FOR(j,n)
            cin >> D[i][j];
    vi parc(n), parct;
    int L = INT_MAX, Lt;
    double d = 0;
    int nb = 0;
    while(double(clock()-clocker)/CLOCKS_PER_SEC+d < 0.95){
        ++nb;
        d = clock();
        solve(parct);
        Lt = 0;
        FOR(i,n){
            Lt += D[parct[i]][parct[(i+1)%n]];
        }
        if(Lt<L){
            L = Lt;
            parc.swap(parct);
        }
        d = (clock() - d)/CLOCKS_PER_SEC;
    }

    cerr << nb << endl;

    cout << L << endl;
    FOR(i,n)
        cout << parc[i]+1 << " ";
    cout << parc[0]+1 << endl;
	return 0;
}
