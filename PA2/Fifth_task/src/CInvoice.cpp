//
// Created by fantomasm on 10/07/24.
//

#include "CInvoice.h"

CDate                    CInvoice::date                          ( void ) const{
    return date_of_invoice;
}
string                   CInvoice::buyer                         ( void ) const{
    return Buyer;
}
string                   CInvoice::seller                        ( void ) const{
    return Seller;
}
unsigned int             CInvoice::amount                        ( void ) const{
    return Amount;
}
double                   CInvoice::vat                           ( void ) const{
    return Vat;
}
unsigned int CInvoice::number(void) const{
    return Number;
}
bool CInvoice::operator !=(const CInvoice & second) const{
    if(string_to_comparison!=second.string_to_comparison ){

        return false;
    }
    return true;
}
string CInvoice::canonical_Buyer(void ) const{
    return Canonical_Buyer;
}
string CInvoice::canonical_Seller(void ) const{
    return Canonical_Seller;
}
//creating key with using canonical name and delimiter to separate data
string key_create(const CInvoice & x) {
    char delimiter[5]="---/";

    string key= change_to_canonical(x.seller())+delimiter+ change_to_canonical(x.buyer())+delimiter+ to_string(x.date().day())+delimiter+
                to_string(x.date().month())+delimiter+ to_string(x.date().year())+
                delimiter+ to_string(x.amount())+delimiter+ to_string(x.vat());
    return key;
}