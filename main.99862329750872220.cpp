//                                              
//                                               

/*                                                                    
                                              
            
                                                                                                            
                                  
                              
                                                           
                                                                    
                                                          
                                                               
                                                                     */
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>

#define NDEBUG ;
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

const int MAX_NO_OF_SONGS = 6000;           //                                
vector<Track> songs;              //                                     
int number_of_comparisons = 0;
/*                                                                       
                                
                                                               
                                                                         
                                                                       */

bool operator<(const Length& a, const Length& b)
{
    if (a.minutes!=b.minutes)
        return a.minutes < b.minutes;
    else
        return a.seconds < b.seconds;
}

bool operator==(const Length& a, const Length& b)
{
    return a.minutes == b.minutes && a.seconds == b.seconds;
}

bool operator>(const Length& a, const Length& b)
{
return b < a ;
}

bool operator<=(const Length& a, const Length& b)
{
return !(b < a) ;
}

bool operator>=(const Length& a, const Length& b)
{
return b <= a ;
}

bool operator!=(const Length& a, const Length& b)
{
    return !(a==b);
}

/*
                                              
 
                            
                         
                               
                                 
                                    
                                
                                 
        
                           
 

                                               
 
                            
                                                                         
                         
 

*/
bool operator<(const Track& a, const Track& b)
{
    number_of_comparisons++;
    if (a.artist != b.artist)
        return a.artist < b.artist ;    //                                                
    else if (a.cd != b.cd)
        return a.cd < b.cd;
    else if (a.year != b.year)
        return a.year < b.year;
    else return a.track_no < b.track_no;
}

bool operator==(const Track& a, const Track& b)
{
    number_of_comparisons++;
    return a.artist == b.artist && a.cd == b.cd && a.year == b.year
        && a.track_no == b.track_no ;   //                                                
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

int minimum(int a, int b)
{
    if (a<b)
        return a;
    else
        return b;
}

int maximum(int a, int b)
{
    if (a>b)
        return a;
    else
        return b;
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
    out << endl ;
    return out ;
}

//                                                                           
int read_songs (ifstream& infile, vector<Track>& songs, int number_songs)
{//               
    assert (infile.is_open ()) ;
/*                 
                                                                              
                                                           
*/
    Track song;
    infile >> song;
    while (infile && songs.size()<(unsigned)number_songs)
    {
        songs.push_back(song);
        infile >> song;
    }
    return songs.size() ;
}

int read_file (string filename, int number_songs)
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
    //                                                
	const int NO_OF_SONGS = read_songs (songsDBS, songs, number_songs);
	songsDBS.close();
	//                                                      
	return NO_OF_SONGS;
}

//                                                                           
void show_all_tracks (vector<Track>& songs, int no_of_songs)
{//               
    assert ((unsigned)no_of_songs <= songs.size()) ;
/*                 
                                                                  
*/
    for (int i = 0 ; i < no_of_songs; i++)
        cout << i+1 << ". " << songs[i] << endl ;
}

/*                                                                       
                                                         
                                                                       */
struct Slice
{
	int from ; 	//             
	int to ; 	//           
} ;

Slice mkSlice (int from, int to)
{//	              
	assert (0 <= from && from <= to);
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

bool is_sorted (vector<Track>& data, Slice s)
{//	              
	assert (valid_slice(s)) ;	//                           
//	               
//	                 	                                
//						                                
//						   
//						                            
	bool sorted = true ;
	for (int i = s.from; i < s.to && sorted; i++)
		if (data[i] > data[i+1])
			sorted = false ;
	return sorted ;
}

int find_position (vector<Track>& data, Slice s, Track y )
{//	              
	assert (valid_slice(s) && is_sorted(data,s)) ;    //                           
//	                                          
	for ( int i = s.from ; i <= s.to ; i++ )
		if ( y <= data [i] )
			return i ;
	return s.to+1;
}

void shift_right (vector<Track>& data, Slice s )
{//	              
	assert (valid_slice (s)) ;	//                               
//	                               	  	                
//			    	               	  	                  
//						   
//			    	             		  	              
	for ( int i = s.to+1 ; i > s.from ; i-- )
		data [i]  = data [i-1] ;
}

void insert (vector<Track>& data, int& length, Track y )
{//               
    Slice s = mkSlice(0,length-1) ;
    assert (length >= 0 && is_sorted (data, s)) ;
/*                 
                                                                                     
                                   
*/

	const int POS = find_position (data, mkSlice (0, length-1), y) ;
	if (POS < length)
		shift_right ( data, mkSlice (POS, length-1) ) ;
	data [POS] = y ;
	length++;
}

void swap (vector<Track>& data, int  i, int  j )
{//	              
	assert ( i >= 0 && j >= 0 ) ;	//                         
						            //                         
//                                                                
	const Track HELP = data [i];
	data [i] = data [j] ;
	data [j] = HELP;
}

void dnf(vector<Track>& data, int first, int last, int& red, int& blue)
{
//	              
	assert(first>=0 && last>=first && last<data.size());
/*                                                                                  
                                                                                
                      
*/
    red = first-1;                              //              
    blue = last+1;                              //                
    int white = first-1;                        //                
    const Track PIVOT = data [first+(last-first)/2];
    while(white< blue-1)                        //                 
    {
        const int NEXT= white+1;                //             
        if(data[NEXT] < PIVOT)                  //               
        {
            red++;  white++;                    //                      
            swap (data, red, NEXT) ;
        }
        else if(data[NEXT] == PIVOT)            //                 
            white++;                            //                      
        else                                    //                
        {
            blue--;                             //                      
            swap (data, NEXT, blue);
        }
    }
}

void quicksort(vector<Track>& data, int first, int last)
{ //     
    assert(0 <= first && last < data.size()) ;
    //                                          
    if (first >= last) return;
    else
    {
        cout << "One more iteration done" << endl;
        int red, blue ;

        dnf(data, first, last, red, blue) ;
        if(red>=0)
            quicksort(data, first, red) ;
        quicksort(data, blue, last) ;
    }

}

int largest(vector<Track>& v, int low, int up)
{
    //     
    assert(0 <= low && up < v.size()) ;
    //                                                                         
    //           
    int biggest = up;
    while(low < up)
    {
        if(v[low]>v[biggest])
            biggest = low;
        low++;
    }
    return biggest;
}

void sort(vector<Track>& v, int n)
{
    //     
    assert(true) ;
    //                                                                            
    //              
    while(n>0)
    {
        int pos = largest(v,0,n);
        swap(v,pos,n);
        n--;
    }
}

/*                                                                       
                                      
                   
                                                                      
                                           
                                          
                                                                       */

int main()
{
    songs.clear();
    int number_songs = 5900;
    const int NO_OF_SONGS = read_file ("Tracks.txt", number_songs);

    if (NO_OF_SONGS < 0)
    {
        cout << "Reading file failed. Program terminates." << endl;
        return NO_OF_SONGS;
    }

    quicksort(songs, 0, songs.size()-1);
    show_all_tracks (songs,NO_OF_SONGS) ;

	return 0;
}

