//
// Created by fantomasm on 10/07/24.
//

#ifndef CMAIL_H
#define CMAIL_H
#include "str.h"
#include <iostream>


class CMail
{
public:
    inline CMail(){


    };
    inline CMail                         ( const char      * from,
                                    const char      * to,
                                    const char      * body ) : Source(from) , Destination(to), Body(body){}
    bool                     operator ==                   ( const CMail     & x ) const;
    CMail  reverse(const CMail & y);
    friend std::ostream         & operator <<                   ( ostream         & os,
                                                              const CMail     & m );

    bool from_comparsion(const str & from2) const;
    bool to_comparsion(const str & from2) const;
    inline CMail(const CMail & other) : Source(other.Source) , Destination(other.Destination),Body(other.Body){};
    CMail & operator=(const CMail & other);

    str Source;
    str Destination;
    str Body;
private:

};
#endif //CMAIL_H
