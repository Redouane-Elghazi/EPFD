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

istream& operator>>(istream& in, Photo& p){
	in >> p.v_or_h >> p.nb_tags;
	p.tags.resize(p.nb_tags);
	FOR(i,p.nb_tags){
		in >> p.tags[i];
	}
	return in;
}

vector<Slide> initial_random(vector<Photo>& photos){
    vector<Slide> ret;
    vector<Photo> verts;
    for(photo x:photos){
        if(photo.isHorizontal()){
            ret.emplace_back(x);
        }
        else{
            verts.pb(x);
        }
    }
    random_shuffle(verts.begin(), verts.end());
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	seed(15);
	int n;
	vector<Photo> data(n);
	FOR(i,n){
		cin >> data[i];
		data[i].index = i;
	}

	vector<Slide> output;
	cout << output.size() << endl;
	for(Slide s : output){
		cout << s.fi->index;
		if(s.se){
			cout << " " << s.se->index;
		}
		cout << endl;
	}
	return 0;
}
