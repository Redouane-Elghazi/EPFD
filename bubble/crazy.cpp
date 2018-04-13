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
#define INF 300000

struct MinTree {
    int* el, s;
    MinTree (int h) { // domain of elements is [0..2^h-1]
        el = new int[2*(s = 1<<h)];
        FOR(x,2*s) el[x] = 0; // maybe you want 0 here?
    }
    ~MinTree() { delete [] el; }
    void Set (int p, int v) { // watch out: will overwrite a smaller value
        for (p += s, el[p] = v, p /= 2; p > 0; p /= 2) el[p] = max(el[2*p],el[2*p+1]);
    }
    int Find (int p, int k) { // min on segment [p,k]
        int m = 0; p += s; k += s;
        while (p < k) {
            if (p&1) m = max(m, el[p++]);
            if (!(k&1)) m = max(m, el[k--]);
            p /= 2; k /= 2;
        }
        if (p == k) m = max(m, el[p]);
        return m;
    }
};

int n;
vi V;
vector<char> C;
vector<vi> E;
MinTree mt(18);

void addword(int i, int u, string& s, int c){
    if(c!=-1){
        if(V[u]!=-1){
            mt.Set(V[u], max(c+1, mt.Find(V[u], V[u]))); /// max with old value
        }
        V[u] = i;
    }
    if(c+1!=s.size()){
        for(int v:E[u]){
            if(C[v]==s[c+1]){
                return addword(i, v, s, c+1);
            }
        }
        C.pb(s[c+1]);
        E.emplace_back();
        V.pb(-1);
        E[u].pb(n);
        ++n;
        return addword(i, n-1, s, c+1);
    }
}

void addword(int i, string& s){
    mt.Set(i, 0);
    addword(i, 0, s, -1);
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);

	int T;
	cin >> T;
	FOR(t,T){
        //INITIALIZE
        n = 1;
        V = vi (1);
        C = vector<char> (1);
        E = vector<vi> (1);
        int N;
        cin >> N;
        vector<string> S(N);
        FOR(i,N)
            cin >> S[i];
        int Q;
        cin >> Q;
        vector<vector<pii> > queries(N);
        vi res(Q);
        FOR(q,Q){
            int l, r;
            cin >> l >> r;
            --l, --r;
            queries[r].emplace_back(q, l);
        }
        FOR(i,N){
            addword(i, S[i]);
            for(auto& p:queries[i]){
                res[p.fi] = mt.Find(p.se, i);
            }
        }
        FOR(q,Q){
            cout << res[q] << endl;
        }
	}
	return 0;
}
