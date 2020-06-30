#include <iostream>
#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
#include <queue>
#include <list>
#include <array>
#include <math.h>

using namespace std;

string Path(int start,int end,  vector <int> prev) {
    string path;
    if (start == end){
        return "" ;
    }
    /*for(int i=0; i<prev.size(); i++){
        cout << prev.at(i) << "\t";
    }*/
    //cout << endl;
    path = to_string(end);
    while (start != end){
        path = path + " -> ";
        //cout << "END  " << end << endl;
        //cout << "Path  " << path << endl << endl;
        end = prev.at(end);
        //path.append(to_string(u));
        path = path + to_string(end);
    }
    return path;
}

int main() {
    fstream ffile;
    ffile.open("map_int.txt");
    string data;
    int nodes,edges,snode,enode;



    getline(ffile,data);
    nodes = stoi(data);
    getline(ffile,data);
    edges = stoi(data);

    vector<vector <int>> adj_matrix (nodes, vector<int> (nodes, INT_MAX));
    //vector  <int> dist (nodes, INT_MAX);




    while(!ffile.eof()) {
        getline(ffile, data);
        //int thesi,thesi1,thesi2;
        // thesi = data.find(" "); thesi1 = data.find(thesi+1,data.(" "))
        cout << stoi(data.substr(0, data.find(" "))) << " " << stoi(data.substr(data.find(" ") +1, data.find(" ")+1)) << " " <<  stoi(data.substr(data.find_last_of(" ") + 1)) << endl;
        adj_matrix.at(stoi(data.substr(0, data.find(" ")))).at(
                stoi(data.substr(data.find(" ") + 1, data.find(" ")+1))) = stoi(data.substr(data.find_last_of(" ") + 1));
    }




    cout << "Give Start Node" << endl;
    cin >> snode;
    cout << "Give End Node" << endl;
    cin >> enode;
    int u;
    double minimum;
    int alt;

    while(snode != enode){
        vector  <int> dist (nodes, INT_MAX);
        vector <int> prev (nodes);
        vector <bool> visited (nodes,false);
        bool flag = true;


        dist.at(snode) = 0;
        

        while(flag) {
            flag =false;
            minimum = INT_MAX;
            for (int i = 0; i < visited.size(); i++) {
                if (!visited.at(i)) {
                    //cout << "i  " << i << "   dist  " << dist.at(i) << endl;
                    flag = true;
                    if (minimum > dist.at(i)) {
                        minimum = dist.at(i);
                        u = i;
                    }
                }
            }
            //cout << "UUUU   " << u << endl;
            visited.at(u) = true;
            for (int i=0; i < nodes; i++){
                if(adj_matrix.at(u).at(i) != INT_MAX){
                    if ((dist.at(u) + adj_matrix.at(u).at(i)) < dist.at(i)){
                        dist.at(i) = dist.at(u) + adj_matrix.at(u).at(i);
                        prev.at(i) = u;
                    }
                }
            }
        }

        //cout << endl;
        cout << "MINIMUM DISTANCE = " << dist.at(enode) << endl;
        cout << endl;
        string path = Path (snode,enode,prev);
        //reverse(path.begin(),path.end());
        cout << path << endl;
        cout << "Give Start Node" << endl;
        cin >> snode;
        cout << "Give End Node" << endl;
        cin >> enode;
    }

}

