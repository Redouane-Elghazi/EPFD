#include <bits/stdc++.h>

using namespace std;

namespace knapsack1{

    int recursiveKnapsack(vector<vector<int>>& score, vector<vector<bool>>& pris, vector<int>& weights, vector<int>& valeur, int poids, int nbItems){
        if (poids < 0){
            return numeric_limits<int>::min();
        }
        if (score[poids][nbItems] == -1){

            int scorePaspris = recursiveKnapsack(score, pris, weights, valeur, poids, nbItems - 1);
            int scorePris = recursiveKnapsack(score, pris, weights, valeur, poids - weights[nbItems-1], nbItems - 1) + valeur[nbItems-1];

            if  (scorePris > scorePaspris) {
                //On prend
                pris[poids][nbItems] = true;
                score[poids][nbItems] = scorePris;
            } else {
                //On prend pas
                pris[poids][nbItems] = false;
                score[poids][nbItems] = scorePaspris;
            }
        }

        return score[poids][nbItems];
    }

    void solve(vector<vector<int>> &lB,
               vector<int> &lD,
               vector<int> &lS,
               vector<int> &books,
               int D,
               vector<int> &Y,
               vector<vector<int> > &K) {

        int L = lB.size();

        //init score no weight left or no items means 0 score
        vector<vector<int>> score (D+1, vector<int>(L+1));
        for(int i = 0; i <= L; ++i){
            score[0][i] = 0;
        }
        for(int i = 0; i <= D; ++i){
            score[i][0] = 0;
        }

        vector<vector<bool> > pris (D+1, vector<bool>(L+1, false));

        vector<int>& weights = lD;
        vector<int> valeur(L, 0);
        for(int i = 0; i < L; ++i){
            for(int b : lB[i]){
                valeur[i] += books[b];
            }
        }

        recursiveKnapsack(score, pris, weights, valeur, D, L);

        vector<bool> finalPris(L);

        int nbPris=0;
        int poids = D;
        for (int i = L; i > 0; ++i){
            finalPris[i-1] = pris[poids][i];
            if (finalPris[i - 1]) {
                ++nbPris;
                poids -= weights[i - 1];
            }
        }

        Y.reserve(nbPris);
        K.resize(nbPris);

        for(int i = 0; i < L; ++i){
            if (finalPris[i]) {
                Y.push_back(i);
                K[i] = lB[i];
            }
        }
    }
}