//
// Created by fantomasm on 09/07/24.
//

#ifndef CRANGELIST_H
#define CRANGELIST_H
#include <iostream>
#include "CRange.h"

bool cmp_include(const interval & first , const interval & second);
bool cmpfunc_first(const interval &  a,const  interval & b);
bool intersection(CRange  first , CRange  second);
class CRangeList
{
public:

    // constructor
    CRangeList(const CRangeList & other);
    CRangeList();
    ~CRangeList();

    CRangeList(long long first, long long second);

    // includes long long / range
    bool includes(const long long num) const;
    bool includes(const CRange x) const;
    void check_for_same();

    CRangeList operator + (CRange  src);

    CRangeList operator+=(CRange src);





    friend CRangeList operator + (CRangeList & dst1, const CRangeList  &dst2);
    friend CRangeList operator += ( CRangeList &  dst1, const CRangeList & dst2);


    CRangeList & operator = ( const CRangeList & second);

    CRangeList & operator = ( const CRange & second);


    friend ostream & operator << (ostream & os , const CRangeList &list);

    vector<interval> intervals;
    void add_interval(const interval & inter);
    CRangeList operator -( CRange inter);
private:


};
//Section with some additional overloaded operators
CRangeList  operator + (CRange src1 ,CRange src2);
CRangeList operator += (CRange dst, const CRange  src);
CRangeList operator -(CRange  first, CRange  second);
CRangeList operator -=(CRangeList &list, const CRange inter);
CRangeList & operator -(CRangeList &list, const CRangeList & list2);
CRangeList & operator -=(CRangeList &list, const CRangeList & list2);
CRangeList  operator += (CRange & dst ,const CRange & src);
bool operator == (const CRange first,const CRange second) ;
bool operator != (const CRange first,const CRange second) ;
bool operator ==(const CRangeList& first, const CRangeList& second);
bool operator !=(const CRangeList& first, const CRangeList& second);


#endif //CRANGELIST_H
