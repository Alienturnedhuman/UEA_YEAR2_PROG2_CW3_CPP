/* 
 * File:   main.cpp
 * Author: Benjamin Dickson
 * Info:   main.cpp file for Assignment 3 - Offline Movie Database in C++
 */

#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <sstream>

using namespace std;



#include "MovieDatabase.h"



string ROOT_FILE_PATH = "/Users/bendickson/Google Drive/UEA/prog 2/cw3/files/";
string MOVIES_FILE_PATH = "movies.txt";
string RATINGS_FILE_PATH = "ratings.txt";


/*
 * main method performs the tasks required for coursework
 */
int main(int argc, char** argv) {
  
    
    
    MovieDatabase* myDB = new MovieDatabase();
    
    cout << "Import '" << MOVIES_FILE_PATH << "' to myDB\n";
    ifstream movieCSV(ROOT_FILE_PATH + MOVIES_FILE_PATH);
    movieCSV >> *myDB;
    
    cout << "Import ratings from '" << RATINGS_FILE_PATH << "'\n\n";
    ifstream ratingCSV(ROOT_FILE_PATH + RATINGS_FILE_PATH);
    ratingCSV >> *(myDB->ioRatings());
    
    
    
    cout << "Coursework Tasks Below:\n\n";
    
    // Task #1
    // Sort the movies in ascending order of release date 
    // and display on the console
    
    
    cout << "\n\nTask 1:\n";
    cout << "Sort the movies in ascending order of release date:\n\n";
            
    // to save on console output, I have given the option to save to file
    // instead, but enter . to send to console
    myDB->sortDatabase(MovieDatabase::SortFields::year,false);
    cout << "Enter file name to output to (enter . for console)\n";
    
    string outputPath;
    cin >> outputPath;
    
    if(outputPath=="." or outputPath==MOVIES_FILE_PATH or 
            outputPath==RATINGS_FILE_PATH)
    {
        if(outputPath==MOVIES_FILE_PATH or outputPath==RATINGS_FILE_PATH)
        {
            cout << "'" << outputPath << "' in use, outputting to console:\n";
        }
        cout << "BEGIN LIST:\n\n";
        cout << *myDB;
        cout << "\nEND LIST\n\n";
    }
    else
    {
        ofstream saveDB(ROOT_FILE_PATH + outputPath, ofstream::out);
        saveDB << *myDB;
        saveDB.close();
    }
    
    
    
    
    // Task #2
    // Display the third longest Film-Noir.
    
    cout << "\n\nTask 2:\n";
    cout << "Display the third longest Film-Noir:\n\n";
    
    
    MovieGenre* filmNoirGenre = myDB->getGenre("Film-Noir");
    MovieDatabase* filmNoirFilms = myDB->genreList(filmNoirGenre);
    filmNoirFilms->sortDatabase(MovieDatabase::SortFields::duration,true);
    
    
    int posCheck = 3;
    
    if(filmNoirFilms->count()<posCheck)
    {
        cout<<"Not enough films!";
    }
    else
    {
        cout<<(*(filmNoirFilms->getIndex(posCheck-1)));
    }
    
    
    
    
    // Task #3
    // Display the tenth highest rated Sci-Fi movie.
    
    cout << "\n\nTask 3:\n";
    cout << "Display the tenth highest rated Sci-Fi movie:\n\n";
    
    MovieGenre* sfGenre = myDB->getGenre("Sci-Fi");
    MovieDatabase* sfFilms = myDB->genreList(sfGenre);
    sfFilms->sortDatabase(MovieDatabase::SortFields::average_rating,true);
    posCheck = 10;
    
    if(sfFilms->count()<posCheck)
    {
        cout<<"Not enough films!";
    }
    else
    {
        cout<<(*(sfFilms->getIndex(posCheck-1)));
    }
    
    
    
    // Task #4
    // Display the highest rated movie
    
    cout << "\n\nTask 4:\n";
    cout << "Display the highest rated movie:\n\n";
    cout<<(*(myDB->extreme(MovieDatabase::SortFields::average_rating,true)));
    
    
    
    
    // Task #6
    // Display the movie with the longest title
    
    cout << "\n\nTask 6:\n";
    cout << "Display the movie with the longest title:\n\n";
    cout<<(*(myDB->extreme(MovieDatabase::SortFields::title_length,true)));
    
    
    
    // Task #5
    // Find the chronologically 101st rating
    
    cout << "\n\nTask 5:\n";
    cout << "Find the chronologically 101st rating:\n\n";
    myDB->ioRatings()->sortDatabase(Ratings::SortFields::chronological,false);
    cout << *(myDB->ioRatings()->getIndex(100));
    
    return EXIT_SUCCESS;
}

