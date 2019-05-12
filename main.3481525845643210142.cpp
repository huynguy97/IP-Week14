#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>

//                      
//                      

using namespace std;

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
struct TrackDisplay
{
	bool showArtist;						//                             
	bool showAlbum;							//                       
	bool showYear;							//                                 
	bool showTrack;							//                           
	bool showTitle;							//                          
	bool showTags;                          //                   
	bool showLength;						//                           
	bool showCountry;                       //                                      
};

const int MAX_NO_OF_SONGS = 6000;
vector<Track> songs;
TrackDisplay all_true = {true, true, true, true, true, true, true, true} ;

/*                                                                                 
                                                                                     

                                                                                                                                                                                        
                                                                                                                                                                                        
                                                                                                                                                                                        
                                                                                                                                                                                        
                                                                                                                                                                                        
                                                                                                                                                                                        
                                                                                                                                                                                        
                                                                                                                                                                                        
                                                                                                                                                                                        
                                                                                                                                                                                        
                                                                                                                                                                                        
                                                                                                                                                                                        
                                                                                                                                                                                        
                                                                                                                                                                                        
                                                                                                                                                                                        
                                                                                                                                                                                        
                                                                                                                                                                                        
                                                                                                                                                                                        
                                                                                                                                                                                        
                                                                                                                                                                                        
                                                                                                                                                                                        
                                                                                                                                                                                        
                                                                                                                                                                                        
                                                                                                                                                                                       
                                                                                                                                                                                       
                                                                                                                                                                                       
                                                                                                                                                                                       
                                                                                                                                                                                       
                                                                                                                                                                                       
                                                                                                                                                  
                                                                                                                                                                                       
                                                                                                                                                                                       
                                                                                                                                                                                       
                                                                                                                                                                                       
                                                                                                                                                                                              
                                                                                                                                                                                              
                                                                                                                                                                                              
                                                                                                                                                                                              
                                                                                                                                                                                              
                                                                                                                                                                                              
                                                                                                                                                                                              
                                                                                                                                                                                              
                          
                                                                         
                                                      
                                                                       */

ostream& operator<< (ostream& out, const Length length)
{//              
    assert (true) ;
/*                
                                                                                          
*/
    out << length.minutes << ':'  << length.seconds ;
    return out ;
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

Length operator+ (const Length& a, const Length& b)
{//              
    assert (0 <= a.minutes && 0 <= a.seconds && a.seconds < 60 && 0 <= b.minutes && 0 <= b.seconds && b.seconds < 60) ;
/*                
                                 
*/
    Length sum ;
    sum.minutes = a.minutes + b.minutes ;
    int total_seconds ;
    total_seconds = a.seconds + b.seconds ;
    if (total_seconds >= 60)
    {
        total_seconds = total_seconds - 60 ;
        sum.minutes++ ;
    }
    sum.seconds = total_seconds ;
    return sum ;
}
/*                                                                       
                                              
                                                                       */
void show_track (Track track, TrackDisplay lt)
{//              
    assert (true) ;
/*                
                                                                                         
*/
    if (lt.showArtist)
        cout << track.artist << "\n" ;
    if (lt.showAlbum)
        cout << track.cd << "\n" ;
    if (lt.showYear)
        cout << track.year << "\n" ;
    if (lt.showTrack)
        cout << track.track_no << "\n" ;
    if (lt.showTitle)
        cout << track.title << "\n" ;
    if (lt.showTags)
        cout << track.tags << "\n" ;
    if (lt.showLength)
        cout << track.time << "\n" ;
    if (lt.showCountry)
        cout << track.country << "\n" ;
}

/*                                                                       
                                                             
                                                                       */
bool operator< (const Length& a, const Length& b)
{//             
    assert(true) ;
//                                                                    
    if (a.minutes == b.minutes)
        return a.seconds < b.seconds ;
    return a.minutes < b.minutes ;
}

bool operator== (const Length& a, const Length& b)
{//             
    assert(true) ;
//                                                                     
    if (a.seconds == b.seconds)
        return a.minutes == b.minutes ;
    return a.seconds == b.seconds ;
}
/*                                                                       
                                                                
                                                              
                                                                       */
bool operator<(const Track& a, const Track& b)
{//             
    assert(true) ;
//                                                      
//                                                                  
    if (a.time == b. time) //                                                  
    {                       //                                                  
        if (a.artist == b.artist)
        {
            if (a.cd == b.cd)
            {
                if (a.year == b.year)
                {
                    return a.track_no < b.track_no ;
                }
                return a.year < b.year ;
            }
            return a.cd < b.cd ;
        }
        return a.artist < b.artist ;
    }                           //                                                  
    return a.time < b.time ;    //                                                  
}

bool operator==(const Track& a, const Track& b)
{//             
    assert(true) ;
//                                                       
//                                                                  
    return (a.time == b.time) && (a.artist == b.artist) && (a.cd == b.cd) && (a.year == b.year) && (a.track_no == b.track_no);   /*                                                 */
    //                                                            
    //                                                 
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

//                                                                           
int read_songs (ifstream& infile, vector<Track>& songs )
{//               
    assert (infile.is_open ()) ;
/*                 
                                                                              
                                                           
*/
    int no_of_read_songs = 0 ;
    do {
        Track song ;
        infile >> song ;
        if (infile)
        {
            songs.push_back(song) ;
            no_of_read_songs++ ;
        }
    }
    while (infile);
    return no_of_read_songs ;
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

/*                                                                       
                               
                                                                       */
void swaptrack(vector<Track>& songs, int a, int b)
{//              
    assert(a >= 0 && a < songs.size() && b >= 0 && b < songs.size()) ;
//                                           
    Track help = songs[b] ;
    songs[b] = songs[a] ;
    songs[a] = help ;
}

void DNF(vector<Track>& songs, int first, int last, int& red, int& blue)
{//              
    assert(true) ;
//                                                                           
    red = first - 1 ;
    blue = last + 1 ;
    int white = last + 1 ;
    const Track PIVOT = songs[first+(last-first)/2] ;
    while (red < white - 1)
    {
        const int NEXT = white - 1 ;
        if (songs[NEXT] < PIVOT)
        {
            red++ ;
            swaptrack(songs, red, NEXT) ;
        }
        else if (songs[NEXT] == PIVOT)
            white-- ;
        else
        {
            white-- ;
            blue-- ;
            swaptrack(songs, NEXT, blue) ;
        }
    }
}

void quicksort(vector<Track>& songs, int first, int last)
{//              
    assert(true) ;
//                                                    
    if (first >= last)
        return ;
    else
    {
        int red, blue ;
        DNF(songs, first, last, red, blue) ;
        quicksort(songs, first, red) ;
        quicksort(songs, blue, last) ;
    }
}
/*                                                                       
                          
                                                                       */
void DNF_adj(vector<Track>& songs, int first, int last, int& red, int& blue)
{//              
    assert(true) ;
//                                                                                    
    red = first - 1 ;
    blue = last + 1 ;
    int white = first -1 ;
    const Track PIVOT = songs[first+(last-first)/2] ;
    while (blue > white + 1)
    {
        const int NEXT = white + 1 ;
        if (songs[NEXT] < PIVOT)
        {
            red++ ;
            white++ ;
            swaptrack(songs, red, NEXT) ;
        }
        else if (songs[NEXT] == PIVOT)
            white++ ;
        else
        {
            blue-- ;
            swaptrack(songs, NEXT, blue) ;
        }
    }
}

void quicksort_adj(vector<Track>& songs, int first, int last)
{//              
    assert(true) ;
//                                                                      
    if (first >= last)
        return ;
    else
    {
        int red, blue ;
        DNF_adj(songs, first, last, red, blue) ;
        quicksort(songs, first, red) ;
        quicksort(songs, blue, last) ;
    }
}
/*                                                                       
                                    
                                                                       */

int largest(vector<Track>& v, int low, int up)
{
    if (low >= up)
        return low ;
    else
    {
        const int POS = largest(v, low + 1, up) ;
        if (v[low] > v[POS])
            return low ;
        else
            return POS ;
    }
}

void sortv(vector<Track>& v, int n)
{
    if (n > 1)
    {
        const int POS = largest (v, 0, n-1) ;
        swaptrack(v, POS, n-1) ;
        sortv (v, n-1) ;
    }
}

int largest_it(vector<Track>& v, int low, int up)
{   //             
    assert(0 <= low && up < v.size());
    int biggest = up;
    //                                                                                                 
    while(low < up)
    {
        if( v[low] > v[biggest])
            biggest = low;
        low++;
    }
    return biggest;
}

void sort_it(vector<Track>& v, int n)
{
    //                
    assert(true);
    //                                               
    while(n > 0)
    {
         int number = largest_it(v, 0, n);
         swaptrack(v, number, n);
         n--;

    }

}

/*                                                                       
           
                                                                       */
int main()
{
    ifstream infile ;
    infile.open("Tracks.txt") ;
    read_songs(infile, songs) ;
   //                                                                                                  
    quicksort_adj(songs, 0, songs.size()-1);
    TrackDisplay only_length = {songs.size()-1} ; //                                                         
    quicksort_adj(songs, 0, songs.size()-1) ;
    for (int i = 0 ; i < songs.size() ; i++)
    {
        show_track(songs[i], only_length) ; //                                                                                             
        //                                               
        cout << '\n' ;
    }
    return 0 ;
}

