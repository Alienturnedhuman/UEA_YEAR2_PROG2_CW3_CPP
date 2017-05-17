/* 
 * File:   Movie.h
 * Author: Benjamin Dickson
 * Info:   A class containing a single movie
 * 
 * My Movie.h and MovieDatabase files are quite integrated, as the Movie class
 * refers back to its parents to determine how the database wishes it to be
 * compared to another movie (eg, by title, year, duration etc...)
 * 
 * comments for functions in cpp files
 */

#ifndef MOVIE_H
#define MOVIE_H

#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

#include "MovieMisc.h"
//class MovieDatabase;

class Movie
{
private:
    string title;
    unsigned int year;
    MovieCertificate* cert;
    vector<MovieGenre*> genre;
    unsigned int duration;
    
    MovieDatabase* parent;
    
    unsigned int reviewCount;
    unsigned int reviewPoints;
public:
    friend class MovieDatabase;
    friend class Movie;
    
    // constructors / deconstructors
    MovieDatabase* ioDatabase();
    Movie();
    Movie(Movie* cloneMovie, MovieDatabase* newParent);
    Movie(MovieDatabase* newParent);
    
    // setters
    void setParent(MovieDatabase* newParent);
    void setCert(MovieCertificate* newCert);
    void setCert(string newCertName);
    void setTitle(string newTitle);
    void setYear(unsigned int newYear);
    void setDuration(unsigned int newDuration);
    void addGenre(MovieGenre* newGenre);
    void addGenre(string newGenreName);
    void removeGenre(MovieGenre* oldGenre);
    void setReviewCount(unsigned int newReviewCount);
    void setReviewPoints(unsigned int newReviewPoints);
    void setReviewAverage(double newReviewAverage);
    void addScore(int score);
    
    
    
    // getters
    MovieDatabase* getParent() const;
    string getCert() const;
    string getTitle() const;
    unsigned int getYear() const;
    unsigned int getDuration() const;
    bool hasGenre(MovieGenre* findGenre);
    string getGenresStr() const;
    int getGenreCount() const;
    unsigned int getReviewCount() const;
    double getAverageScore() const;
    
    
    
};




inline std::ostream& operator<<(ostream &os, Movie &m)
{
    return os << '"' << m.getTitle() << '"' << ',' << m.getYear() << ',' <<
            '"' << m.getCert() << '"' << ',' << '"' << m.getGenresStr() <<
            '"' << ',' << m.getDuration() << ',' << m.getAverageScore() <<
            ',' << m.getReviewCount();
};

inline std::stringstream& operator>>(stringstream &is, Movie* m)
{
// "The Gold Rush",1925,"NOT RATED","Adventure/Comedy/Drama",95,0,0
// "<title>",<year>,"<certificate>","<genre>/<genre>/...",<duration>,
//      <average_review>,<review_count>
   
    string discard;
    string streamTitle,streamYear,streamCert,streamGenres,streamDuration;
    string streamAverageReview,streamReviewCount;
    
    // discard everything until first "
    getline(is,discard,'"');
    
    // title is everything until next "
    getline(is,streamTitle,'"');
    
    // proceed to comma
    getline(is,discard,',');
    
    // year is everything until next comma
    getline(is,streamYear,',');
    
    // discard everything until next "
    getline(is,discard,'"');
    
    // certificate is everything until next "
    getline(is,streamCert,'"');
    
    // discard everything until next "
    getline(is,discard,'"');
    
    // genres are everything until next "
    getline(is,streamGenres,'"');
    
    // proceed to comma
    getline(is,discard,',');
    
    // duration is everything until next comma
    getline(is,streamDuration,',');
    
    // average review is everything until next comma
    getline(is,streamAverageReview,',');
    
    // review count is everything left
    getline(is,streamReviewCount);
    
    // add the title as this is string
    m->setTitle(streamTitle);
    
    
    // add the ones that are just numbers (cast of unsigned int)
    m->setYear((unsigned int)stoi(streamYear));
    m->setDuration((unsigned int)stoi(streamDuration));
    m->setReviewCount((unsigned int)stoi(streamReviewCount));
    
    m->setReviewAverage(stod(streamAverageReview));
    // add the certificate
    m->setCert(streamCert);
    
    
    // add the genres
    stringstream ssGenres(streamGenres);
    string streamGenre;
    
    while(ssGenres)
    {
        getline(ssGenres,streamGenre,'/');
        m->addGenre(streamGenre);
        //m.addGenre((m.ioDatabase())->getGenre(streamGenre));
    }
   
   return is;
};



inline bool operator<(const Movie &a, const Movie &b)
{
    return CompareHandler::movieLT(a,b,*a.getParent());
}
inline bool operator>(const Movie &a, const Movie &b)
{
    return CompareHandler::movieGT(a,b,*a.getParent());
}
inline bool operator==(const Movie &a, const Movie &b)
{
    return CompareHandler::movieEQ(a,b,*a.getParent());
}
inline bool operator!=(const Movie &a, const Movie &b)
{
    return !CompareHandler::movieEQ(a,b,*a.getParent());
}
inline bool operator<=(const Movie &a, const Movie &b)
{
    return !CompareHandler::movieGT(a,b,*a.getParent());
}
inline bool operator>=(const Movie &a, const Movie &b)
{
    return !CompareHandler::movieLT(a,b,*a.getParent());
}



#endif /* MOVIE_H */
