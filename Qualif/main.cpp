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
long long totalScore;
vector<Ride> rides;
vector<Vehicle> vehicles;
set<int> remainingRides;
vector<vector<int> > result;

void getInput(const string& filename){

	ifstream in(filename.c_str());

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
		remainingRides.insert(i);
	}

	result.resize(F);

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


int bestride(int v, int& newRelease){
    int res = -1;
    double obj = 0;
    long long newScore = 0;
    newRelease = T+1;
    Vehicle& V = vehicles[v];
    for(int r:remainingRides){
        int finish = max(V.releaseTime + d(V.x, V.y, rides[r].startX, rides[r].startY), rides[r].startTime) +
            d(rides[r].startX, rides[r].startY, rides[r].endX, rides[r].endY);
        double new_obj;
        if(V.releaseTime + d(V.x, V.y, rides[r].startX, rides[r].startY)<=rides[r].startTime){
            new_obj = (double)(rides[r].score+B)/(finish - V.releaseTime);
            newScore = rides[r].score+B;
        }
        else{
            new_obj = (double)rides[r].score/(finish - V.releaseTime);
            newScore = rides[r].score;
        }
        if(finish <= rides[r].deadline and new_obj > obj){
            obj = new_obj;
            res = r;
            newRelease = finish;
        }
    }
    totalScore += newScore;
    return res;
}


void findrides(){//maj remaining ride

	priority_queue<pair<int,int> > q_vehicle; /* check si en place. Seems ok*/
	for(int v = 0; v < F; ++v){
		q_vehicle.emplace(-vehicles[v].releaseTime,v);
	}

	int mini = 0;

	while(mini < T){
		pair<int,int> veh_updated = q_vehicle.top();
		q_vehicle.pop();

		int new_time;
		int new_ride = bestride(veh_updated.second, new_time);

		if(new_ride != -1){
			//Update the vehicle
			vehicles[veh_updated.second].x = rides[new_ride].endX;
			vehicles[veh_updated.second].y = rides[new_ride].endY;
			vehicles[veh_updated.second].releaseTime = new_time;
			q_vehicle.emplace(-new_time,veh_updated.second);

			remainingRides.erase(new_ride);
			result[veh_updated.second].push_back(new_ride);
		}
		else{
			vehicles[veh_updated.second].releaseTime = T+1;
		}
		mini = -q_vehicle.top().first;
	}
}

int main(int argc, const char * argv[]) {

    totalScore = 0;
	if (argc != 2){
		std::cout << "Erreur: nb Param" << std::endl;
		return 1;
	}

	getInput(argv[1]);// "/Users/lois/Documents/Projet Perso/Hashcode/EPFD/Qualif/input/a_example.in"); //

	std::cout << "Hello, World!\n";
    return 0;

}
