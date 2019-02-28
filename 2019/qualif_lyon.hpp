#ifndef QUALIF_LYON_HPP_INCLUDED
#define QUALIF_LYON_HPP_INCLUDED

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

struct Photo{
	char v_or_h;
	int nb_tags;
	std::vector<std::string> tags;
	int index;
	
	bool isVertical(){
		return v_or_h == 'V';
	}
	bool isHorizontal(){
		return v_or_h == 'H';
	}
};

struct Slide{
	Photo* left;
	Photo* right;

	Slide(){
		left = nullptr;
		right = nullptr;
	}

	Slide(Photo* l){
		left = l;
		right = nullptr;
	}

	Slide(Photo* l, Photo* r){
		left = l;
		right = r;
	}
};

int costInterSlide(Slide& s1, Slide& s2);


#endif // QUALIF_LYON_HPP_INCLUDED
