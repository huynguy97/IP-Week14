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

#define NDEBUG;

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

vector<Track> songs;              //                                     

int count_compare;

/*                                                                       
                                
                                                               
                                                                         
                                                                       */
bool operator< (const Length& a, const Length& b)
{

    if (a.minutes < b.minutes) return true;
    if (b.minutes < a.minutes) return false;
    if(a.seconds < b.seconds) return true;
    if(b.seconds < a.seconds) return false;

    return false;
}

bool operator== (const Length& a, const Length& b)
{

    return (a.minutes == b.minutes && a.seconds == b.seconds);
}

bool operator<(const Track& a, const Track& b)
{
    count_compare++;

    if(a.time < b.time) return true;
    if(b.time < a.time) return false;

    if (a.artist < b.artist) return true;
    if (b.artist < a.artist) return false;

    if (a.cd < b.cd) return true;
    if (b.cd < a.cd) return false;

    if (a.year < b.year) return true;
    if (b.year < a.year) return false;

    if (a.track_no < b.track_no) return true;
    if (b.track_no < a.track_no) return false;

     return false;

     ;    /*                                                 */
}

bool operator==(const Track& a, const Track& b)
{
    count_compare++;
    return (a.time==b.time && a.artist == b.artist && a.cd == b.cd && a.year == b.year && a.track_no == b.track_no);   /*                                                 */
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

int sizevector ( vector<Track> a )
{
    //               
    assert(true);
    /*               
                                           
    */
    return static_cast<int>(a.size());
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
    while (infile);
    return no_of_read_songs ;
}

int read_file (string filename)
{//               
    assert (sizevector (songs) == 0) ;
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
void show_all_tracks (vector<Track>& songs, int number_of_songs)
{//               
    assert (true) ;
/*                 
                                                                  
*/
    for (int i = 0 ; i < number_of_songs; i++)
        cout << songs[i] << endl ;
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

bool is_sorted (vector<Track>& data , Slice s)
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

int find_position ( vector<Track>& data , Slice s, Track y )
{//	              
	assert (valid_slice(s) && is_sorted(data,s)) ;    //                           
//	                                          
	for ( int i = s.from ; i <= s.to ; i++ )
		if ( y <= data [i] )
			return (i);
	return s.to;
}

void shift_right ( vector<Track>& data , Slice s )
{//	              
	assert (valid_slice (s)) ;	//                               
//	                               	  	                
//			    	               	  	                  
//						   
//			    	             		  	              
	for ( int i = s.to+1 ; i > s.from ; i-- )
		data [i]  = data [i-1] ;
}

void insert ( vector<Track>& data , int& length, Track y )
{//               
    Slice s = mkSlice(0,length-1) ;

    assert(is_sorted (data, s)) ;
/*                 
                                                                                     
                                   
*/
	const int POS = find_position (data, mkSlice (0, length-1), y) ;
	if (POS < length)
		shift_right ( data, mkSlice (POS, length-1) ) ;
	data [POS] = y ;
	length++;
}

void swap (vector<Track>& data , int  i, int  j )
{//	              
	assert ( i >= 0 && j >= 0 ) ;	//                         
						            //                         
//                                                                
	const Track HELP = data [i];
	data [i] = data [j] ;
	data [j] = HELP;
}

//	                           
void insertion_sort ( vector<Track>& data , int length )
{
	int sorted = 1 ;
    while ( sorted < length )
    {
        //                       
        insert ( data, sorted, data[sorted] ) ;
    }
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

void selection_sort ( vector<Track>& data, int length )
{	for ( int unsorted = 0 ; unsorted < length ; unsorted++ )
	{   const int k = smallest_value_at (data, mkSlice (unsorted, length-1));
	    swap ( data, unsorted, k ) ;
	}
}

//	                        
bool bubble ( vector<Track>& data, Slice s )
{//	              
	assert (valid_slice(s));	//                          
//	               
//	                                                    
//	                                        
	bool is_sorted = true ;
	for ( int i = s.from ; i < s.to ; i++)
	    if ( data [i] > data [i+1])
		{	swap ( data, i, i+1 ) ;
			is_sorted = false ;
		}
	return is_sorted ;
}

void bubble_sort ( vector<Track>& data, int length )
{
    while ( !bubble ( data, mkSlice (0, length-1 ) ) )
        length-- ;
}

void dnf (vector<Track>& data, int first, int last, int& red, int& blue)
{
    red = first -1;
    blue = last+1;
    int white = last+1;
    const Track PIVOT = data [first+((last-first)/2)];
    while(red < white -1)
    {
        const int NEXT = white -1;
        if(data[NEXT] < PIVOT)
        {
            red++;
            swap(data, red, NEXT);
        }
        else if (data[NEXT]==PIVOT) white--;
        else
        {
            white --; blue--;
            swap(data, NEXT, blue);
        }
    }
}

void dnf_adjusted (vector<Track>& data, int first, int last, int& red, int& blue)
{
    red = first -1;
    blue = last+1;
    int white = first-1;
    const Track PIVOT = data [first+((last-first)/2)];
    while(white < blue-1)
    {
        const int NEXT = white +1;
        if(data[NEXT] < PIVOT)
        {
            red++; white ++;
            swap(data, red, NEXT);
        }
        else if (data[NEXT]==PIVOT) white++;
        else
        {
            blue--;
            swap(data, NEXT, blue);
        }
    }
}

void quicksort (vector<Track>& data, int first, int last)
{
    //    
    assert(0 <= first && last < data.size());
    //                                         
    //                                    
    if (first >= last) return;
    else
    {
        int red, blue;
        //                                   
        dnf_adjusted(data, first, last, red, blue);
        if(!(red < first)) quicksort(data, first, red);
        if (!(blue > last)) quicksort(data, blue, last);
    }
}

void swap_array(int & a, int & b)
{
    int temp = a;
    a = b;
    b = temp;
}

int itt_largest(int v[], int low, int up){
        int POS = up;
        while(low < up)
        {
             if(v[low] > v[POS]) POS = low ;
             low++;
        }

        return POS;
}

void itt_sort (int v[], int n){
        while (!(n < 1)){
            int POS = itt_largest(v, 0, n-1);
            swap_array(v[n-1], v[POS]);
            n--;
        }
}

int main()
{
	const int NO_OF_SONGS = read_file ("Tracks.txt");
	count_compare = 0;

    quicksort(songs, 0, NO_OF_SONGS-1);

    int v[8] = {2,3,4,5,5,6,3,2};
    itt_sort(v,8);
	return 0;
}

