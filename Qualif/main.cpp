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


void findrides(){//maj remaining ride

	priority_queue<pair<int,int>> q_vehicle; /* check si en place. Seems ok*/
	for(int v = 0; v < F; ++v){
		q_vehicle.push(make_pair(-vehicles[v].releaseTime,v))
	}

	int mini = 0;

	while(mini < T){
		pair<int,int> veh_updated = q_vehicle.top();
		q_vehicle.pop();
		int new_ride = bestride(veh_updated.second);

		//update veh_updated

		//insert it back in queue

		mini = -q_vehicle.top();
	}
}

int main(int argc, const char * argv[]) {

	findrides();
	if (argc != 2){
		std::cout << "Erreur: nb Param" << std::endl;
		return 1;
	}

	getInput(argv[1]);

	std::cout << "Hello, World!\n";
    return 0;

}
