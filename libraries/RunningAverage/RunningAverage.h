//
//    FILE: RunningAverage.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.04
// PURPOSE: RunningAverage library for Arduino
//
// The library stores the last N individual values in a circular buffer,
// to calculate the running average.
//
// HISTORY:
// 0.1.00 - 2011-01-30 initial version
// 0.1.01 - 2011-02-28 fixed missing destructor in .h
// 0.2.00 - 2012-??-?? Yuval Naveh added trimValue (found on web)
//          http://stromputer.googlecode.com/svn-history/r74/trunk/Arduino/Libraries/RunningAverage/RunningAverage.cpp
// 0.2.01 - 2012-11-21 refactored
// 0.2.02 - 2012-12-30 refactored trimValue -> fillValue
// 0.2.03 - 2013-11-31 getElement
// 0.2.04 - 2014-07-03 added memory protection
//
// Released to the public domain
//


#ifndef RunningAverage_h
#define RunningAverage_h
//
//    FILE: RunningAverage.h
//  AUTHOR: Rob dot Tillaart at gmail dot com
// PURPOSE: RunningAverage library for Arduino
//     URL: http://arduino.cc/playground/Main/RunningAverage
// HISTORY: See RunningAverage.cpp
//
// Released to the public domain
//

// backwards compatibility
// clr() clear()
// add(x) addValue(x)
// avg() getAverage()

#define RUNNINGAVERAGE_LIB_VERSION "0.2.04"

#include "Arduino.h"

class RunningAverage
{
public:
    RunningAverage(void);
    RunningAverage(int);
    ~RunningAverage();

    void clear();
    void addValue(float);
    void fillValue(float, int);

    float getAverage();

    float getElement(uint8_t idx);
    uint8_t getSize() { return _size; }
    uint8_t getCount() { return _cnt; }

protected:
    uint8_t _size;
    uint8_t _cnt;
    uint8_t _idx;
    float   _sum;
    float * _ar;
};

#endif
// END OF FILE
