//
// Created by fantomasm on 10/07/24.
//

#include "CVATRegister.h"


bool                     CVATRegister::registerCompany               ( const string    & name ){

        string canonical_name=(change_to_canonical(name));
        //if there is no client with same key, then insert new client, key is his canonical name(words separated by one space between and one space in the end of string)
        if(unordered_companies.count(canonical_name)==0){
            unordered_companies.insert({canonical_name,CCompany(name)});
            return true;
        }
        return false;



    }
    //basic check if buyer and seller are in register and if they are not the same
    bool CVATRegister::sanity_check(const CInvoice  & x) const{
        if(unordered_companies.count(x.canonical_Buyer())==0 || unordered_companies.count(x.canonical_Seller())==0 ||
           x.canonical_Buyer()== x.canonical_Seller()){
            return false;
        }
        return true;
    }
    bool
    CVATRegister::addIssued                     ( const CInvoice  & x ){
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

    bool                     CVATRegister::addAccepted                   ( const CInvoice  & x ){
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
    bool                     CVATRegister::delIssued                     ( const CInvoice  & x ){
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
    bool                     CVATRegister::delAccepted                   ( const CInvoice  & x ){
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
    list<CInvoice>           CVATRegister::unmatched                     ( const string    & company,
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