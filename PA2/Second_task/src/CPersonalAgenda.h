//
// Created by fantomasm on 09/07/24.
//



#ifndef CPERSONALAGENDA_H
#define CPERSONALAGENDA_H
#include <iostream>
#include "Worker.h"
using namespace std;


#define basic_name "Error 404"
#define basic_surname "Error 505"
#define basic_salary 666666
#define basic_email  "who_cares@yahoo.com"
bool cmpfunc_email(const Worker &lhs,const Worker &rhs);

bool cmpfunc_surname(const Worker &lhs,const Worker &rhs);

class CPersonalAgenda {
public:
    CPersonalAgenda(void);

    ~CPersonalAgenda(void);

    bool add(const string &name,
             const string &surname,
             const string &email,
             unsigned int salary);

    bool del(const string &name,
             const string &surname);

    bool del(const string &email);

    bool changeName(const string &email,
                    const string &newName,
                    const string &newSurname);

    bool changeEmail(const string &name,
                     const string &surname,
                     const string &newEmail);

    bool setSalary(const string &name,
                   const string &surname,
                   unsigned int salary);

    bool setSalary(const string &email,
                   unsigned int salary);

    unsigned int getSalary(const string &name,
                           const string &surname) const;

    unsigned int getSalary(const string &email) const;

    bool getRank(const string &name,
                 const string &surname,
                 int &rankMin,
                 int &rankMax) const;

    bool getRank(const string &email,
                 int &rankMin,
                 int &rankMax) const;

    bool getFirst(string &outName,
                  string &outSurname) const;

    bool getNext(const string &name,
                 const string &surname,
                 string &outName,
                 string &outSurname) const;


    //Printing method for testing
    void Print();

private:
    //methods for adding worker into vector, after founding his future position by lower_bound
    void add_to_Surname_sort(const Worker &New_Worker,
                             __gnu_cxx::__normal_iterator<Worker *, vector<Worker>> it);

    void add_to_email_sort(const Worker &New_Worker,
                           __gnu_cxx::__normal_iterator<Worker *, vector<Worker>> it) ;
    //------------------------------------------------------------------------
    //methods for checking if user with this name,surname/email isn't already in vectors
    bool check_for_similarity(const string &name,
                              const string &surname) const ;

    bool check_for_similarity(const string &email) const ;
    //-------------------------------------------------------------

    //iterators are pointing to possible location of user in vector found by lower_bound
    bool check_if_worker_exists(const Worker &find,
                                const __gnu_cxx::__normal_iterator<const Worker *, vector<Worker>> surname_it,
                                const __gnu_cxx::__normal_iterator<const Worker *, vector<Worker>> email_it) const ;

    bool check_if_worker_exists_surname(const Worker &find,
                                        const __gnu_cxx::__normal_iterator<const Worker *, vector<Worker>> surname_it) const ;

    bool check_if_worker_exists_email(const Worker &find,
                                      const __gnu_cxx::__normal_iterator<const Worker *, vector<Worker>> email_it) const ;
    //-------------------------------------------------------------
    vector<Worker> List_by_surname;
    vector<Worker> List_by_email;
};


#endif //CPERSONALAGENDA_H
