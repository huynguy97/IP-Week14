//                                
//                            

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>
#include <random>
#define NDEBUG

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
int counter = 0;
int slice_counter2 = 0;

bool operator<(const Track& a, const Track& b)
{
    counter++;
    slice_counter2++;
    if (a.artist == b.artist)
        if (a.cd == b.cd)
            if (a.year == b.year)
                return a.track_no < b.track_no;
            else return a.year < b.year;
        else return a.cd < b.cd;
    else return a.artist < b.artist ;    /*                                                 */
}

bool operator==(const Track& a, const Track& b)
{
    counter++;
    slice_counter2++;
    return a.artist == b.artist && a.cd == b.cd && a.year == b.year && a.track_no == b.track_no;
}

//	                                 
bool operator>(const Track& a, const Track& b)
{
    counter++;
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

bool operator<(const Length& c, const Length& d)
{
    int c_running_time = c.minutes * 60 + c.seconds;
    int d_running_time = d.minutes * 60 + d.seconds;
    return c_running_time < d_running_time;
}

bool operator==(const Length& c, const Length& d)
{
    int c_running_time = c.minutes * 60 + c.seconds;
    int d_running_time = d.minutes * 60 + d.seconds;
    return c_running_time == d_running_time;
}

bool operator>(const Length& c, const Length& d)
{
    int c_running_time = c.minutes * 60 + c.seconds;
    int d_running_time = d.minutes * 60 + d.seconds;
    return c_running_time > d_running_time;
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
    out << endl ;
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
            songs.push_back(song) ;
    }
    while (infile);
    return songs.size() ;
}

int read_file (string filename)
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
    cout << "Read " << NO_OF_SONGS << " tracks." << endl;
    return NO_OF_SONGS;
}

void show_all_tracks (vector<Track>& songs, int no_of_songs)
{//               
    assert (no_of_songs <= songs.size()) ;
/*                 
                                                                  
*/
    for (int i = 0 ; i <= songs.size(); i++)
    {
        if (songs[i].year != 0)
            cout << i << ". " << songs[i] << endl ;
    }
}

void swap (vector<Track>& songs, int  i, int  j )
{//	              
    assert ( i >= 0 && j >= 0 ) ;	//                          
    //                          
//                                                                  
    const Track HELP = songs [i];
    songs [i] = songs [j] ;
    songs [j] = HELP;
}

void dnf1_a (vector<Track>& songs, int first, int last, int& red, int& blue)
{
    //               
    assert(first >= 0 && last <= songs.size());
    //                
    //                                                             
    //                                                                               
    red = first - 1;
    blue = last + 1;
    int white = last + 1;
    const Track PIVOT = songs[first+(last-first)/2];
    while(red < white - 1)
    {
        const int NEXT = white - 1;
        if(songs[NEXT] < PIVOT)
        {
            red++;
            swap(songs, red, NEXT);
        }
        else if(songs[NEXT]== PIVOT)
        {
            white--;
        }
        else
        {
            white--;
            blue--;
            swap(songs, NEXT, blue);
        }
    }
}

void dnf1_b (vector<Track>& songs, int first, int last, int& red, int& blue)
{
    //               
    assert(first >= 0 && last <= songs.size());
    //                
    //                                                                              
    red = first - 1;
    blue = last + 1;
    int white = last + 1;
    const Track PIVOT = songs[first+(last-first)/2];
    while(red < white - 1)
    {
        const int NEXT = white - 1;
        if(songs[NEXT].time < PIVOT.time)
        {
            red++;
            swap(songs, red, NEXT);
        }
        else if(songs[NEXT].time == PIVOT.time)
        {
            white--;
        }
        else
        {
            white--;
            blue--;
            swap(songs, NEXT, blue);
        }
    }
}

void dnf2_a (vector<Track>& songs, int first, int last, int& red, int& blue)
{
    //               
    assert(first >= 0 && last <= songs.size());
    //                
    //                                                                     
    //                                                                               
    red = first - 1;
    blue = last + 1;
    int white = first - 1;
    const Track PIVOT = songs[first+(last-first)/2];
    while(blue > white + 1)
    {
        const int NEXT = white + 1;
        if(songs[NEXT] > PIVOT)
        {
            blue--;
            swap(songs, NEXT, blue);
        }
        else if(songs[NEXT]== PIVOT)
        {
            white++;
        }
        else
        {
            white++;
            red++;
            swap(songs, red, NEXT);
        }
    }
}

void dnf2_b (vector<Track>& songs, int first, int last, int& red, int& blue)
{
    //               
    assert(first >= 0 && last <= songs.size());
    //                
    //                                                                                      
    red = first - 1;
    blue = last + 1;
    int white = first - 1;
    const Track PIVOT = songs[first+(last-first)/2];
    while(blue > white + 1)
    {
        const int NEXT = white + 1;
        if(songs[NEXT].time > PIVOT.time)
        {
            blue--;
            swap(songs, NEXT, blue);
        }
        else if(songs[NEXT].time == PIVOT.time)
        {
            white++;
        }
        else
        {
            white++;
            red++;
            swap(songs, red, NEXT);
        }
    }
}

void quicksort(vector<Track>& songs, int first, int last)
{//              
    assert(first >= 0);
//               
//                                    
    if (first >= last) return;
    else
    {
        int red, blue;
        //                                      
        //                                      
        //                                      
        dnf2_b(songs, first, last, red, blue);
        quicksort(songs, first, red);
        quicksort(songs, blue, last);
    }
}

//       

typedef int El;

fill_vector(vector<El>& v)
{
    //               
    assert(true);
    //                
    //                                                   
    for(int i = 0; i < rand()%10+3; i++)
        v.push_back(rand()%15);
}

show_vector(vector<El> v)
{
    //               
    assert(true);
    //                
    //                              
    for(int i = 0; i < v.size(); i++)
        cout << v[i] << " ";
    cout << endl;
}
int largest_rec (vector<El>&v, int low, int up)
{
    //               
    assert(low >= 0 && up < v.size());
    //                
    //                                                      
    if ( low >= up )
        return low;
    else
    {
        const int POS = largest_rec (v, low+1, up) ;
        if (v [low] > v [POS])
            return low;
        else
            return POS ;
    }
}

int largest_it(vector<El>& v, int low, int up)
{
    //               
    assert(low >= 0 && up <= v.size());
    //                
    //                                                     
    int POS = low;
    for(int i = low; i <= up-1; i++)
    {
       if(v[i]> v[POS])
            POS = i;
    }
    return POS;
}

bool swap (vector<El>& v, int  i, int  j )
{//	              
    assert ( i >= 0 && j >= 0 ) ;	//                          
    //                          
//                                                                  
    const El HELP = v [i];
    v [i] = v [j] ;
    v [j] = HELP;
}

void sort_rec(vector<El>& v, int n)
{//	              
    assert(n >= 0 && n <= v.size());
//                
//                                  
    if (n > 1)
    {
        const int POS = largest_rec(v, 0, n-1);
        swap (v, POS, n-1);
        sort_rec (v, n-1);
    }
}

void sort_it(vector<El>& v, int n)
{//	              
    assert(n >= 0 && n <= v.size());
//               
//                                  
    while (n > 1)
    {
        const int POS = largest_it(v, 0, n);
        swap (v, POS, n-1);
        n = n-1;
    }
}

int main()
{
    //           
    const int NO_OF_SONGS = read_file ("Tracks.txt");
    if (NO_OF_SONGS < 0)
    {
        cout << "Reading file failed. Program terminates." << endl;
        return NO_OF_SONGS;
    }
    int red = 0;
    int blue = songs.size();
    quicksort(songs, 0, songs.size());
    show_all_tracks(songs, songs.size());

    //       
    vector<El> v;
    fill_vector(v);
    cout << "The unsorted vector: ";
    show_vector(v);
    int sol_rec = largest_rec(v, 0, v.size()-1);
    int sol_it = largest_it(v, 0, v.size());
    cout << "The position of the largest value is " << sol_it << ", the value is " <<v[sol_it] << endl;
    sort_it(v, v.size());
    cout << "The sorted vector: ";
    show_vector(v);
}

