//
// Created by fantomasm on 10/07/24.
//

#include "CSortOpt.h"


CSortOpt               & CSortOpt::addKey                        ( int               key,
                                                             bool              ascending ) {
    sorting sorts;
    switch(key){
        case 0:
            if(ascending) {
                sorts = sorting::BY_DATE_HIGH;
            }
            else{
                sorts = sorting::BY_DATE_LOW;

            }
        break;
        case 1:
            if(ascending) {
                sorts = sorting::BY_BUYER_HIGH;
            }
            else{
                sorts = sorting::BY_BUYER_LOW;
            }
        break;
        case 2:
            if(ascending) {
                sorts = sorting::BY_SELLER_HIGH;
            }
            else{
                sorts = sorting::BY_SELLER_LOW;
            }
        break;
        case 3:
            if(ascending) {
                sorts = sorting::BY_AMOUNT_HIGH;
            }
            else{
                sorts = sorting::BY_AMOUNT_LOW;
            }

        break;
        case 4:
            if(ascending) {
                sorts = sorting::BY_VAT_HIGH;
            }
            else{
                sorts = sorting::BY_VAT_LOW;
            }
        break;
        default:
            sorts=DEFAULT;
        break;

    }
    //collecting sorting orders in vector
    Sort_values.push_back(sorts);
    return *this;
}