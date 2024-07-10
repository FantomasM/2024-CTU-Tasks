//
// Created by fantomasm on 10/07/24.
//
#include "CMail.h"
#include <iostream>




  bool                     CMail::operator ==                   ( const CMail     & x ) const{
    if(Source==x.Source &&  Destination==x.Destination && Body==x.Body){

        return true;
    }
    return false;
}
CMail  CMail::reverse(const CMail & y){
    CMail newcmail=y;
    str tmp=y.Source;
    newcmail.Source=Destination;
    newcmail.Destination=tmp;
    return newcmail;
}
std::ostream         & operator <<                   ( ostream         & os,
                                                          const CMail     & m ){

    os << "From: " << m.Source << ", To: " << m.Destination << ", Body: " << m.Body;
    return os;
}

bool CMail::from_comparsion(const str & from2) const{
    if(from2==Source){
        return true;
    }
    return false;
}
bool CMail::to_comparsion(const str & from2) const{
    if(from2==Destination){
        return true;
    }
    return false;
}

CMail & CMail::operator=(const CMail & other){
    if(this==&other){
        return *this;
    }
    Source=other.Source;
    Destination=other.Destination;
    Body=other.Body;
    return *this;
}
