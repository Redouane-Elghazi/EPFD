/* Copyright (C) Redouane ELGHAZI
 * TBD
 */
#pragma GCC push_options
#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define ll long long
#define p(i) ((i)/2)
#define f1(i) ((i)*2)
#define f2(i) ((i)*2+1)
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

    void actualize(ll i){
        S[i] = T::op(S[f1(i)], S[f2(i)]);
        if(i!=1){
            actualize(p(i));
        }
    }
    void replace(ll a, ll c){
        if(n<=a){
            while(n<=a){
                n=max(1LL, 2*n);
            }
            vector<ll> I;
            S.swap(I);
            S = vector<ll> (2*n,T::neutral());
            for(unsigned int i = I.size()/2; i<I.size(); ++i){
                replace(i-I.size()/2,I[i]);
            }
        }
        S[a+n] = c;
        actualize(p(a+n));
    }
    void pr(){
        for(unsigned int i = 0; i<S.size(); ++i){
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
        for(unsigned int i = 0; i<I.size(); ++i){
            replace(i,I[i]);
        }
    }
private:
    ll n;
    vector<ll> S;
};
ll score(string& s){
    return accumulate(s.begin(), s.end(), 0) - s.size()*('a'-1);
}

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    int nb, n = 0;
    cin >> nb;
    fenwick<sum> row(10000);
    unordered_map<string, pair<int, int> > place;
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
                int sc = score(s);
                place[s] = make_pair(n, sc);
                row.replace(n, sc);
                ++n;
            }
            break;
        }
        case 'S':{
            string s, t;
            cin >> s >> t;
            auto &p1 = place[s], &p2 = place[t];
            row.replace(p1.first, p2.second);
            row.replace(p2.first, p1.second);
            swap(p1.first, p2.first);
            break;
        }
        case 'M':{
            string s, t;
            cin >> s >> t;
            int k = place[s].first, l = place[t].first;
            if(k>l)
                swap(k,l);
            cout << row.query(k, l+1) << endl;
            break;
        }
        case 'R':{
            string s, t;
            cin >> s >> t;
            pair<int,int> p = place[s];
            p.second = score(t);
            row.replace(p.first, p.second);
            place[t] = p;
            place.erase(s);
            break;
        }
        case 'N':{
            cout << n << endl;
            break;
        }
        default:
            row.pr();
        }
    }
    return 0;
}
