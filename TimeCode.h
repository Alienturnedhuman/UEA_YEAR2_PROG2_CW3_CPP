/* 
 * File:   TimeCode.h
 * Author: Benjamin Dickson
 * Info:   A class for handling Timestamps in the ratings.txt file
 * 
 * Notes - it was my understanding we were not permitted to use standard
 * library time handling classes, as that would defeat the point of writing
 * our own TimeCode class - so this is why I have not used any, as I do
 * realise they would have made my life a lot easier as I could just use
 * standard library functions for converting to UNIX time rather than
 * writing my own code to gets number of seconds since Jan 1st 2000
 * 
 * comments for functions in cpp files
 */

#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <sstream>

#ifndef TIMESTAMP_H
#define TIMESTAMP_H
using namespace std;
class TimeCode
{
private:
    unsigned int year,month,day,hour,minute,second,nsecond;  // all of the units
    
    // required for converting date into numeric comparison value
    const static unsigned int SECONDS_IN_MINUTE;
    const static unsigned int MINUTES_IN_HOUR;
    const static unsigned int HOURS_IN_DAY;
    const static unsigned int DAYS_IN_YEAR;
    const static unsigned int YEAR_ZERO;

    const static unsigned int MONTH_COUNT;
    const static unsigned int FEBRUARY; // February index
    
    const static int MONTH_DAYS[];
     
    static bool isLeapYear(int testYear);
    static unsigned int dayOfYear(int dYear, int dMonth, int dDay);
    static unsigned int yearLength(int lYear);
    
public:
    // list of getters:
    unsigned int getYear() const
    {
        return this->year;
    };
    unsigned int getMonth() const
    {
        return this->month;
    };
    unsigned int getDay() const
    {
        return this->day;
    };
    unsigned int getHour() const
    {
        return this->hour;
    };
    unsigned int getMinute() const
    {
        return this->minute;
    };
    unsigned int getSecond() const
    {
        return this->second;
    };
    unsigned long toNumeric() const;
    
    void fromNumeric(unsigned long timeCodeInt);
    static unsigned int getYearZero()
    {
        return YEAR_ZERO;
    }
    
    // constructor
    TimeCode();
    TimeCode(string timeStamp);
    TimeCode(unsigned long timeCodeInt);
    TimeCode(unsigned int Y,unsigned int M, unsigned int D, unsigned int h,
    unsigned int m,unsigned  int s);
    
    // operators
    inline TimeCode& operator+=(const TimeCode &a);
    inline TimeCode& operator+=(unsigned int a);
    inline TimeCode& operator++();
    inline TimeCode& operator++(int);
};


/*
 *  Comparison operators below (straight forwards)
 */

inline bool operator<(const TimeCode &a, const TimeCode &b)
{
    return a.toNumeric() < b.toNumeric();
}
inline bool operator>(const TimeCode &a, const TimeCode &b)
{
    return a.toNumeric() > b.toNumeric();
}
inline bool operator==(const TimeCode &a, const TimeCode &b)
{
    return a.toNumeric() == b.toNumeric();
}
inline bool operator!=(const TimeCode &a, const TimeCode &b)
{
    return !(a==b);
}
inline bool operator<=(const TimeCode &a, const TimeCode &b)
{
    return !(a>b);
}
inline bool operator>=(const TimeCode &a, const TimeCode &b)
{
    return !(a<b);
}



/*
 *  Mathematical operators below
 * Done for the purposes of coursework, but little real practicality as
 * Year zero (even in a gregorian calendar) is arbitrary.
 * While it is useful to be able to add 5 days, or 2 months and 4 hours to do
 * this, any TimeCode object (no matter where you set Year Zero) is actually
 * the length of time to have passed since year zero. So while there is a 
 * practical bonus of exploiting this system to add a small interval of time
 * to an existing TimeCode object, it makes little semnatic sense from a 
 * programming point of view.
 * 
 * Consequently, someone could have a TimeCode that was generated for 5/1/2000 
 * and it is the same thing as a 5 days unit of time to increment a day.
 * 
 * It would make more sense to have a TimeCodeInverval class used for this 
 * purpose so TimeCodes used for dates can't accidentally be used for addition.
 * 
 * What I am trying to say, is I understand that this is needed for the
 * coursework, to demonstrate the knowledge of operator overloading, I just
 * don't think it's a good idea in practice.
 * 
 * For the increments of integers, I am going to assume people will want to
 * increment by one day.
 */

inline TimeCode operator+(const TimeCode &a, const TimeCode &b)
{
    return TimeCode(a.toNumeric() + b.toNumeric());
}

inline TimeCode operator+(const TimeCode &a, const int b)
{
    return TimeCode(a.toNumeric() + 
            TimeCode(a.getYearZero(),1,(unsigned int)b,0,0,0).toNumeric());
}


inline TimeCode& TimeCode::operator+=(const TimeCode &a)
{
    unsigned long b = this->toNumeric();
    this->fromNumeric(b+a.toNumeric());
    return *this;
}
inline TimeCode& TimeCode::operator+=(unsigned int a)
{
    unsigned long b = this->toNumeric();
    this->fromNumeric(b + TimeCode(this->getYearZero(),1,(unsigned int)a,0,0,0).toNumeric());
    return *this;
}
inline TimeCode& TimeCode::operator++()
{
    return (*this+=1);
}

inline TimeCode& TimeCode::operator++(int)
{
    TimeCode* returnVal = new TimeCode(this->toNumeric());
    (*this)+=1;
    return *returnVal;
}




inline std::ostream& operator<<(std::ostream &os, const TimeCode &t)
{
    // format dd/mm/yyyyTHH:MM:SSZ
   return os << std::setw(2) << std::setfill('0') << t.getDay()   << "/" 
             << std::setw(2) << std::setfill('0') << t.getMonth()   << "/" 
             << std::setw(4) << std::setfill('0') << t.getYear()   << "T" 
             << std::setw(2) << std::setfill('0') << t.getHour() << ":"
             << std::setw(2) << std::setfill('0') << t.getMinute() << ":"
             << std::setw(2) << std::setfill('0') << t.getSecond() << "Z";
}    

inline std::stringstream& operator>>(stringstream &is, TimeCode &t)
{
    // format dd/mm/yyyyTHH:MM:SSZ
   string year, month, day,hour,minute,second;  
   
   getline(is,day,'/');
   getline(is,month,'/');
   getline(is,year,'T');
   getline(is,hour,':');
   getline(is,minute,':');
   getline(is,second,'Z');
   
   t = TimeCode((unsigned int)stoi(year),(unsigned int)stoi(month),(unsigned int)stoi(day),
            (unsigned int)stoi(hour),(unsigned int)stoi(minute),(unsigned int)stoi(second));
   
   return is;
}
#endif /* TIMESTAMP_H */
