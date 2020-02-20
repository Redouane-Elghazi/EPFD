/* Copyright (C) Redouane ELGHAZI
 * TBD
 */
#include "qualif_lyon.hpp"
#include "slideshow.hpp"

using namespace std;

using namespace std;


/********************
 PHOTO
 ***********************/

bool Photo::isVertical(){
	return v_or_h == 'V';
}

bool Photo::isHorizontal(){
	return v_or_h == 'H';
}


/********************
 SLIDE
 ***********************/

Slide::Slide(){
	left = nullptr;
	right = nullptr;
}

Slide::Slide(Photo* l){
	if (not l->isHorizontal()){
		cerr << "Warning: Creating Mono picture Slide with vertical Photo" << endl;
	}
	left = l;
	right = nullptr;
	tags = l->itags;
    for(int i:tags){
        booltag.set(i);
    }
	if (tags.size() > 100){
		cerr << tags.size() << " Create clone" << endl;
	}
}

Slide::Slide(Photo* l, Photo* r){
	if (l->isHorizontal() || r->isHorizontal()){
		cerr << "Warning: Creating Double picture Slide with horizontal Photo" << endl;
	}
	left = l;
	right = r;

	set_union(left->itags.begin(),left->itags.end(),right->itags.begin(),right->itags.end(),
			  std::inserter(tags,tags.begin()));
    for(int i:tags){
        booltag.set(i);
    }
	if (tags.size() > 200){
		cerr << tags.size() << " Create merge" << endl;
	}
}

bool Slide::isDouble(){
	return right!=nullptr;
}

const Photo* Slide::getLeft() const{
	return left;
}
const Photo* Slide::getRight() const{
	return right;
}

int operator^(const Slide& s1, const Slide& s2){
	set<int> intersect;
	for(int i:s1.tags)
        if(s2.tags.find(i)!=s2.tags.end())
            intersect.insert(i);
	int interSize = int(intersect.size());
	set<int> diff1=s1.tags;
	for(int i:s2.tags)
        diff1.erase(i);
	int diff1Size = int(diff1.size());
	set<int> diff2=s2.tags;
	for(int i:s1.tags)
        diff2.erase(i);
	int diff2Size = int(diff2.size());
	return min(interSize, min(diff1Size, diff2Size));
}
int chapeau(const Slide& s1, const Slide& s2){
	return min((s1.booltag & ~s2.booltag).count(), min((~s1.booltag & s2.booltag).count(), (s1.booltag & s2.booltag).count()));
}

/********************
 OTHER
 ***********************/



istream& operator>>(istream& in, Photo& p){
	static map<string, int> dico;

	in >> p.v_or_h >> p.nb_tags;
	p.tags.resize(p.nb_tags);
	FOR(i,p.nb_tags){
		in >> p.tags[i];
	}
	FOR(i,p.nb_tags){
		auto res = dico.find(p.tags[i]);
		if (res == dico.end()){
			dico[p.tags[i]] = int(dico.size())-1;
			p.itags.insert(dico[p.tags[i]]);
		}else{
			p.itags.insert(res->second);
		}
	}

	return in;
}

ostream& operator<< (ostream& stream, const Slide& s){
    cout << s.left->index;
    if(s.right){
        cout << " " << s.right->index;
    }
    cout << endl;
    return stream;
}

vector<Slide> initial_random(vector<Photo>& photos){
    vector<Slide> ret;
    vector<Photo*> verts;
    for(Photo &x:photos){
        if(x.isHorizontal()){
            ret.emplace_back(&x);
        }
        else{
            verts.pb(&x);
        }
    }
    random_shuffle(verts.begin(), verts.end());
    for(unsigned int i = 0; i+1<verts.size(); i+=2){
        ret.emplace_back(verts[i], verts[i+1]);
    }
    random_shuffle(ret.begin(), ret.end());
    return ret;
}

vector<Slide> greedy_nul(vector<Photo>& photos){
	vector<Slide> init = initial_random(photos);

	vector<Slide> ret(init.size());
	vector<bool> seen(ret.size(),false);
	ret[0] = init[0];
	seen[0] = true;

	FOR(i,ret.size()-1){
		int maxi_ind = -1;
		int maxi = -1;
		if(i%10 == 0){
			cerr << i << endl;
		}
		FOR(j,init.size()){
			if(seen[j]){
				continue;
			}
			int chall_val = chapeau(ret[i],init[j]);
			if(chall_val > maxi){
				maxi_ind = j;
				maxi = chall_val;
			}
		}
		seen[maxi_ind] = true;
		ret[i+1] = init[maxi_ind];
	}
	return ret;
}

int score(vector<Slide>& s){
    int res = 0;
    for(size_t i = 0; i+1<s.size(); ++i){
        res += chapeau(s[i],s[i+1]);
    }
    return res;
}



int main(){
	//ifstream cin("/Users/lois/Documents/Projet Perso/Hashcode/EPFD/2019/statement/e_shiny_selfies.txt");
	cin.sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin >> n;
	vector<Photo> data(n);
	FOR(i,n){
		cin >> data[i];
		data[i].index = i;
	}
	int maxscore = 0;
	vector<Slide> output;
	srand(0);
	for(int i = 0; i<1; ++i){
        srand(rand());
        vector<Slide> t = greedy_nul(data);
        int S = score(t);
        if(maxscore<S){
            maxscore = S;
            output = t;
        }
	}
	cerr << score(output) << endl;
	cout << output.size() << endl;
	for(Slide& s : output){
		cout << s;
	}
	return 0;
}
