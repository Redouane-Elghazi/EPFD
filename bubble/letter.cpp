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

int main(){
    int T;
    cin >> T;
    FOR(t, T){
        int n;
        cin >> n;
        string s;
        cin >> s;
        vector<int> A(26, -1);
        vector<int> res(n, -1);
        FOR(i,n){
            FOR(j,s[n-i-1]-'a'){
                A[j] = n-i;
            }
            res[n-i-1] = A[s[n-i-1]-'a'];
        }
        FOR(i,n-1)
        cout << res[i] << " ";
        cout << res[n-1] << endl;
    }
	return 0;
}
