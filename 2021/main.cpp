
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
        names[id] = name;
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

    //Tableau de tableaux contenant pour chaque intersection le temps allume de chaque rue entrante
    vector<vector<int> > cycles(I);
    for(int i = 0; i < I; ++i){
        cycles[i].resize(intersectionIn[i].size());
    }

    

    cout << cycles.size() << endl;

    for (int i = 0; i < cycles.size(); ++i){
        cout << i << endl;
        cout << cycles[i].size() << endl;
        for (int j = 0; j < intersectionIn[i].size(); ++j){
            cout << names[intersectionIn[i][j]] << " " << cycles[i][j] << endl;
        }
    }


    return 0;
}