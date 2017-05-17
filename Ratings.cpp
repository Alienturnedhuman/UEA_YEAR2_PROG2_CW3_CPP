/* 
 * File:   Rating.cpp
 * Author: Benjamin Dickson
 * Info:   Please see header file
 */

#include "Ratings.h"
#include "Movie.h"



// constructors
RatingUser::RatingUser(string newName)
{
    name = newName;
}

Rating::Rating(TimeCode* newTimeStamp, RatingUser* newUser, Movie* newMovie 
            , unsigned int newRating , Ratings* rdb )
{
    timeStamp = newTimeStamp;
    user = newUser;
    movie = newMovie;
    rating = newRating;
    ratingsDB = rdb;
};

Ratings::Ratings()
{
    ratingsSum = 0;
    ratingsCount = 0;
    sortDescending = false;
}

Ratings::Ratings(MovieDatabase* parent)
{
    ratingsSum = 0;
    ratingsCount = 0;
    sortDescending = false;
    movies = parent;
}

/*
 * RatingUser::getName()
 * returns the name of the user as a string
 */
inline string RatingUser::getName()
{
    return name;
}

/*
 * RatingUser::addMovie(Movie* movie)
 * if the user has not already reviewed the film, then the it adds the movie
 * to be added, and returns true.
 * 
 * If the user has reviewed the film, it does not add the film and returns false
 */
bool RatingUser::addMovie(Movie* movie)
{
    int i = -1;
    int ii = reviewed.size();
    while(++i<ii)
    {
        if(reviewed[i] == movie)
        {
            return false;
        }
    }
    reviewed.push_back(movie);
    return true;
}

/*
 * Rating::getParent()
 * 
 * returns the parent Ratings database
 */
Ratings* Rating::getParent() const
{
    return ratingsDB;
}

/*
 * Rating::toString()
 * 
 * returns a string representation of the Rating
 */
string Rating::toString() const
{
    stringstream r;
    r << (*timeStamp) << ",\"" << user->getName() << "\",\"" << 
            movie->getTitle() << "\"," << rating;
    return r.str();
}

/*
 * Rating::getTimeStamp()
 * 
 * returns the timeStamp of the review as a TimeCode pointer
 */
TimeCode* Rating::getTimeStamp() const
{
    return timeStamp;
}

/*
 * Rating::getUser()
 *
 * returns the name of the user as a string
 */
string Rating::getUser() const
{
    return user->getName();
}

/*
 * Rating::getRating()
 *
 * returns an the rating score given as an unsigned integer
 */
unsigned int Rating::getRating() const
{
    return rating;
}

/*
 * Rating::getMovie()
 *
 * returns the movies the review is of as a pointer to a Movie
 */
Movie* Rating::getMovie() const
{
    return movie;
}


/*
 * Ratings::addRating(TimeCode* newTimeStamp, RatingUser* user, Movie* newMovie,
 *         unsigned int newRating)
 *
 * This attempts to add the review to a user. If success it updates the rest of
 * the database to take into account the new review.
 * 
 * It adds it to the Ratings Database, and updates the score of the Movie.
 */
bool Ratings::addRating(TimeCode* newTimeStamp, RatingUser* user, Movie* newMovie,
        unsigned int newRating)
{
    // At the moment I am prioritizing the movie that was added first in the CSV
    // list, however it would probably make sense to eventually upgrade this
    // system to take the newest movie chronologically , however that would 
    // add additional programming complexity, and as checking for existing
    // reviews was not a requirement listed in the task sheet, I feel that
    // this is already going a step further and showing the potential of
    // how I have chosen to set this up for being further expanded for future
    // features
    if(user->addMovie(newMovie))
    {
        Rating* tRating = new Rating(newTimeStamp,user,newMovie,newRating,this);
        ratings.push_back(tRating);
        MovieDatabaseLink::addRating(newRating , *newMovie);
        return true;
    }
    return false;
};

/*
 * RatingUser* Ratings::getUser(string user)
 *
 * A string of a username is put into this function. The function checks if
 * there is a user with this name. If there is, the RaitingUser pointer is
 * returned.
 * 
 * If there is not a user, a new RatingUser is created, appended to the vector
 * and the pointer to that RatingUser returned instead
 */
RatingUser* Ratings::getUser(string user)
{
    int i = -1;
    int ii = users.size();
    while(++i<ii)
    {
        if(users[i]->getName() == user)
        {
            return users[i];
        }
    }
    return addUser(user);
}

/*
 * RatingUser* Ratings::addUser(string user)
 *
 * Adds a user to the users vector in the Ratings class
 */
RatingUser* Ratings::addUser(string user)
{
    RatingUser* newUser = new RatingUser(user);
    users.push_back(newUser);
    return newUser;
};

/*
 * double Ratings::meanScore()
 * 
 * calculates the mean score of all of the reviews and returns as a double
 */
double Ratings::meanScore()
{
    return (double)ratingsSum/ratingsCount;
};

/*
 * float Ratings::medianScore()
 * 
 * calculates the median score of all the reviews and returns as a float
 * 
 * the reason for float is that it will always be .0 or .5 exactly, so double
 * precision is not required
 */
float Ratings::medianScore()
{
    if(ratingsCount==0)
    {
        return 0;
    }
    sortField = SortFields::rating;
    sortDescending = false;
    sortDatabase();
    
    bool isEven = (ratingsCount%2==0);
    
    int midPoint = (ratingsCount+1)/2;
    
    float median = (float)(ratings.at(midPoint)->rating);
    
    if(isEven)
    {
        median = (median+(float)(ratings.at(midPoint+1)->rating))/2;
    }
    return median;
    
};

/*
 * unsigned long Ratings::count() const
 * 
 * returns the number of all of the reviews.
 * 
 * unsigned long used in case this should become a big data database
 */
unsigned long Ratings::count() const
{
    return this->ratings.size();
};

/*
 * Ratings::sortDatabase()
 *
 * sorts the database according to the surrent settings
 */
void Ratings::sortDatabase()
{
    sort(ratings.begin(),ratings.end());
};

/*
 * Ratings::getSortField()
 *
 * returns the current sorting column for the data and returns the enum
 */
Ratings::SortFields Ratings::getSortField() const
{
    return sortField;
}

/*
 * Ratings::getSortDescendings()
 *
 * returns true if the database it set to sort descending.
 */
bool Ratings::getSortDescendings() const
{
    return sortDescending;
}

/**
 * Ratings::getIndex(int i)
 * 
 * returns the rating at position i in the database
 * 
 * @param i
 * @return Rating* pointer
 */
Rating* Ratings::getIndex(int i) const
{
    return ratings.at(i);
};

/**
 * Ratings::toString()
 * 
 * @return a string representation of the database
 */
string Ratings::toString()
{
    stringstream r;
    r << "Total number of ratings in database: " << count();
    return r.str();
}