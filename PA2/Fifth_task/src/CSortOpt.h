//
// Created by fantomasm on 10/07/24.
//
#include <iostream>
#include "CInvoice.h"
#ifndef CSORTOPT_H
#define CSORTOPT_H
enum sorting{ BY_DATE_LOW,BY_DATE_HIGH , BY_BUYER_LOW,BY_BUYER_HIGH,BY_SELLER_LOW,BY_SELLER_HIGH ,BY_AMOUNT_LOW,BY_AMOUNT_HIGH, BY_VAT_LOW,BY_VAT_HIGH,DEFAULT };


//---------------------------------------------------------------------------------------------
class CSortOpt
{
public:
    static const int         BY_DATE                       = 0;
    static const int         BY_BUYER                      = 1;
    static const int         BY_SELLER                     = 2;
    static const int         BY_AMOUNT                     = 3;
    static const int         BY_VAT                        = 4;
    inline CSortOpt                      ( void ){};


    CSortOpt               & addKey                        ( int               key,
                                                             bool              ascending = true );


    vector<sorting> Sort_values;
private:
};
#endif //CSORTOPT_H
