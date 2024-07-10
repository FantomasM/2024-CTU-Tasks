//
// Created by fantomasm on 10/07/24.
//

#ifndef VECTOR_H
#define VECTOR_H
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
template <typename T>
class vector{
public:
    inline vector() :M_Size(2), M_Capacity(0),m_Data(new T[2]){

    }
    inline vector(const vector& other) : M_Size(other.M_Size), M_Capacity(other.M_Capacity), m_Data(new T[other.M_Size]){

        for (size_t i = 0; i < other.M_Capacity; i++) {
            m_Data[i] = other.m_Data[i];
        }
    }
    inline ~vector(){


           delete [] m_Data;

    }
    [[nodiscard]] inline size_t size() const {return M_Capacity;}
    inline size_t count_of_members () const{
        return M_Capacity-1;
    }
    inline void push_back(const T& obj){

        if(M_Size<=M_Capacity){
            try{
                realloc();
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << '\n';
                exit(EXIT_FAILURE);
            }
        }
        m_Data[M_Capacity]=obj;
        M_Capacity++;

    }
    inline void insert(size_t position, const T & value){
        if(position > M_Size-1){
            push_back(value);

        }
        else{
            if(M_Size<=M_Capacity){
                try{
                realloc();
                }
                catch (const std::exception& e)
                {
                    std::cout << e.what() << '\n';
                    exit(EXIT_FAILURE);
                }
            }
            for(size_t i=M_Capacity;i>position;i--){
                m_Data[i]=m_Data[i-1];
            }
            m_Data[position]=value;
            M_Capacity++;
        }
    }
    inline T & operator[](size_t index) const{
        return m_Data[index];
    }
    inline bool empty() const{
        if(M_Capacity==0){
        return true;
                }
        else{
            return false;
        }
    }
    inline void clear(){
        delete []m_Data;
        m_Data=new T[2];
        M_Size=2;
        M_Capacity=0;
    }
    inline vector & operator =(const vector & src){
        if(&src==this ){
            return *this;
        }
        clear();
        try{
        realloc(src.M_Size);
        }
         catch (const std::exception& e)
         {
             std::cout << e.what() << '\n';
             exit(EXIT_FAILURE);
         }
        for(size_t i=0;i<src.M_Capacity;i++){
           m_Data[i]=src.m_Data[i];
        }
        M_Capacity=src.M_Capacity;
        return *this;

    }
    inline void realloc(size_t new_size){

       while(M_Size < new_size){
           M_Size*=1.5;
       }

        T * tmp=new T[M_Size];
         if(tmp==nullptr){
             throw std::runtime_error("Probably run out of memory");
         }
        for(size_t i=0;i<M_Capacity;i++){
            tmp[i]=m_Data[i];
        }
        delete[] m_Data;
        m_Data=tmp;
    }
    inline bool operator ==(const vector & src) const{
        if(M_Capacity!=src.M_Capacity){
            return false;
        }
        for(size_t i=0;i<M_Capacity;i++){
            if(m_Data[i]!=src.m_Data[i]){
                return false;
            }
        }
        return true;
    }
    inline void realloc(){
        M_Size*=1.5;

        T * tmp=new T[M_Size];
        if(tmp==nullptr){
        throw std::runtime_error("Probably run out of memory");
        }
        for(size_t i=0;i<M_Capacity;i++){
            tmp[i]=m_Data[i];
        }
        delete[] m_Data;
        m_Data=tmp;
    }
    inline void Print_vector() const{
        for(size_t i=0;i<M_Capacity;i++){
            cout << m_Data[i] << endl;
        }
    }
private:
    size_t M_Size=2;
    size_t M_Capacity=0;
    T * m_Data;

};


#endif //VECTOR_H
