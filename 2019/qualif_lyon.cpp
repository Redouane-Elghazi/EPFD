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
	tags = nullptr;
}

//TODO: setTags
Slide::Slide(Photo* l){
	if (not l->isHorizontal()){
		cerr << "Warning: Creating Mono picture Slide with vertical Photo" << endl;
	}
	left = l;
	right = nullptr;
	tags = &l->itags;
}

Slide::Slide(Photo* l, Photo* r){
	if (l->isHorizontal() || r->isHorizontal()){
		cerr << "Warning: Creating Double picture Slide with horizontal Photo" << endl;
	}
	left = l;
	right = r;
	tags = new set<int>();
	set_union(left->itags.begin(),left->itags.end(),right->itags.begin(),right->itags.end(),
			  std::inserter(*tags,tags->begin()));
}

bool Slide::isDouble(){
	return right!=nullptr;
}

Photo* Slide::getLeft(){
	return left;
}
Photo* Slide::getRight(){
	return right;
}

int operator^(const Slide& s1, const Slide& s2){
	set<int> intersect;
	set_intersection(s1.tags->begin(),s1.tags->end(),s2.tags->begin(),s2.tags->end(),
					 std::inserter(intersect,intersect.begin()));
	int interSize = int(intersect.size());
	set<int> diff1;
	set_difference(s1.tags->begin(),s1.tags->end(),s2.tags->begin(),s2.tags->end(),
				   std::inserter(diff1,diff1.begin()));
	int diff1Size = int(diff1.size());
	set<int> diff2;
	set_difference(s2.tags->begin(),s2.tags->end(),s1.tags->begin(),s1.tags->end(),
				   std::inserter(diff2,diff2.begin()));
	int diff2Size = int(diff2.size());
	return min(interSize, min(diff1Size, diff2Size));
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
			p.itags.insert(int(dico.size()));
			dico[p.tags[i]] = int(dico.size());
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


int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	srand(15456);
	int n;
	cin >> n;
	vector<Photo> data(n);
	FOR(i,n){
		cin >> data[i];
		data[i].index = i;
	}

	vector<Slide> output = initial_random(data);
	cout << output.size() << endl;
	for(Slide& s : output){
        cout << s;
	}
	return 0;
}
