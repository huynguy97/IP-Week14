#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>
#include <algorithm>
#include <sstream>
using namespace std;
//                     
//                                                                                                                        

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

const int MAX_NO_OF_SONGS = 6000;           //                                
Track songs [MAX_NO_OF_SONGS];              //                                     

vector<Track> tot_songs;

bool operator<(const Track& a, const Track& b)
{
    if (a.artist == b.artist)
    {
        if (a.cd == b.cd)
        {
            if (a.year == b.year)
            {
                if (a.track_no == b.track_no)
                    return a.track_no == b.track_no;
                else
                    return a.track_no < b.track_no;
            }
            else
                return a.year < b.year;
        }
        else
            return a.cd < b.cd;
    }
    else
        return a.artist < b.artist ;

}

bool operator==(const Track& a, const Track& b)
{

    return a.artist == b.artist && a.cd == b.cd && a.track_no == b.track_no && a.year == b.year;
}

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

istream& operator>> (istream& in, Track& track)
{//               
    assert (true) ;
/*                 
                                                                                                                   
                                      
*/
    string linebreak;
    getline(in, linebreak);
    if (linebreak.empty()) {
        getline(in, track.artist);
        if (track.artist.empty()) {
            return in;
        }
    } else {
        track.artist = linebreak;
    }
    getline(in, track.cd);
    string yearstring;
    getline(in, yearstring);
    track.year = stoi(yearstring);
    string tracknumstring;
    getline(in, tracknumstring);
    track.title = stoi(tracknumstring);
    getline(in, track.title);
    getline(in, track.tags);
    Length length;
    string l;
    stringstream ss;
    getline(in, l);
    ss << l;
    ss >> length;
    track.time = length;
    getline(in, track.country);
    return in;
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
int read_songs (ifstream& infile, vector<Track>&songs)
{//               
    assert (infile.is_open ()) ;
/*                 
                                                                              
                                                           
*/
    Track track;
    int count = 0;
    while (infile >> track) {
        count++;
        songs.push_back(track);
    }
    return count;
}

int read_file (string filename)
{//               
    assert (tot_songs.size() == 0) ;
/*                 
                                                                              
                                                                                             
                                        
*/
    ifstream songsDBS (filename.c_str());
    if (!songsDBS)
    {
        cout << "Could not open '" << filename << "'." << endl;
        return -1;
    }
    cout << "Reading '" << filename << "'." << endl;
    const int NO_OF_SONGS = read_songs (songsDBS, tot_songs);
    songsDBS.close();
    cout << " Read " << NO_OF_SONGS << " tracks." << endl;
    return NO_OF_SONGS;
}

//                                                                           
void show_all_tracks (Track songs [MAX_NO_OF_SONGS], int no_of_songs)
{//               
    assert (no_of_songs < MAX_NO_OF_SONGS) ;
/*                 
                                                                  
*/
    for (int i = 0 ; i < no_of_songs; i++)
        cout << i+1 << ". " << songs[i] << endl ;
}

/*                                                                       
                                                         
                                                                       */
/*
            
 
               	               
             	             
   

                                
   	              
                                     
                   
                                              
*/	Slice s = { from, to } ;
    return s ;
}

bool valid_slice (Slice s)
{//               
    assert (true) ;
/*                 
                                                                                      
*/
    return 0 <= s.from && s.from <= s.to ;
}

typedef int El ;                //                                                       

bool is_sorted (vector<Track>& tot_songs, Slice s)
{//	              
    assert (valid_slice(s)) ;	//                           
//	               
//	                 	                                
//						                                
//						   
//						                            
    bool sorted = true ;
    for (int i = s.from; i < s.to && sorted; i++)
        if (tot_songs[i] > tot_songs[i+1])
            sorted = false ;
    return sorted ;
}

int find_position (vector<Track>& tot_songs, Slice s, Track y)
{//	              
    assert (valid_slice(s) && is_sorted(tot_songs,s)) ;    //                           
//	                                          
    for ( int i = s.from ; i <= s.to ; i++ )
        if ( y <= tot_songs [i] )
            return i ;
    return s.to+1;
}

void shift_right ( vector<Track>& tot_songs, Slice s )
{//	              
    assert (valid_slice (s)) ;	//                               
//	                               	  	                
//			    	               	  	                  
//						   
//			    	             		  	              
    for ( int i = s.to+1 ; i > s.from ; i-- )
        tot_songs [i]  = tot_songs [i-1] ;
}

void insert ( vector<Track>& tot_songs, int& length, Track y )
{//               
    Slice s = mkSlice(0,length-1) ;
    assert (length >= 0 && is_sorted (tot_songs, s)) ;
/*                 
                                                                                     
                                   
*/
    const int POS = find_position (tot_songs, mkSlice (0, length-1), y) ;
    if (POS < length)
        shift_right ( tot_songs, mkSlice (POS, length-1) ) ;
    tot_songs [POS] = y ;
    length++;
}
*/
void swap (vector<Track>& tot_songs, int  i, int  j )
{//	              
    assert ( i >= 0 && j >= 0 ) ;	//                         
    //                         
//                                                                
    const Track HELP = tot_songs[i];
    tot_songs [i] = tot_songs [j] ;
    tot_songs [j] = HELP;
}
/*
  	                           
                                                           
 
                    
                             
                                                         
     
 

  	                           
                                                           
   	              
                              	                          
  	                                                            
  	                                               
                              
                                                          
                                                         
                                 
                        
 

                                                            
 	                                                         
                                                                                  
                                         
     
 

  	                        
                                                 
   	              
                            	                            
  	               
  	                                                    
  	                                        
                           
                                          
                                             
         	                            
                               
         
                      
 

                                                         
 
                                                           
                  
 

*/
/*                                                                       
                                      
                   
                                                                      
                                           
                                          
                                                                       */
/*
                                                                               
                                                          

                                   
 
                                                                
                                                
                                                              
                
                   
                                                                          
                                                 
 
*/

void dnf (vector<Track>& tot_songs, int first, int last, int& red, int& blue)
{//   
    assert(true);
    //                      
    red = first-1;
    blue = last+1;
    int white = last+1;
    const Track PIVOT = tot_songs[first+(last-first)/2];
    while (red < white -1)
    {
        const int NEXT = white -1;
        if (tot_songs[NEXT] < PIVOT)
        {
            red++;
            swap(tot_songs,red,NEXT);
        }
        else if (tot_songs[NEXT] == PIVOT)
        {
            white--;
        }
        else
        {
            white--; blue--;
            swap(tot_songs,NEXT,blue);
        }
    }
}

void quicksort (vector<Track>& tot_songs, int first, int last)
{
    //   
    assert (0 <= first && last <  tot_songs.size());
    //                                                    
    if (first >= last) return;
    else
    {
        int red, blue;
        dnf (tot_songs,first,last,red,blue);
        quicksort(tot_songs,first,red);
        quicksort(tot_songs,blue,last);
    }
}

void adapted_dnf (vector<Track>& tot_songs, int first, int last, int& red, int& blue)
{
    red = first-1;
    blue = last+1;
    int white = last+1;
    const Track PIVOT = tot_songs[first+(last-first)/2];
    while (red < white -1)
    {
        const int NEXT = white +1;
        if (tot_songs[NEXT] > PIVOT)
        {
            blue++;
            swap(tot_songs,blue,NEXT);
        }
        else if (tot_songs[NEXT] == PIVOT)
        {
            white++;
        }
        else
        {
            white--; red--;
            swap(tot_songs,NEXT,blue);
        }
    }
}

int iterative_largest (vector<El>& v, int low, int up)
{
    vector<El> Stack;
    while (low < up)
    {
        Stack.push_back(low);
        low++;
        const int POS = low;
        if (v[low] <= v[POS]) return POS;
    }

    return low;

}

void iterative_sort(vector<El>& v, int n)
{
while (n <= 1)
{
    const int POS = iterative_largest(v,0,n-1);
    swap(v,POS,n-1);
    n--;
}
}

int main()
{
    const int NO_OF_SONGS = read_file ("Tracks.txt");
    if (NO_OF_SONGS < 0)
    {
        cout << "Reading file failed. Program terminates." << endl;
        return NO_OF_SONGS;
    }
/*                                             
                                                                    
              
     
                                                                           
                                                                           
                                                                           
                                                
     
                                      */

    quicksort(tot_songs,0,tot_songs.size()-1);
    cout << "k";
    show_all_tracks (songs,NO_OF_SONGS) ;
    cout << "kk";

    return 0;
}

