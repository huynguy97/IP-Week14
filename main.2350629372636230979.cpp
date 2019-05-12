#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <cassert>

using namespace std;
//                          
//                       

/*                                                                             
                                                 
                                                                              */

/*                                                                    
                                            
                                                                     */
struct Length
{
    int minutes;                            //               
    int seconds;                            //                 
};
struct Track
{
    string artist;                          //            
    string cd;                              //         
    int    year;                            //                   
    int    track_no;                        //             
    string title;                           //            
    string tags;                            //                            
    Length time;                            //             
    string country;                         //                                         
};

/*                                                                       
                                
                                                               
                                                                         
                                                                       */
bool operator<(const Length& a, const Length& b) {
    if (a.minutes != b.minutes)
        return a.minutes < b.minutes;
    return a.seconds < b.seconds;
}

bool operator==(const Length& a, const Length& b) {
    return a.minutes == b.minutes &&
        a.seconds == b.seconds;
}

bool operator!=(const Length& a, const Length& b) {
    return !(a == b);
}

bool operator<(const Track& a, const Track& b)
{
    if (a.artist != b.artist)
        return a.artist < b.artist;
    if (a.cd != b.cd)
        return a.cd < b.cd;
    if (a.year != b.year)
        return a.year < b.year;
    if (a.track_no != b.track_no)
        return a.track_no < b.track_no;
    if (a.title != b.title)
        return a.title < b.title;
    if (a.tags != b.tags)
        return a.tags < b.tags;
    if (a.time != b.time)
        return a.time < b.time;
    if (a.country != b.country)
        return a.country < b.country;
    return false;
}

bool operator==(const Track& a, const Track& b)
{
    return a.artist == b.artist &&
        a.cd == b.cd &&
        a.year == b.year &&
        a.track_no == b.track_no &&
        a.title == b.title &&
        a.tags == b.tags &&
        a.time == b.time &&
        a.country == b.country;
}

//                                   
bool operator>(const Track& a, const Track& b)
{
    return b < a ;
}

bool operator<=(const Track& a, const Track& b)
{
    return !(b < a) ;
}

bool operator>=(const Track& a, const Track& b)
{
    return b <= a ;
}

/*                                                                       
                            
                                                                       */
istream& operator>> (istream& in, Length& length)
{//               
    assert (true) ;
/*                 
                                                                                                      
*/
    char colon ;
    in >> length.minutes >> colon >> length.seconds ;
    return in ;
}

ostream& operator<< (ostream& out, const Length length)
{//               
    assert (true) ;
/*                 
                                                                       
*/
    out << length.minutes << ':';
    if (length.seconds < 10)
        out << '0';
    out << length.seconds;
    return out ;
}

void skip_to_next_newline (istream& infile)
{//               
    assert (true) ;
/*                 
                                                                        
*/
    string remains ;
    getline (infile, remains) ;
}

istream& operator>> (istream& infile, Track& track)
{//               
    assert (true) ;
/*                 
                                                                                                                   
                                      
*/
    getline(infile,track.artist);       //       
    getline(infile,track.cd);           //   
    infile >> track.year ;              //     
    skip_to_next_newline(infile) ;
    infile >> track.track_no ;          //             
    skip_to_next_newline(infile) ;
    getline(infile,track.title);        //            
    getline(infile,track.tags);         //           
    infile >> track.time ;              //           
    skip_to_next_newline(infile) ;
    getline(infile,track.country);      //        
    skip_to_next_newline(infile) ;
    return infile ;
}

//                                                                                                        
ostream& operator<< (ostream& out, const Track track)
{//               
    assert (true) ;
/*                 
                                                                                
*/
    out << track.artist   << endl ;
    out << track.cd       << endl ;
    out << track.year     << endl ;
    out << track.track_no << endl ;
    out << track.title    << endl ;
    out << track.tags     << endl ;
    out << track.time     << endl ;
    out << track.country  << endl ;
    return out ;
}

int read_songs (ifstream& infile, vector<Track>& songs)
{//               
    assert (infile.is_open ()) ;
/*                 
                                                                              
                                                           
*/
    do {
        Track song ;
        infile >> song ;
        if (infile)
            songs.push_back(song);
    }
    while (infile);
    return songs.size() ;
}

int read_file (string filename, vector<Track>& songs)
{//               
    assert (songs.size() == 0) ;
/*                 
                                                                              
                                                                                             
                                        
*/
    ifstream songsDBS (filename.c_str());
    if (!songsDBS)
    {
        cout << "Could not open '" << filename << "'." << endl;
        return -1;
    }
    cout << "Reading '" << filename << "'." << endl;
    const int NO_OF_SONGS = read_songs (songsDBS, songs);
    songsDBS.close();
    cout << " Read " << NO_OF_SONGS << " tracks." << endl;
    return NO_OF_SONGS;
}

void show_all_tracks (vector<Track> songs)
{//               
    assert (songs.size() >= 0) ;
/*                 
                                                                  
*/
    for (int i = 0 ; i < static_cast<int>(songs.size()); i++)
        cout << i+1 << ". " << songs[i] << endl ;
}

void swap (vector<Track>& data, int  i, int  j )
{//               
    assert ( i >= 0 && j >= 0 ) ;   //                         
                                    //                         
//                                                                
    const Track HELP = data [i];
    data [i] = data [j] ;
    data [j] = HELP;
}
/*                                                                             
                                               
                                                                              */
int size(const vector<Track>& v) {
    //               
    assert(true);
    /*                
                                         
     */
    return static_cast<int>(v.size());
}

void dnf(vector<Track>& data, int first, int last, int& red, int& blue) {
    //               
    assert(first >= 0);
    assert(last < size(data));
    /*                
                                                                        
                                                                      
                                                                            
                                                                          
             
     */
    red       = first -1;
    blue      = last + 1;
    int white = last + 1;
    const Track PIVOT = data[first+(last-first)/2];

    while (red < white - 1) {
        const int NEXT = white - 1;
        if (data[NEXT] < PIVOT) {
            red++;
            swap(data, red, NEXT);
        } else if (data[NEXT] == PIVOT) {
            white--;
        } else {
            white--;
            blue--;
            swap(data, NEXT, blue);
        }
    }
}

void dnf2(vector<Track>& data, int first, int last, int& red, int& blue) {
    //               
    assert(first >= 0);
    assert(last < size(data));
    /*                
                                                                        
                                                                      
                                                                            
                                                                          
             
     */
    red       = first - 1;
    blue      = last + 1;
    int white = first - 1;
    const Track PIVOT = data[first+(last-first)/2];

    while (white < blue - 1) {
        const int NEXT = white + 1;
        if (data[NEXT] < PIVOT) {
            red++;
            white++;
            swap(data, red, NEXT);
        } else if (data[NEXT] == PIVOT) {
            white++;
        } else {
            blue--;
            swap(data, NEXT, blue);
        }
    }
}

void quicksort(vector<Track>& data, int first, int last) {
    //               
    assert(first >=0 );
    assert(last < size(data));
    /*                
                                          
     */
    int red, blue;

    if (first >= last)
        return;

    dnf(data, first, last, red, blue);
    quicksort(data, first, red);
    quicksort(data, blue, last);
}

void quicksort2(vector<Track>& data, int first, int last) {
    //               
    assert(first >=0 );
    assert(last < size(data));
    /*                
                                          
     */
    int red, blue;

    if (first >= last)
        return;

    dnf2(data, first, last, red, blue);
    quicksort2(data, first, red);
    quicksort2(data, blue, last);
}

int largest(vector<Track>& v, int low, int up) {
    //               
    assert(low >= 0);
    assert(up < size(v));
    /*                
                                                                 
     */
    //                                                                          
    //                                                         
    int lowest = up;
    for (int i = up; i >= low; i--) {
        if (v[i] < v[lowest]) {
            lowest = i;
        }
    }
    return lowest;
}

void sort(vector<Track>& v) {
    //               
    assert(true);
    /*                
                  
     */
    for (int i = size(v); i > 0; i--) {
        const int POS = largest(v, 0, i-1);
        swap(v, POS, i-1);
    }
}

int main(int argc, char* argv[]) {
    //               
    assert(argv[0]);
    /*                
                       
     */
    vector<Track> songs;
    songs.reserve(53019);

    const int NO_OF_SONGS = read_file("tracks_shuffled.txt", songs);
    if (NO_OF_SONGS < 0) {
        cerr << "Reading \"Tracks.txt\" failed. Exiting." << endl;
        return NO_OF_SONGS;
    }

    if (string(argv[0]) == "./ssort.out") {
        cerr << "Using simple sort transformed" << endl;
        //                              
        sort(songs);
    } else if (string(argv[0]) == "./alt.out") {
        cerr << "Using quicksort with alternate DNF" << endl;
        quicksort2(songs, 0, NO_OF_SONGS - 1);
    } else {
        cerr << "Using regular quicksort with DNF" << endl;
        quicksort(songs, 0, NO_OF_SONGS - 1);
    }

    for (int i=0; i < NO_OF_SONGS; i++) {
        cout << songs[i] << endl;
    }

    return 0;
}

