/* 
 * File:   MovieMisc.h
 * Author: Benjamin Dickson
 *
 * This file was created for handle exchanges between classes that did not
 * yet have access to all of the properties of each other. While I may have
 * solved this problem later on with restructuring my code, it was too late
 * to go back and try again without it, and I needed to submit something that
 * worked.
 * 
 * I had a lot of problems stemming from the fact that Movie and MovieDatabase
 * needed to access methods from each other, so the purpose of this was to
 * try and rectify that, while keeping the coursework's requirement to have
 * separate C files for Movie and MovieDatabase (having them in one would
 * have solved most of this)
 * 
 * Created on April 27, 2017, 11:58 AM
 */

#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <sstream>

#ifndef MOVIEMISC_H
#define MOVIEMISC_H

class Rating;
class Ratings;
class Movie;
class MovieDatabase;

using namespace std;
// small number of MovieCertificate types, so seems logical to have one
// place to store the data. Also, if a certificate gets rebranded (like X to 18)
// then it's just one change to affect all movies using that rating

/*
 * My reason for using classes, is that this allows for a fluid, self updating
 * system (ie, an unknow Certificate is found, the system will create a new 
 * Certificate class for it.
 * 
 * Also, it could be upgraded to have a list of pointers to movies containing
 * this genre, to create a relational database, in the future - if the speed
 * increase warranted it for the purposes required
 * 
 * This same reasoning applied for the MovieGenre class below
 */
class MovieCertificate
{
private:
    string name;
public:
    string toString() const
    {
        return name;
    };
    MovieCertificate(string newName)
    {
        name = newName;
    };
};


inline bool operator==(const MovieCertificate &a, const string &b)
{
    return (a.toString()) == b;
}
inline bool operator!=(const MovieCertificate &a, const string &b)
{
    return !(a == b);
}

// MovieGenre code - see notes on MovieCertificate above
class MovieGenre
{
private:
    string name;
public:
    string toString() const
    {
        return name;
    };
    MovieGenre(string newName)
    {
        name = newName;
    };
};


inline bool operator==(const MovieGenre &a, const string &b)
{
    return (a.toString()) == b;
}
inline bool operator!=(const MovieGenre &a, const string &b)
{
    return !(a == b);
}

/*
 * This was created to allow Movies to be compared based on the settings of the
 * parent database
 */
 class CompareHandler
 {
 public:
    static bool movieLT(const Movie &a, const Movie &b, const MovieDatabase &c);
    static bool movieGT(const Movie &a, const Movie &b, const MovieDatabase &c);
    static bool movieEQ(const Movie &a, const Movie &b, const MovieDatabase &c);
    static bool ratingLT(const Rating &a , const Rating &b , const Ratings &c);
    static bool ratingGT(const Rating &a , const Rating &b , const Ratings &c);
    static bool ratingEQ(const Rating &a , const Rating &b , const Ratings &c);
 };

 /*
  * This was created to allow Rating / Movie / MovieDatabse classes to
  * connect with each other
  */
 class MovieDatabaseLink
 {
 public:
     static MovieCertificate* getCert(string certStr , MovieDatabase &mdb);
     static MovieGenre* getGenre(string certStr , MovieDatabase &mdb);
     static void addRating(int score , Movie &m);
 };
 

#endif /* MOVIEMISC_H */
