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

class sum{
public:
    static ll op(ll a, ll b){
        return a+b;
    }
    static ll neutral(){
        return 0;
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
        while(a>=n){
            n=max(1LL, 2*n);
            vector<ll> I;
            S.swap(I);
            S = vector<ll> (2*n,T::neutral());
            for(ll i = I.size()/2; i<I.size(); ++i){
                replace(i-I.size()/2,I[i]);
            }
        }
        S[a+n] = c;
        replace(0, n, c, 1, a);
    }
    void pr(){
        for(ll i = 0; i<S.size(); ++i){
            cerr << i << ":" << S[i] << endl;
        }
    }
    fenwick(ll nb = 0){
        n=1;
        while(n<nb){
            n*=2;
        }
        S = vector<ll> (2*n,T::neutral());
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

ll score(string& s){
    ll res = 0;
    for(char c:s){
        res += c-'a'+1;
    }
    return res;
}

int main(){
    int nb, n = 0;
    cin >> nb;
    fenwick<sum> row(10000);
    map<string, ll> place;
    for(int i = 0; i<nb; ++i){
        string a;
        cin >> a;
        char c = a[0];
        switch(c){
        case 'A':{
            string s;
            cin >> s;
            if(place.find(s)!=place.end()){
                cout << "Can't add " << s << endl;
            }
            else{
                place[s] = n;
                row.replace(n, score(s));
                ++n;
            }
            break;
        }
        case 'S':{
            string s, t;
            cin >> s >> t;
            int k = place[s], l = place[t];
            place[s] = l, place[t] = k;
            row.replace(l, score(s));
            row.replace(k, score(t));
            break;
        }
        case 'M':{
            string s, t;
            cin >> s >> t;
            int k = place[s], l = place[t];
            if(k>l)
                swap(k,l);
            cout << row.query(k, l+1) << endl;
            break;
        }
        case 'R':{
            string s, t;
            cin >> s >> t;
            int k = place[s];
            row.replace(k, score(t));
            place[t] = k;
            place.erase(s);
            break;
        }
        case 'N':{
            cout << n << endl;
            break;
        }
        }
    }
    return 0;
}
