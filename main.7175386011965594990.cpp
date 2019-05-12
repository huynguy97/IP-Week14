/*
             
                      
              
*/

#define NDEBUG
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>

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
vector<Track> songs;
int counter;

/*                                                                       
                                
                                                               
                                                                         
                                                                       */
bool operator<(const Length& a, const Length& b)
{
    //             
    assert(true);
    //                                                            
    if(a.minutes == b.minutes)
        return a.seconds < b.seconds; //                                                 
    else
        return a.minutes < a.minutes;
}

bool operator==(const Length& a, const Length& b)
{
    //             
    assert(true);
    //                                                        
    return (a.minutes==b.minutes && a.seconds==b.seconds);
}

bool operator==(const Track& a, const Track& b)
{
    //             
    assert(true);
    //                                                
    counter++;
    return (a.time==b.time && a.artist==b.artist && a.cd==b.cd && a.year==b.year && a.track_no==b.track_no);
}

bool operator<(const Track& a, const Track& b)
{
    //             
    assert(true);
    //                                                                 
    counter++;
/* 
                                               
                               
 */
    if(a.artist != b.artist)
        return a.artist < b.artist; //                                                                                                                                
    if(a.cd != b.cd)
        return a.cd < a.cd;
    if(a.year != b.year)
        return a.year < b.year;
    if(a.track_no != b.track_no)
        return a.track_no < b.track_no;

    return false; //                                                                      
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

int read_songs (ifstream& infile, vector<Track>& songs_vector)
{//               
    assert (infile.is_open ()) ;
/*                 
                                                                              
                                                           
*/
    int no_of_read_songs = 0;
    do {
        Track song;
        infile >> song;
        if(infile)
        {
            songs_vector.push_back(song);
            no_of_read_songs++;
        }
    }
    while (infile && no_of_read_songs < MAX_NO_OF_SONGS);
    return no_of_read_songs ;
}

int size(vector<Track>& tracks)
{
    return static_cast<int>(tracks.size());
}

int read_file (string filename)
{//               
    assert (size(songs) == 0) ;
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
void show_all_tracks (vector<Track> songs, int no_of_songs)
{//               
    assert (no_of_songs < MAX_NO_OF_SONGS) ;
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

//	                           
int smallest_value_at ( vector<Track>& data, Slice s )
{//	              
	assert (valid_slice (s)) ;	//                        
//	                                                            
//	                                               
	int smallest_at = s.from ;
	for ( int index = s.from+1 ; index <= s.to ; index++ )
		if ( data [index] < data [smallest_at] )
			smallest_at = index ;
	return smallest_at ;
}

void copy_vector(vector<Track>& copy_to, vector<Track>& copy_from, Slice s)
{//	              
	assert (valid_slice(s));
//	                                                             
    int j = 0;
    for (int i = s.from; i <= s.to; i++)
    {
        copy_to.push_back(copy_from[i]);
        j++;
    }
}

/*                                    */

/*             
                                                                       
                
                                                              
                                                                  

                                       
                                        
                                             
                                                   

                                               
     
                                                   
                                                 
             
                                                 
                                      
             
                                                           
                                                
                                  
         
                                                      
                                   
         
     
 
 */

//           
void dnf(vector<Track>& data, int first, int last, int& red, int& blue)
{//             
    assert (0 <= first && last < size(data) && first <= last);
    //                                                            

    red = first-1;    //               
    blue = last+1;   //                 
    int white = last+1;  //                  
    int white_last = white;  //                
    const Track PIVOT = data[first+(last-first)/2];

    while (white_last < blue - 1) //                 
    {
        const int NEXT = blue - 1;  //            
        if (data[NEXT] < PIVOT) //               
            {
                red++;  //                       
                swap(data, red, NEXT);
            }
        else if (data[NEXT] == PIVOT)   //                 
            white--;   //                      
        else    //                
        {
            white--; blue--;   //                     
            swap(data, NEXT, blue);
        }
    }
}

void quicksort (vector<Track>& data, int first, int last)
{//             
    assert (0 <= first && last < size(data));
//                                                    
    if(first >= last)
        return;
    else
    {
        int red, blue ;
        dnf (data, first, last, red, blue);
        quicksort (data, first, red);
        quicksort (data, blue, last);
    }
}

//           
int largest(vector<Track>& v, int low, int up)
{//             
    assert(true);
    //                                                       
    if(low >= up)
        return low;
    else
    {
        const int POS = largest(v,low+1,up);
        if(v[low] > v[POS])
            return low;
        else
            return POS;
    }
}

void sort(vector<Track>& v, int n)
{//             
    assert(n>=0 && n < size(v));
//                                        
    while(n>1)
    {
        n--;
        const int POS = largest(v,0,n);
        swap(v,POS,n);
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

    //                                 
    sort(songs,NO_OF_SONGS);

    show_all_tracks(songs,NO_OF_SONGS);

	return 0;
}

