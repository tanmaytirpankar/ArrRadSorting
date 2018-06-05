//
// Created by tanmay on 29/5/18.
//

#ifndef UNTITLED_POINTS_H
#define UNTITLED_POINTS_H


//
// Created by tanmay on 29/5/18.
//
template <class T>
class Points{
    T x,y,z;
public:
    Points()
    {
        this->x=0;
        this->y=0;
        this->z=0;
    }
    Points(T x,T y, T z)
    {
        this->x=x;
        this->y=y;
        this->z=z;
    }
    T getX()
    {
        return x;
    }
    T getY()
    {
        return y;
    }
    T getZ()
    {
        return z;
    }
};


#endif //UNTITLED_POINTS_H
