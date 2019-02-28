#ifndef QUALIF_LYON_HPP_INCLUDED
#define QUALIF_LYON_HPP_INCLUDED

#pragma GCC push_options
#pragma GCC optimize ("O3")
#   include <vector>
#	include <iostream>
#	include <fstream>
#	include <algorithm>
#	include <set>
#	include <map>
#	include <queue>
#	include <cmath>
#	include <bitset>
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

std::istream& operator>>(std::istream& in, Photo& p);

struct Slide{
private:
	Photo* left;
	Photo* right;
	std::set<int> tags;
	std::bitset<220> booltag;

public:
	Slide();
	Slide(Photo* l);
	Slide(Photo* l, Photo* r);

	const Photo* getLeft() const;
	const Photo* getRight() const;

	bool isDouble();

	friend int chapeau(const Slide& s1, const Slide& s2);
	friend int operator^(const Slide& s1, const Slide& s2);
	friend std::ostream& operator<< (std::ostream& stream, const Slide& s);
};


int score(std::vector<Slide>& s);


#endif // QUALIF_LYON_HPP_INCLUDED
