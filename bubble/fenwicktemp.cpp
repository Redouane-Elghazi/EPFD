/* Copyright (C) Redouane ELGHAZI
 * TBD
 */
#include <bits/stdc++.h>
#define ll long long
#define p(i) i/2
#define f1(i) i*2
#define f2(i) i*2+1
using namespace std;

class mini{
public:
    static ll op(ll a, ll b){
        return min(a,b);
    }
    static ll neutral(){
        return LONG_MAX;
    }
};

template <class T>
class fenwick{
public:
    ll query(ll l, ll r, ll i, ll a, ll b){
        if(a<=l and r<=b){
            return S[i];
        }
        else{
            ll res = T::neutral();
            if(a<(l+r)/2){
                res = T::op(res, query(l, (l+r)/2, f1(i), a, b));
            }
            if(b>(l+r)/2){
                res = T::op(res, query((l+r)/2, r, f2(i), a, b));
            }
            return res;
        }
    }
    ll query(ll a, ll b){
        return query(0,n,1,a,b);
    }

    ll replace(ll l, ll r, ll c, ll i, ll a){
        if(l<=a and a<r){
            if(l+1!=r){
                S[i] = T::neutral();
                S[i] = T::op(S[i], replace(l, (l+r)/2, c, f1(i), a));
                S[i] = T::op(S[i], replace((l+r)/2, r, c, f2(i), a));
            }
        }
        return S[i];
    }
    ll replace(ll a, ll c){
        S[a+n] = c;
        replace(0, n, c, 1, a);
    }
    void pr(){
        for(ll i = 0; i<S.size(); ++i){
            cerr << i << ":" << S[i] << endl;
        }
    }
    fenwick(vector<ll>& I){
        n=1;
        while(n<I.size()){
            n*=2;
        }
        S = vector<ll> (2*n,T::neutral());
        for(ll i = 0; i<I.size(); ++i){
            replace(i,I[i]);
        }
    }
private:
    ll n;
    vector<ll> S;
};

int main(){
    vector<ll> A({6,4,3,1,9,4});
    for(int i:A)
        cout << i << " ";
    cout << endl;
    fenwick<mini> F(A);
    F.pr();
    return 0;
}
