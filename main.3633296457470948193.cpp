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
vector<Track> songs;              //                                     

/*                                                                       
                                
                                                               
                                                                         
                                                                       */
int counter = 0;

bool operator< (Length a, Length b) {
    //    
    assert(true);
    //     
    //                                                                                                            
    if (a.minutes == b.minutes) {
        return a.seconds < b.seconds;
    } else {
        return a.minutes < b.minutes;
    }
}

bool operator== (Length a, Length b) {
    //    
    return a.minutes == b.minutes && a.seconds == b.seconds;
}

bool operator!= (Length a, Length b) {
    return !(a==b);
}

bool operator> (Length a, Length b) {
    return b < a;
}

bool operator<= (Length a, Length b) {
    return a < b || a == b;
}

bool operator>= (Length a, Length b) {
    return a > b || a == b;
}

bool operator<(const Track& a, const Track& b)
{
    counter ++;
    if (a.time != b.time)
    {
        return a.time < b.time;
    } else if (a.artist != b.artist)
    {
        return a.artist < b.artist;    /*                                                 */
    } else if (a.cd != b.cd)
    {
        return a.cd < b.cd;
    } else if (a.year != b.year)
    {
        return a.year < b.year;
    } else
    {
        return a.track_no < b.track_no;
    }
}

bool operator==(const Track& a, const Track& b)
{
    counter ++;
    return a.artist == b.artist && a.cd == b.cd && a.year == b.year && a.track_no == b.track_no;   /*                                                 */
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
template <typename T>
 size(vector<T> v) {
    return static_cast<int>(v.size());
}

int maximum(int a, int b) {
    //    
    assert(true);
    //     
    //                                            
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

int minimum(int a, int b) {
    //    
    assert(true);
    //     
    //                                            
    if (a > b) {
        return b;
    } else {
        return a;
    }
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

//                                                                           
int read_songs (ifstream& infile, vector<Track>& songs)
{//               
    assert (infile.is_open ()) ;
/*                 
                                                                              
                                                           
*/
    int no_of_read_songs = 0 ;
    do {
        Track song ;
        infile >> song ;
        if (infile){
            songs.push_back(song);
            no_of_read_songs++;
        }
    }
    while (infile && no_of_read_songs < MAX_NO_OF_SONGS);
    return no_of_read_songs ;
}

int read_file (string filename)
{//               
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

typedef Track El ;                //                                                       

bool is_sorted (vector<El> &data, Slice s)
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

int find_position (vector<El> &data, Slice s, El y )
{//	              
	assert (valid_slice(s) && is_sorted(data,s)) ;    //                           
//	                                          
	for ( int i = s.from ; i <= s.to ; i++ )
		if ( y <= data [i] )
			return i ;
	return s.to+1;
}

void shift_right (vector<El> &data, Slice s )
{//	              
	assert (valid_slice (s)) ;	//                               
//	                               	  	                
//			    	               	  	                  
//						   
//			    	             		  	              
	for ( int i = s.to+1 ; i > s.from ; i-- )
		data [i]  = data [i-1] ;
}

void swap (vector<El> &data, int  i, int  j )
{//	              
	assert ( i >= 0 && j >= 0 ) ;	//                         
						            //                         
//                                                                
	const El HELP = data [i];
	data [i] = data [j] ;
	data [j] = HELP;
}

void dnf (vector<El>& data, int first, int last, int& red, int& blue) {
    //   
    assert(first <= last);
    //    
    //                                                         
    red = first-1; //               
    blue = last+1; //                 
    int white = first-1; //                 
    const El PIVOT = data [first+(last-first)/2];
    while (blue > white + 1) //                 
    { const int NEXT = blue - 1; //            
        if (data[NEXT] < PIVOT) //               
        {   red++; //                       
            white++;
            swap (data, red, NEXT) ;
        }
        else if (data[NEXT] == PIVOT)
        { //                 
            white++; //                      
            swap(data, white, NEXT);
        }
        else //                
        {
            blue--;
        }
    }
}

void quicksort (vector<El>& data, int first, int last)
{
    //     
    assert (0 <= first && last < size (data)) ;
    //                                           
    if (first >= last)
        return ;
    else { int red, blue ;
        dnf (data, first, last, red, blue) ;
        quicksort (data, first, red) ;
        quicksort (data, blue, last) ;
    }
}

int largest (vector<El> &v, int first, int last) {
    //   
    assert(last <= size(v)));
    //    
    //                                     
    vector<int> istack = {};
    int largestIndex = last;
    int i = 0;
    while (i < last)) {
        istack.push_back(i++);
    }
    while (size(istack) > 0) {
        int currenti = istack.back();
        istack.pop_back();
        if (v[currenti] > v[largestIndex]) {
            largestIndex = currenti;
        }
    }
    return largestIndex;
}

void sort (vector<El>& v, int n)
{
    //    
    assert(n <= size(v));
    //     
    //                                     
    while (n > 0)
    {   const int POS = largest (v, 0, n - 1) ;
        swap (v, POS, n-1) ;
        n--;
    }
}
/*                                                                       
                                      
                   
                                        
                                           
                                          
                                                                       */

int main()
{
	const int NO_OF_SONGS = read_file ("Tracks.txt");
	if (NO_OF_SONGS < 0)
	{
        cout << "Reading file failed. Program terminates." << endl;
	    return NO_OF_SONGS;
    }
    cout << counter << endl;
    quicksort(songs, 0, size(songs));
    cout << "Tracks sorted." << endl;
    show_all_tracks (songs,NO_OF_SONGS) ;
	return 0;
}

/*

                   

           
           
           

                                           
                                                          

*/

