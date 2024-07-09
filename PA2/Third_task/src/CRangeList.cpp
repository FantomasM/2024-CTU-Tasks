//
// Created by fantomasm on 09/07/24.
//
#include "CRangeList.h"

CRangeList::CRangeList(const CRangeList & other){
    intervals=other.intervals;
};
CRangeList::CRangeList(){
    intervals.reserve(25);
}
CRangeList::~CRangeList(){
    intervals.clear();
}

CRangeList::CRangeList(long long first, long long second){
    interval inter;
    inter.first=first;
    inter.second=second;
    intervals.push_back(inter);
}

// includes long long / range
bool CRangeList::includes(const long long num) const{
    return includes(CRange(num,num));

}
bool CRangeList::includes(const CRange x) const{
    auto it= lower_bound(intervals.begin(),intervals.end(),x.Interval, cmp_include);

    if(it==intervals.end()){
        return false;
    }

    if(x.Interval.first >= it->first && x.Interval.second <= it->second){
        return true;
    }

    return false;
}
void CRangeList::check_for_same() {

    sort(intervals.begin(),intervals.end(), cmpfunc_first);

    vector<interval> final_vector;

    for(size_t i=0; i<intervals.size();i++){

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

CRangeList CRangeList::operator+=(CRange src){
    return *this+src;
}





 CRangeList operator + (CRangeList & dst1, const CRangeList  &dst2){
    for(const auto & interval : dst2.intervals){
        dst1+CRange(interval.first,interval.second);
    }
    return dst1;
}
CRangeList operator += ( CRangeList &  dst1, const CRangeList & dst2) {
    for(const auto & interval : dst2.intervals){
        dst1+CRange(interval.first,interval.second);
    }
    return dst1;

}


CRangeList & CRangeList::operator = ( const CRangeList & second){

    intervals.clear();
    intervals=second.intervals;

    return *this;
}

CRangeList & CRangeList::operator = ( const CRange & second){
    this->intervals.clear();
    this->intervals.push_back(second.Interval);
    ;
    return *this;
}


ostream & operator << (ostream & os , const CRangeList &list){
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


void CRangeList::add_interval(const interval & inter){
    intervals.push_back(inter);
}
bool cmpfunc_first(const interval &  a,const  interval & b) {
    return a.first < b.first;
}


bool intersection(CRange  first , CRange  second) {
    long long lower = std::max(first.Interval.first, second.Interval.first);
    long long upper = std::min(first.Interval.second, second.Interval.second);
    if (lower <= upper+1) {
        return true;


    }
    else if(upper==LLONG_MAX && lower <=upper){
        return true;
    }
    else{
        return false;

    }
}



CRangeList  operator + (CRange src1 ,CRange src2){
    if(intersection(src1,src2)){

        CRangeList tmp(std::min(src1.Interval.first, src2.Interval.first),std::max(src1.Interval.second, src2.Interval.second));
        return  tmp;
    }
    else{
        CRangeList tmp3(min(src1.Interval.first,src2.Interval.first),min(src1.Interval.second,src2.Interval.second));



        interval tmp2;

        tmp2= make_pair(max(src1.Interval.first,src2.Interval.first),max(src1.Interval.second,src2.Interval.second));
        tmp3.add_interval(tmp2);



        return tmp3;


    }
}

CRangeList operator += ( CRange dst, const CRange  src){


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

                CRangeList tmp(first.Interval.first,second.Interval.first-1);
                return tmp;
            }
            if(first.Interval.second > second.Interval.first && first.Interval.second > second.Interval.second){
                CRangeList tmp3(first.Interval.first,second.Interval.first-1);



                interval tmp2;
                tmp2.first=second.Interval.second+1;
                tmp2.second=first.Interval.second;
                tmp3.add_interval(tmp2);

                return tmp3;
            }

        }
        if(first.Interval.first >= second.Interval.first && first.Interval.second <= second.Interval.second ){

            CRangeList tmp;

            return  tmp;
        }
        if(first.Interval.first > second.Interval.first && first.Interval.second > second.Interval.second){

            CRangeList tmp(second.Interval.second+1,first.Interval.second);

            return  tmp;

        }
        if(first.Interval.first ==second.Interval.first && first.Interval.second > second.Interval.second){
            CRangeList tmp(second.Interval.second+1,first.Interval.second);

            return  tmp;
        }

    }


    CRangeList tmp(first.Interval.first, first.Interval.second);

    return  tmp;


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


CRangeList CRangeList::operator + (CRange  src){

    auto it = lower_bound(intervals.begin(),intervals.end(), src.Interval, cmp_include);

    if(it==this->intervals.end()){
        intervals.push_back(src.Interval);
        return *this;

    }
    CRangeList tmp_tmp=CRange(it->first,it->second)+CRange(src.Interval.first,src.Interval.second);

    switch (tmp_tmp.intervals.size()) {
        case 1:
            *it=tmp_tmp.intervals[0];

        break;
        case 2:
            it=intervals.insert(it,src.Interval);
        return *this;
        break;

    }
    auto to_change=it;
    it++;




    while(it!=intervals.end()){

        if(intersection(CRange(it->first,it->second),CRange(src.Interval.first,src.Interval.second))){
            switch (tmp_tmp.intervals.size()) {
                case 1:
                    to_change->second=max(it->second,src.Interval.second);
                it=intervals.erase(it);

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

CRangeList CRangeList::operator -( const CRange  inter){




    auto it=lower_bound(intervals.begin(),intervals.end(),inter.Interval, cmp_include);

    interval tmp23;
    if(it==intervals.end()){

        return *this;
    }
    if(intersection(CRange(it->first,it->second),inter)) {
        CRangeList tmp = CRange(it->first, it->second) - inter;

        switch (tmp.intervals.size()) {
            case 1:
                *it = tmp.intervals[0];
                it++;
                break;
            case 2:
                *it = tmp.intervals[0];
                it = intervals.insert(++it, tmp.intervals[1]);

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