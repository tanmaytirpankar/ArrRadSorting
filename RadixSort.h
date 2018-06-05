//
// Created by tanmay on 29/5/18.
//

#ifndef UNTITLED_RADIXSORT_H
#define UNTITLED_RADIXSORT_H
//
// Created by tanmay on 29/5/18.
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
        omp_set_num_threads(num_threads);
#pragma omp parallel for
        for (int i = 0; i < n; i++) {
            arr[i]=Points<T>(rand()%10,rand()%10,rand()%10);
        }
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
        if(num_elements<=1 || level<1)
        {
            return ;
        }
        int count[8],position[8],position1[8];
        vector<Points<T>> temp(num_elements);
        omp_set_num_threads(num_threads);
#pragma omp parallel for
        for (int j = 0; j < 8; j++) {
            count[j]=position[j]=0;
        }
        omp_set_num_threads(num_threads);
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
            #pragma omp critical
            count[x+y+z]++;
        }
        position[0]=position1[0]=first;
        for (int k = 1; k < 8; k++) {
            position[k]=position[k-1]+count[k-1];
            position1[k]=position[k];
        }
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
            arr[position[x+y+z]]=temp[i];
            position[x+y+z]++;
        }
        temp.clear();
        temp.shrink_to_fit();
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
        print();
    }
    /*void sorting()
    {
        vector<Points<T>> sortedarr;
        T unsortedarr[n];
        int lvls= sizeof(arr->getX())*8;

        for (int i = 0; i < this->n; i++)
        {
            unsortedarr[i]=arr[i];
        }
        sortedarr=Sort(unsortedarr, 0,n-1,lvls);
        for (int i=0;i<n;i++)
        {
            cout<<"("<<arr[i].getX()<<","<<arr[i].getY()<<","<<arr[i].getZ()<<"),";
        }
    }*/
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