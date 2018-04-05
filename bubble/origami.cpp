#include <bits/stdc++.h>
using namespace std;
#define REP(i,a,b) for (int i = (a); i <= (b); ++i)
#define REPD(i,a,b) for (int i = (a); i >= (b); --i)
#define FORI(i,n) REP(i,1,n)
#define FOR(i,n) REP(i,0,int(n)-1)
#define mp make_pair
#define pb push_back
#define pll pair<long, long>
#define vi vector<int>
#define ll long long
#define SZ(x) int((x).size())
#define DBG(v) //cerr << #v << " = " << (v) << endl;
#define FOREACH(i,t) for (auto i = t.begin(); i != t.end(); ++i)
#define fi first
#define se second

ll vec(pll a,pll b){return a.fi*b.se-a.se*b.fi;}

ll scal(pll a,pll b){return a.fi*b.fi+a.se*b.se;}

//right(X,Y,Z) iff Z is on the right of line XY
bool right(pll X,pll Y,pll Z){
	return ((X.fi-Z.fi)*(Y.se-Z.se)-(X.se-Z.se)*(Y.fi-Z.fi))<=0;
}

// returns the 2D convex hull in counterclockwise direction.
// consecutive vertices are not collinear.
vector<pll> convexhull(vector<pll> ab) {
	sort(ab.begin(),ab.end());
	ab.erase(unique(ab.begin(),ab.end()),ab.end());
	int l=SZ(ab),i,j,k;
	vector<pll> res(l+1);

	if (l<3)
		return ab;

	j=0;
	for(i=0;i<l;i++) {
		while (j-2>=0 && right(res[j-2],res[j-1],ab[i]))
			j--;
		res[j++]=ab[i];
	}
	k=j;
	for(i=l-2;i>=0;i--) {
		while (j-1>=k && right(res[j-2],res[j-1],ab[i]))
			j--;
		res[j++]=ab[i];
	}
	if (res[j-1]==res[0])
		j--;
	return vector<pll>(res.begin(),res.begin()+j);
}

double area(pll v_base, pll p1, pll p2, pll p3, pll p4){
	pll v_larg = mp(p3.fi - p1.fi, p3.se - p1.se), v_long = mp(p2.fi - p4.fi, p2.se - p4.se);

	ll norm_carre = v_base.fi*v_base.fi + v_base.se*v_base.se;
	ll larg = vec(v_base,v_larg);
	ll longu = scal(v_base,v_long);

	//cerr << larg << " " << longu << " " << (double)larg*longu/norm_carre << endl;
	return (double)larg*longu/norm_carre;
}

int main () {
	int n;
	cin >> n;
	vector<pll> vertices(n);
	FOR(i,n){
		int x,y;
		cin >> x >> y;
		vertices[i] = mp(x,y);
	}

	vector<pll> ch = convexhull(vertices);

	int i0,i1,i2,i3,i4,aux;/**si 0-1 dirige la longueur, 2-4 représente la longueur et 1-3 la largeur (donc dans l'ordre on a 0-1-2-3-4)**/
	i0 = SZ(ch)-1;
	i1 = 0; //Tight on (SZ(ch)-1, 0)
	i2 = i1;
	i3 = i2;
	i4 = i3;


	pll p2,p2_new,v2,v2_new,p3,p3_new,v3,v3_new,p4,p4_new,v4,v4_new;

	double min_area = numeric_limits<double>::max();
	while(i1 < SZ(ch)){
		pll p0 = ch[i0], p1 = ch[i1];
		pll v_base = mp(p1.fi - p0.fi, p1.se - p0.se);
		//Update of p2
		i2 = max(i1,i2);
		aux = i2;
		do{
			i2 = aux;
			p2 = ch[i2];
			aux = (i2 + 1)%SZ(ch);
			p2_new = ch[aux];
			v2 = mp(p2.fi - p0.fi, p2.se - p0.se), v2_new = mp(p2_new.fi - p0.fi, p2_new.se - p0.se);
		}while(scal(v_base,v2) < scal(v_base,v2_new));

		//Update of p3
		i3 = max(i2,i3);
		aux = i3;
		do{
			i3 = aux;
			p3 = ch[i3];
			aux = (i3 + 1)%SZ(ch);
			p3_new = ch[aux];
			v3 = mp(p3.fi - p0.fi, p3.se - p0.se), v3_new = mp(p3_new.fi - p0.fi, p3_new.se - p0.se);
		}while(vec(v_base,v3) < vec(v_base,v3_new));

		if(i2 == i1 or i2 == i3){//!TODO Je ne sais pas si ce cas là pose un problème... (le sommet confondu est dans un coin du rectangle)
			//cerr << "Sharp angle detected in " << i2 << endl;
		}

		//Update of p4
		i4 = max(i3,i4);
		aux = i4;
		do{
			i4 = aux;
			p4 = ch[i4];
			aux = (i4 + 1)%SZ(ch);
			p4_new = ch[aux];
			v4 = mp(p4.fi - p0.fi, p4.se - p0.se), v4_new = mp(p4_new.fi - p0.fi, p4_new.se - p0.se);
		}while(scal(v_base,v4) > scal(v_base,v4_new));

		if(i4 == i0 or i4 == i3){//!TODO Ni celui là
			//cerr << "Sharp angle detected in " << i4 << endl;
		}

		//cerr << i0 << " " << i1 << " " << i2 << " " << i3 << " " << i4 << endl;
		double new_area = area(v_base,p1,p2,p3,p4);
		if(new_area < min_area){
			min_area = new_area;
		}

		++i1;
		i0 = i1-1;
	}

	cout << round(min_area) << endl;
	return 0;
}
