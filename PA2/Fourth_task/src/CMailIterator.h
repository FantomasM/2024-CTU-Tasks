//
// Created by fantomasm on 10/07/24.
//

#ifndef CMAILITERATOR_H
#define CMAILITERATOR_H
#include <iostream>
#include "vector.h"
#include "CMail.h"




class CMailIterator
{


public:
    explicit                 operator bool                 ( void ) const;
    bool                     operator !                    ( void ) const;
    const CMail            & operator *                    ( void ) const;
    CMailIterator          & operator ++                   ( void );
    inline CMailIterator(vector<CMail>& vec) : base(vec){

    }
    inline CMailIterator() : ok(false),index(0){}

    vector<CMail> base;

    bool ok= true;
private:


    size_t index=0;


};
#endif //CMAILITERATOR_H
