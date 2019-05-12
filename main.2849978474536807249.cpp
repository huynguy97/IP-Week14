/*                                                                    
                                              
            
                                                                                                            
                                  
                              
                                                           
                                                                    
                                                          
                                                               
                                                                     */
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

//                                                                              
vector<Track> songs;              //                                     
int global_counter;

/*                                                                       
                                
                                                               
                                                                         
                                                                       */
//                           
bool operator<(const Length& a, const Length& b) {
    //              
    assert (0 <= a.minutes && 0 <= a.seconds && a.seconds < 60 && 0 <= b.minutes && 0 <= b.seconds && b.seconds < 60);
    //                                                                               
    if(a.minutes != b.minutes) {
        return a.minutes < b.minutes;
    } else if(a.seconds != b.seconds) {
        return a.seconds < b.seconds;
    } else {
        return false;
    }
}

bool operator==(const Length& a, const Length& b) {
    return a.minutes == b.minutes && a.seconds == b.seconds;
}

bool operator<(const Track& a, const Track& b)
{
    global_counter++;
    /*                         
                               
                                     
                                   
	                               
                                 
	                         
                           
	        
                     
	 
                               */
    if(a.artist != b.artist) {
        return a.artist < b.artist;
	} else if(a.cd != b.cd) {
        return a.cd < b.cd;
	} else if(a.year != b.year) {
        return a.year < b.year;
	} else if(a.track_no != b.track_no) {
        return a.track_no < b.track_no;
	} else {
        return false;
	}
}

bool operator==(const Track& a, const Track& b)
{
    global_counter++;
    return a.artist == b.artist
        && a.cd == b.cd
        && a.year == b.year
        && a.track_no == b.track_no;   /*                                                 */
}

//	                                 
bool operator>(const Track& a, const Track& b)
{
	return b < a;
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

int read_songs (ifstream& infile, vector<Track>& songs)
{//               
    assert (infile.is_open()) ;
/*                 
                                                                              
                                                           
*/
    int no_of_read_songs = 0 ;
    do {
        Track song ;
        infile >> song;
        if (infile){
            no_of_read_songs++;
            songs.push_back(song);
        }
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

//                                                                           
void show_all_tracks (vector<Track> songs, int no_of_songs)
{//               
    assert (true) ;
/*                 
                                                                  
*/
    for (int i = 0 ; i < no_of_songs; i++)
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

typedef int El;                //                                                       

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
		data.at(i)  = data.at(i-1) ;
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
	data.at(POS) = y ;
	length++;
}

void swap (vector<Track>& data, int  i, int  j )
{//	              
	assert ( i >= 0 && j >= 0 && i <= data.size() && j <= data.size()) ;	//                         
						            //                         
//                                                                
	const Track HELP = data [i];
	data [i] = data [j] ;
	data [j] = HELP;
}

//	                           
void insertion_sort ( vector<Track>& data, int length )
{
	int sorted = 1 ;
    while ( sorted < length )
    {
        insert ( data, sorted, data.at(sorted) ) ;
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

/*                  
                 
                   */

/*                                   */
void dnf(vector<Track>& data, int first, int last, int& red, int& blue) {
    //              
    assert(true);
    //                                                                               
    red = first - 1;
    blue = last + 1;
    int white = last + 1;
    Track m = data[first + (last-first)/2];
    while(red < white - 1) {
        if(data[white-1] < m) {
            red++;
            swap(data, red, white-1);
        } else if(data[white-1] == m) {
            white--;
        } else {
            white--;
            blue--;
            swap(data, white, blue);
        }
    }
}

/*                                   */
void dnf2(vector<Track>& data, int first, int last, int& red, int& blue) {
    //              
    assert(true);
    //                                                                               
    red = first - 1;        //              
    blue = last + 1;        //                
    int white = first - 1;  //                
    Track m = data[first + (last-first)/2];
    while(blue > white + 1) { //                                                                        
        if(data[blue-1] < m) { //                                              
            red++;
            if(red > white) {   //                                                                                                                                     
                white++;        //                                                                                            
            }
            swap(data, red, blue-1);
        } else if(data[blue-1] == m) {
            white++;
            swap(data, white, blue-1);
        } else {
            blue--;
        }
    }
}

/*                        */
void quicksort(vector<Track>& data, int first, int last) {
    //              
    assert(true);
    //                               
    if(first >= last) {
        return;
    } else {
        int red, blue;
        //                        
        dnf2(data, first, last, red, blue); //                                                                                  
        //                          
        quicksort(data, first, red);
        quicksort(data, blue, last);
    }
}

/*          */
//                 
int largest(vector<Track>& v, int low, int up) {
    //              
    assert(low >= 0 && up < v.size() && low <= up);
    //                                                             
    if(low >= up) {
        return low;
    } else {
        const int POS = largest(v, low+1, up);
        if(v[low] > v[POS]) { //                      
            return low;
        } else {
            return POS;
        }
    }
}
//                 
int largest_iter(vector<Track>& v, int low, int up) {
    //              
    assert(low >= 0 && up < v.size() && low <= up);
    //                                                             
    vector<int> stack;
    while(low < up) {
        stack.push_back(low);
        low++;
    }
    int POS = low;
    while(stack.size() > 0) {
        int x = stack[stack.size() - 1];
        stack.pop_back();
        if(v[x] > v[POS]) {
            POS = x;
        } //                
    }
    return POS;
}
//                 
void sort(vector<Track>& v, int n) {
    //             
    assert(n <= v.size());
    //                                          
    if(n>1) {
        const int POS = largest(v, 0, n-1);
        swap(v, POS, n-1);
        sort(v, n-1);
    } else {
        return;
    }
}
//                 
void sort_iter(vector<Track>& v, int n) {
	//             
    assert(n <= v.size());
    //                                          
    while(n>1) {
        const int POS = largest_iter(v, 0, n-1);
        swap(v, POS, n-1);
        n--;
    }
    return;
}

/*                                                                       
                                      
                   
                                                                      
                                           
                                          
                                                                       */
enum SortingMethod {InsertionSort,SelectionSort,BubbleSort,Quicksort,NoOfSortingMethods};
string methods [] = {"insertion", "selection", "bubble", "quicksort"} ;

int maximum(int a, int b) {
    if(a > b) {
        return a;
    } else {
        return b;
    }
}
int minimum(int a, int b) {
    if(a < b) {
        return a;
    } else {
        return b;
    }
}

SortingMethod get_sorting_method ()
{
    cout << "What sorting method do you want to use? " << endl ;
    for (int m = 0; m < NoOfSortingMethods; m++)
        cout << m+1 << ": " << methods[m] << " sort" << endl ;
    int choice ;
    cin >> choice ;
    choice = maximum (1, minimum (choice, NoOfSortingMethods)) ;
    return static_cast<SortingMethod>(choice-1) ;
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

    //                                              
	return 0;
}

