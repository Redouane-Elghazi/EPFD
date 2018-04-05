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

int lost[] =    {0b100100100, 0b010010010, 0b001001001,
                 0b111000000, 0b000111000, 0b000000111,
                 0b100010001, 0b001010100};

int score[512] = {};

int S(int board){
    if(score[board] == -1){
        FOR(i,8){
            if((board&lost[i])==lost[i]){
                score[board] = 0;
                return 0;
            }
        }
        int mov = 1;
        set<int> sons;
        FOR(i,9){
            if((board&mov)==0){
                sons.insert(S(board|mov));
            }
            mov = mov<<1;
        }
        FOR(i,10){
            if(sons.find(i)==sons.end()){
                score[board] = i;
                break;
            }
        }
    }
    return score[board];
}

int stob(string& s){
    int res = 0;
    for(char c:s){
        res*=2;
        res+=c-'0';
    }
    return res;
}

int main(){
    FOR(i, 512){
        score[i] = -1;
    }
    int T;
    cin >> T;
    FOR(t, T){
        int n;
        cin >> n;
        string s;
        int res = 0;
        FOR(i,n){
            cin >> s;
            res = res^S(stob(s));
        }
        cout << (res?"Kang":"Kung") << endl;
    }
	return 0;
}
