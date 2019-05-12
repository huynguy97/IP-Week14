//                        
//                         

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

struct Length
{
    int minutes;							//               
    int seconds;							//                 
};
struct Track
{
    string artist;                          //            
    string cd;                              //         
    int    year;                            //                   
    int    track_no;						//             
    string title;                           //            
    string tags;                            //                            
    Length time;							//             
    string country;                         //                                         
};

vector<Track> songs;
int aan = 0;

bool operator!= (const Length& a, const Length& b)
{
    return a.minutes != b.minutes || a.seconds != b.seconds;
}

bool operator==(const Length& a, const Length& b)
{
    return a.minutes == b.minutes && a.seconds == b.seconds;
}

bool operator< (const Length& a, const Length& b)
{
    if (a.minutes < b.minutes)
        return true;

    else if (a.minutes == b.minutes)
    {
        if (a.seconds < b.seconds)
            return true;

        else
            return false;
    }
    else
        return false;
}

bool operator==(const Track& a, const Track& b)
{
    aan++;
    return a.time == b.time && a.artist == b.artist && a.cd == b.cd && a.year == b.year && a.track_no == b.track_no && a.title == b.title && a.tags == b.tags && a.country == b.country ;   /*                                                 */
}

ostream& operator<< (ostream& out, const Length length)
{
    //               
    assert (true) ;
    /*                 
                                                                           
    */
    out << length.minutes << ':';
    if (length.seconds < 10)
        out << '0';
    out << length.seconds;
    return out ;
}

bool operator<(const Track& a, const Track& b)
{
    aan++;
    if (a.time != b.time)
    {
        return a.time < b.time;
    }
    else if (a.artist != b.artist)
    {
        return a.artist < b.artist;
    }
    else if (a.cd != b.cd)
    {
        return a.cd < b.cd;
    }
    else if (a.year != b.year)
    {
        return a.year < b.year;
    }
    else if (a.track_no != b.track_no)
    {
        return a.track_no < b.track_no;
    }
    else if (a.title != b.title)
    {
        return a.title < b.title;
    }
    else if (a.tags != b.tags)
    {
        return a.tags < b.tags;
    }
    else if (a.country != b.country)
    {
        return a.country < b.country;
    }
    else
    {
        return false;
    }
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

istream& operator>> (istream& in, Length& length)
{
    //               
    assert (true) ;
    /*                 
                                                                                                          
    */
    char colon ;
    in >> length.minutes >> colon >> length.seconds ;
    return in ;
}

void skip_to_next_newline (istream& infile)
{
    //               
    assert (true) ;
    /*                 
                                                                            
    */
    string remains ;
    int size ();
    getline (infile, remains) ;
}

istream& operator>> (istream& infile, Track& track)
{
    //               
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
{
    //               
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

int size (vector<Track>&songs)
{
    return static_cast<int>(songs.size());
}

int read_songs (ifstream& infile, vector<Track>&songs)
{
    //               
    assert (infile.is_open ()) ;
    /*                 
                                                                                  
                                                               
    */
    int no_of_read_songs = 0 ;
    do
    {
        Track song ;
        infile >> song ;
        if (infile)
        {
            songs.push_back(song);
            songs[no_of_read_songs++] = song ;
        }
    }
    while (infile);
    return no_of_read_songs ;
}

int read_file (string filename)
{
    //               
    assert (size (songs) == 0) ;
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

void show_all_tracks (vector<Track>&songs, int no_of_songs)
{
    //               
    assert (true) ;
    /*                 
                                                                      
    */
    for (int i = 0 ; i < no_of_songs; i++)
        cout << i+1 << ". " << songs[i] << endl ;
}

void swap (vector<Track>& songs, int colour, int NEXT)
{
//    
assert (true);
//     
//                                               
    const Track T = songs[colour];
    songs[colour] = songs[NEXT];
    songs[NEXT] = T;
}

void dnf_common (vector<Track>& songs, int first, int last, int& red, int& blue)
{
//    
    assert (true);
//     
//                                                           
    red = first -1;
    blue = last+1;
    int white = last+1;
    const Track PIVOT = songs[first+(last-first)/2];
    while (red < white -1)
    {
        const int NEXT = white -1;
        if (songs[NEXT] < PIVOT)
        {
            red++;
            swap (songs, red, NEXT);
        }
        else if (songs[NEXT] == PIVOT)
            white--;
        else
        {
            white--;
            blue--;
            swap (songs, NEXT, blue);
        }
    }
}

void quicksort_common (vector<Track>& songs, int first, int last)
{
//    
    assert (true);
//     
//                                                          
    if (first >= last)
        return;
    else
    {
        int red=0;
        int blue=0;
        dnf_common (songs, first, last, red, blue);
        quicksort_common (songs, first, red);
        quicksort_common (songs, blue, last);
    }
}

void dnf_new (vector<Track>& songs, int first, int last, int& red, int& blue)
{
//    
    assert (true);
//     
//                                           
    red = first -1;
    blue = last+1;
    int white = first -1;
    const Track PIVOT = songs[first+(last-first)/2];
    while (blue > white +1)
    {
        const int NEXT = white +1;
        if (songs[NEXT] < PIVOT)
        {
            red++;
            white++;
            swap (songs, red, NEXT);
        }
        else if (songs[NEXT] == PIVOT)
            white++;
        else
        {
            blue--;
            swap (songs, NEXT, blue);
        }
    }
}

void quicksort_new (vector<Track>& songs, int first, int last)
{
//    
    assert (true);
//     
//                                      
    if (first >= last)
        return;
    else
    {
        int red=0;
        int blue=0;
        dnf_new (songs, first, last, red, blue);
        quicksort_new (songs, first, red);
        quicksort_new (songs, blue, last);
    }
}

int main()
{
    const int NO_OF_SONGS = read_file ("Tracks.txt");
    string antwoord;

    cout << "Hoe wil je het sorteren? Standaard of andersom?" << endl;
    cin >> antwoord;
    string check = "ok";
    if (antwoord == "standaard")
        quicksort_common(songs, 0, NO_OF_SONGS-1);
    else if (antwoord == "andersom")
        quicksort_new(songs, 0, NO_OF_SONGS-1);
    else
        check = "no";
    while (check != "ok")
    {
        cin.clear();
        cout << "Geef aub een geldig commando-> standaard/andersom." << endl;
        cin >> antwoord;
        if (antwoord == "standaard")
        {
            quicksort_common(songs, 0, NO_OF_SONGS-1);
            check = "ok";
        }
        if (antwoord == "andersom")
        {
            quicksort_new(songs, 0, NO_OF_SONGS-1);
            check = "ok";
        }
    }

    for (int i =0; i < NO_OF_SONGS; i++)
        cout << songs[i] << endl;
//         
//                                                                                                                                      

    return 0;
}

/*                                                                                                                                                                                                                    
       

                                            
 
                    
         
                            
                                 
                       
         
                 
                       
         
              
     
               
 

                               
 
                 
     
                                            
                           
            
     
 

*/

