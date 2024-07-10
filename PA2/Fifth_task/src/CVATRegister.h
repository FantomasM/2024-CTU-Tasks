//
// Created by fantomasm on 10/07/24.
//

#ifndef CVATREGISTER_H
#define CVATREGISTER_H
#include <iostream>
#include "CCompany.h"
class CVATRegister
{
public:
    inline CVATRegister                  ( void ){}
    bool                     registerCompany               ( const string    & name );
    //basic check if buyer and seller are in register and if they are not the same
    bool sanity_check(const CInvoice  & x) const;
    bool
    addIssued                     ( const CInvoice  & x );

    bool                     addAccepted                   ( const CInvoice  & x );
    bool                     delIssued                     ( const CInvoice  & x );
    bool                     delAccepted                   ( const CInvoice  & x );
    list<CInvoice>           unmatched                     ( const string    & company,
                                                             const CSortOpt  & sortBy ) const;


private:
    unordered_map<string,CCompany> unordered_companies;

    int id=0;
    int obj_value=1;
};
#endif //CVATREGISTER_H
