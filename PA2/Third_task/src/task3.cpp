#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <ctime>
#include <climits>
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <stdexcept>
#include <memory>
using namespace std;
#endif /* __PROGTEST__ */

// uncomment if your code implements initializer lists
// #define EXTENDED_SYNTAX
using interval =pair<long long,long long>;



class CRange
{
public:
    // constructor
    CRange(long long first, long long second){
        interval inter;
        inter.first=first;
        inter.second=second;
        if(second < first){

            throw logic_error("Wrong input, last value is less than first");
        }
        else{
            Interval= make_pair(first,second);
        }
    }
    CRange(long long first){




        Interval= make_pair(first,first);

    }
    CRange & operator = ( const CRange & second)  {
        this->Interval.first=second.Interval.first;
        this->Interval.second=second.Interval.second;
        return *this;
    }

    interval Interval;
    //bool more_than_one=false;

private:

};

bool cmpfunc_first(const interval &  a,const  interval & b) {
    return a.first < b.first;
}


bool intersection(CRange  first , CRange  second) {
    long long lower = std::max(first.Interval.first, second.Interval.first);
    long long upper = std::min(first.Interval.second, second.Interval.second);
    if (lower <= upper+1) {
        return true;
        // return make_pair(lower, upper);

    }
    else if(upper==LLONG_MAX && lower <=upper){
        return true;
    }
    else{
        return false;

    }
}

bool cmp_include(const interval & first , const interval & second);
class CRangeList
{
public:

    // constructor
    CRangeList(const CRangeList & other){
        intervals=other.intervals;
    };
    CRangeList(){
        intervals.reserve(25);
    }
    ~CRangeList(){
        intervals.clear();
    }
    //CRangeList(vector<interval> intervals = {}) : intervals(intervals) {};
    CRangeList(long long first, long long second){
        interval inter;
        inter.first=first;
        inter.second=second;
        intervals.push_back(inter);
    }

    // includes long long / range
    bool includes(const long long num) const{
        return includes(CRange(num,num));

    }
    bool includes(const CRange x) const{
        auto it= lower_bound(intervals.begin(),intervals.end(),x.Interval, cmp_include);

        if(it==intervals.end()){
            return false;
        }

        if(x.Interval.first >= it->first && x.Interval.second <= it->second){
            return true;
        }

        return false;
    }
    void check_for_same() {

        sort(intervals.begin(),intervals.end(), cmpfunc_first);

        vector<interval> final_vector;

        for(size_t i=0; i<intervals.size();i++){
            //cout << intervals[i].first << " " << intervals[i].second << endl;
            if(i!=intervals.size()-1 && intervals[i].first==intervals[i+1].first){
                interval  tmp;
                tmp.first=intervals[i].first;
                tmp.second=max(intervals[i].second,intervals[i+1].second);
                final_vector.push_back(tmp);
                i+=1;
                continue;
            }
            if(final_vector.empty() || final_vector.back().second <intervals[i].first-1){
                final_vector.push_back(intervals[i]);
            }
            else{
                final_vector.back().second=max(final_vector.back().second,intervals[i].second);
            }

        }
        intervals=final_vector;

    }

    CRangeList operator + (CRange  src);
      /*  //cout << endl<< " src is" << src.Interval.first << " " << src.Interval.second << endl;
        auto it = lower_bound(intervals.begin(),intervals.end(), src.Interval, cmp_include);
        if(it==this->intervals.end()){
            intervals.push_back(src.Interval);
          //  intervals.insert(it,src.Interval);
        }

        while(it!=intervals.end()){
            CRangeList tmp=CRange(it->first,it->second)+CRange(src.Interval.first,src.Interval.second);
        }






        if(it != intervals.begin()&&  it!=intervals.end() && std::prev(it)->second >= src.Interval.first-1 ){
            src.Interval.first=std::prev(it)->first;
            src.Interval.second=max(src.Interval.second,std::prev(it)->second);
            intervals.erase(std::prev(it));
        }

        while(it!=intervals.end() && it->first-1 <= src.Interval.second){

            src.Interval.second=max(src.Interval.second,it->second);

            it++;


        }

        if(it !=intervals.end() ){
            intervals.insert(it,src.Interval);
        }
        else{
            intervals.push_back(src.Interval);
        }

        check_for_same();


        return *this;

    }
       */
    CRangeList operator+=(CRange src){
        return *this+src;
    }





    friend CRangeList operator + (CRangeList & dst1, const CRangeList  &dst2){
        for(const auto & interval : dst2.intervals){
            dst1+CRange(interval.first,interval.second);
        }
        return dst1;
    }
    friend CRangeList operator += ( CRangeList &  dst1, const CRangeList & dst2) {
        for(const auto & interval : dst2.intervals){
            dst1+CRange(interval.first,interval.second);
        }
        return dst1;

    }


    CRangeList & operator = ( const CRangeList & second){

        intervals.clear();
        intervals=second.intervals;

        return *this;
    }

    CRangeList & operator = ( const CRange & second){
        this->intervals.clear();
        this->intervals.push_back(second.Interval);
        ;
        return *this;
    }


    friend ostream & operator << (ostream & os , const CRangeList &list){
        os<< "{";
        for(size_t i=0; i < list.intervals.size();i++){
            if(list.intervals[i].first!=list.intervals[i].second) {
                os << "<" << list.intervals[i].first << ".." << list.intervals[i].second << ">";
            }
            else{
                os << list.intervals[i].second;
            }
            if(list.intervals.size()-1!=i){
                os << ",";
            }
        }
        os << "}";

        return os;
    }

    vector<interval> intervals;
    void add_interval(const interval & inter){
        intervals.push_back(inter);
    }
    CRangeList operator -( CRange inter);
private:
    // todo

};
CRangeList  operator + (CRange src1 ,CRange src2){
    if(intersection(src1,src2)){

        CRangeList tmp(std::min(src1.Interval.first, src2.Interval.first),std::max(src1.Interval.second, src2.Interval.second));
        return  tmp;
    }
    else{
        CRangeList tmp3(min(src1.Interval.first,src2.Interval.first),min(src1.Interval.second,src2.Interval.second));



        interval tmp2;
       // tmp2.first=max(src1.Interval.first,src2.Interval.first);
      //  tmp2.second=max(src1.Interval.second,src2.Interval.second);
        tmp2= make_pair(max(src1.Interval.first,src2.Interval.first),max(src1.Interval.second,src2.Interval.second));
        tmp3.add_interval(tmp2);



        return tmp3;


    }
}
CRangeList CRangeList::operator + (CRange  src){
    //cout << endl<< " src is" << src.Interval.first << " " << src.Interval.second << endl;
    auto it = lower_bound(intervals.begin(),intervals.end(), src.Interval, cmp_include);
   // cout << "src is" << src.Interval.first <<" " << src.Interval.second << endl;
  //  cout << "it is" << it->first << " " << it->second << endl;
    if(it==this->intervals.end()){
        intervals.push_back(src.Interval);
        return *this;
        //  intervals.insert(it,src.Interval);
    }
    CRangeList tmp_tmp=CRange(it->first,it->second)+CRange(src.Interval.first,src.Interval.second);

    switch (tmp_tmp.intervals.size()) {
        case 1:
            *it=tmp_tmp.intervals[0];
           // cout << "corrected it is" << it->first << " " << it->second << endl;
            break;
        case 2:
            it=intervals.insert(it,src.Interval);
            return *this;
            break;

    }
    auto to_change=it;
    it++;



   // auto second_it = it;
    while(it!=intervals.end()){
        //CRangeList tmp=CRange(it->first,it->second)+CRange(src.Interval.first,src.Interval.second);
        if(intersection(CRange(it->first,it->second),CRange(src.Interval.first,src.Interval.second))){
            switch (tmp_tmp.intervals.size()) {
                case 1:
                    to_change->second=max(it->second,src.Interval.second);
                    it=intervals.erase(it);
                    //it++;
                    break;
                case 2:
                    it=intervals.insert(it,src.Interval);
                    return *this;
                    break;

            }
        }
        else{
            break;
        }

    }






    return *this;

}
CRangeList operator += ( CRange dst, const CRange  src){
    //  cout << "smth1" << endl;

    return (dst+src);
}

CRangeList operator -(CRange  first, CRange  second){
    if(second.Interval.first==second.Interval.second){
        if(second.Interval.first >= first.Interval.first && second.Interval.first <= first.Interval.second) {
            if(first.Interval.first==first.Interval.second){
                CRangeList tmp;

                return  tmp;
            }
            if(second.Interval.first==first.Interval.first){
                CRangeList tmp(first.Interval.first+1,first.Interval.second);
                return tmp;
            }
            if(second.Interval.first==first.Interval.second){
                CRangeList tmp(first.Interval.first,first.Interval.second-1);
                return tmp;
            }
            else{
                CRangeList tmp3(first.Interval.first,second.Interval.first-1);
                interval tmp2;
                //tmp2.first=second.Interval.second+1;
               // tmp2.second=first.Interval.second;
                tmp2=make_pair(second.Interval.second+1,first.Interval.second);
                tmp3.add_interval(tmp2);
                return tmp3;
            }
        }
        CRangeList tmp(first.Interval.first, first.Interval.second);

        return  tmp;
    }
    if(intersection(first,second)){
        if(first.Interval.first < second.Interval.first){
            if(first.Interval.second >= second.Interval.first && first.Interval.second <= second.Interval.second){
                //auto tmp= make_unique<CRangeList>(first.Interval.first,second.Interval.first-1);
                CRangeList tmp(first.Interval.first,second.Interval.first-1);
                return tmp;
            }
            if(first.Interval.second > second.Interval.first && first.Interval.second > second.Interval.second){
                CRangeList tmp3(first.Interval.first,second.Interval.first-1);


                //if(first.Interval.second!=second.Interval.second){//auto tmp= make_unique<CRangeList>(first.Interval.first,second.Interval.first-1);
                interval tmp2;
                tmp2.first=second.Interval.second+1;
                tmp2.second=first.Interval.second;
                tmp3.add_interval(tmp2);
                //}
                //unique_ptr p=make_unique<CRangeList>(tmp3);
                // tmp->add_interval(tmp2);
                // return tmp3;
                return tmp3;
            }

        }
        if(first.Interval.first >= second.Interval.first && first.Interval.second <= second.Interval.second ){
           // auto tmp= make_unique<CRangeList>();
            CRangeList tmp;

            return  tmp;
        }
        if(first.Interval.first > second.Interval.first && first.Interval.second > second.Interval.second){
            //auto tmp= make_unique<CRangeList>(second.Interval.second+1,first.Interval.second);
            CRangeList tmp(second.Interval.second+1,first.Interval.second);

            return  tmp;
            //return  *tmp.release();
        }
        if(first.Interval.first ==second.Interval.first && first.Interval.second > second.Interval.second){
            CRangeList tmp(second.Interval.second+1,first.Interval.second);

            return  tmp;
        }

    }


    CRangeList tmp(first.Interval.first, first.Interval.second);

    return  tmp;
    //auto tmp= make_unique<CRangeList>(first.Interval.first, first.Interval.second);
   // return  *tmp.release();

}
bool cmp_include(const interval & first , const interval & second){
    if(first.second==LLONG_MAX){
        return false;
    }
    if(second.first > first.second+1){
        return true;
    }
    return false;
}
CRangeList CRangeList::operator -( const CRange  inter){


  // vector<interval> new_vector=intervals;

    auto it=lower_bound(intervals.begin(),intervals.end(),inter.Interval, cmp_include);
   // cout << "it is" << it->first << " " << it->second << endl;
   // cout << "inter is " << CRangeList(inter.Interval.first,inter.Interval.second) << endl;
    interval tmp23;
    if(it==intervals.end()){

        return *this;
    }
    if(intersection(CRange(it->first,it->second),inter)) {
        CRangeList tmp = CRange(it->first, it->second) - inter;
        //cout <<"tmp is " << tmp << endl;
        switch (tmp.intervals.size()) {
            case 1:
                *it = tmp.intervals[0];
                it++;
                break;
            case 2:
                *it = tmp.intervals[0];
                it = intervals.insert(++it, tmp.intervals[1]);
              //  cout << " tmp after inserting 2 intervals" << tmp << endl;
               // cout << "---------------------------------------" <<endl;
                //for(size_t i=0; i<intervals.size();i++){
               //     cout << intervals[i].first << " " << intervals[i].second << endl;
               // }
               // cout << "---------------------------------------" <<endl;
                return *this;
                break;
            default:
                it=intervals.erase(it);
                break;

        }
    }
    else{
        return *this;
    }

    while(it!=intervals.end()) {

        if (intersection(CRange(it->first, it->second), inter)) {
            CRangeList tmp = CRange(it->first, it->second) - inter;
            switch (tmp.intervals.size()) {
                case 1:
                    *it = tmp.intervals[0];
                    return *this;
                    break;
                case 2:
                    *it = tmp.intervals[0];
                    it = intervals.insert(++it, tmp.intervals[1]);
                    return *this;
                    break;
                default:
                    it = intervals.erase(it);
                    break;

            }
        }
        else{
            break;
        }
    }




      return *this;



}
CRangeList operator -=(CRangeList &list, const CRange inter){
    return list-inter;
}
CRangeList & operator -(CRangeList &list, const CRangeList & list2){
    for(const auto & interval : list2.intervals){
        list-CRange(interval.first,interval.second);
    }
    return list;
}
CRangeList & operator -=(CRangeList &list, const CRangeList & list2){

    return list-list2;
}
CRangeList  operator += (CRange & dst ,const CRange & src){

    return dst+src;
    //CRangeList(dst.Interval.first,dst.Interval.second) + CRangeList(src.Interval.first,src.Interval.second);
}
bool operator == (const CRange first,const CRange second) {
    if(first.Interval.first == second.Interval.first && second.Interval.second==first.Interval.second){
        return true;
    }
    return false;
}
bool operator != (const CRange first,const CRange second) {
    if(!(first==second)) {
        return true;
    }
    return false;
}
bool operator ==(const CRangeList& first, const CRangeList& second){
    if(first.intervals.size() !=second.intervals.size()){
        return false;
    }
    for(size_t i=0;i<first.intervals.size();i++){
        if(!(CRange(first.intervals[i].first,first.intervals[i].second)==CRange(second.intervals[i].first,second.intervals[i].second))){
            return false;
        }
    }
    return true;
}
bool operator !=(const CRangeList& first, const CRangeList& second){
    if(!(first==second)){
        return true;
    }
    return false;
}
#ifndef __PROGTEST__
string             toString                                ( const CRangeList& x )
{
    ostringstream oss;
    oss << x;
    return oss . str ();
}

int                main                                    ( void )
{
    CRangeList a, b;

   
   assert ( sizeof ( CRange ) <= 2 * sizeof ( long long ) );
    a = CRange ( 5, 10 ) ;

    a += CRange ( 25, 100 );

    assert (toString ( a ) == "{<5..10>,<25..100>}" );
    a += CRange ( -5, 0 );
    a += CRange ( 8, 50 );

    assert ( toString ( a ) == "{<-5..0>,<5..100>}" );



    a += CRange ( 101, 105 ) + CRange ( 120, 150 ) + CRange ( 160, 180 ) + CRange ( 190, 210 );

    assert ( toString ( a ) == "{<-5..0>,<5..105>,<120..150>,<160..180>,<190..210>}" );
    a += CRange ( 106, 119 ) + CRange ( 152, 158 );


    assert ( toString ( a ) == "{<-5..0>,<5..150>,<152..158>,<160..180>,<190..210>}" );
    a += CRange ( -3, 170 );
    a += CRange ( -30, 1000 );
    assert ( toString ( a ) == "{<-30..1000>}" );
    b = CRange ( -500, -300 ) + CRange ( 2000, 3000 ) + CRange ( 700, 1001 );
    a += b;


    assert ( toString ( a ) == "{<-500..-300>,<-30..1001>,<2000..3000>}" );
    a -= CRange ( -400, -400 );



    assert ( toString ( a ) == "{<-500..-401>,<-399..-300>,<-30..1001>,<2000..3000>}" );
    a -= CRange ( 10, 20 ) + CRange ( 900, 2500 ) + CRange ( 30, 40 ) + CRange ( 10000, 20000 );


    assert ( toString ( a ) == "{<-500..-401>,<-399..-300>,<-30..9>,<21..29>,<41..899>,<2501..3000>}" );
    try
    {
        a += CRange ( 15, 18 ) + CRange ( 10, 0 ) + CRange ( 35, 38 );
        assert ( "Exception not thrown" == nullptr );
    }
    catch ( const std::logic_error & e )
    {
    }
    catch ( ... )
    {
        assert ( "Invalid exception thrown" == nullptr );
    }
    assert ( toString ( a ) == "{<-500..-401>,<-399..-300>,<-30..9>,<21..29>,<41..899>,<2501..3000>}" );
    b = a;
    assert ( a == b );
    assert ( !( a != b ) );
    b += CRange ( 2600, 2700 );
    assert ( toString ( b ) == "{<-500..-401>,<-399..-300>,<-30..9>,<21..29>,<41..899>,<2501..3000>}" );
    assert ( a == b );
    assert ( !( a != b ) );
    b += CRange ( 15, 15 );

    assert ( toString ( b ) == "{<-500..-401>,<-399..-300>,<-30..9>,15,<21..29>,<41..899>,<2501..3000>}" );
    assert ( !( a == b ) );
    assert ( a != b );
    assert ( b . includes ( 15 ) );
    assert ( b . includes ( 2900 ) );
    assert ( b . includes ( CRange ( 15, 15 ) ) );
    assert ( b . includes ( CRange ( -350, -350 ) ) );
    assert ( b . includes ( CRange ( 100, 200 ) ) );
    assert ( !b . includes ( CRange ( 800, 900 ) ) );
    assert ( !b . includes ( CRange ( -1000, -450 ) ) );
    assert ( !b . includes ( CRange ( 0, 500 ) ) );
    a += CRange ( -10000, 10000 ) + CRange ( 10000000, 1000000000 );
    assert ( toString ( a ) == "{<-10000..10000>,<10000000..1000000000>}" );
    b += a;
    assert ( toString ( b ) == "{<-10000..10000>,<10000000..1000000000>}" );
    b -= a;


    assert ( toString ( b ) == "{}" );
    b += CRange ( 0, 100 ) + CRange ( 200, 300 ) - CRange ( 150, 250 ) + CRange ( 160, 180 ) - CRange ( 170, 170 );
    assert ( toString ( b ) == "{<0..100>,<160..169>,<171..180>,<251..300>}" );


    b -= CRange ( 10, 90 ) - CRange ( 20, 30 ) - CRange ( 40, 50 ) - CRange ( 60, 90 ) + CRange ( 70, 80 );

    assert ( toString ( b ) == "{<0..9>,<20..30>,<40..50>,<60..69>,<81..100>,<160..169>,<171..180>,<251..300>}" );



    return EXIT_SUCCESS;


#ifdef EXTENDED_SYNTAX
    CRangeList x { { 5, 20 }, { 150, 200 }, { -9, 12 }, { 48, 93 } };
  assert ( toString ( x ) == "{<-9..20>,<48..93>,<150..200>}" );
  ostringstream oss;
  oss << setfill ( '=' ) << hex << left;
  for ( const auto & v : x + CRange ( -100, -100 ) )
    oss << v << endl;
  oss << setw ( 10 ) << 1024;
  assert ( oss . str () == "-100\n<-9..20>\n<48..93>\n<150..200>\n400=======" );

#endif /* EXTENDED_SYNTAX */
    return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
