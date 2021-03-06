//
// Created by tanmay on 29/5/18.
//

#ifndef UNTITLED_RADIXSORT_H
#define UNTITLED_RADIXSORT_H
//
// Created by tanmay tirpankar on 29/5/18.
//

#include "Points.h"
#include <vector>
#include <iostream>
#include <omp.h>
#include <time.h>
#include <fstream>
#include <string>
#include <chrono>
using namespace std;
template <class T>
class RadixSort{
    vector <Points<T>> arr;
    int num_threads;
    int n;
public:
    RadixSort(int n,int num)
    {
        this->n=n;
        this->num_threads=num;
        unsigned int x,y,z;
        /*ifstream in;
        string line;
        string filename = "exampleOutput5.csv";
        in.open(filename);
        arr=vector<Points<T>>(n);
        for (int i = 0; i < n; i++) {
            getline( in, line,',');
            x=stoi(line);
            getline( in, line,',');
            y=stoi(line);
            getline( in, line,'\n');
            z=stoi(line);
            arr[i]=Points<T>(x,y,z);
        }
        in.close();*/
        arr=vector<Points<T>>(n);
        srand(2);
        omp_set_num_threads(num_threads);
#pragma omp parallel for
        for (int i = 0; i < n; i++) {
            arr[i]=Points<T>(rand()%10,rand()%10,rand()%10);
        }
        //print();
        cout<<endl;
        /*cout<<"Enter Points";
        arr=new Points<T>[n];
        for (int i = 0; i < n; i++) {
            unsigned int x,y,z;
            cin>>x>>y>>z;
            arr[i]=Points<T>(x,y,z);
        }*/
    }

    void print()
    {
        for (int i = 0; i < this->n; i++)
        {
            cout<<"("<<arr[i].getX()<<","<<arr[i].getY()<<","<<arr[i].getZ()<<"),";
        }
    }
    void Sort(int first,int last, int level)
    {
        int num_elements=last-first+1;
        vector<vector<int>> count(num_threads);
        vector<vector<int>> position(num_threads);
        for (int l = 0; l < num_threads; ++l) {
            count[l] = vector<int>(8);
            position[l]=vector<int>(8);
        }
        if(num_elements<=1 || level<1)
        {
            return ;
        }
        int position1[8];
        vector<Points<T>> temp(num_elements);
        chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
        omp_set_num_threads(num_threads);
#pragma omp parallel for
        for (int j = 0; j < 8; j++) {
            position1[j]=0;
            count[omp_get_thread_num()][j]=0;
            position[omp_get_thread_num()][j]=0;
        }
        chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>( t2 - t1 ).count();

        //cout <<endl <<"The time taken for initialization is "<<duration <<" microseconds"<<endl;

        t1 = chrono::high_resolution_clock::now();
        omp_set_num_threads(num_threads);
//        cout<<"first: "<<first<<" last: "<<last<<" sizeof(count): "<<count.size()<<" sizeof(count[0])"<<count[0].size()<<endl;
#pragma omp parallel for
        for (int i = first; i <= last; i++)
        {
            temp[i-first]=arr[i];
            T x=arr[i].getX();
            T y=arr[i].getY();
            T z=arr[i].getZ();
            x=x>>(level-1);
            y=y>>(level-1);
            z=z>>(level-1);
            x=x&1;
            y=y&1;
            z=z&1;
            y=y<<1;
            x=x<<2;
            count[omp_get_thread_num()][x+y+z]++;
        }
        t2 = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::microseconds>( t2 - t1 ).count();

        //cout <<endl <<"The time taken for calculating counts is "<<duration <<" microseconds"<<endl;
//        t1 = chrono::high_resolution_clock::now();
//        cout<<"Values in count:"<<endl;
//        for(int i = 0; i < num_threads; i++){
//            for(int j = 0; j < 8; j++){
//                cout<<count[i][j]<<" ";
//            }
//            cout<<endl;
//        }
        t1 = chrono::high_resolution_clock::now();
//        position[0][0]=position1[0]=first;
//        int prev_buc=0;
//        for (int buc = 0; buc < 8; buc++) {
//            for (int tid = 0; tid < num_threads; tid++) {
//                if (tid==0)
//                    position1[buc+1]=position[tid][buc]=prev_buc;
//                else
//                    position[tid][buc]=position[tid-1][buc]+count[tid-1][buc];
//            }
//            prev_buc=position[num_threads-1][buc]+count[num_threads-1][buc];
//        }

        position[0][0]=position1[0]=first;
        for (int buc = 0; buc < 8; buc++) {
            for (int tid = 1; tid < num_threads; tid++) {
                if(tid==0&&buc==0)
                {}
                else
                {
                    position[tid][buc]=position[tid-1][buc]+count[tid-1][buc];
                }
            }
            if(buc<7)
            position1[buc+1]=position[0][buc+1]=position[num_threads-1][buc]+count[num_threads-1][buc];
        }

//        cout<<"Positions in position at depth "<<level<<" is:"<<endl;
//        for(int i = 0; i < num_threads; i++){
//            for(int j = 0; j < 8; j++){
//                cout<<position[i][j]<<" ";
//            }
//            cout<<endl;
//        }
        omp_set_num_threads(num_threads);
#pragma omp parallel for
        for (int i = 0; i < num_elements; i++) {
            T x = temp[i].getX();
            T y = temp[i].getY();
            T z = temp[i].getZ();
            x = x >> (level - 1);
            y = y >> (level - 1);
            z = z >> (level - 1);
            x = x & 1;
            y = y & 1;
            z = z & 1;
            y = y << 1;
            x = x << 2;
            arr[position[omp_get_thread_num()][x+y+z]]=temp[i];
            position[omp_get_thread_num()][x+y+z]++;
        }
        temp.clear();
        temp.shrink_to_fit();
        t2 = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::microseconds>( t2 - t1 ).count();

        //cout <<endl <<"The time taken for final sorting is "<<duration <<" microseconds"<<endl;

        //cout<<"Recursion number "<<level<<endl;

        omp_set_num_threads(num_threads);
#pragma omp parallel for
        for (int i = 0; i < 8; i++)  {
            int begin=position1[i];
            int ending;
            if(i!=7)
                ending=position1[i+1]-1;
            else
                ending=last;
            Sort(begin,ending,level-1);
        }
    }
    void sorting()
    {
        int lvls=sizeof(arr[0].getX())*8;
        vector<Points<T>> arr1(n);
        Sort(0,n-1,lvls);
        //print();
    }
};

#endif //UNTITLED_RADIXSORT_H

/*
 * Algorithm Sort(pointslist,start,end,level)
 * base case: If number of elements in pointslist (end-start+1) is less than or equal to 1,
 *            If  level<=1
 *                  return .point
 *maintain a count array for number of elements in different buckets (8 buckets here) and initialize them to 0
 * for each element in pointslist
 *        Copy element into a temporary array of size = number of elements in pointslist/bucket
 *        Right shift x,y,z by level-1
 *        x,y,z&1
 *        y<<1
 *        z<<2
 *        bucketnum=x+y+z
 *        Increment count of corresponding bucket by 1.
 * Create a position list by accumulatively adding counts in count array
 * Maintain a copy of this position array which will be used later for passing the start and end positions to next iteration
 * for each element in templist
 *        Right shift x,y,z by level-1
 *        x,y,z&1
 *        y<<1
 *        z<<2
 *        bucketnum=x+y+z
 *        Place this element at positionlist[position[bucketnum]]
 *        Increment the position value of the bucket by 1.
 * for each i=0 to 7 do
 *        start=position[i]
 *        end=position[i+1]-1
 *        Sort(pointslist, start,end,level-1)
 *
 */