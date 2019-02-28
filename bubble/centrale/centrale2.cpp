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
#define s(u) (u+1)%n
#define p(u) (u+n-1)%n
static const double eps = pow(2,-20);

vector<vi> D;
int n;
int nb = 0;


int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);


    auto clocker = clock();
    srand('E'+'P'+'F'+'D');
    cin >> n;
    D = vector<vi> (n, vi(n));
    FOR(i,n)
        FOR(j,n){
            cin >> D[i][j];
        }
    vi res(n);
    res[0] = 10;
    vector<int> alive;
    FOR(i,n)
        if(i!=res[0])
            alive.pb(i);
    int u = res[0];
    FOR(i,n-1){
        int v = 0;
        FOR(vt,alive.size()){
            if(D[u][alive[vt]]<D[u][alive[v]])
                v = vt;
        }
        res[i+1] = alive[v];
        u = alive[v];
        swap(alive[v], alive.back());
        alive.pop_back();
    }
    int S = 0;
    FOR(i,n){
        S += D[res[i]][res[(i+1)%n]];
    }
    //int cons = 0;
    double d = 0;
    while(double(clock()-clocker)/CLOCKS_PER_SEC+d < 0.9){
        ++nb;
        int u = nb%n;
        int v = u, score = D[res[p(u)]][res[u]] + D[res[u]][res[s(u)]] - D[res[p(u)]][res[s(u)]];
        //int delta = -score;
        FOR(vt,n){
            if(vt!=u and s(vt)!=u){
                if(D[res[vt]][res[u]] + D[res[u]][res[s(vt)]] - D[res[vt]][res[s(vt)]]<score){
                    score = D[res[vt]][res[u]] + D[res[u]][res[s(vt)]] - D[res[vt]][res[s(vt)]];
                    v = vt;
                }
            }
        }
        /*if(cons == 100 and double(clock()-clocker)/CLOCKS_PER_SEC<0.8){
            v = rand()%(n-2);

            if(v>=min(u, p(u)))
                ++v;
            if(v>=max(u, p(u)))
                ++v;

            score = D[res[v]][res[u]] + D[res[u]][res[s(v)]] - D[res[v]][res[s(v)]];
        }*/
        int tobemoved = res[u];
        for(int i = u; i!=v; i=s(i)){
            res[i] = res[s(i)];
        }
        res[v] = tobemoved;
        /*delta+=score;
        if(delta == 0)
            ++cons;
        else
            cons = 0;
        S+=delta;
        cerr << delta << endl;*/
        /*if(u!=v){
        cerr << u << " goes to " << v << endl;
        }*/
    }

    /*FOR(i,n){
        FOR(j,n){
            cerr << P[i][j] << " ";
        }
        cerr << endl;
    }*/

    cerr << nb << endl;
    int L = 0;
    FOR(i,n){
        L += D[res[i]][res[(i+1)%n]];
    }
    cout << L << endl;
    FOR(i,n)
        cout << res[i]+1 << " ";
    cout << res[0]+1 << endl;
	return 0;
}
