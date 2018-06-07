#include <iostream>
#include "RadixSort.h"
#include <time.h>
#include <fstream>
#include <string>
#include <math.h>
#include <chrono>
using namespace std;
int main() {
    int n,num,buck;
    cout<<"Enter the number of points:";
    cin>>n;
    cout<<"Number of points "<<n<<endl;
    cout<<"Enter the number of threads:";
    cin>>num;
    cout<<"Enter the size of bucketing number";
    cin>>buck;
    /*ofstream fs;
    string filename = "exampleOutput5.csv";
    fs.open(filename);
    for (int counter = 0; counter <  n; counter++)
    {

        fs << (rand()%(2^31)) << "," << (rand()%(2^31)) << "," << (rand()%(2^31)) << endl;
    }
    fs.close();*/
    RadixSort<int> *obj=new RadixSort<int>(n,num,buck);
    //obj->printinp();
    //clock_t t1,t2;
    //t1=clock();
    chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
    obj->sorting();
    chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>( t2 - t1 ).count();

    cout <<endl <<"The time taken is "<<duration <<" microseconds"<<endl;
    //t2=clock();
    //float diff ((float)t2-(float)t1);
    //cout<<diff<<endl;
    return 0;
}