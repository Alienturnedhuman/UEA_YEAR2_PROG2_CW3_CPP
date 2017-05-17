/* 
 * File:   MovieDatabase.cpp
 * Author: Benjamin Dickson
 * Info:   Please see header file
 */
#include "MovieDatabase.h"

// these was adapted from:
// http://stackoverflow.com/questions/7446743/sorting-vector-of-pointers
bool comparePtrToMovie(Movie* a, Movie* b) { return (*a < *b); }
bool comparePtrToMovieDesc(Movie* a, Movie* b) { return (*b < *a); }
bool comparePtrToRating(Rating* a, Rating* b) { return (*a < *b); }
bool comparePtrToRatingDesc(Rating* a, Rating* b) { return (*b < *a); }


// own code below

// these CompareHandlers are set up to allow Movie/MovieDatabase and
// Rating/Movie to do sort comparisions as they need access to each others
// methods but have to be declared in different files for the coursework
bool CompareHandler::movieLT(const Movie &a , const Movie &b , 
        const MovieDatabase &c)
{
    switch(c.getSortField())
    {
        case MovieDatabase::SortFields::year:
            return a.getYear() < b.getYear();
            break;
        case MovieDatabase::SortFields::genre:
            return a.getGenreCount() < b.getGenreCount();
            break;
        case MovieDatabase::SortFields::certificate:
            return a.getCert() < b.getCert();
            break;
        case MovieDatabase::SortFields::duration:
            return a.getDuration() < b.getDuration();
            break;
        case MovieDatabase::SortFields::average_rating:
            return a.getAverageScore() < b.getAverageScore();
            break;
        case MovieDatabase::SortFields::review_count:
            return a.getReviewCount() < b.getReviewCount();
            break;
        case MovieDatabase::SortFields::title_length:
            return a.getTitle().length() < b.getTitle().length();
            break;
        case MovieDatabase::SortFields::title:
        default:
            return a.getTitle() < b.getTitle();
            break;
    }
}



bool CompareHandler::movieGT(const Movie &b , const Movie &a , 
        const MovieDatabase &c)
{
    switch(c.getSortField())
    {
        case MovieDatabase::SortFields::year:
            return a.getYear()>b.getYear();
            break;
        case MovieDatabase::SortFields::genre:
            return a.getGenreCount()>b.getGenreCount();
            break;
        case MovieDatabase::SortFields::certificate:
            return a.getCert()>b.getCert();
            break;
        case MovieDatabase::SortFields::duration:
            return a.getDuration() > b.getDuration();
            break;
        case MovieDatabase::SortFields::average_rating:
            return a.getAverageScore()>b.getAverageScore();
            break;
        case MovieDatabase::SortFields::review_count:
            return a.getReviewCount()>b.getReviewCount();
            break;
        case MovieDatabase::SortFields::title_length:
            return a.getTitle().length()>b.getTitle().length();
            break;
        case MovieDatabase::SortFields::title:
        default:
            return a.getTitle()>b.getTitle();
            break;
    }
}






bool CompareHandler::movieEQ(const Movie &a , const Movie &b , 
        const MovieDatabase &c)
{
    switch(c.getSortField())
    {
        case MovieDatabase::SortFields::year:
            return a.getYear() == b.getYear();
            break;
        case MovieDatabase::SortFields::genre:
            return a.getGenreCount() == b.getGenreCount();
            break;
        case MovieDatabase::SortFields::certificate:
            return a.getCert() == b.getCert();
            break;
        case MovieDatabase::SortFields::duration:
            return a.getDuration() == b.getDuration();
            break;
        case MovieDatabase::SortFields::average_rating:
            return a.getAverageScore() == b.getAverageScore();
            break;
        case MovieDatabase::SortFields::review_count:
            return a.getReviewCount() == b.getReviewCount();
            break;
        case MovieDatabase::SortFields::title_length:
            return a.getTitle().length() == b.getTitle().length();
            break;
        case MovieDatabase::SortFields::title:
        default:
            return a.getTitle() == b.getTitle();
            break;
    }
}





bool CompareHandler::ratingLT(const Rating &a , const Rating &b , 
        const Ratings &c)
{
    switch(c.getSortField())
    {
        case Ratings::SortFields::user:
            return a.getUser() < b.getUser();
            break;
        case Ratings::SortFields::rating:
            return a.getRating() < b.getRating();
            break;
        case Ratings::SortFields::movie:
            return a.getMovie()->getTitle() < b.getMovie()->getTitle();
            break;
        case Ratings::SortFields::chronological:
        default:
            return (*(a.getTimeStamp())) < (*(b.getTimeStamp()));
            break;
    }
}


bool CompareHandler::ratingGT(const Rating &a , const Rating &b , 
        const Ratings &c)
{
    switch(c.getSortField())
    {
        case Ratings::SortFields::user:
            return a.getUser() > b.getUser();
            break;
        case Ratings::SortFields::rating:
            return a.getRating() > b.getRating();
            break;
        case Ratings::SortFields::movie:
            return a.getMovie()->getTitle() > b.getMovie()->getTitle();
            break;
        case Ratings::SortFields::chronological:
        default:
            return (*(a.getTimeStamp())) > (*(b.getTimeStamp()));
            break;
    }
}

bool CompareHandler::ratingEQ(const Rating &a , const Rating &b , 
        const Ratings &c)
{
    switch(c.getSortField())
    {
        case Ratings::SortFields::user:
            return a.getUser() == b.getUser();
            break;
        case Ratings::SortFields::rating:
            return a.getRating() == b.getRating();
            break;
        case Ratings::SortFields::movie:
            return a.getMovie()->getTitle() == b.getMovie()->getTitle();
            break;
        case Ratings::SortFields::chronological:
        default:
            return (*(a.getTimeStamp())) == (*(b.getTimeStamp()));
            break;
    }
}







/**
 * getCert
 * 
 * takes a string, a MovieDatabase pointer and runs the MovideDatabase's
 * getCert function, to obtain the pointer to the relevant certificate
 */
MovieCertificate* MovieDatabaseLink::getCert(string certStr ,  MovieDatabase &mdb)
{
    return mdb.getCert(certStr);
};

/**
 * gets a MovieGenre pointer given a string and a MovieDatabase pointer
 * (runs the MovieDatabase::getGenre() function
 * @param genreStr
 * @param mdb
 * @return 
 */
MovieGenre* MovieDatabaseLink::getGenre(string genreStr , MovieDatabase &mdb)
{
    return mdb.getGenre(genreStr);
};

/**
 * adds a review score to a movie
 * @param score
 * @param m
 */
void MovieDatabaseLink::addRating(int score , Movie &m)
{
    m.addScore(score);
};

/**
 * adds a rating to the database, but only if the movie is in the database
 * @param rStream
 * @return 
 */
bool Ratings::addRating(stringstream &rStream)
{
    // 03/03/2013T08:11:29Z,"George Emerson","American History X",4
    // <timestamp>,"<user>","<movie>",<rating>
    string discard;
    string timestamp,user,movie,rating;
    getline(rStream,timestamp,',');
    getline(rStream,discard,'"');
    getline(rStream,user,'"');
    getline(rStream,discard,'"');
    getline(rStream,movie,'"');
    getline(rStream,discard,',');
    getline(rStream,rating);
    
    
    // check if movie exists
    if(movies->hasMovie(movie))
    {
        Movie* tempMovie = movies->getMovie(movie);
        RatingUser* tempUser = getUser(user);
        TimeCode* tempTimeCode = new TimeCode();
        stringstream timestampStream(timestamp);
        timestampStream >> *tempTimeCode;
        unsigned int tempRating = stoi(rating);
        return addRating(tempTimeCode,tempUser,tempMovie,tempRating);
    }
    return false;
};


/**
 * sorts the movie database for the given settings
 * @param field
 * @param sortDesc
 */
void Ratings::sortDatabase(SortFields field,bool sortDesc)
{
    sortField = field;
    sortDescending = sortDesc;
    if(sortDescending)
    {
        sort(ratings.begin(),ratings.end(),comparePtrToRatingDesc);       
    }
    else
    {
        sort(ratings.begin(),ratings.end(),comparePtrToRating);
    }
};





/**
 * constructor for Movie Database
 */
MovieDatabase::MovieDatabase()
{
    sortDesc = false;  
    sortField = title;
    ratingsDB = new Ratings(this);
}

/**
 * returns true if the movie was added to the database (if it was not already
 * in the database it will be added)
 * @param newMovie
 * @return 
 */
bool MovieDatabase::addMovie(Movie* newMovie)
{
    int i =-1;
    int ii = titles.size();
    while(++i<ii)
    {
        if(newMovie->getTitle() == titles[i])
        {
            return false;
        }
    }
    (this->titles).push_back(newMovie->title);
    (this->movies).push_back(newMovie);
    return true;
};

/**
 * returns true if the movie was successful added from the provided CSV
 * line stream
 * @param CSVlinestream
 * @return 
 */
bool MovieDatabase::addMovie(stringstream& CSVlinestream)
{
    Movie* newMovie = new Movie(this);
    CSVlinestream >> newMovie;
    return this->addMovie(newMovie);
};



/**
 * returns true if the movie title is in the database
 * @param title
 * @return 
 */
bool MovieDatabase::hasMovie(string title)
{
    int i = -1;
    int ii = titles.size();
    while(++i<ii)
    {
        if(title==titles[i])
        {
            return true;
        }
    }
    return false;
}


/**
 * returns the movie pointer for the given title
 * @param title
 * @return 
 */
Movie* MovieDatabase::getMovie(string title)
{
    int i =-1;
    int ii = movies.size();
    while(++i<ii)
    {
        if(movies[i]->getTitle()==title)
        {
            return movies[i];
        }
    };
    return nullptr;
};

/**
 * gets the pointer to the certificate for the string provided (or creates a new
 * one and adds to the vector if it does not exist)
 * @param certStr
 * @return 
 */
MovieCertificate* MovieDatabase::getCert(string certStr)
{
    int ii = (this->certificates).size();
    int i=-1;
    while(++i<ii)
    {
        if(*((this->certificates)[i])==certStr)
        {
            return ((this->certificates)[i]);
        }
    }
    MovieCertificate* newCert = new MovieCertificate(certStr);
    (this->certificates).push_back(newCert);
    return newCert;
    
};

/**
 * gets the pointer to the genre for the string provided (or creates a new
 * one and adds to the vector if it does not exist)
 * @param genreStr
 * @return 
 */
MovieGenre* MovieDatabase::getGenre(string genreStr)
{
    int ii = (this->genres).size();
    int i=-1;
    while(++i<ii)
    {
        if(*((this->genres)[i])==genreStr)
        {
            return (this->genres[i]);
        }
    }
    MovieGenre* newGenre = new MovieGenre(genreStr);
    (this->genres).push_back(newGenre);
    return newGenre;
};



/**
 * returns a pointer to the Ratings of the database
 * @return 
 */
Ratings* MovieDatabase::ioRatings()
{
    return ratingsDB;
}

  /**
   * sets the sort field for the database (but does not trigger sort)
   * @param newField
   */  
void MovieDatabase::setSortField(SortFields newField)
{
    sortField = newField;
};

/**
 * sets the database to sort descending (but does not trigger sort)
 * @param desc
 */
void MovieDatabase::setSortDescending(bool desc)
{
    sortDesc = desc;
}
/**
 * returns the enum for the sort field set
 * @return 
 */
MovieDatabase::SortFields MovieDatabase::getSortField() const
{
   return MovieDatabase::sortField;
};

/**
 * returns true if the database is set to sort descending
 * @return 
 */
bool MovieDatabase::getSortDescending() const
{
    return MovieDatabase::sortDesc;
}

/**
 * returns the number of movies in the database
 * @return 
 */
long MovieDatabase::count() const
{
    return movies.size();
};

/**
 * sorts the database for the given settings
 * @param field
 * @param desc
 */
void MovieDatabase::sortDatabase(MovieDatabase::SortFields field,bool desc)
{
    sortField = field;
    sortDesc = desc;
    if(sortDesc)
    {
        sort(movies.begin(),movies.end(),comparePtrToMovieDesc);
    }
    else
    {
        sort(movies.begin(),movies.end(),comparePtrToMovie);
    }
};

/**
 * Gives the most extreme movie for a specific sort parameter
 * @param field
 * @param desc
 * @return 
 */
Movie* MovieDatabase::extreme(SortFields field,bool desc)
{
    sortField = field;
    sortDesc = desc;
    int i=0;
    int ii = movies.size();
    Movie* r = movies[0];
    while(++i<ii)
    {
        if(*r<*movies[i])
        {
            r = movies[i];
        }
    }
    return r;
}

/**
 * Extracts a new Movie Database for a given genre
 * @param findGenre
 * @return 
 */
 MovieDatabase* MovieDatabase::genreList(MovieGenre* findGenre)
 {
    MovieDatabase* rMDB = new MovieDatabase();
    rMDB->genres = this->genres;
    int i=0;
    int ii = movies.size();
    Movie* r = movies[0];
    while(++i<ii)
    {
        if(movies[i]->hasGenre(findGenre))
        {
            /*
             * Movies have to be cloned, as they need to point to the
             * new Movie Database to get sort settings
             */
            Movie* clone = new Movie(movies[i],rMDB);
            rMDB->addMovie(clone);
        }
    }
    return rMDB;
 };
 
/**
 * Returns the movie pointer at index i
 * @param i
 * @return 
 */
 Movie* MovieDatabase::getIndex(int i) const
 {
     if(i>=0 && i<movies.size())
     {
         return movies[i];
     }
     else if(i<0)
     {
         return movies[0];
     }
     return movies[movies.size()-1];
 };
 
 
 /**
  * returns a Movie as a string
  * @param mp
  * @return 
  */
 string MovieDatabase::movieString(Movie& mp) const
 {
     stringstream r;
     r << mp;
     return r.str();
 }
 
 