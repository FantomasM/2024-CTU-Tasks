//
// Created by fantomasm on 10/07/24.
//
#include "str.h"
#include <iostream>
void str::Realloc(size_t num){
        while (num >= max){
            max*=1.5;
        }

        char * tmp=new char[max];

    if(tmp==nullptr){
        throw std::runtime_error("Probably run out of memory");
    }
        memcpy(tmp,array_of_chars,size);

        delete [] array_of_chars;
        array_of_chars=tmp;



    }

    void str::Realloc(){

            max*=1.5;

            char * tmp=new char[max];
    if(tmp==nullptr){
        throw std::runtime_error("Probably run out of memory");
    }
       memcpy(tmp,array_of_chars,size);

            delete [] array_of_chars;
            array_of_chars=tmp;



    }
    str & str::operator + (const char* src){
        str source(src);
       size_t tmpmax=max;
        while(source.size+size+1>tmpmax){
            tmpmax*=1.5;
        }if(tmpmax!=max) {
        try{
            Realloc(tmpmax);
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << '\n';
                exit(EXIT_FAILURE);
            }
        }
        memcpy(array_of_chars+size,src,source.size);

        size+=source.size;
        array_of_chars[size]='\0';

        return *this;
    }

    str & str::operator +=(const char * src){
        return *this+src;
    }
     bool str::operator ==(const char * second) const{
        str sec(second);
         if(sec.size!= size){
             return false;
         }
        int switch_ride=strncmp(array_of_chars,second,size);
         if (switch_ride == 0) {

             return true;
         }
         else{
             return false;


         }
    }
    bool str::operator ==(const str & second)const {

       if(second.size!= size ){
           return false;
       }


          int strcm = strncmp(array_of_chars, second.array_of_chars,size);

        if (strcm == 0) {

            return true;
        }
        else{
                return false;


        }
    }
    bool str::operator !=(const str &second)const{
        return !(second==array_of_chars);
    }
    bool str::operator !=(const char* second)const{
        return second != array_of_chars;
    }

    ostream & operator << (ostream & os , const str &stri){
        for(size_t i=0;i< stri.size;i++){
            os <<stri.array_of_chars[i];
        }

        return os;
    }
    char str::operator [](size_t index) const{
        return array_of_chars[index];

    }
    str & str::operator =(  const str & sec ) {
         if(&sec== this){
             return *this;
         }
        delete []array_of_chars;
        size=0;
        array_of_chars=new char [2];
    if(array_of_chars==nullptr){
        throw std::runtime_error("Probably run out of memory");
    }
        max=2;
        size_t tmpmax=max;
        while(sec.size+size+1>tmpmax){
            tmpmax*=1.5;
        }
        if(tmpmax!=max) {
            Realloc(tmpmax);
        }
        memcpy(array_of_chars,sec.array_of_chars,sec.size);
        size=sec.size;
        return *this;
   }

    str & str::operator =(  const char * sec ) {
        if(sec== this->array_of_chars){
            return *this;
        }
        delete []array_of_chars;
        size=0;
        array_of_chars=new char [2];
    if(array_of_chars==nullptr){
        throw std::runtime_error("Probably run out of memory");
    }
        max=2;
        size_t secsize= strlen(sec);
        size_t tmpmax=max;
        while(secsize+size+1>tmpmax){
            tmpmax*=1.5;
        }
        if(tmpmax!=max) {
            Realloc(tmpmax);
        }
        memcpy(array_of_chars,sec,secsize);
        size=secsize;
        return *this;
    }
   void str::clear(){
         delete []array_of_chars;
        size=0;
        array_of_chars=new char [2];
        max=2;
    }

    int str::compare(const str & second) const {
        const size_t length1 = size;
        const size_t length2 = second.size;
        const size_t commonLength = (length1 < length2 ? length1 : length2);
        const int cmp = memcmp(array_of_chars, second.array_of_chars, commonLength);
        if (cmp != 0) {
            return cmp < 0 ? -1 : 1;
        }
        return (length1 == length2) ? 0 : (length1 < length2) ? -1 : 1;

    }

bool operator<(const str& lhs, const str& rhs)  {
    return lhs.compare(rhs) < 0;
}
bool operator <=(const str& lhs , const str &rhs){
    return lhs < rhs || lhs==rhs;
}