#include <iostream>
#include <stdlib.h>
#include <vector>
#include <ctime>
#include <cmath>
#include <bitset>
#include <queue>
#include <bits/stdc++.h>
#include <fstream>

using namespace std;

#define SIZE 10000

void printQueue( queue<vector<int> > q)
{
    //printing content of queue
    while (!q.empty()){
        for(int i = 0; i < q.front().size();i++)
            cout<<" " << q.front().at(i);
        cout << endl << "Debug:PrintQueue" << endl;
        q.pop();
    }
    cout<<endl;
}

void printpath(vector<int>& path){
    int size = path.size();
    for (int i = 0; i < size; i++)
        cout << path[i] << " ";
    cout << endl;
}

// utility function to check if current
// vertex is already present in path
int isNotVisited(int x, vector<int>& path){
    int size = path.size();
    for (int i = 0; i < size; i++)
        if (path[i] == x)
            return 0;
    return 1;
}

vector<vector<int>> findpaths(vector<vector<int> >&g, int src,int dst, int v){
    // create a queue which stores
    // the paths
    //cout << "Debug" << endl;
    queue<vector<int> > q;

    cout << "Source: " << src << " Dest: " << dst << " Size: " << v << endl << endl;

    /*for(int i=0;i<v;i++) {
        for (int j = 0; j < v; j++) {
            cout << g.at(i).at(j) << "\t";
        }
        cout << endl;
    }
    cout << endl;*/


    // path vector to store the current path
    vector<int> path;
    vector<vector<int>> store_path;

    path.push_back(src);
    q.push(path);
    while (!q.empty()) {

       // cout << "Debug:while ";
        path = q.front();
        q.pop();
        int last = path[path.size() - 1];
        //cout << last << " == " << dst << endl;

        // if last vertex is the desired destination
        // then print the path
       // cout << "Debug:path_size: " << path.size() << endl;

        if (last == dst){
            //cout << "Debug:if" << endl;
            /*for(int i = 0;i < path.size();i++)
                cout << path.at(i) << "\t";
            cout << endl;*/
            printpath(path);
            store_path.push_back(path);


        }

        /*cout << "Queue: ";
        printQueue(q);
        cout << endl;*/

        // traverse to all the nodes connected to
        // current vertex and push new path to queue
        for (int i = 0; i < g[last].size(); i++) {
            if (isNotVisited(g[last][i], path)) {
                vector<int> newpath(path);
                newpath.push_back(g[last][i]);
                q.push(newpath);
            }
        }
    }

    return store_path;
}

int main() {

    int nodes, edges, connect, temp, source, dest;

    srand(time(0));
    cout <<"Random graph generation: ";

    nodes = 20 + rand() % 9;
    edges = 0;

    vector<vector<int>> path;
    vector<vector<int>> trans(nodes, vector<int>(nodes, 0));

    set<int>::iterator sp;
    vector<int>::iterator it, ls;

//--------------------------------------------------------
//Random Graph Generation


  vector<vector<int>> adj_matrix(nodes, vector<int>(nodes, 0));
  cout << "\nThe graph has " << nodes <<" vertices";

    for(int i=0;i<nodes;i++){
        connect = 0;
        for(int j=i+1;j<nodes;j++){
            adj_matrix.at(i).at(j) = rand() % 2;
            if( adj_matrix.at(i).at(j) == 1) {
                edges++;
                connect++;
            }
        }

        //cout << "debug";
        if((connect == 0) && (nodes-i-1 > 0)){
            temp = i + 1 + (rand() % (nodes-i-1));
            //cout << " temp:" << temp;
            adj_matrix.at(i).at(temp) = 1;
        }
    }

    vector<vector<int>> list;
    list.resize(nodes);
    for(int i=0; i<adj_matrix.size(); i++){
        for (int j=0; j<adj_matrix.at(i).size(); j++){
            if (i == j)
                continue;
            if (adj_matrix.at(i).at(j) == 1){
                list[i].push_back(j);
            }
        }
    }


//--------------------------------------------------------
//File Graph Generation
/*
    fstream ffile;
    ffile.open("map_int.txt");
    string data;

    getline(ffile, data);
    nodes = stoi(data);
    getline(ffile, data);
    edges = stoi(data);

    //vector<vector<int>> adj_matrix(nodes, vector<int>(nodes, 0));
    cout << "\nThe graph has " << nodes <<" vertices";


    vector<vector<int>> list;
    list.resize(nodes);

    while (!ffile.eof()) {
        getline(ffile, data);
        list[(stoi(data.substr(0, data.find(" "))))].push_back(stoi(data.substr(data.find(" ") + 1, data.find(" ") + 1)));
    }
*/
//--------------------------------------------------------
    cout<< " and "<< edges <<" edges." << endl << endl;

    set <int> control;

    for(int i = 0;i < nodes;i++){
        control.insert(i);
    }

    source = 0;
    dest = nodes - 1;
    path = findpaths(list, source, dest, nodes);

    bitset<SIZE> comps;
    long long int comp_size;
    fstream file;
    file.open("result.txt");

    for(int i = 0;i < path.size();i++) {
        set<int> vertices;
        vector<int> result(nodes - path.at(i).size());

        for (int j = 0; j < path.at(i).size(); j++) {
            //cout << path.at(i).at(j) << "\t";
            vertices.insert(path.at(i).at(j));
        }
        //cout << endl;

        ls = set_difference(control.begin(), control.end(), vertices.begin(), vertices.end(), result.begin());

        /*cout << endl << "Debug:set" << endl;

        for (sp = control.begin(); sp != control.end(); ++sp)
            cout << ' ' << *sp;

        cout << endl << "Debug:set" << endl;
        for (sp = vertices.begin(); sp != vertices.end(); ++sp)
            cout << ' ' << *sp;

        cout << endl << "Debug:result" << endl;
        for (it = result.begin(); it != ls; ++it)
            cout << ' ' << *it;
        cout << endl;*/

        //--------------------------------------------------
        comp_size = pow(2, result.size());
        //cout << "Bitset: " << comp_size << " Result:size " << result.size() << endl;

        for (int x = 0; x < comp_size; x++) {
            comps = x;

                for (int j = 0; j < path.at(i).size(); j++) {
                    file << "R" << path.at(i).at(j) << " ";
                }

                for (int y = 0; y < result.size(); y++) {
                    if (comps[y] == 0) {
                        file << "(1-R" << result.at(y) << ") ";
                    } else {
                        file << "R" << result.at(y) << " ";
                    }
                }
                file << " + " << endl;
            }
        //------------------------------------------------------------
    }

    cout << "Finished! Find results in \"result.txt\"." << endl;
    return 0;
}
