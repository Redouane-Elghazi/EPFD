#ifdef __APPLE__
#   include <vector>
#	include <iostream>
#	include <fstream>
#	include <algorithm>
#	include <set>
#	include <queue>
#else
#	include <bits/stdc++.h>
#endif


using namespace std;

class Ride{
public:
	int startX;
	int startY;
	int endX;
	int endY;
	int startTime;
	int deadline;
};

class Vehicle{
public:
	int x;
	int y;
	int releaseTime;
	bool operator<(Vehicle other) const{
		return releaseTime < other.releaseTime;
	}
};

int R;
int C;
int N;
int T;
int F;
int B;
vector<Ride> rides;
vector<Vehicle> vehicles;


void getInput(const string& filename){

	ifstream in(filename);

	in >> R;
	in >> C;
	in >> F;
	in >> N;
	in >> B;
	in >> T;

}

void printRides(vector<vector<int> > &results){
	std::vector<int>::size_type sz;
	for (int i=0; i<N; ++i){
		sz = results[i].size();
		cout << sz;
		for (int j=0; j<sz; ++j){
			cout << ' ' << results[i][j];
		}
		cout << endl;
	}
}


int bestride(int v){

	return 0;
}

void findrides(){//màj remaining ride
	priority_queue<Vehicle> q_vehicle(vehicles.begin(),vehicles.end()); /**TODO check si en place**/
}

int main(int argc, const char * argv[]) {

	if (argc != 2){
		std::cout << "Erreur: nb Param" << std::endl;
		return 1;
	}

	getInput(argv[1]);

	std::cout << "Hello, World!\n";
    return 0;

}
