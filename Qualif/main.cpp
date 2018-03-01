#include <iostream>
#include <fstream>
#include <vector>


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


int main(int argc, const char * argv[]) {
	
	if (argc != 2){
		std::cout << "Erreur: nb Param" << std::endl;
		return 1;
	}
	
	getInput(argv[1]);
	
	std::cout << "Hello, World!\n";
    return 0;
	
}
