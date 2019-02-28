/* Copyright (C) Redouane ELGHAZI
 * TBD
 */
#include "qualif_lyon.hpp"

using namespace std;

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
    for(Photo x:photos){
        if(x.isHorizontal()){
            ret.emplace_back(&x);
        }
        else{
            verts.pb(x);
        }
    }
    random_shuffle(verts.begin(), verts.end());
    for(int i = 0; i+1<verts.size(); i+=2){
        ret.emplace_back(&verts[i], &verts[i+1]);
    }
    random_shuffle(ret.begin(), ret.end());
    return ret;
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	srand(15);
	int n;
	vector<Photo> data(n);
	FOR(i,n){
		cin >> data[i];
		data[i].index = i;
	}

	vector<Slide> output;
	cout << output.size() << endl;
	for(Slide s : output){
		cout << s.left->index;
		if(s.right){
			cout << " " << s.right->index;
		}
		cout << endl;
	}
	return 0;
}
