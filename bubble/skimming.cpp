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
#define v(i,j) (0<=i and i<n and 0<=j and j<n)

int n;

/*
1
4
##..
###.
.###
..##
 */
int main(){
    int T;
    cin >> T;
    FOR(t,T){
        cin >> n;
        vector<string> M(n);
        FOR(i,n){
            cin >> M[i];
        }
        set<pair<int, pii> > O;
        map<pii, int> NB;
        FOR(i,n){
            FOR(j,n){
                if(M[i][j]=='#'){
                    int nb = 0;
                    if(v(i-1,j) and M[i-1][j]=='#')
                        ++nb;
                    if(v(i+1,j) and M[i+1][j]=='#')
                        ++nb;
                    if(v(i,j-1) and M[i][j-1]=='#')
                        ++nb;
                    if(v(i,j+1) and M[i][j+1]=='#')
                        ++nb;
                    O.insert(mp(nb, mp(i,j)));
                    NB[mp(i,j)] = nb;
                }
            }
        }
        int res = 0;
        while(!O.empty()){
            int nb = O.begin()->fi;
            int i = O.begin()->se.fi;
            int j = O.begin()->se.se;
            //cerr << i << " " << j << " " << nb << endl;
            M[i][j] = '.';
            O.erase(mp(NB[mp(i,j)], mp(i,j)));
            NB.erase(mp(i,j));
            if(v(i-1,j) and M[i-1][j]=='#'){
                int k = i-1, l = j;
                O.erase(mp(NB[mp(k,l)], mp(k,l)));
                --NB[mp(k,l)];
                O.insert(mp(NB[mp(k,l)], mp(k,l)));
            }
            if(v(i+1,j) and M[i+1][j]=='#'){
                int k = i+1, l = j;
                O.erase(mp(NB[mp(k,l)], mp(k,l)));
                --NB[mp(k,l)];
                O.insert(mp(NB[mp(k,l)], mp(k,l)));
            }
            if(v(i,j-1) and M[i][j-1]=='#'){
                int k = i, l = j-1;
                O.erase(mp(NB[mp(k,l)], mp(k,l)));
                --NB[mp(k,l)];
                O.insert(mp(NB[mp(k,l)], mp(k,l)));
            }
            if(v(i,j+1) and M[i][j+1]=='#'){
                int k = i, l = j+1;
                O.erase(mp(NB[mp(k,l)], mp(k,l)));
                --NB[mp(k,l)];
                O.insert(mp(NB[mp(k,l)], mp(k,l)));
            }



            if(nb!=0){
                ++res;
                if(v(i-1,j) and M[i-1][j]=='#')
                    i = i-1, j = j;
                else if(v(i+1,j) and M[i+1][j]=='#')
                    i = i+1, j = j;
                else if(v(i,j-1) and M[i][j-1]=='#')
                    i = i, j = j-1;
                else
                    i = i, j = j+1;
                M[i][j] = '.';
                O.erase(mp(NB[mp(i,j)], mp(i,j)));
                NB.erase(mp(i,j));
                if(v(i-1,j) and M[i-1][j]=='#'){
                    int k = i-1, l = j;
                    O.erase(mp(NB[mp(k,l)], mp(k,l)));
                    --NB[mp(k,l)];
                    O.insert(mp(NB[mp(k,l)], mp(k,l)));
                }
                if(v(i+1,j) and M[i+1][j]=='#'){
                    int k = i+1, l = j;
                    O.erase(mp(NB[mp(k,l)], mp(k,l)));
                    --NB[mp(k,l)];
                    O.insert(mp(NB[mp(k,l)], mp(k,l)));
                }
                if(v(i,j-1) and M[i][j-1]=='#'){
                    int k = i, l = j-1;
                    O.erase(mp(NB[mp(k,l)], mp(k,l)));
                    --NB[mp(k,l)];
                    O.insert(mp(NB[mp(k,l)], mp(k,l)));
                }
                if(v(i,j+1) and M[i][j+1]=='#'){
                    int k = i, l = j+1;
                    O.erase(mp(NB[mp(k,l)], mp(k,l)));
                    --NB[mp(k,l)];
                    O.insert(mp(NB[mp(k,l)], mp(k,l)));
                }
            }
        }
        cout << "Case " << t+1 << ": " << res << endl;
    }
	return 0;
}
