/* 
 * File:   Rating.h
 * Author: Benjamin Dickson
 * Info:   A class for handling the Ratings
 *         This is an object handling all of the ratings for a movie, contained
 *         within that movie object
 * 
 * comments for functions in cpp files
 */

#ifndef RATING_H
#define RATING_H


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
#include "TimeCode.h"
#include "Movie.h"

class MovieDatabase;
class Movie;
class Ratings;

/**
 * RatingUser
 * 
 * This class contains a user name and list of pointers to movies they have
 * reviewed. This means that duplicate reviews from them can be discarded (or
 * replaced)
 * 
 *  name - string of user's name
 *  reviewed - collecting of pointers to movies reviewed by the user
 */
class RatingUser
{
private:
    string name;
    vector<Movie*> reviewed;
public:
    inline string getName();
    bool addMovie(Movie* movie);
    RatingUser(string newName);
};





/**
 * Rating
 * 
 * This class contains the information of a specific rating:
 * 
 * timeStamp - TimeCode that the review was posted
 * user - RatingUser for recording the user
 * rating - unsigned int for the score assigned
 * movie - pointer to the movie
 */

class Rating
{
private:
    TimeCode* timeStamp;
    RatingUser* user;
    unsigned int rating;  
    Movie* movie;
    Ratings* ratingsDB;
public:
    friend class Ratings;
    Ratings* getParent() const;
    string toString() const;
    TimeCode* getTimeStamp() const;
    string getUser() const;
    unsigned int getRating() const;
    Movie* getMovie() const;
    
    Rating(TimeCode* newTimeStamp, RatingUser* newUser, Movie* newMovie 
            , unsigned int newRating , Ratings* rdb);
};


inline std::ostream& operator<<(std::ostream &os, const Rating &r)
{
    os << *(r.getTimeStamp());
    os << ',' << '"' << r.getUser() << '"' << ',' 
            << '"' << r.getMovie()->getTitle() << '"' << ',' << r.getRating();
    return os;
}


inline bool operator<(const Rating &a, const Rating &b)
{
    return CompareHandler::ratingLT(a,b,*a.getParent());
}
inline bool operator>(const Rating &a, const Rating &b)
{
    return CompareHandler::ratingGT(a,b,*a.getParent());
}
inline bool operator==(const Rating &a, const Rating &b)
{
    return CompareHandler::ratingEQ(a,b,*a.getParent());
}
inline bool operator!=(const Rating &a, const Rating &b)
{
    return !CompareHandler::ratingEQ(a,b,*a.getParent());
}
inline bool operator<=(const Rating &a, const Rating &b)
{
    return !CompareHandler::ratingGT(a,b,*a.getParent());
}
inline bool operator>=(const Rating &a, const Rating &b)
{
    return !CompareHandler::ratingLT(a,b,*a.getParent());
}



/**
 * Ratings
 * 
 * This class is a database of all of the ratings.
 * 
 * it can be interrogated to sort ratings by different fields and extract
 * information.
 */
class Ratings
{
public:
    enum SortFields{chronological,user,movie,rating};
private:
    // vector of ratings
    vector<Rating*> ratings;
    
    // vector of existing users (will be quicker to search this to check if
    // user has already added a review
    vector<RatingUser*> users;
    
    
    // these values are used for quickly retrieving the average score
    // done as long in case we ever become bigger than IMDB
    unsigned long ratingsSum;
    unsigned long ratingsCount;
    SortFields sortField;
    bool sortDescending;
    
    MovieDatabase* movies;
    
public:
    // constructor
    Ratings();
    Ratings(MovieDatabase* parent);
    
    // true if added, false if not added
    bool addRating(TimeCode* newTimeStamp, RatingUser* user, Movie* newMovie,
            unsigned int newRating);
    bool addRating(stringstream &rStream);
    
    RatingUser* getUser(string user);
    RatingUser* addUser(string user);
    
    double meanScore();
    float medianScore();
    
    // returns number of reviews
    unsigned long count() const;
    
    void sortDatabase();
    void sortDatabase(SortFields field,bool sortDesc);
    SortFields getSortField() const;
    bool getSortDescendings() const;
    
    Rating* getIndex(int i) const;
    
    
    // to String summary of ratings
    string toString();
};


inline std::ifstream& operator>>(ifstream &is, Ratings& rdb)
{
    string lineString;
    bool addCheck;
    unsigned int rejectCount=0;
    while(getline(is,lineString))
    {
        stringstream lineStream(lineString);
        addCheck = rdb.addRating(lineStream);
        if(!addCheck)
        {
            rejectCount++;
        }
    }
    
    
    // I have left this line in to highlight that I am rejecting duplicate
    // ratings. It was not specified as a requirement in the coursework,
    // however, I feel it was a reasonable assumption to have made, and I
    // discovered 26 duplicate reviewed by user: "Gerald Anstruther Vail"
    // so my scores do not include these in the final tallies.
    
    // if it was not intended to discard these 26 reviews, then my tallies will
    // be different (for everything relating to ratings)
    cout << "\n\nRatings added: " << rdb.count() << 
            "\nDuplicate Ratings Rejected: " << rejectCount << "\n\n";
    
    
    return is;
}


inline std::ofstream& operator<<(std::ofstream &os, const Ratings &rdb)
{
    int ii = rdb.count();
    if(ii<1)
    {
        return os;
    }
        
   os << rdb.getIndex(0);
   int i = 0;
   while(++i<ii)
   {
       os << "\r\n" << rdb.getIndex(i);
   }
   return os;
}





#endif /* RATING_H */
