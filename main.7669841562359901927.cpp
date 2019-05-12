//                         
//                            

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

struct Length
{
int minutes;       //               
int seconds;       //                 
};
struct Track
{
string artist;                          //            
string cd;                              //         
int    year;                            //                   
int    track_no;      //             
string title;                           //            
string tags;                            //                            
Length time;       //             
string country;                         //                                         
};

struct TrackDisplay
{
bool showArtist;      //                             
bool showAlbum;       //                       
bool showYear;       //                                 
bool showTrack;       //                           
bool showTitle;       //                          
bool showTags;                          //                   
bool showLength;      //                           
bool showCountry;                       //                                      
};

const int MAX_NO_OF_SONGS = 6000;
vector<Track> songs;

//                                                                                                               
/*
                                             
         
*/
bool operator<(const Length& a, const Length& b)
{
    if(a.minutes < b.minutes)
    {
        return true;
    }
    else if(a.minutes == b.minutes)
    {
        if(a.seconds < b.seconds)
        {
            return true;
        }
        return false;
    }
    return false;
}

bool operator==(const Length& a, const Length& b)
{
    return a.minutes == b.minutes && a.seconds == b.seconds;
}

bool operator<(const Track& a, const Track& b)
{
    //           
    //                                                                                                           
    if(a.time < b.time)
    {
        return true;
    }
    else if(a.time == b.time)
    {
        if(a.artist < b.artist)
        {
            return true;
        }
        else if(a.artist == b.artist)
        {
            if(a.cd < b.cd)
            {
                return true;
            }
            else if(a.cd == b.cd)
            {
                if(a.year < b.year)
                {
                    return true;
                }
                else if(a.year == b.year)
                {
                    if(a.track_no < b.track_no)
                    {
                        return true;
                    }
                    return false;
                }
                return false;
            }
            return false;
        }
        return false;
    }
    return false;
}

bool operator==(const Track& a, const Track& b)
{
    return a.artist == b.artist && a.cd == b.cd && a.year == b.year && a.track_no == b.track_no;
}

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

Length operator+ (const Length& a, const Length& b)
{//              
    assert (0 <= a.minutes && 0 <= a.seconds && a.seconds < 60 && 0 <= b.minutes && 0 <= b.seconds && b.seconds < 60) ;
/*                
                                 
*/
    Length total;
    total.seconds = (a.seconds + b.seconds)%60;
    total.minutes = a.minutes + b.minutes + ((a.seconds + b.seconds)-((a.seconds + b.seconds)%60))/60;
    return total;
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
    out << endl ;
    return out ;
}

//                                                                           
int read_songs (ifstream& infile, vector<Track>& songs)
{//               
    assert(infile.is_open());
/*                 
                                                                              
                                                           
*/
    int no_of_read_songs = 0 ;
    do {
        Track song ;
        infile >> song ;
        if (infile)
        {
            songs.push_back(song);
            no_of_read_songs++;
        }
    }
    while (infile && no_of_read_songs < MAX_NO_OF_SONGS);
    return no_of_read_songs ;
}

int read_file (string filename)
{//               
    assert(true) ;
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

//                                                                           
void show_all_tracks (vector<Track>& songs, int no_of_songs)
{//               
    assert (no_of_songs < MAX_NO_OF_SONGS) ;
/*                 
                                                                  
*/
    for (int i = 0 ; i < no_of_songs; i++)
        cout << i+1 << ". " << songs[i] << endl ;
}

void swap (vector<Track>& data, int  i, int  j )
{//               
    assert ( i >= 0 && j >= 0 ) ; //                         
    //                         

    const Track HELP = data [i];
    data [i] = data [j] ;
    data [j] = HELP;
}

void show_track (Track track, TrackDisplay lt)
{//              
    assert (true) ;
/*                
                                                                                         
*/
    if(lt.showArtist)
    {
        cout << track.artist << endl;
    }
    if(lt.showAlbum)
    {
        cout << track.cd << endl;
    }
    if(lt.showYear)
    {
        cout << track.year << endl;
    }
    if(lt.showTrack)
    {
        cout << track.track_no << endl;
    }
    if(lt.showTitle)
    {
        cout << track.title << endl;
    }
    if(lt.showTags)
    {
        cout << track.tags << endl;
    }
    if(lt.showLength)
    {
        cout << track.time << endl;
    }
    if(lt.showCountry)
    {
        cout << track.country << endl;
    }
}

/*
                                                
                           
*/

void dnf_adapted(vector<Track>& songs, int first, int last, int& red, int& blue)
{
    //    
    assert(first <= last);
    //     
    //                                       
    red = first-1;
    blue = last+1;
    int white = first-1;
    const Track PIVOT = songs[first + int((last-first)/2)];
    while(blue>white+1)
    {
        const int NEXT = white + 1;
        if(songs[NEXT] < PIVOT)
        {
            red++;
            white++;
            swap(songs, red, NEXT);
        }
        else if(songs[NEXT] == PIVOT)
            white++;
        else{
            blue--;
            swap(songs, NEXT, blue);
        }
    }
}

void Quicksort_adapted(vector<Track>& songs, int first, int last)
{
    //    
    assert(true);
    //     
    //                                                
    if(first>=last)
        return;
    else{
        int red;
        int blue;
        dnf_adapted(songs, first, last, red, blue);
        Quicksort_adapted(songs, first, red);
        Quicksort_adapted(songs, blue, last);
    }
}

//                                                  
//                                                 
//                           

int largest(vector<Track>& songs, int low, int up)
{
    //    
    assert(low < up);
    //     
    //                                                  
    int biggest = up;
    while(low<up)
    {
        if(songs[low] > songs[biggest])
            biggest = low;
        low++;
    }
    return biggest;
}

void iterative_sort(vector<Track>& songs, int n)
{
    //    
    assert(n>1);
    //     
    //                                      
    while(n>1)
    {
        const int POS = largest(songs, 0, n-1);
        swap(songs, POS, n-1);
        n--;
    }
}

//                                                  

int main()
{
    //                                                 
    //                            
    //                                                                        
    ifstream infile;
    infile.open("Tracks.txt");
    vector<Track> songs;
    read_songs(infile, songs);
    Quicksort_adapted(songs, 0, songs.size()-1);
    TrackDisplay show_length = {false, false, false, false, false, false, true, false};
    for(int i = 0; i < songs.size(); i++)
    {
        show_track(songs[i], show_length);
    }
    return 0;
}

