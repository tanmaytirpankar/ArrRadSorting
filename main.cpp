#include <iostream>
#include "RadixSort.h"
#include <fstream>
#include <string>
#include <ctime>
#include <cmath>
#include <chrono>
#include <getopt.h>
using namespace std;
int main(int argc, char **argv) {
    unsigned int n;
    int num,user_word_size,max_levels;
    int c;
    //Loop used to assign parameters based on parameter name. Used for python scripts.
    while ((c = getopt (argc, argv, "p:t:w:l:")) != -1)
        switch (c)
        {
            case 'p':
                n = atoi(optarg);
                break;
            case 't':
                num = atoi(optarg);
                break;
            case 'w':
                user_word_size = atoi(optarg);
                break;
            case 'l':
                max_levels = atoi(optarg);
                break;
            default:
                abort ();
        }
    cout<<"Number of points "<< n << " Number of threads " <<num<< " Word size " <<user_word_size<< " Levels "<<max_levels<<endl;
    /*ofstream fs;
    string filename = "exampleOutput5.csv";
    fs.open(filename);
    for (int counter = 0; counter <  n; counter++)
    {

        fs << (rand()%(2^31)) << "," << (rand()%(2^31)) << "," << (rand()%(2^31)) << endl;
    }
    fs.close();*/
//    omp_set_max_active_levels(3);
//    cout<<omp_get_thread_limit()<<endl;

    omp_set_max_active_levels(max_levels);
    omp_set_nested(1);

    RadixSort<unsigned long > *obj=new RadixSort<unsigned long>(n,num,user_word_size);
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