
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Voiture{
public:
    vector<int> path;
    int ID=-1;
};

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
    vector<int> length(S);
    vector<string> names(S);

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
        voitures[i].ID = i;
        for (int j = 0; j < P; ++j){
            string name;
            cin >> name;
            voitures[i].path.push_back(labels[name]);
        }
    }

    vector<vector<int> > cycles(I);

    




    return 0;
}