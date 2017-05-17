/* 
 * File:   MovieDatabase.h
 * Author: Benjamin Dickson
 * Info:   A database for handling all of the movies
 * 
 * My Movie.h and MovieDatabase files are quite integrated, as the Movie class
 * refers back to its parents to determine how the database wishes it to be
 * compared to another movie (eg, by title, year, duration etc...)
 * 
 * comments for functions in cpp files
 */

#ifndef MOVIEDATABASE_H
#define MOVIEDATABASE_H

#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <sstream>

using namespace std;

#include "Ratings.h"
#include "Movie.h"
class MovieDatabase
{
public:
    enum SortFields{title,year,certificate,genre,duration,average_rating
        ,review_count,title_length};
private:
    std::vector<string> titles;
    std::vector<Movie*> movies;
    
    
    std::vector<MovieCertificate*> certificates;
    std::vector<MovieGenre*> genres;
    
    SortFields sortField;
    bool sortDesc;
    
    Ratings* ratingsDB;

    
public:
    friend class MovieDatabase;
    bool addMovie(Movie* newMovie);
    bool addMovie(stringstream &CSVlinestream);
    
    
    bool hasMovie(string title);
    Movie* getMovie(string title);
    
    Movie* getIndex(int i) const;
    
    void setSortField(SortFields newField);
    void setSortDescending(bool desc);
    
    SortFields getSortField() const;
    bool getSortDescending() const;
    
    void sortDatabase(SortFields field,bool desc);
    Movie* extreme(SortFields field,bool desc);
    
    MovieCertificate* getCert(string certStr);
    MovieGenre* getGenre(string genreStr);
    
    Ratings* ioRatings();
    
    MovieDatabase* genreList(MovieGenre* findGenre);
    
    long count() const;
    
    string movieString(Movie& mp) const;
    
    MovieDatabase();
    
};


inline std::ifstream& operator>>(ifstream &is, MovieDatabase& mdb)
{
    string lineString;
    while(getline(is,lineString))
    {
        stringstream lineStream(lineString);
        mdb.addMovie(lineStream);
    }
    cout << "\n" << mdb.count() <<  "MOVIES IMPORTED!!!\n\n";
    return is;
}

inline std::ofstream& operator<<(std::ofstream &os, const MovieDatabase& mdb)
{
    int ii = mdb.count();
    if(ii<1)
    {
        return os;
    }
        
   os << mdb.movieString(*mdb.getIndex(0));
   int i = 0;
   while(++i<ii)
   {
       os << "\r\n" << mdb.movieString(*mdb.getIndex(i));
   }
   return os;
}


inline std::ostream& operator<<(std::ostream &os, const MovieDatabase& mdb)
{
    int ii = mdb.count();
    if(ii<1)
    {
        return os;
    }
        
   os << mdb.movieString(*mdb.getIndex(0));
   int i = 0;
   while(++i<ii)
   {
       os << "\r\n" << mdb.movieString(*mdb.getIndex(i));
   }
   return os;
}
#endif /* MOVIEDATABASE_H */
