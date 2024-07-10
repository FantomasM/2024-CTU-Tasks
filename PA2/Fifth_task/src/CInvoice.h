//
// Created by fantomasm on 10/07/24.
//

#ifndef CINVOICE_H
#define CINVOICE_H
#include <iostream>
#include "CDate.h"

class CInvoice
{
public:
    inline CInvoice                      ( const CDate     & date,
                                    const string    & seller,
                                    const string    & buyer,
                                    unsigned int      amount,
                                    double            vat ) : Buyer(buyer),Seller(seller),date_of_invoice(date),Amount(amount),Vat(vat){
        char delimiter[5]="---/";
        //making string of all data for faster comparing
        string_to_comparison= Seller+delimiter+ Buyer+delimiter+ to_string(date_of_invoice.day())+delimiter+
                    to_string(date_of_invoice.month())+delimiter+ to_string(date_of_invoice.year())+
                    delimiter+ to_string(Amount)+delimiter+ to_string(Vat);
        //changing name of buyer and seller to canonical (all words separated by one space(plus space in the end) and all letters changed to lower)
        Canonical_Buyer= change_to_canonical(Buyer);
        Canonical_Seller= change_to_canonical(Seller);
        Number=0;
    }
    inline CInvoice                      ( const CDate     & date,
                                    const string    & seller,
                                    const string    & buyer,
                                    unsigned int      amount,
                                    double            vat ,
                                    bool Issue,
                                    bool Accept,
                                    unsigned int number) : issue(Issue),accept(Accept),Buyer(buyer),Seller(seller),Number(number),date_of_invoice(date),Amount(amount),Vat(vat){
        char delimiter[5]="---/";
        //making string of all data for faster comparing
        string_to_comparison= Seller+delimiter+ Buyer+delimiter+ to_string(date_of_invoice.day())+delimiter+
                              to_string(date_of_invoice.month())+delimiter+ to_string(date_of_invoice.year())+
                              delimiter+ to_string(Amount)+delimiter+ to_string(Vat);
        //changing name of buyer and seller to canonical (all words separated by one space(plus space in the end) and all letters changed to lower)
        Canonical_Buyer= change_to_canonical(Buyer);
        Canonical_Seller= change_to_canonical(Seller);
        //Number=0;
    }
    CDate                    date                          ( void ) const;
    string                   buyer                         ( void ) const;
    string                   seller                        ( void ) const;
    unsigned int             amount                        ( void ) const;
    double                   vat                           ( void ) const;
    unsigned int number(void) const;
    bool operator !=(const CInvoice & second) const;
    string canonical_Buyer(void ) const;
    string canonical_Seller(void ) const;

    string string_to_comparison;

    bool issue= false;
    bool accept= false;
    string Buyer;
    string Seller;
    int Number;
private:
    CDate date_of_invoice;
    string Canonical_Buyer;
    string Canonical_Seller;
    unsigned int Amount;
    double Vat;

};


string key_create(const CInvoice & x);
#endif //CINVOICE_H
