#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>
#define NDEBUG

using namespace std;
//                      
//                          

/*                                                                    
                                            
                                                                     */
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

vector<Track> songs ;
int counter ;

/*                                                                       
                                
                                                               
                                                                         
                                                                       */
bool operator<(const Length& a, const Length& b)
{
    if (a.minutes < b.minutes)
    {
        return true ;
    }
    else if (a.minutes == b.minutes && a.seconds < b.seconds)
    {
        return true ;
    }
    return false ;
}

bool operator>(const Length& a, const Length& b)
{
    if (a.minutes > b.minutes)
    {
        return true ;
    }
    else if (a.minutes == b.minutes && a.seconds > b.seconds)
    {
        return true ;
    }
    return false ;
}

bool operator==(const Length& a, const Length& b)
{
    return ((a.minutes == b.minutes) && (a.seconds == b.seconds)) ;
}

bool operator<(const Track& a, const Track& b)
{
    counter++ ;
    if (a.time < b.time)
    {
        return true ;
    }
    else if (a.time == b.time && a.artist < b.artist)
    {
        return true ;
    }
    else if (a.time == b.time && a.artist == b.artist && a.title < b.title)
    {
        return true ;
    }
    else if (a.time == b.time && a.artist == b.artist && a.title == b.title && a.cd < b.cd)
    {
        return true ;
    }
    return false ;
}

bool operator>(const Track& a, const Track& b)
{
    counter++ ;
    if (a.time > b.time)
    {
        return true ;
    }
    else if (a.time == b.time && a.artist > b.artist)
    {
        return true ;
    }
    else if (a.time == b.time && a.artist == b.artist && a.title > b.title)
    {
        return true ;
    }
    else if (a.time == b.time && a.artist == b.artist && a.title == b.title && a.cd > b.cd)
    {
        return true ;
    }
    return false ;
}
bool operator==(const Track& a, const Track& b)
{
    counter++ ;
    return ((a.artist == b.artist) && (a.cd == b.cd) && (a.year == b.year) && (a.track_no == b.track_no)) ;
}

//	                                 

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
    out << endl ;
    return out ;
}

int read_songs (ifstream& infile, vector<Track>& songs)
{//               
    assert (infile.is_open ()) ;
/*                 
                                                                              
                                                           
*/
    int no_of_read_songs = 0 ;
    do {
        Track song ;
        infile >> song ;
        if (infile)
            songs.push_back(song) ;
        no_of_read_songs++ ;
    }
    while (infile);
    return no_of_read_songs ;
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
    cout << " Read " << NO_OF_SONGS << " tracks." << endl;
    return NO_OF_SONGS;
}

void swap (vector<Track>& data, int  i, int  j )
{//	              
    assert ( i >= 0 && j >= 0 ) ;	//                         
    //                         
//                                                                
    const Track HELP = data [i] ;
    data [i] = data [j] ;
    data [j] = HELP ;
}

void dnf1 (vector<Track>& tracks, int first, int last, int& red, int& blue)
{
    //                                
    //             
    assert(0 <= first && last < tracks.size()) ;
    //                                                                                                                                   
    red = first-1 ;
    blue = last+1 ;
    int white = last+1 ;
    const Track PIVOT= tracks[first+(last-first)/2] ;
    while(red < white -1)
    {
        const int NEXT = white-1 ;
        if(tracks[NEXT]<PIVOT)
        {
            red++ ;
            swap (tracks, red, NEXT) ;
        }
        else if (tracks[NEXT]== PIVOT)
        {
            white-- ;
        }
        else
        {
            white-- ;
            blue-- ;
            swap(tracks, NEXT, blue) ;
        }
    }
}

void dnf2 (vector<Track>& tracks, int first, int last, int& red, int& blue)
{
    //                                
    //             
    assert(0 <= first && last < tracks.size()) ;
    //                                                                                                                                   
    red = first-1 ;
    blue = last+1 ;
    int white = first-1 ;
    const Track PIVOT= tracks[first+(last-first)/2] ;
    while(blue > white +1)
    {
        const int NEXT = white+1 ;
        if(tracks[NEXT] > PIVOT)
        {
            blue-- ;
            swap (tracks, blue, NEXT) ;
        }
        else if (tracks[NEXT]== PIVOT)
        {
            white++ ;
        }
        else
        {
            white++ ;
            red++ ;
            swap(tracks, NEXT, red) ;
        }
    }
}

void quicksort (vector<Track>& tracks, int first, int last)
{
    //             
    assert (0 <= first && last < tracks.size()) ;
    //                                                       
    if(first >= last)
    {
        return ;
    }
    else
    {
        int red ;
        int blue ;
        dnf2(tracks, first, last, red, blue) ;
        quicksort(tracks, first, red) ;
        quicksort(tracks,blue,last) ;
    }
}

//                   
int largest(vector<int>& v, int low, int up)
{
    int pos = 0 ;
    vector<int> stack_vect ;
    if (low >= up)
    {
        return low ;
    }
    else
    {
        while (low < up)
        {
            low++ ;
            stack_vect.push_back(low) ;
        }
        pos = low ;
        while(stack_vect.size() > 0)
        {
            if (v[stack_vect.size()-1] > v[pos])
            {
                pos = v[stack_vect.size()-1] ;
            }
            stack_vect.pop_back() ;
        }
    }
    return pos ;
}

void vec_swap(vector<int>& v, int a, int b)
{
    const int HELP = v[a] ;
    v[a] = v[b] ;
    v[b] = HELP ;
}

void sort_iterative(vector<int>& v, int n)
{
    int pos = 0 ;
    while (n > 1)
    {
        pos = largest(v, 0, n - 1) ;
        vec_swap(v, pos, n-1) ;
        n-- ;
    }
}

int main()
{
    string t = "Tracks.txt" ;
    read_file(t) ;
    quicksort(songs, 0, songs.size()-1) ;
    for(int i = 0; i< songs.size(); i++)
    {
        cout << songs[i] ;
    }
}

