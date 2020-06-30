#include <iostream>
#include <stdlib.h>
#include <vector>
#include <ctime>
#include <cmath>
#include <bitset>
#include <fstream>
using namespace std;




// A utility function to print a polynomial
void printPoly(vector<int> poly)
{
    cout << "Poly" << endl;
    int n = poly.size();
    for (int i=0; i<n; i++)
    {
        cout << poly[i];
        if (i != 0)
            cout << "x^" << i ;
        if (i != n-1)
            cout << " + ";
    }

    cout << "Poly1" << endl;
}

vector<int> multiply(vector<int> A, vector<int> B, int m, int n)
{
    cout << "Multiply1" << endl;
    vector<int> prod(m+n,0);

    // Initialize the porduct polynomial
    /* for (int i = 0; i<m+n-1; i++) {
         cout << "Multiply1" << endl;
         prod.at(i)=0 ;
     }
     */

    // Multiply two polynomials term by term

    // Take ever term of first polynomial
    for (int i=0; i<m; i++)
    {
        // Multiply the current term of first polynomial
        // with every term of second polynomial.
        for (int j=0; j<n; j++)
            (prod.at(i+j)) += A[i]*B[j];
    }
    //printPoly(prod);
    cout << "Multiply" << endl;
    return prod;
}


int main() {
    int nodes,edges;
    int wrong_counter,correct_counter;
    wrong_counter=correct_counter=0;
    int *prod;

    float lamvda,r,mttf;
    lamvda=2;
    mttf=0;
    int connect,temp;
    edges = 0;
    srand(time(0));
    cout <<"Random graph generation: ";
    //nodes = 25 + rand() % 1;
    //cout << "\nThe graph has " << nodes <<" vertices";
    //Graph Generation
    /*vector<vector<int>> adj_matrix(nodes, vector<int>(nodes, 0));
    vector<vector<int>> trans(nodes, vector<int>(nodes, 0));
    vector<int> result (nodes,0);*/
//--------------------------------------------------------
//Random Graph Generation


     cout <<"Random graph generation: ";
    nodes = 25 + rand() % 1;
    cout << "\nThe graph has " << nodes <<" vertices";
    //Graph Generation
    vector<vector<int>> adj_matrix(nodes, vector<int>(nodes, 0));
    vector<vector<int>> trans(nodes, vector<int>(nodes, 0));
    vector<int> result (nodes,0);

     for(int i=0;i<nodes;i++){
       connect = 0;
       for(int j=i+1;j<nodes;j++){
           adj_matrix.at(i).at(j) = rand() % 2;
           if (adj_matrix.at(i).at(j) != 0){
               adj_matrix.at(i).at(j) = 1;
           }
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
//--------------------------------------------------------
//File Graph Generation
  /*
    fstream ffile;
    //ffile.open("hw2_ex5a.txt");
    ffile.open("hw2_ex5b.txt");
    string data;
    getline(ffile, data);
    nodes = stoi(data);
    getline(ffile, data);
    edges = stoi(data);
    vector<vector<int>> adj_matrix(nodes, vector<int>(nodes, 0));
    vector<vector<int>> trans(nodes, vector<int>(nodes, 0));

    while (!ffile.eof()) {
        getline(ffile, data);
        //cout << stoi(data.substr(0, data.find(" "))) << " " << stoi(data.substr(data.find(" ") + 1, data.find(" ") + 1))
        //<< " " << stoi(data.substr(data.find_last_of(" ") + 1)) << endl;
        adj_matrix.at(stoi(data.substr(0, data.find(" ")))).at(
                stoi(data.substr(data.find(" ") + 1, data.find(" ") + 1))) = stoi(
                data.substr(data.find_last_of(" ") + 1));
    }
    cout << "\nThe graph has " << nodes <<" vertices";
    */
//--------------------------------------------------------
    cout<< " and "<< edges <<" edges." << endl << endl;
    for(int i=0;i<nodes;i++) {
        for (int j = 0; j < nodes; j++) {
            cout << adj_matrix.at(i).at(j) << "\t";
        }
        cout << endl;
    }
    cout << endl << endl;
    //cout<< " --------------- " << endl;
    bitset<50> comps;
    vector<int> works;
    long long int comp_size = pow(2,nodes);

    clock_t tStart = clock();
    cout << "Bitset: " << comp_size << endl;

    ofstream outfile;
    outfile.open("result.txt");

    for(int x = 0; x < comp_size; x++){
        comps = x;
        //cout << "debug" << endl;
        for(int i=0;i<nodes;i++) {
            for (int j = 0; j < nodes; j++) {
                trans.at(i).at(j) = adj_matrix.at(i).at(j);
            }
        }
        //cout << "Bitset: " << comps << endl;
        for(int y = 0; y < nodes; y++){
            if(comps[y] == 0) {
                for(int z = 0;z < nodes;z++){
                    trans.at(y).at(z) = 0;
                    trans.at(z).at(y) = 0;
                }
            }
        }
        for (int k = 0; k < nodes; k++) {
            for (int i = 0; i < nodes; i++) {
                for (int j = 0; j < nodes; j++) {
                    trans.at(i).at(j) = (trans.at(i).at(j) || (trans.at(i).at(k) && trans.at(k).at(j)));
                }
            }
        }
        vector<int> result (nodes+1,0);
        if(trans.at(0).at(nodes-1) == 1){
            //cout << "--------" << endl;
            result.at(0)=1;
            for(int y = 1; y < nodes-1; y++){
                if(comps[y] == 0) {
                    vector<int> tempa(2);
                    tempa.at(0)=1;
                    tempa.at(1)=-1;
                    cout << "Nodes " << nodes << endl;
                    result = (multiply(tempa,result,2,nodes+1));
                    //cout<< "Pao stin poly" << endl;
                    //printPoly(result);
                    //cout << "Exit Poly" << endl;
                    //cout << "(1-R" << y << ") ";
                    outfile << "(1-R" << y << ") ";
                    wrong_counter++;
                }
                else{
                    //cout << "R" << y << " ";
                    outfile << "R" << y << " ";
                    correct_counter++;
                }
            }
            vector<int> tempb(correct_counter+1,0);
            tempb.at(correct_counter)=1;
            result=multiply(tempb,result,correct_counter+1,nodes);
            printPoly(result);
            //cout << " + " << endl;
            outfile << " + " << endl;
            outfile << "Wrong: " << wrong_counter << endl;
            outfile << "Correct: " << correct_counter << endl;
            cout << "Size " << result.size() << endl;
            for (int pol=1;pol<result.size();pol++){
                if (result.at(pol) != 0 ){
                    mttf= mttf + (float) result.at(pol) * ((float)1 / pol);
                }
            }
            mttf = mttf + result.at(0);
            //cout << "Comp: " << x << " works." << endl;
            works.push_back(x);
            wrong_counter = 0;
            correct_counter=0;
        }
    }

    outfile << mttf << "*1/LAMBDA" << endl;
    cout << mttf << "*1/LAMBDA" << endl;
    outfile << mttf*((float)1/lamvda) << endl;
    cout << mttf*((float)1/lamvda) << endl;
    printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0;
    /*for(int i=0;i<nodes;i++){
       connect = 0;
       for(int j=i+1;j<nodes;j++){
           adj_matrix.at(i).at(j) = rand() % 2;
           if( adj_matrix.at(i).at(j) == 1) {
               edges++;
               connect++;
               }
           }
       cout << "debug";
       if((connect == 0) && (nodes-i-1 > 0)){
           temp = i + 1 + (rand() % (nodes-i-1));
           cout << " temp:" << temp;
           adj_matrix.at(i).at(temp) = 1;
       }
   }*/

    /*for(int i = 0;i < works.size();i++){
        cout << works.at(i) << "\t";
    }*/
    /*for (i = 0; i < av_items; i++){
        cout << name[i] << "\t" << weight[i] << "\t" << value[i] << endl;
    }*/
    /*for(int i = 0; i < comp_size; i++){
        b_index = i;
        for(int j = 0; j < av_items; j++){
            if(b_index[j] == 1) {
            }
        }
    }*/
    /* for (int k = 0; k < nodes; k++) {
         for (int i = 0; i < nodes; i++) {
             for (int j = 0; j < nodes; j++) {
                 trans.at(i).at(j) = (trans.at(i).at(j) || (trans.at(i).at(k) && trans.at(k).at(j)));
             }
         }
     }
     for(int i=0;i<nodes;i++) {
         for (int j = 0; j < nodes; j++) {
             cout << trans.at(i).at(j) << "\t";
         }
         cout << endl;
     }*/

}