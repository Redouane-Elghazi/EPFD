#include <bits/stdc++.h>

using namespace std;

void output(vector<int>& Y, vector<vector<int> >& K){
    cout << Y.size() << endl;

    for (int i = 0; i < Y.size(); ++i){
        cout << Y[i] << " " << K[i].size() << endl;
        for (int b : K[i]){
            cout << b << " ";
        }
        cout << endl;
    }

}

int main() {

    vector<vector<int>> librariesBooks;
    vector<int> librariesDelay;
    vector<int> librariesShipment;
    vector<int> books;

    int D, B, L;
    int tmp, tmp_size, tmp_delay, tmp_ship;

    cin >> B >> L >> D;
    
    books.reserve(B);
    librariesBooks.reserve(L);
    librariesDelay.reserve(L);
    librariesShipment.reserve(L);
    
    for(int b=0; b < B; b++){
       cin >> tmp;
       books.push_back(tmp);
    }
    
    for(int l=0; l < L;l++){
        cin >> tmp_size >> tmp_delay >> tmp_ship;
        librariesBooks.emplace_back(tmp_size);
        librariesDelay.push_back(tmp_delay);
        librariesShipment.push_back(tmp_ship);
        for(int i=0; i < tmp_size; ++i){
            cin >> librariesBooks[l][i];
        }
    }
    
    return 0;
}
