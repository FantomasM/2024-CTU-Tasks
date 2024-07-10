//
// Created by fantomasm on 10/07/24.
//

#ifndef STR_H
#define STR_H
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cctype>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

class str{
public:
     inline str(){
array_of_chars=new char[2];
	if(array_of_chars==nullptr){
	exit(EXIT_FAILURE);}

	};

    inline str(const str & copy){
		array_of_chars=new char[2];
        delete []array_of_chars;
        size=0;
        array_of_chars=new char [2];
        max=2;
        size_t tmpmax=max;
        while(copy.size+size+1>tmpmax){
            tmpmax*=1.5;
        }
        if(tmpmax!=max) {
            Realloc(tmpmax);
        }
        memcpy(array_of_chars,copy.array_of_chars,copy.size);
        size=copy.size;


    }
    inline str(const char * char_array) {
			array_of_chars=new char[2];
         size_t arraysize= strlen(char_array);
         size_t tmpmax=max;
         while(arraysize+size+1>tmpmax){
             tmpmax*=1.5;
         }
         if(tmpmax!=max) {
             Realloc(tmpmax);
         }


        for(size_t i=0;i< arraysize;i++){
            array_of_chars[i]=char_array[i];
            size++;
        }
    }


    inline ~str(){
        delete [] array_of_chars;
    }
    void Realloc(size_t num);

    void Realloc();
    str & operator + (const char* src);

    str & operator +=(const char * src);
     bool operator ==(const char * second) const;

    bool operator ==(const str & second)const ;
    bool operator !=(const str &second)const;
    bool operator !=(const char* second)const;

    friend ostream & operator << (ostream & os , const str &stri);
    char operator [](size_t index) const;
    str & operator =(  const str & sec );

    str & operator =(  const char * sec );
   void clear();

    int compare(const str & second) const;
    size_t size=0;
    char * array_of_chars;
private:

    size_t max=2;

};

    bool operator<(const str& lhs, const str& rhs);
    bool operator <=(const str& lhs , const str &rhs);
#endif //STR_H
