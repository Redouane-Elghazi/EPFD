/* Copyright (C) Redouane ELGHAZI
 * TBD
 */
#pragma GCC push_options
#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 10001;
unordered_map<string, pair<int, int>> place;
int row[N] = {};

void update(int pos, int x) {
    for (int i = pos; i <= N; i += i & -i) {
        row[i] += x;
    }
}

int query(int pos) {
    int sum = 0;
    for (int i = pos; i > 0; i -= i & -i) {
        sum += row[i];
    }
    return sum;
}

int query(int l, int r) {
    return query(r) - query(l - 1);
}
int score(string& s){
    return accumulate(s.begin(), s.end(), 0) - s.size()*('a'-1);
}

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    int nb, n = 0;
    cin >> nb;
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
                ++n;
                int sc = score(s);
                place[s] = make_pair(n, sc);
                update(n, sc);
            }
            break;
        }
        case 'S':{
            string s, t;
            cin >> s >> t;
            auto &p1 = place[s], &p2 = place[t];
            int diff = p1.second - p2.second;
            update(p1.first, -diff);
            update(p2.first, diff);
            swap(p1.first, p2.first);
            break;
        }
        case 'M':{
            string s, t;
            cin >> s >> t;
            int k = place[s].first, l = place[t].first;
            if(k>l)
                swap(k,l);
            cout << query(k, l) << endl;
            break;
        }
        case 'R':{
            string s, t;
            cin >> s >> t;
            pair<int,int> p = place[s];
            int diff = score(t) - p.second;
            p.second += diff;
            update(p.first, diff);
            place[t] = p;
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
