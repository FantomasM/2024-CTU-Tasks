//
// Created by fantomasm on 13.4.23.
//
#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <set>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <iterator>
#include <functional>
using namespace std;

class CDate
{
public:
    //---------------------------------------------------------------------------------------------
    CDate                         ( int               y,
                                    int               m,
                                    int               d )
            : m_Year ( y ),
              m_Month ( m ),
              m_Day ( d )
    {
    }
    //---------------------------------------------------------------------------------------------
    int                      compare                       ( const CDate     & x ) const
    {
        if ( m_Year != x . m_Year )
            return m_Year - x . m_Year;
        if ( m_Month != x . m_Month )
            return m_Month - x . m_Month;
        return m_Day - x . m_Day;
    }
    //---------------------------------------------------------------------------------------------
    int                      year                          ( void ) const
    {
        return m_Year;
    }
    //---------------------------------------------------------------------------------------------
    int                      month                         ( void ) const
    {
        return m_Month;
    }
    //---------------------------------------------------------------------------------------------
    int                      day                           ( void ) const
    {
        return m_Day;
    }
    //---------------------------------------------------------------------------------------------
    friend ostream         & operator <<                   ( ostream         & os,
                                                             const CDate     & x )
    {
        char oldFill = os . fill ();
        return os << setfill ( '0' ) << setw ( 4 ) << x . m_Year << "-"
                  << setw ( 2 ) << static_cast<int> ( x . m_Month ) << "-"
                  << setw ( 2 ) << static_cast<int> ( x . m_Day )
                  << setfill ( oldFill );
    }
    //---------------------------------------------------------------------------------------------
private:
    int16_t                  m_Year;
    int8_t                   m_Month;
    int8_t                   m_Day;
};
#endif /* __PROGTEST__ */
string change_to_canonical(string name);
bool operator < (const CDate & x, const CDate &y) {
    if(x.compare(y) > 0){
        return false;
    }
    else{
        return true;
    }
}
bool operator > (const CDate & x, const CDate &y){
    if(y.compare(x) > 0){
        return false;
    }
    else{
        return true;
    }
}
//---------------------------------------------------------------------------------------------
class CInvoice
{
public:
    CInvoice                      ( const CDate     & date,
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
    CInvoice                      ( const CDate     & date,
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
    CDate                    date                          ( void ) const{
        return date_of_invoice;
    }
    string                   buyer                         ( void ) const{
        return Buyer;
    }
    string                   seller                        ( void ) const{
        return Seller;
    }
    unsigned int             amount                        ( void ) const{
        return Amount;
    }
    double                   vat                           ( void ) const{
        return Vat;
    }
    unsigned int number(void) const{
        return Number;
    }
    bool operator !=(const CInvoice & second) const{
        if(string_to_comparison!=second.string_to_comparison ){

            return false;
        }
        return true;
    }
    string canonical_Buyer(void ) const{
        return Canonical_Buyer;
    }
    string canonical_Seller(void ) const{
        return Canonical_Seller;
    }

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
    CSortOpt                      ( void ){};


    CSortOpt               & addKey                        ( int               key,
                                                             bool              ascending = true ) {
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


    vector<sorting> Sort_values;
private:
};

//---------------------------------------------------------------------------------------------
struct CompareInvoice {
public:
    CompareInvoice (const CSortOpt& sortBy) : Sort_values(sortBy) {}

    bool operator () (const CInvoice& first, const CInvoice& second) {
        for (const auto &x: Sort_values.Sort_values) {
            switch (x) {
                case sorting::BY_DATE_HIGH:
                    //comparing by date if ascending is true

                    if (first.date().compare(second.date()) < 0) {
                        return true;
                    }


                        //if comparison says that values are equal, then go to next compare function/alternative compare function
                        if (first.date().compare(second.date()) == 0) {
                            continue;
                        }

                        break;
                        case sorting::BY_DATE_LOW:
                            //comparing by date in inverted order
                            if (second.date().compare(first.date()) < 0) {
                                return true;
                            }
                        if (first.date().compare(second.date()) == 0) {
                            continue;
                        }
                        break;
                        case sorting::BY_BUYER_HIGH: {
                            //copying names of buyers to strings and change them to lower because we sort case-insensitive
                            string first_buyer = first.buyer();
                            string second_buyer = second.buyer();
                            transform(first_buyer.begin(), first_buyer.end(), first_buyer.begin(), ::tolower);
                            transform(second_buyer.begin(), second_buyer.end(), second_buyer.begin(), ::tolower);
                            //comparing by buyer name if ascending is true

                            if (first_buyer < second_buyer) {
                                return true;
                            }
                            if (first_buyer == second_buyer) {
                                continue;
                            }


                            break;
                        }
                        case sorting::BY_BUYER_LOW: {
                            //copying names of buyers to strings and change them to lower because we sort case-insensitive
                            string first_buyer = first.buyer();
                            string second_buyer = second.buyer();
                            transform(first_buyer.begin(), first_buyer.end(), first_buyer.begin(), ::tolower);
                            transform(second_buyer.begin(), second_buyer.end(), second_buyer.begin(), ::tolower);
                            //comparing by buyer name in inverted order

                            if (first_buyer > second_buyer) {
                                return true;
                            }


                            if (first_buyer == second_buyer) {
                                continue;
                            }


                            break;
                        }
                        case sorting::BY_SELLER_HIGH: {
                            //copying names of sellers to strings and change them to lower because we sort case-insensitive
                            string first_seller = first.seller();
                            string second_seller = second.seller();
                            transform(first_seller.begin(), first_seller.end(), first_seller.begin(), ::tolower);
                            transform(second_seller.begin(), second_seller.end(), second_seller.begin(), ::tolower);
                            //comparing by seller name if ascending is true

                            if (first_seller < second_seller) {
                                return true;
                            }


                            if (first_seller == second_seller) {
                                continue;
                            }


                            break;
                        }
                        case sorting::BY_SELLER_LOW: {
                            //copying names of sellers to strings and change them to lower because we sort case-insensitive
                            string first_seller = first.seller();
                            string second_seller = second.seller();
                            transform(first_seller.begin(), first_seller.end(), first_seller.begin(), ::tolower);
                            transform(second_seller.begin(), second_seller.end(), second_seller.begin(), ::tolower);
                            //comparing by seller in inverted order
                            if (first_seller > second_seller) {
                                return true;
                            }


                            if (first_seller == second_seller) {
                                continue;
                            }


                            break;
                        }
                        case sorting::BY_AMOUNT_HIGH:
                            //comparing by amount, if ascending is true

                            if (first.amount() < second.amount()) {
                                return true;
                            }


                        if (first.amount() == second.amount()) {
                            continue;
                        }

                        break;
                        case sorting::BY_AMOUNT_LOW:
                            //comparing by amount in inverted order
                            if (first.amount() > second.amount()) {
                                return true;
                            }
                        if (first.amount() == second.amount()) {
                            continue;
                        }
                        break;
                        case sorting::BY_VAT_HIGH:
                            //comparing by vat if ascending is true

                            if (first.vat() < second.vat()) {
                                return true;
                            }


                        if (first.vat() == second.vat()) {
                            continue;
                        }

                        break;
                        case sorting::BY_VAT_LOW:
                            //comparing by vat in inverted order

                            if (first.vat() > second.vat()) {
                                return true;
                            }


                        if (first.vat() == second.vat()) {
                            continue;
                        }

                        break;
                        case sorting::DEFAULT:
                            //wrong value, no sorting :(
                            break;
                    }

                    return false;
            }

            return first.number() < second.number();
        }

private:
    CSortOpt Sort_values;

};

//---------------------------------------------------------------------------------------------
class CCompany{
public:
    CCompany(const string & name){
        real_name=name;
        canonical_name= change_to_canonical(name);

    }
    string real_name;
    string canonical_name;
    int count_of_paired_invoices=0;
    int count_of_unpaired_invoices=0;
    int obj_value_issued=1;
    void pair_invoices(){
        count_of_paired_invoices++;
        count_of_unpaired_invoices--;
    }
    void unpair_invoices(){
        count_of_paired_invoices--;
        count_of_unpaired_invoices++;
    }

    unordered_map<string ,CInvoice> CInvoices;
private:

};
//---------------------------------------------------------------------------------------------




//creating canonical name by changing all leters to lower and then separating words by one space and also one space will be in the end
//For example canonical name for "CaT GarFielD" will be "cat garfield "
string change_to_canonical( string  old){
    std::transform(old.begin(),old.end(),old.begin(),[](unsigned char c){return std::tolower(c);});
    istringstream iss(old);
    vector<string> words;
    copy(istream_iterator<string> (iss),istream_iterator<string>(), back_inserter(words));
    ostringstream oss;
    copy(words.begin(),words.end(), ostream_iterator<string>(oss," "));


    return oss.str();
}

//creating key with using canonical name and delimiter to separate data
string key_create(const CInvoice & x) {
    char delimiter[5]="---/";

    string key= change_to_canonical(x.seller())+delimiter+ change_to_canonical(x.buyer())+delimiter+ to_string(x.date().day())+delimiter+
                to_string(x.date().month())+delimiter+ to_string(x.date().year())+
                delimiter+ to_string(x.amount())+delimiter+ to_string(x.vat());
    return key;
}

//---------------------------------------------------------------------------------------------
class CVATRegister
{
public:
    CVATRegister                  ( void ){}
    bool                     registerCompany               ( const string    & name ){

        string canonical_name=(change_to_canonical(name));
        //if there is no client with same key, then insert new client, key is his canonical name(words separated by one space between and one space in the end of string)
        if(unordered_companies.count(canonical_name)==0){
            unordered_companies.insert({canonical_name,CCompany(name)});
            return true;
        }
        return false;



    }
    //basic check if buyer and seller are in register and if they are not the same
    bool sanity_check(const CInvoice  & x) const{
        if(unordered_companies.count(x.canonical_Buyer())==0 || unordered_companies.count(x.canonical_Seller())==0 ||
           x.canonical_Buyer()== x.canonical_Seller()){
            return false;
        }
        return true;
    }
    bool
    addIssued                     ( const CInvoice  & x ){
        //check if buyer and seller are in register and buyer and seller are not the same(comparing by canonical name)
        if(!sanity_check(x)){
            return false;
        }
        //creating unique key of canonic buyer's name and canonic seller's name and by converting other data to string
        string key=key_create(x);

        //creating some short expressions for seller and buyer invoices
        auto &my_invoices_seller = unordered_companies.at(x.canonical_Seller()).CInvoices;
        auto &myinvoices_buyer = unordered_companies.at(x.canonical_Buyer()).CInvoices;
        //if cant find same invoice, then add it to seller invoices and to buyer invoices with signs that it is issued invoice
        if(my_invoices_seller.count(key)==0) {
           my_invoices_seller.insert({key, CInvoice(x.date(),x.Seller,x.Buyer,x.amount(),x.vat(), true, false,++id)});
           myinvoices_buyer.insert({key, CInvoice(x.date(),x.Seller,x.Buyer,x.amount(),x.vat(), true, false,id)});
            my_invoices_seller.at(key).Seller=unordered_companies.at(x.canonical_Seller()).real_name;
            myinvoices_buyer.at(key).Seller=unordered_companies.at(x.canonical_Seller()).real_name;
            my_invoices_seller.at(key).Buyer=unordered_companies.at(x.canonical_Buyer()).real_name;
            myinvoices_buyer.at(key).Buyer=unordered_companies.at(x.canonical_Buyer()).real_name;
           unordered_companies.at(x.canonical_Seller()).count_of_unpaired_invoices++;
            unordered_companies.at(x.canonical_Buyer()).count_of_unpaired_invoices++;
           return true;
       }
        //if invoice is found but, it's an accepted invoice, then pair him with issued invoice
       else if(my_invoices_seller.count(key)==1 && !myinvoices_buyer.at(key).issue){
           my_invoices_seller.at(key).issue= true;
           myinvoices_buyer.at(key).issue= true;
            unordered_companies.at(x.canonical_Seller()).pair_invoices();
            unordered_companies.at(x.canonical_Buyer()).pair_invoices();
           return true;
       }

        return false;
    }

    bool                     addAccepted                   ( const CInvoice  & x ){
        //check if buyer and seller are in register and buyer and seller are not the same(comparing by canonical name)
        if(!sanity_check(x)){
            return false;
        }
        //creating unique key of canonic buyer's name and canonic seller's name and by converting other data to string
        string key= key_create(x);
        //creating some short expressions for seller and buyer invoices
        auto &my_invoices_seller = unordered_companies.at(x.canonical_Seller()).CInvoices;
        auto &myinvoices_buyer = unordered_companies.at(x.canonical_Buyer()).CInvoices;
        //if cant find same invoice, then add it to seller invoices and to buyer invoices with signs that it is accepted invoice
        if(my_invoices_seller.count(key)==0) {
            my_invoices_seller.insert({key, CInvoice(x.date(),x.Seller,x.Buyer,x.amount(),x.vat(), false, true,++id)});
            myinvoices_buyer.insert({key, CInvoice(x.date(),x.Seller,x.Buyer,x.amount(),x.vat(), false, true,id)});
            my_invoices_seller.at(key).Seller=unordered_companies.at(x.canonical_Seller()).real_name;
            myinvoices_buyer.at(key).Seller=unordered_companies.at(x.canonical_Seller()).real_name;
            my_invoices_seller.at(key).Buyer=unordered_companies.at(x.canonical_Buyer()).real_name;
            myinvoices_buyer.at(key).Buyer=unordered_companies.at(x.canonical_Buyer()).real_name;
            unordered_companies.at(x.canonical_Seller()).count_of_unpaired_invoices++;
            unordered_companies.at(x.canonical_Buyer()).count_of_unpaired_invoices++;
            return true;
        }
        //if invoice is found but, it's an issued invoice, then pair him with accepted invoice
        if(my_invoices_seller.count(key)==1 && !myinvoices_buyer.at(key).accept){
            my_invoices_seller.at(key).accept= true;
            myinvoices_buyer.at(key).accept= true;
            unordered_companies.at(x.canonical_Seller()).pair_invoices();
            unordered_companies.at(x.canonical_Buyer()).pair_invoices();
            return true;
        }

        return false;
    }
    bool                     delIssued                     ( const CInvoice  & x ){
        //creating unique key of canonic buyer's name and canonic seller's name and by converting other data to string
        string key= key_create(x);
        //check if buyer and seller are in register and buyer and seller are not the same(comparing by canonical name)
        if(!sanity_check(x)){
            return false;
        }
        //creating some short expressions for seller and buyer invoices
        auto &my_invoices_seller = unordered_companies.at(x.canonical_Seller()).CInvoices;
        auto &myinvoices_buyer = unordered_companies.at(x.canonical_Buyer()).CInvoices;
        //if seller don't have this invoice then it doesn't exist
        if(my_invoices_seller.count(key)==0){
            return false;
        }
        //if invoice is not paired, delete it from both companies
        if(!my_invoices_seller.at(key).accept){
            my_invoices_seller.erase(key);
            myinvoices_buyer.erase(key);
            unordered_companies.at(x.canonical_Seller()).count_of_unpaired_invoices--;
            unordered_companies.at(x.canonical_Buyer()).count_of_unpaired_invoices--;

        }

        else{
            //if invoice is paired, then just unpair them
            if(my_invoices_seller.at(key).issue){
                my_invoices_seller.at(key).issue= false;
                myinvoices_buyer.at(key).issue= false;
                unordered_companies.at(x.canonical_Seller()).unpair_invoices();
                unordered_companies.at(x.canonical_Buyer()).unpair_invoices();
            }
            //issued invoice doesnt exist
            else{
                return false;
            }
        }
        return true;

    }
    bool                     delAccepted                   ( const CInvoice  & x ){
        //creating unique key of canonic buyer's name and canonic seller's name and by converting other data to string
        string key= key_create(x);


        //check if buyer and seller are in register and buyer and seller are not the same(comparing by canonical name)
        if(!sanity_check(x) ){
            return false;
        }
        //creating some short expressions for seller and buyer invoices
        auto &my_invoices_seller = unordered_companies.at(x.canonical_Seller()).CInvoices;
        auto &myinvoices_buyer = unordered_companies.at(x.canonical_Buyer()).CInvoices;
        //if seller don't have this invoice then it doesn't exist
        if(my_invoices_seller.count(key)==0){
            return false;
        }

        if(my_invoices_seller.at(key).issue){
            //if invoice is paired, then just unpair them
            if(my_invoices_seller.at(key).accept){
                my_invoices_seller.at(key).accept= false;
                myinvoices_buyer.at(key).accept= false;
                unordered_companies.at(x.canonical_Seller()).unpair_invoices();
                unordered_companies.at(x.canonical_Buyer()).unpair_invoices();
            }
            //accepted invoice doesnt exist
            else{
                return false;
            }
        }
            //if invoice is not paired, delete it from both companies
        else{
            my_invoices_seller.erase(key);
            myinvoices_buyer.erase(key);
            unordered_companies.at(x.canonical_Seller()).count_of_unpaired_invoices--;
            unordered_companies.at(x.canonical_Buyer()).count_of_unpaired_invoices--;

        }
        return true;

    }
    list<CInvoice>           unmatched                     ( const string    & company,
                                                             const CSortOpt  & sortBy ) const{
        list<CInvoice> tmp;
        CCompany Tmp(company);
        //if company is not found ,or it doesn't have invoices, or it has only paired invoices, return empty list
        if(unordered_companies.count(Tmp.canonical_name)==0 ||  unordered_companies.at(Tmp.canonical_name).CInvoices.empty() ||
        unordered_companies.at(Tmp.canonical_name).count_of_unpaired_invoices==unordered_companies.at(Tmp.canonical_name).count_of_paired_invoices){
            return tmp;
        }
        //iterating through invoices of company
        for (const auto &  company1: unordered_companies.at(Tmp.canonical_name).CInvoices) {
            //looking for unpaired invoices, if its issued and not accepted, or accepted and not issued, then insert it in list
          if((company1.second.accept && !company1.second.issue) || (!company1.second.accept && company1.second.issue)){
              tmp.push_back(company1.second);
          }
        }
        //sorting list according to CSortOpt
        tmp.sort(CompareInvoice(sortBy));



        return tmp;
    }


private:
    unordered_map<string,CCompany> unordered_companies;

    int id=0;
    int obj_value=1;
};
//---------------------------------------------------------------------------------------------
#ifndef __PROGTEST__
bool equalLists ( const list<CInvoice> & a, const list<CInvoice> & b )
{
if(a.size()==0 && b.size()==a.size()){
    return true;
}
    if (a.size() != b.size() ) {
        return false;
    }


        for (unsigned int i = 0; i < a.size(); ++i) {
            CInvoice ai = a.front();
            CInvoice bi = b.front();

            if (ai.buyer() != bi.buyer() || ai.seller() != bi.seller() || ai.date().compare(bi.date())!=0 || ai.amount() !=bi.amount() || ai.vat() !=bi.vat()) {
                return false;
            }


        }


    return true;
}

int main ( void )
{


    CVATRegister r;
    assert ( r . registerCompany ( "first Company" ) );
    assert ( r . registerCompany ( "Second     Company" ) );
    assert ( r . registerCompany ( "ThirdCompany, Ltd." ) );
    assert ( r . registerCompany ( "Third Company, Ltd." ) );
    assert ( !r . registerCompany ( "Third Company, Ltd." ) );
    assert ( !r . registerCompany ( " Third  Company,  Ltd.  " ) );



    assert ( r . addIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", "Second Company ", 100, 20 ) ) );
    assert ( r . addIssued ( CInvoice ( CDate ( 2000, 1, 2 ), "FirSt Company", "Second Company ", 200, 30 ) ) );
    assert ( r . addIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", "Second Company ", 100, 30 ) ) );
    assert ( r . addIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", "Second Company ", 300, 30 ) ) );
    assert ( r . addIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", " Third  Company,  Ltd.   ", 200, 30 ) ) );
    assert ( r . addIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "Second Company ", "First Company", 300, 30 ) ) );
    assert ( r . addIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "Third  Company,  Ltd.", "  Second    COMPANY ", 400, 34 ) ) );
    assert ( !r . addIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", "Second Company ", 300, 30 ) ) );
    assert ( !r . addIssued ( CInvoice ( CDate ( 2000, 1, 4 ), "First Company", "First   Company", 200, 30 ) ) );
    assert ( !r . addIssued ( CInvoice ( CDate ( 2000, 1, 4 ), "Another Company", "First   Company", 200, 30 ) ) );


    assert ( equalLists ( r . unmatched ( "First Company", CSortOpt () . addKey ( CSortOpt::BY_SELLER, true ) . addKey ( CSortOpt::BY_BUYER, false ) . addKey ( CSortOpt::BY_DATE, false ) ),
                          list<CInvoice>
                                  {
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Third Company, Ltd.", 200, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 2 ), "first Company", "Second     Company", 200, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 20.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 300, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 30.000000 )
                                  } ) );
    assert ( equalLists ( r . unmatched ( "First Company", CSortOpt () . addKey ( CSortOpt::BY_DATE, true ) . addKey ( CSortOpt::BY_SELLER, true ) . addKey ( CSortOpt::BY_BUYER, true ) ),
                          list<CInvoice>
                                  {
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 20.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 300, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Third Company, Ltd.", 200, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 2 ), "first Company", "Second     Company", 200, 30.000000 )
                                  } ) );
    assert ( equalLists ( r . unmatched ( "First Company", CSortOpt () . addKey ( CSortOpt::BY_VAT, true ) . addKey ( CSortOpt::BY_AMOUNT, true ) . addKey ( CSortOpt::BY_DATE, true ) . addKey ( CSortOpt::BY_SELLER, true ) . addKey ( CSortOpt::BY_BUYER, true ) ),
                          list<CInvoice>
                                  {
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 20.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Third Company, Ltd.", 200, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 2 ), "first Company", "Second     Company", 200, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 300, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 30.000000 )
                                  } ) );

  assert ( equalLists ( r . unmatched ( "First Company", CSortOpt () ),
           list<CInvoice>
           {
             CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 20.000000 ),
             CInvoice ( CDate ( 2000, 1, 2 ), "first Company", "Second     Company", 200, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 300, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Third Company, Ltd.", 200, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 30.000000 )
           } ) );
  assert ( equalLists ( r . unmatched ( "second company", CSortOpt () . addKey ( CSortOpt::BY_DATE, false ) ),
           list<CInvoice>
           {
             CInvoice ( CDate ( 2000, 1, 2 ), "first Company", "Second     Company", 200, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 20.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 300, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "Third Company, Ltd.", "Second     Company", 400, 34.000000 )
           } ) );
  assert ( equalLists ( r . unmatched ( "last company", CSortOpt () . addKey ( CSortOpt::BY_VAT, true ) ),
           list<CInvoice>
           {
           } ) );
  assert ( r . addAccepted ( CInvoice ( CDate ( 2000, 1, 2 ), "First Company", "Second Company ", 200, 30 ) ) );
  assert ( r . addAccepted ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", " Third  Company,  Ltd.   ", 200, 30 ) ) );
  assert ( r . addAccepted ( CInvoice ( CDate ( 2000, 1, 1 ), "Second company ", "First Company", 300, 32 ) ) );
  assert ( equalLists ( r . unmatched ( "First Company", CSortOpt () . addKey ( CSortOpt::BY_SELLER, true ) . addKey ( CSortOpt::BY_BUYER, true ) . addKey ( CSortOpt::BY_DATE, true ) ),
           list<CInvoice>
           {
             CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 20.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 300, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 32.000000 )
           } ) );
  assert ( !r . delIssued ( CInvoice ( CDate ( 2001, 1, 1 ), "First Company", "Second Company ", 200, 30 ) ) );
  assert ( !r . delIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "A First Company", "Second Company ", 200, 30 ) ) );
  assert ( !r . delIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", "Second Hand", 200, 30 ) ) );
  assert ( !r . delIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", "Second Company", 1200, 30 ) ) );
  assert ( !r . delIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", "Second Company", 200, 130 ) ) );
  assert ( r . delIssued ( CInvoice ( CDate ( 2000, 1, 2 ), "First Company", "Second Company", 200, 30 ) ) );
  assert ( equalLists ( r . unmatched ( "First Company", CSortOpt () . addKey ( CSortOpt::BY_SELLER, true ) . addKey ( CSortOpt::BY_BUYER, true ) . addKey ( CSortOpt::BY_DATE, true ) ),
           list<CInvoice>
           {
             CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 20.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 300, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 2 ), "first Company", "Second     Company", 200, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 32.000000 )
           } ) );
  assert ( r . delAccepted ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", " Third  Company,  Ltd.   ", 200, 30 ) ) );
  assert ( equalLists ( r . unmatched ( "First Company", CSortOpt () . addKey ( CSortOpt::BY_SELLER, true ) . addKey ( CSortOpt::BY_BUYER, true ) . addKey ( CSortOpt::BY_DATE, true ) ),
           list<CInvoice>
           {
             CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 20.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 300, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 2 ), "first Company", "Second     Company", 200, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Third Company, Ltd.", 200, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 32.000000 )
           } ) );
  assert ( r . delIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", " Third  Company,  Ltd.   ", 200, 30 ) ) );
  assert ( equalLists ( r . unmatched ( "First Company", CSortOpt () . addKey ( CSortOpt::BY_SELLER, true ) . addKey ( CSortOpt::BY_BUYER, true ) . addKey ( CSortOpt::BY_DATE, true ) ),
           list<CInvoice>
           {
             CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 20.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 300, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 2 ), "first Company", "Second     Company", 200, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 32.000000 )
           } ) );

    return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */