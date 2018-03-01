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
	int score;
	Ride(){}
};

istream& operator>> (istream& in, Ride& r){
	
	in >> r.startY;
	in >> r.startX;
	in >> r.endY;
	in >> r.endX;
	in >> r.startTime;
	in >> r.deadline;
	
	r.score = abs(r.startX - r.endX) + abs(r.startY - r.endY);
	
	return in;
}

class Vehicle{
public:
	int x;
	int y;
	int releaseTime;
	
	Vehicle(){
		x = 0;
		y = 0;
		releaseTime = 0;
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
	
	vehicles.resize(F);
	rides.resize(N);
	
	for (int i = 0; i < N; ++i){
		in >> rides[i];
	}

}


int bestride(int v){

	return 0;
}

void findrides(){

}

int main(int argc, const char * argv[]) {
	
	if (argc != 2){
		std::cout << "Erreur: nb Param" << std::endl;
		return 1;
	}
	
	getInput(argv[1]);// "/Users/lois/Documents/Projet Perso/Hashcode/EPFD/Qualif/input/a_example.in"); //
	
	std::cout << "Hello, World!\n";
    return 0;

}
