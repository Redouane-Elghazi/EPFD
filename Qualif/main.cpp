#include <bits/stdc++.h>

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
};

int R;
int C;
int N;
int T;
int F;
vector<Ride> rides;
vector<Vehicle> vehicles;
set<int> remainingRides;

int d(int x1, int y1, int x2, int y2){
    return abs(x1 - x2) + abs(y1 - y2);
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

void findrides(){

}

int main(int argc, const char * argv[]) {

	// insert code here...
	cout << "Hello, World!\n";
    return 0;

}
