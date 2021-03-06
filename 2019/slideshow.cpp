#include "slideshow.hpp"
#include "qualif_lyon.hpp"

using namespace std;

//Vertical random
//Horizontal linear
vector<Slide> greedy_nul(vector<Photo>& photos){
	vector<Slide> init = initial_random(photos);

	vector<Slide> ret(init.size());
	vector<bool> seen(ret.size(),false);
	ret[0] = init[0];
	seen[0] = true;

	FOR(i,ret.size()-1){
		int maxi_ind = -1;
		int maxi = -1;
		if(i%1000 == 0){
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
