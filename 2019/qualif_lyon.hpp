#ifndef QUALIF_LYON_HPP_INCLUDED
#define QUALIF_LYON_HPP_INCLUDED

#pragma GCC push_options
#pragma GCC optimize ("O3")
<<<<<<< HEAD
#   include <vector>
#	include <iostream>
#	include <fstream>
#	include <algorithm>
#	include <set>
#	include <map>
#	include <queue>
#	include <cmath>
using namespace std;
=======
#include <bits/stdc++.h>
>>>>>>> origin/master
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
	std::set<int> itags;
	int index;
	
	bool isVertical();
	bool isHorizontal();
};

struct Slide{
private:
	Photo* left;
	Photo* right;
	std::set<int>* tags;

public:
	Slide();
	Slide(Photo* l);
	Slide(Photo* l, Photo* r);
	
	Photo* getLeft();
	Photo* getRight();
	
	bool isDouble();
	
	friend int operator^(const Slide& s1, const Slide& s2);
};



#endif // QUALIF_LYON_HPP_INCLUDED
