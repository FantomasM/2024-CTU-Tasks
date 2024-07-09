//
// Created by fantomasm on 09/07/24.
//

#ifndef CRANGE_H
#define CRANGE_H
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
using interval =pair<long long,long long>;
class CRange
{
public:
    // constructor
    CRange(long long first, long long second);
    CRange(long long first);
    CRange & operator = ( const CRange & second);

    interval Interval;
    ;

private:

};
#endif //CRANGE_H
