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

int d(int x1, int y1, int x2, int y2){
    return abs(x1 - x2) + abs(y1 - y2);
}

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
set<int> remainingRides;


void getInput(const string& filename){

	ifstream in(filename);

	in >> R;
	in >> C;
	in >> F;
	in >> N;
	in >> B;
	in >> T;

}


int bestride(int v){
    int res = -1;
    double obj = 0;
    Vehicle& V = vehicles[v];
    for(int r:remainingRides){
        int finish = max(V.releaseTime + d(V.x, V.y, rides[r].startX, rides[r].startY), rides[r].startTime) +
            d(rides[r].startX, rides[r].startY, rides[r].endX, rides[r].endY);
        double new_obj = (double)rides[r].score/(finish - V.releaseTime);
        if(finish <= rides[r].deadline and new_obj > obj){
            obj = new_obj;
            res = r;
        }
    }
    return res;
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
