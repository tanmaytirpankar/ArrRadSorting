#include <iostream>
#include "RadixSort.h"
#include <fstream>
#include <string>
#include <ctime>
#include <cmath>
#include <chrono>
using namespace std;
int main() {
    unsigned int n;
    int num,buck;
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
//    omp_set_max_active_levels(3);
//    omp_set_nested(1);
    RadixSort<int> *obj=new RadixSort<int>(n,num,buck);
    //obj->printinp();
    //clock_t t1,t2;
    //t1=clock();
    chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
    obj->sorting();
    chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>( t2 - t1 ).count();
    cout <<endl <<"The time taken is "<<duration <<" microseconds"<<endl;
    obj->transfer();

//    chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
//    obj->insertionSort(0,n-1,9);
//    chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
//    auto duration = chrono::duration_cast<chrono::microseconds>( t2 - t1 ).count();
//    cout <<endl <<"The time taken is "<<duration <<" microseconds"<<endl;
//    obj->print();
    //t2=clock();
    //float diff ((float)t2-(float)t1);
    //cout<<diff<<endl;
//    chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
//    int size=100000000;
//    int *arr=new int[size];
//    int stride=100000;
//    for (int i = 0; i < size; i++) {
//        arr[i]=i;
//    }
////    for (int j = 0; j < stride; j++) {
////        for (int i = 0; i < size/stride; i++) {
////            arr[stride*i+j]*=10;
////        }
////    }
//    for (int j = 0; j < size; j++) {
//        arr[j]*=10;
//    }
//    chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
//    auto duration = chrono::duration_cast<chrono::microseconds>( t2 - t1 ).count();
//
//    cout <<endl <<"The time taken is "<<duration <<" microseconds"<<endl;

    return 0;
}