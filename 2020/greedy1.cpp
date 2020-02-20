#include <bits/stdc++.h>

using namespace std;

namespace greedy1{
double ALPHA = 0.9;
double BETA = 0;
int solve(vector<vector<int>> &lB,
          vector<int> &lD,
          vector<int> &lS,
          vector<int> &books,
          int D,
          vector<int> &Y,
          vector<vector<int> > &K){
    int res = 0;
    int L = lD.size();
    int B = books.size();
    Y.clear();
    K.clear();
    vector<set<pair<int, int> > > ordered_books(L);
    set<int> alive;
    vector<set<int> > book2lib(B);
    for(int i = 0; i<L; ++i){
        alive.insert(i);
        for(int b:lB[i]){
            book2lib[b].insert(i);
        }
    }
    for(int i = 0; i<L; ++i){
        for(int b:lB[i]){
            ordered_books[i].emplace(-(books[b]), b);
        }
    }

    while(D>0){
        int maxi = -1;
        double maxv = -1;
        for(int i:alive){
            double cur = 0;
            int remain = (D-lD[i])*lS[i];
            //cerr << "r " << remain << endl;
            for(auto b:ordered_books[i]){
                if(remain<=0)
                    break;
                --remain;
                cur += -b.first;
            }
            cur -= BETA*remain;
            cur /= std::pow(lD[i], ALPHA);
            if(cur>maxv){
                maxi = i;
                maxv = cur;
            }
//cerr << i << " " << cur << " " << maxi << " " << maxv << endl;
        }
        if(maxv <= 0)
            break;
//cerr << maxi << endl;
        Y.push_back(maxi);
        K.emplace_back();
        int remain = (D-lD[maxi])*lS[maxi];
        //cerr << "r " << remain << endl;
        alive.erase(maxi);
        for(auto b:ordered_books[maxi]){
            book2lib[b.second].erase(maxi);
            if(remain<=0){
                for(int i:book2lib[b.second]){
                    ordered_books[i].erase(b);
                    ordered_books[i].emplace(-(books[b.second]),
                                             b.second);
                }
            }
            else{
                --remain;
                K.back().push_back(b.second);
                res += books[b.second];
                for(int i:book2lib[b.second]){
                    ordered_books[i].erase(b);
                }
            }
        }
        D-=lD[maxi];
    }
    cerr << res << endl;
    return res;
}
}
