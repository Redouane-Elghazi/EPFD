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



    std::cout << "Hello, World!" << std::endl;
    return 0;
}
