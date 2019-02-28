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

#define N 650
vector<vi> D;
template <int T>
class MCTS;

template <>
class MCTS<0> {
    double sample(set<int>& alive, int u){return 0;}
    double points(){return 0;}
    double score, nb;
    int u;
};

template <int T>
class MCTS {
    MCTS(): nb(0), score(0){}
    int sample(set<int>& alive, int u, int L){
        alive.erase(u);
        if(alive.empty()){
            ++nb;
            score+=L+D[u][0];
            return L+D[u][0];
        }
        else{
            int i = 0;
            double bscore = -1;
            for(int v:alive){
                if(i>=C.size()){
                    C.emplace_back();
                    return C.back().sample(alive, v, L+D[u][v]);
                }
                if(bscore == -1 or bscore<)
                ++i;
            }
            return
        }
    }
    double points(){
        return score/nb;
    }
    double score, nb;
    vector<MCTS<T-1> > C;
};

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
    auto clocker = clock();
    srand(0);
    int n;
    cin >> n;
    D = vector<vi> (n, vi(n));
    FOR(i,n)
        FOR(j,n)
            cin >> D[i][j];
    MCTS<650> mcts;
    while(double(clock()-clocker)/CLOCKS_PER_SEC < 0.95){

    }


    vi parc(n);
    int L = 0;
    FOR(i,n){
        L += D[parc[i]][parc[(i+1)%n]];
    }
    cout << L << endl;
    FOR(i,n)
        cout << parc[i]+1 << " ";
    cout << parc[0]+1 << endl;
	return 0;
}
