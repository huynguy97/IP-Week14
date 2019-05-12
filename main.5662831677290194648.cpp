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

vector<Track> songs;

/*                                                                       
                                
                                                               
                                                                         
                                                                       */
bool operator<(const Length& a, const Length& b)
{
    if (a.minutes != b.minutes)
        return a.minutes < b.minutes;
    return a.seconds < b.seconds;
}

bool operator==(const Length& a, const Length& b)
{
    return (a.minutes == b.minutes && a.seconds == b.seconds);
}

//	                                  
bool operator!=(const Length& a, const Length& b)
{
    return !(a == b);
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

bool operator<(const Track& a, const Track& b)
{
    //      
    /*                         
                                   
                     
                           
                         
                               
                                   */
    //      
    if (a.time != b.time)
        return a.time < b.time;
    if (a.artist != b.artist)
        return a.artist < b.artist;
    if (a.title != b.title)
        return a.title < b.title;
    return a.cd < b.cd;
}

bool operator==(const Track& a, const Track& b)
{
    //      
    /*                                
                            
                                
                                     
              */
    //      
    return ( a.artist == b.artist &&
             a.cd == b.cd &&
             a.title == b.title &&
             a.time == b.time
            );
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
            songs.push_back(song);
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
	cout << " Read " << NO_OF_SONGS << " tracks." << endl;
	return NO_OF_SONGS;
}

void show_all_tracks (vector<Track>& songs)
{//               
    assert (true) ;
/*                 
                                                                  
*/
    for (int i = 0 ; i < songs.size(); i++)
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
	assert (valid_slice(s));	//                           
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

int find_position ( vector<Track>& data, Slice s, Track y )
{//	              
	assert (valid_slice(s) && is_sorted(data,s)) ;    //                           
//	                                          
	for ( int i = s.from ; i <= s.to ; i++ )
		if ( y <= data [i] )
			return i ;
	return s.to+1;
}

void shift_right ( vector<Track>& data, Slice s )
{//	              
	assert (valid_slice (s)) ;	//                               
//	                               	  	                
//			    	               	  	                  
//						   
//			    	             		  	              
	for ( int i = s.to+1 ; i > s.from ; i-- )
		data [i]  = data [i-1] ;
}

void insert ( vector<Track>& data, int& length, Track y )
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

typedef int El;

void swap (vector<El>& data, int  i, int  j )
{//	              
	assert ( i >= 0 && j >= 0 ) ;	//                         
						            //                         
//                                                                
	const El HELP = data [i];
	data [i] = data [j] ;
	data [j] = HELP;
}

void dnf (vector<Track>& data, int first, int last, int& red, int& blue)
{
    //              
    assert(first >= 0 && first <= last && last < data.size());
    //               
    //
    red = first-1; //               
    blue = last+1; //                 
    int white = first-1; //                 
    const Track PIVOT = data [first+(last-first)/2];
    while (white < blue - 1) //                 
    {
        const int NEXT = white + 1; //             
        if (data[NEXT] < PIVOT) //               
        {
            red++;
            white++; //                       
            swap (data, red, NEXT) ;
        }
        else if (data[NEXT] == PIVOT) //                 
            white++ ; //                      
        else //                
        {
            blue--; //                     
            swap (data, NEXT, blue);
        }
    }
}

void quicksort (vector<Track>& data, int first, int last)
{
    //              
    assert(true);
    //               
    //                                    
    //                                     
    if (first >= last)
        return ;
    else {
        int red, blue ;
        dnf (data, first, last, red, blue) ;
        quicksort (data, first, red) ;
        quicksort (data, blue, last) ;
    }
}

int largest_recursive (vector<El>& v, int low, int up)
{
    if ( low >= up) //            
        return low ; //            
    else
    {
        const int POS = largest_recursive (v, low+1, up) ; //                                                   
        if (v [low] > v [POS]) //                
            return low ;
        else
            return POS ;
    }
}

int largest_iterative (vector<El>& v, int low, int up)
{
    //              
    assert(low >= 0 && low < up && up < v.size());
    //               
    //                                                      
    //                                   
    vector<El> stack;
    while ( low < up) //             
    {
        stack.push_back(low);
        low = low+1;
    }
    //                           
    stack.push_back(low);
    while (stack.size() > 1)
    {
        const int POS = stack[stack.size()-1];
        stack.pop_back();
        low = stack[stack.size()-1];
        stack.pop_back();
        if (v [low] > v [POS]) //                
            stack.push_back(low) ;
        else
            stack.push_back(POS) ;
    }
    return stack[0];
}

void sort_recursive (vector<El>& v, int n)
{
    if (n > 1) //             
    {
        const int POS = largest_recursive (v, 0, n-1) ; //            
        swap (v, POS, n-1) ; //         
        sort_recursive (v, n-1) ; //                                  
    }
}

void sort_iterative (vector<El>& v, int n)
{
    //              
    assert(n >= 0 && n <= v.size());
    //               
    //                                                                        
    //                                            
    while (n > 1) //             
    {
        const int POS = largest_iterative (v, 0, n-1) ; //            
        swap (v, POS, n-1) ; //         
        n-- ; //                                       
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
    quicksort(songs, 0, songs.size()-1);
    show_all_tracks(songs);

    //                     
    vector<El> v = {37, 2, 3, 6, 2, 76, 23, 5, 6, 124, 404, 976, 34, 67};

    cout << endl << "Output of largest_iterative:" << endl;
    cout << v[largest_iterative(v, 0, v.size()-1)] << endl;
    cout << endl << "Output of sort_iterative:" << endl;
    sort_iterative(v, v.size());
    for (int i = 0; i < v.size(); i++)
        cout << v[i] << endl;
    return 0;
}

