//
// Created by fantomasm on 09/07/24.
//
#include "CRange.h"
CRange::CRange(long long first, long long second){
    interval inter;
    inter.first=first;
    inter.second=second;
    if(second < first){

        throw logic_error("Wrong input, last value is less than first");
    }
    else{
        Interval= make_pair(first,second);
    }
}
CRange::CRange(long long first){




    Interval= make_pair(first,first);

}
CRange & CRange::operator = ( const CRange & second)  {
    this->Interval.first=second.Interval.first;
    this->Interval.second=second.Interval.second;
    return *this;
}