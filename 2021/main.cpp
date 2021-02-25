
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Voiture{
public:
    vector<int> path;
    int ID=-1;
};

int scoreOptOneCar(const Voiture& v, vector<int>& length, int D, int F){
    int trajet = 0;
    for(int rue : v.path){
        trajet += length[rue];
    }

    if(trajet < D){
        return F + (D - trajet);
    }else{
        return 0;
    }
}

int scoreOptAllCar(const vector<Voiture>& voitures, vector<int>& length, int D, int F){
    int res = 0;
    for(const Voiture& v : voitures){
        res += scoreOptOneCar(v, length, D, F);
    }
    return res;
}

int main(){
    int D;
    int I;
    int S;
    int V;
    int F;
    unordered_map<string, int> labels;

    cin >> D >> I >> S >> V >> F;

    vector<vector<int>> intersectionIn(I);
    vector<vector<int>> intersectionOut(I);
    vector<int> length(I);

    vector<Voiture> voitures(V);

    for (int i = 0; i < S; ++i){
        string name;
        int start, end, len;
        cin >> start >> end;
        cin >> name;
        cin >> len;
        int id = labels[name] = labels.size();
        intersectionIn[end].push_back(id);
        intersectionOut[start].push_back(id);
        length[id] = len;
    }

    for (int i = 0; i < V; ++i){
        int P;
        cin >> P;
        voitures.emplace_back();
        voitures.back().ID = i;
        for (int j = 0; j < P; ++j){
            string name;
            cin >> name;
            voitures.back().path.push_back(labels[name]);
        }
    }



    return 0;
}