//
// Created by fantomasm on 10/07/24.
//

#ifndef CMAILSERVER_H
#define CMAILSERVER_H
#include <iostream>
#include "Client.h"
class CMailServer
{
  public:
                             CMailServer                   ( void );
                             CMailServer                   ( const CMailServer & src );
    CMailServer            & operator =                    ( const CMailServer & src );
                             ~CMailServer                  ( void );
    void                     sendMail                      ( const CMail     & m );
    CMailIterator            outbox                        ( const char      * email ) const ;

    CMailIterator            inbox                         ( const char      * email ) const;
    void Print();

    vector<Client> base;
  private:


};

size_t Lower_bound(const vector<Client> & base, str array);
#endif //CMAILSERVER_H
