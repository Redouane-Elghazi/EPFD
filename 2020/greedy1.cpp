#include <bits/stdc++.h>

using namespace std;

namespace greedy1{
void solve(vector<vector<int>> &lB,
          vector<int> &lD,
          vector<int> &lS,
          vector<int> &books,
          int D,
          vector<int> &Y,
          vector<vector<int> > &K){
    int L = lD.size();
    int B = books.size();
    Y.clear();
    K.clear();
    vector<set<pair<int, int> > > ordered_books(L);
    set<int> alive;
    vector<vector<int> > book2lib(B);
    for(int i = 0; i<L; ++i){
        alive.insert(i);
        for(int b:lB[i]){
            ordered_books[i].emplace(-books[b], b);
            book2lib[b].push_back(i);
        }
    }

    while(D>0){
        int maxi = -1, maxv = -1;
        for(int i:alive){
            int cur = 0;
            int remain = (D-lD[i])*lS[i];
            //cerr << "r " << remain << endl;
            for(auto b:ordered_books[i]){
                if(remain<=0)
                    break;
                --remain;
                cur += -b.first;
            }
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
            if(remain<=0)
                break;
//cerr << b.second << endl;
            --remain;
            K.back().push_back(b.second);
            for(int i:book2lib[b.second]){
                if(i!=maxi){
                    ordered_books[i].erase(b);
                }
            }
        }
        D-=lD[maxi];
    }
}
}
