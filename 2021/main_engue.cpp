
#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassert>
#include <map>

using namespace std;

class Voiture{
public:
    vector<int> path;
    int ID=-1;
};

int min_degueulasse = 1000000;
int scoreOptOneCar(const Voiture& v, vector<int>& length, int D, int F, vector<int>& jam){
    int trajet = jam[v.path[0]]++;
    for (int i = 1; i < v.path.size(); ++i){
        trajet += length[v.path[i]];
    }

    min_degueulasse = min(min_degueulasse, trajet);
    if (trajet <= D){
        return F + (D - trajet);
    } else {
        return 0;
    }
}

int scoreOptAllCar(const vector<Voiture>& voitures, vector<int>& length, int D, int F){
    int res = 0;
    int voituresInutiles = 0;
    vector<int> jam(length.size(),0);
    for (const Voiture& v : voitures){
        int score = scoreOptOneCar(v, length, D, F, jam);
        if (score == 0){
            voituresInutiles += 1;
        }
        res += score;
    }
    cerr << "Nombre de voitures inutiles: " << voituresInutiles << endl;
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
    vector<int> length(S);
    vector<string> names(S);

    vector<int> roadToInterIn(S);

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
        roadToInterIn[id] = end;
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

    cerr << "Score Optimal:" << scoreOptAllCar(voitures, length, D, F) << endl;

    cerr << "Temps premier: " << min_degueulasse << endl;
    int cyclesSize;
    cin >> cyclesSize;

    //Tableau de tableaux contenant pour chaque intersection la séquence (rue, temps)
    vector<vector<pair<int,int>>> cycles(cyclesSize);
    for(int i = 0; i < cyclesSize; ++i){
        int unCycleSize;
        cin >> unCycleSize;
        cycles[i].resize(unCycleSize);
        for(int j = 0; j < unCycleSize; ++j){
            string nameRue;
            int tailleCycle;
            cin >> nameRue >> tailleCycle;
            cycles[i][j] = make_pair(labels[nameRue], tailleCycle);
        }
    }

    vector<int> cyclesLength(cyclesSize);
    for(int i = 0; i < cyclesSize; ++i){
        int r = 0;
        for(auto p : cycles[i]){
            r += p.second;
        }
        cyclesLength[i] = r;
    }

    vector<map<int,pair<int,int>>> tickets(intersectionIn.size());
    for(int i = 0; i < tickets.size(); ++i){
        for(int j : intersectionIn[i]){
            tickets[i][j] = make_pair(1,1);
        }
    }

    // tuple(nbroad, lenghtroadremaining if negatif, tickets if positive
    vector<pair<int, int>> voitPathTick(V);

    // Prise de tickets everywhere
    for(int i = 0; i < V; ++i){
        int road = voitures[i].path[0];
        int curTicket = tickets[roadToInterIn[road]][road].second++;
        voitPathTick[i] = make_pair(0, curTicket);
    }

    int score = 0;
    for(int j = 0; j < D; ++j){
        for(int i = 0; i < V; ++i){
            if(voitPathTick[i].first < voitures[i].path.size()){
                int road = voitures[i].path[voitPathTick[i].first];
                if (voitPathTick[i].second == 0){
                    int curTicket = tickets[roadToInterIn[road]][road].second++;
                    voitPathTick[i].second = curTicket;
                }
                if (voitPathTick[i].second > 0){
                    if(tickets[roadToInterIn[road]][road].first == voitPathTick[i].second){
                        tickets[roadToInterIn[road]][road].first++;

                        int timeMod = j % cyclesLength[roadToInterIn[road]];
                        int computeTime = 0;
                        int k;
                        for(k = 0; k < cycles[roadToInterIn[road]].size() and cycles[roadToInterIn[road]][k].first != road; ++k){
                            computeTime += cycles[roadToInterIn[road]][k].second;
                        }
                        assert(k < cycles[roadToInterIn[road]].size());
                        if(computeTime <= timeMod and timeMod < computeTime + cycles[roadToInterIn[road]][k].second){
                            voitPathTick[i].first += 1;
                            if(voitPathTick[i].first == voitures[i].path.size()){
                                score += F;
                                score += D - j;
                            }
                            voitPathTick[i].second = -voitures[i].path[voitPathTick[i].first]+1;
                        }
                    }
                } else {
                    voitPathTick[i].second += 1;
                }
            }
        }
    }
    return 0;
}