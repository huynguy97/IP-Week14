/*                                                                    
                                              
            
                                                                                                            
                                  
                              
                                                           
                                                                    
                                                          
                                                               
                                                                     */
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>
#include <algorithm>
using namespace std;
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

const int MAX_NO_OF_SONGS = 6000;           //                                
vector<Track> songs;              //                                     

/*                                                                       
                                
                                                               
                                                               
                                                                         
                                                                       */
bool operator < (const Length a, const Length b){
    int time_a = a.minutes*60 + a.seconds;
    int time_b = b.minutes*60 + b.seconds;

    return time_a < time_b;
}

bool operator == (const Length a, const Length b){
    if(a < b){
        if(b < a){
            return false;
        }
    }
    return true;
}
bool operator<(const Track& a, const Track& b)
{
    if(a.artist == b.artist){
        if(a.cd== b.cd){
            if(a.track_no == b.track_no){
                if(a.year == b.year){
                    return a.time < b.time;
                }
                return a.year < b.year;
            }
            return a.track_no < b.track_no;
        }
        return a.cd < b.cd ;    /*                                                 */
        }
    return a.artist < b.artist;
}

bool operator==(const Track& a, const Track& b)
{
    if(a.artist < b.artist){
        if(a.cd < b.cd){
            if(a.track_no < b.track_no){
                if(a.year < b.year){
                    return a.time == b.time;
                }
                return a.year == b.year;
            }
            return a.track_no == b.track_no;
        }
        return a.cd == b.cd ;   /*                                                 */
        }
    return a.artist == b.artist;
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

int minimum(int a, int b){
    return max(a,b);
}
int maximum(int a, int b){
    return min(a,b);
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
            no_of_read_songs++;
            songs.push_back(song) ;
        }
    }
    while (infile && no_of_read_songs < MAX_NO_OF_SONGS);
    return no_of_read_songs ;
}

int read_file (string filename)
{//               
//                                
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
void show_all_tracks (vector<Track>& songs, int no_of_songs)
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

bool is_sorted (vector<Track>& songs, Slice s)
{//	              
	assert (valid_slice(s)) ;	//                           
//	               
//	                 	                                
//						                                
//						   
//						                            
	bool sorted = true ;
	for (int i = s.from; i < s.to && sorted; i++)
		if (songs[i] > songs[i+1])
			sorted = false ;
	return sorted ;
}

int find_position ( vector<Track>& songs, Slice s, Track y )
{//	              
	assert (valid_slice(s) && is_sorted(songs,s)) ;    //                           
//	                                          
	for ( int i = s.from ; i <= s.to ; i++ )
		if ( y <= songs [i] )
			return i ;
	return s.to+1;
}

void shift_right ( vector<Track>& songs, Slice s )
{//	              
	assert (valid_slice (s)) ;	//                               
//	                               	  	                
//			    	               	  	                  
//						   
//			    	             		  	              
	for ( int i = s.to+1 ; i > s.from ; i-- )
		songs [i]  = songs [i-1] ;
}

void insert ( vector<Track>& songs, int& length, El y )
{//               
    Slice s = mkSlice(0,length-1) ;
    assert (length >= 0 && is_sorted (songs, s)) ;
/*                 
                                                                                     
                                   
*/
	const int POS = find_position (songs, mkSlice (0, length-1), y) ;
	if (POS < length)
		shift_right ( songs, mkSlice (POS, length-1) ) ;
	songs [POS] = y ;
	length++;
}

void swap (vector<Track>& songs, int  i, int  j )
{//	              
	assert ( i >= 0 && j >= 0 ) ;	//                         
						            //                         
//                                                                
	const El HELP = songs [i];
	songs [i] = songs [j] ;
	songs [j] = HELP;
}

void swapInt (vector<int>& songs, int  i, int  j )
{//	              
	assert ( i >= 0 && j >= 0 ) ;	//                         
						            //                         
//                                                                
	const int HELP = songs [i];
	songs [i] = songs [j] ;
	songs [j] = HELP;
}

//	                           
void insertion_sort ( vector<Track>& songs, int length )
{
	int sorted = 1 ;
    while ( sorted < length )
    {   insert ( songs, sorted, songs[sorted] ) ;
    }
}

//	                           
int smallest_value_at ( vector<Track>& songs, Slice s )
{//	              
	assert (valid_slice (s)) ;	//                        
//	                                                            
//	                                               
	int smallest_at = s.from ;
	for ( int index = s.from+1 ; index <= s.to ; index++ )
		if ( songs [index] < songs [smallest_at] )
			smallest_at = index ;
	return smallest_at ;
}

void selection_sort ( vector<Track>& songs, int length )
{	for ( int unsorted = 0 ; unsorted < length ; unsorted++ )
	{   const int k = smallest_value_at (songs, mkSlice (unsorted, length-1));
	    swap ( songs, unsorted, k ) ;
	}
}

//	                        
bool bubble ( vector<Track>& songs, Slice s )
{//	              
	assert (valid_slice(s));	//                          
//	               
//	                                                    
//	                                        
	bool is_sorted = true ;
	for ( int i = s.from ; i < s.to ; i++)
	    if ( songs [i] > songs [i+1])
		{	swap ( songs, i, i+1 ) ;
			is_sorted = false ;
		}
	return is_sorted ;
}

void bubble_sort ( vector<Track>& songs, int length )
{
    while ( !bubble ( songs, mkSlice (0, length-1 ) ) )
        length-- ;
}
/*        */
void dnf(vector<Track>& songs, int first, int last, int& red, int& blue)
{
    red = first-1;
    blue = last+1;
    int white = last+1;
    const Track PIVOT = songs[first + (last-first)/2];
    while(red < white-1){
        const int NEXT = white-1;
        if( songs[NEXT] < PIVOT){
            red++;
            swap(songs, red, NEXT);
        }
        else if(songs[NEXT] == PIVOT){
            white --;
        } else {
            white--; blue--;
            swap(songs, NEXT, blue);
        }
    }
}

void quicksort( vector<Track>& songs, int first, int last)
{
    if(first >= last)return;
    else{
        int red, blue;
        dnf(songs, first, last, red, blue);
        quicksort(songs, first, red);
        quicksort(songs, blue, last);
    }
}
/*            */
/*        */
int largest(vector<int>& v, int start){
    int largest = 0;
    int index = 0;
    for(int i = start; i < v.size(); i++){
        if(v[i] > largest){
            largest = v[i];
            index = i;
        }
    }
    return index;
}

void sortIt(vector<int>& v){
    for(int i = 0; i < v.size(); i++){
        int x = largest(v, i);
        swapInt(v, i, x);
    }
}
/*            */

/*                                                                       
                                      
                   
                                                                      
                                           
                                          
                                                                       */
enum SortingMethod {InsertionSort,SelectionSort,BubbleSort, QuickSort, NoOfSortingMethods};
string methods [] = {"insertion", "selection", "bubble", "quick"} ;

SortingMethod get_sorting_method ()
{
    cout << "What sorting method do you want to use? " << endl ;
    for (int m = 0; m < NoOfSortingMethods; m++)
        cout << m+1 << ": " << methods[m] << " sort" << endl ;
    int choice ;
    cin >> choice ;
    //                                                            
    return static_cast<SortingMethod>(choice-1) ;
}

int main()
{
	const int NO_OF_SONGS = read_file ("Tracks.txt");
	vector<int> test = { 1, 3, 5 ,2, 1, 6, 7, 4, 2, 12, 5, 23, 21, 42, 123, 23, 5, 6, 7, 3, 2, 3};
	int r = 0;
	int b = 0;
	if (NO_OF_SONGS < 0)
	{
        cout << "Reading file failed. Program terminates." << endl;
	    return NO_OF_SONGS;
    }
    cout << songs[0].track_no << "This is to detect what happens" << endl;
    //                                  
    sortIt(test);
    for(int i = 0; i < test.size(); i++){
        cout << test[i] << ' ';
    }
    cout << endl;

    SortingMethod m = get_sorting_method () ;
    cout << "Sorting tracks with " << methods[m] << " sort" << endl;
    switch (m)
    {
        case InsertionSort: insertion_sort(songs,NO_OF_SONGS) ; break ;
        case SelectionSort: selection_sort(songs,NO_OF_SONGS) ; break ;
        case BubbleSort:    bubble_sort   (songs,NO_OF_SONGS) ; break ;
        case QuickSort:     quicksort     (songs, 0, NO_OF_SONGS) ; break;
        default:        cout << "Huh?" << endl ;
    }
    cout << "Tracks sorted." << endl;
    show_all_tracks (songs,NO_OF_SONGS) ;
	return 0;
}

