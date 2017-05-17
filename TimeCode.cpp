/* 
 * File:   TimeCode.cpp
 * Author: Benjamin Dickson
 * Info:   Please see header file
 */


#include "TimeCode.h"


/*
 * values below are required for date calculation
 */
const int TimeCode::MONTH_DAYS[] = {31,28,31,30,31,30,31,31,30,31,30,31};
const unsigned int TimeCode::SECONDS_IN_MINUTE = 60;
const unsigned int TimeCode::MINUTES_IN_HOUR = 60;
const unsigned int TimeCode::HOURS_IN_DAY = 24;
const unsigned int TimeCode::DAYS_IN_YEAR = 365;
const unsigned int TimeCode::YEAR_ZERO = 2000;
const unsigned int TimeCode::MONTH_COUNT = 12;
const unsigned int TimeCode::FEBRUARY = 1;

// TimeCode constructors

// blank constructor
TimeCode::TimeCode()
{
    this->day = 0;
    this->month = 0;
    this->second = 0;
    this->hour = 0;
    this->minute = 0;
    this->year=0;
}

// constructor from string value
// I wrote this constructor before reading that stream input was required in
// the coursework, but as the code was already written I left it in
TimeCode::TimeCode(string timeStamp)
{
    // format dd/mm/yyyyTHH:MM:SSZ
    // dd = days
    // mm = months
    // yyyy = year
    // HH = hours
    // MM = minutes
    // SS = seconds
    // because this is a fixed format, we can just grab the string positions
    
    unsigned int t_day = stoi(timeStamp.substr(0,2));
    unsigned int t_month = stoi(timeStamp.substr(3,2));
    unsigned int t_year = stoi(timeStamp.substr(6,4));
    unsigned int t_hour = stoi(timeStamp.substr(11,2));
    unsigned int t_minute = stoi(timeStamp.substr(14,2));
    unsigned int t_second = stoi(timeStamp.substr(17,2));
    
    TimeCode(t_year,t_month,t_day,t_hour,t_minute,t_second);
    
};

// constructor from unsigned long (reverse engineers to date)
TimeCode::TimeCode(unsigned long timeCodeInt)
{
    fromNumeric(timeCodeInt);
};

// constructor from Y,M,D,h,m,s values
TimeCode::TimeCode(unsigned int Y,unsigned int M,unsigned int D,unsigned int h,
        unsigned int m,unsigned int s)
{
    // checks for a valid date
    // unsigned ints means lower bound check
    if(
        Y>=YEAR_ZERO
        &&
        M>0 && M<=MONTH_COUNT
        &&
        D>0
        &&
        (
            isLeapYear(Y)&&M==FEBRUARY
            ?
            D<=MONTH_DAYS[FEBRUARY]+1
            :
            D<=MONTH_DAYS[M-1]
        )
        &&
        h<HOURS_IN_DAY
        &&
        m<MINUTES_IN_HOUR
        &&
        s<SECONDS_IN_MINUTE
    )
    {
        this->year = Y;
        this->month = M;
        this->day = D;
        this->hour = h;
        this->minute = m;
        this->second = s;
    }
    else
    {
        this->year = 0;
        this->month = 0;
        this->day = 0;
        this->hour = 0;
        this->minute = 0;
        this->second = 0;
    }
}


/**
 * TimeCode::isLeapYear(int testYear)
 * 
 * leap year checker
 * 
 * @param testYear - integer of year being tested
 * @return true if testYear is a leap year, false if not
 */
bool TimeCode::isLeapYear(int testYear)
{
    if(testYear%4!=0)
    {
        return false;
    }
    if(testYear%100!=0)
    {
        return true;
    }
    return (testYear%400==0);
};

/**
 * TimeCode::yearLength(int lYear)
 * 
 * @param lYear - int of year
 * @return integer of number days in the year
 */
unsigned int TimeCode::yearLength(int lYear)
{
    if(isLeapYear(lYear))
    {
        return DAYS_IN_YEAR + 1;
    }
    return DAYS_IN_YEAR;
}

/**
 * @param dYear
 * @param dMonth
 * @param dDay
 * @return number of days into the year for specified date
 */
unsigned int TimeCode::dayOfYear(int dYear, int dMonth, int dDay)
{
    dMonth--;
    unsigned int r = dDay;
    
    int m = 0;
    while(m++<dMonth)
    {
        r += MONTH_DAYS[m-1];
    }
    
    
    if(dMonth>FEBRUARY&&isLeapYear(dYear))
    {
        r += 1;
    }
    return r;
};

/**
 * 
 * @return  long representation of the time as number of seconds that have
 *          passed since January 1st YEAR_ZERO
 */
unsigned long TimeCode::toNumeric() const
{
    unsigned long r = 0;
    
    if(this->year<YEAR_ZERO)
    {
        // this is a problem, throw an error!
        // but the coursework doesn't have any dates prior to 2000 so isn't
        // necessary for this task
        return r;
    }
    
    unsigned int relativeYear = this->year - YEAR_ZERO;
    unsigned int iYear = 0;
    while(iYear<relativeYear)
    {
        r += DAYS_IN_YEAR;
        if(isLeapYear(iYear))
        {
            r += 1;
        }
        iYear++;
    }
    r += dayOfYear(this->year,this->month,this->day);
    
    r *= HOURS_IN_DAY;
    r += this->hour;
    
    r *= MINUTES_IN_HOUR;
    r += this->minute;
    
    r *= SECONDS_IN_MINUTE;
    r += this->second;
    
    return r;
};

/**
 * imports a time from an unsigned long int showing seconds since YEAR_ZERO
 * @param timeCodeInt
 */
void TimeCode::fromNumeric(unsigned long timeCodeInt)
{
    unsigned long interval = SECONDS_IN_MINUTE * MINUTES_IN_HOUR * HOURS_IN_DAY;
    
    // calculate number of whole days 
    unsigned long dayCount = timeCodeInt / interval;
    
    // remaining time has HH:MM:SS which are consistent so easy to determine
    timeCodeInt %= interval;
    interval /= HOURS_IN_DAY;
    
    this->hour = timeCodeInt / interval;
    
    timeCodeInt %= interval;
    interval /= MINUTES_IN_HOUR;
    
    this->minute = timeCodeInt / interval;
    
    timeCodeInt %= interval;
    interval /= SECONDS_IN_MINUTE;
    
    this->second = timeCodeInt / interval;
    
    // now we need to get the number of years:
    unsigned int tYear = YEAR_ZERO;
    
    while(dayCount>yearLength(tYear))
    {
        dayCount -= yearLength(tYear);
        tYear += 1;
    }
    this->year = tYear;
    
    // now months and days, made ugly by inconsistent month-day pattern
    unsigned int tMonth = 0;
    unsigned int tFeb = MONTH_DAYS[FEBRUARY] + (isLeapYear(tYear)?1:0);
    
    while(dayCount>(tMonth==FEBRUARY?tFeb:MONTH_DAYS[tMonth]))
    {
        dayCount -= (tMonth==FEBRUARY?tFeb:MONTH_DAYS[tMonth]);
        tMonth+=1;
    }
    
    this->month = tMonth+1;
    this->day = dayCount;
}