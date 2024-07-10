//
// Created by fantomasm on 10/07/24.
//
#include "CMailIterator.h"
               CMailIterator::operator bool                 ( void ) const{


    if (index<=base.count_of_members() && ok== true && base.size()!= 0){
        return true;
    }
    return false;


}
bool                     CMailIterator::operator !                    ( void ) const{


    if(  base.size()==0 || index > base.count_of_members()) {
        return true;
    }

    return false;

}
const CMail            & CMailIterator::operator *                    ( void ) const{
    return base[index];
}
CMailIterator          & CMailIterator::operator ++                   ( void ){

    index++;

    return *this;

}