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

// returns 0-based indices of matches
vi kmp(string t, string p) { // text, pattern
vi kn(SZ(p)+1,-1); // Knuth prefix function
FORI(i,SZ(p)) {
int j = kn[i-1];
while (j != -1 && p[j] != p[i-1]) j=kn[j];
kn[i] = j+1;
}
// kn is computed
vi ans;
int ppos=0,tpos=0;
while (tpos<SZ(t)) {
while (ppos!=-1 && (ppos == SZ(p) || p[ppos]!=t[tpos])) ppos=kn[ppos];
ppos++; tpos++;
if (ppos==SZ(p)) ans.pb(tpos-SZ(p));
}
return ans;
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);

    string s,n,w,e,x;
    cin >> n >> s >> e >> w >> x;
    int l = x.size(), maxsize = max(max(n.size(), s.size()), max(e.size(), w.size())) + 1;
    vector<vector<pii> > targ(maxsize);
    vector<bool> Pn(l), Ps(l), Pe(l), Pw(l);
    for(int i:kmp(x,n))
        Pn[i] = true;
    for(int i:kmp(x,s))
        Ps[i] = true;
    for(int i:kmp(x,e))
        Pe[i] = true;
    for(int i:kmp(x,w))
        Pw[i] = true;
    targ[0].emplace_back(l,l);
    cerr << "init end" << endl;
    FOR(i,l){
        if(Pn[i]){
            vector<pii> toAdd, Uni;
            int new_i = ((i+n.size())%maxsize);
            for(auto& p:targ[i%maxsize])
                toAdd.emplace_back(p.fi, p.se+1);
            set_union(targ[new_i].begin(), targ[new_i].end(), toAdd.begin(), toAdd.end(), inserter(Uni, Uni.begin()));
            targ[new_i].swap(Uni);
        }
        if(Ps[i]){
            vector<pii> toAdd, Uni;
            int new_i = ((i+s.size())%maxsize);
            for(auto& p:targ[i%maxsize])
                toAdd.emplace_back(p.fi, p.se-1);
            set_union(targ[new_i].begin(), targ[new_i].end(), toAdd.begin(), toAdd.end(), inserter(Uni, Uni.begin()));
            targ[new_i].swap(Uni);
        }
        if(Pe[i]){
            vector<pii> toAdd, Uni;
            int new_i = ((i+e.size())%maxsize);
            for(auto& p:targ[i%maxsize])
                toAdd.emplace_back(p.fi+1, p.se);
            set_union(targ[new_i].begin(), targ[new_i].end(), toAdd.begin(), toAdd.end(), inserter(Uni, Uni.begin()));
            targ[new_i].swap(Uni);
        }
        if(Pw[i]){
            vector<pii> toAdd, Uni;
            int new_i = ((i+w.size())%maxsize);
            for(auto& p:targ[i%maxsize])
                toAdd.emplace_back(p.fi-1, p.se);
            set_union(targ[new_i].begin(), targ[new_i].end(), toAdd.begin(), toAdd.end(), inserter(Uni, Uni.begin()));
            targ[new_i].swap(Uni);
        }
        targ[i%maxsize].clear();
    }
    cout << targ[l%maxsize].size() << endl;
	return 0;
}
