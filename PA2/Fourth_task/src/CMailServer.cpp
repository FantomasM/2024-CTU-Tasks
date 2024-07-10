//
// Created by fantomasm on 10/07/24.
//

#include "CMailServer.h"

CMailServer::~CMailServer()=default;

void CMailServer::Print(){
        for(size_t i=0;i<base.size();i++){
            cout << "email: " <<base[i].email() <<endl << "input: -----------------------------------------------------------" <<endl;
            base[i].print_input();
            cout << "output: ---------------------------------------------------------------------" << endl;
            base[i].print_output();
            cout << "///////////////////////////////////////////////////////" << endl;
        }
    }

size_t Lower_bound(const vector<Client> & base, str array) {
   size_t mid;
   size_t low=0;
   size_t high=base.size();
   while(low  <high){
       mid=low+(high-low)/2;
       if(base[mid].email() < array){
           low=mid+1;
       }

       else{
           high=mid;
       }
   }
   if(low < base.size() && base[low].email() < array ){
       low++;
   }
    return low;
}

CMailServer::CMailServer()=default;




CMailIterator CMailServer::outbox(const char *email) const {

    str em(email);
    size_t position= Lower_bound(base,em);


        if( position <=base.count_of_members() &&base[position].email()==email){

                return CMailIterator{base[position].output};




        }
        else{
            return CMailIterator{};
        }



}

CMailServer::CMailServer(const CMailServer & src) : base(src.base) {}






CMailIterator CMailServer::inbox(const char *email) const {


    str em(email);
    size_t position= Lower_bound(base,em);
        if( position <=base.count_of_members() && base[position].email()==email){

                return CMailIterator{base[position].input};




        }
        else{
            return CMailIterator{};
        }



}


CMailServer &CMailServer::operator=(const CMailServer &src)  {
    if(&src==this){
        return *this;
    }
    base=src.base;

    return *this;
}

void CMailServer::sendMail(const CMail &m) {




    size_t position= Lower_bound(base,m.Source);


        if(position <=base.count_of_members() && m.from_comparsion(base[position].email())){
            base[position].add_output(m);

        }
        else{
            Client Lilychad(m.Source);
            base.insert(position,Lilychad);
            base[position].add_output(m);
        }

    size_t position2= Lower_bound(base,m.Destination);





        if(position2 <=base.count_of_members() && m.to_comparsion(base[position2].email())){
            base[position2].add_input(m);


        }
        else{
            Client Lilychad(m.Destination);
            base.insert(position2,Lilychad);
            base[position2].add_input(m);
        }




}