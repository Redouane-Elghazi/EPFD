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

void clusterize(vector<vector<int> >& clusters){
    int nb_cluster = ceil()
    clusters = vector<vector<int> > ();
}

void solve(vi& res){

}


int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);


    auto clocker = clock();
    srand(1337);
    cin >> n;
    D = vector<vi> (n, vi(n));
    FOR(i,n)
        FOR(j,n)
            cin >> D[i][j];
    vi parc(n), parct(n);
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
