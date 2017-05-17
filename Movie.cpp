/* 
 * File:   Movie.cpp
 * Author: Benjamin Dickson
 * Info:   Please see header file
 */

#include "Movie.h"

/**
 * Constructor for cloning a movie for use in a different database
 * @param cloneMovie
 * @param newParent
 */
Movie::Movie(Movie* cloneMovie,MovieDatabase* newParent)
{
    this->parent = newParent;
    this->setTitle(cloneMovie->getTitle());
    this->setCert(cloneMovie->getCert());
    this->setYear(cloneMovie->getYear());
    this->setDuration(cloneMovie->getDuration());
    this->setReviewCount(cloneMovie->getReviewCount());
    this->setReviewAverage(cloneMovie->getAverageScore());
    
    int i=0;
    int ii = cloneMovie->getGenreCount();
    while(++i<ii)
    {
        this->addGenre(cloneMovie->genre[i]);
    }
};

/**
 * Creates a new movie with a pointer to its parent
 * @param newParent
 */
Movie::Movie(MovieDatabase* newParent)
{
    this->parent = newParent;
};

/**
 * sets the parent database of a Movie
 * @param newParent
 */
void Movie::setParent(MovieDatabase* newParent)
{
    this->parent = newParent;
};

/**
 * returns a pointer to the parent MovieDatabase
 * @return 
 */
MovieDatabase* Movie::getParent() const
{
    return parent;
};

/**
 * returns a string of the movie certificate
 * @return 
 */
string Movie::getCert() const
{
    return this->cert->toString();
};

/**
 * sets the certifcate to the pointer provided
 * @param newCert
 */
void Movie::setCert(MovieCertificate* newCert)
{
    this->cert = newCert;
};

/**
 * takes a string, and gets a MovieCertificate point from the parent database
 * @param newCertName
 */
void Movie::setCert(string newCertName)
{
    this->setCert(MovieDatabaseLink::getCert(newCertName,*(this->getParent())));
    
};


/**
 * Getters and setters below - will not detail where obvious
 * @param newTitle
 */
void Movie::setTitle(string newTitle)
{
    this->title = newTitle;
};
string Movie::getTitle() const
{
    return this->title;
};





void Movie::setYear(unsigned int newYear)
{
    this->year = newYear;
};
unsigned int Movie::getYear() const
{
    return this->year;
};



void Movie::setDuration(unsigned int newDuration)
{
    this->duration = newDuration;
};
unsigned int Movie::getDuration() const
{
    return this->duration;
};



/**
 * adds a genre to the vector of genres
 * @param newGenre
 */
void Movie::addGenre(MovieGenre* newGenre)
{
    if(!hasGenre(newGenre))
    {
        (this->genre).push_back(newGenre);
    }
};
/**
 * takes a string, and passes it to the parent moviedatabase to get a pointer
 * for the certificate (the parent will create a new certificate if it a new
 * type)
 * @param newGenreName
 */
void Movie::addGenre(string newGenreName)
{
    this->addGenre(MovieDatabaseLink::getGenre(newGenreName,*(this->getParent())));
};
/**
 * removes a genre from  the vector of genres
 * @param oldGenre
 */
void Movie::removeGenre(MovieGenre* oldGenre)
{
    int i = this->genre.size();
    while((i--)>-1)
    {
        if(this->genre[i] == oldGenre)
        {
            (this->genre).erase((this->genre).begin()+i);
        }
    }
};
/**
 * checks if a movie has a genre
 * @param findGenre
 * @return 
 */
bool Movie::hasGenre(MovieGenre* findGenre)
{
    int i = -1;
    int ii = genre.size();
    while(++i<ii)
    {
        if(genre[i]==findGenre)
        {
            return true;
        }
    }
    return false;
}
/**
 * returns the list of genres as a '/' delimited string
 * @return 
 */
string Movie::getGenresStr() const
{
    int total = this->genre.size();
    if(total==0)
    {
        return "";
    };
    stringstream rStream;
    rStream << this->genre[0]->toString();
    if(total>1)
    {
        int i = 0;
        while(++i<total)
        {
            rStream << '/' << this->genre[i]->toString();
        };
    };
    return rStream.str();
};
/**
 * returns the number of genres a movie has
 * @return 
 */
int Movie::getGenreCount() const
{
    return genre.size();
};



/**
 * sets the number of rating reviews
 * @param newReviewCount
 */
void Movie::setReviewCount(unsigned int newReviewCount)
{
    this->reviewCount = newReviewCount;
};
/**
 * sets the sum of all of the points
 * @param newReviewPoints
 */
void Movie::setReviewPoints(unsigned int newReviewPoints)
{
    this->reviewPoints = newReviewPoints;
};

/**
 * sets the total points based on an average and the number of reviews
 * @param newReviewAverage
 */
void Movie::setReviewAverage(double newReviewAverage)
{
    this->reviewPoints = (unsigned int)(0.5 + (newReviewAverage * 
            this->reviewCount));
};

/**
 * adds a review score to the movie
 * @param score
 */
void Movie::addScore(int score)
{
    this->reviewPoints += score;
    this->reviewCount++;
}



/**
 * returns the average score
 * @return 
 */
double Movie::getAverageScore() const
{
    if(this->reviewCount == 0)
    {
        return 0;
    }
    return ((double)this->reviewPoints)/(this->reviewCount);
};
/**
 * returns the number of reviews
 * @return 
 */
unsigned int Movie::getReviewCount() const
{
    return this->reviewCount;
};



