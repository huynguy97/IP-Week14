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
int compare_counter = 0;

/*                                                                       
                                
                                                               
                                                                         
                                                                       */
//                                    

bool operator<(const Length& a, const Length& b)
{
    if (a.minutes == b.minutes)
    {
        return a.seconds < b.seconds;
    }
    else
    {
        return a.minutes < b.minutes;
    }
}

bool operator==(const Length& a, const Length& b)
{
    if(a.minutes == b.minutes && a.seconds == b.seconds)
    {
        return true;
    }
    else
    {
        return false;
    }
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
	return !(b == a) ;
}
//                                 
//  
bool operator<(const Track& a, const Track& b)
{
    compare_counter++;
    if(a.time != b.time)
    {
        return a.time < b.time;
    }
    else if (a.artist != b.artist)
    {
        return a.artist < b.artist ;
    }
    else if (a.cd != b.cd)
    {
        return a.cd < b.cd;
    }
    else
    {
        return false;
    }
}

bool operator==(const Track& a, const Track& b)
{
    compare_counter++;
    if (a.time != b.time)
    {
        return false;
    }
    else if (a.artist != b.artist)
    {
        return false;
    }
    else if (a.cd != b.cd)
    {
        return false;
    }
    else if (a.year != b.year)
    {
        return false;
    }
    else if (a.track_no != b.track_no)
    {
        return false;
    }
    else
    {
        return true;
    }
}
//  
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
        if (infile)
        {
            songs.push_back(song);
            no_of_read_songs++;
        }

    }
    while (infile);
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
    assert (true) ;
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

//	                           
void insertion_sort (vector<Track>& data, int length )
{
	int sorted = 1 ;
    while ( sorted < length )
    {   insert ( data, sorted, data[sorted] ) ;
    }
}

//	                           
int smallest_value_at (vector<Track>& data, Slice s )
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

void selection_sort (vector<Track>& data, int length )
{	for ( int unsorted = 0 ; unsorted < length ; unsorted++ )
	{   const int k = smallest_value_at (data, mkSlice (unsorted, length-1));
	    swap ( data, unsorted, k ) ;
	}
}
/*           
            
           */
/*
                                                                       
   	              
	                                                           
  	                                                                        
                  
                  
                       
                                                   
                          
     
                                 
                              
         
                  
                                
         
                                     
         
                    
         
            
         
                    
                   
                                   
         
     
 

                                                          
   	              
	                 
  	                                                                        
                 
           
    
 
                  
                                  
                                
                              
 
 

*/
/*           
          
           */

/*           
            
           */
void dnf(vector<Track>& data, int first, int last, int& red, int& blue)
{//	              
	assert(0<=first&&last<data.size()&& 0 <= red && 0 <= blue);
//                                                                          
//                                                             
    red = first-1;
    blue = last+1;
    int white = first-1;
    const Track pivot = data[first+(last-first)/2];
    while (blue > white+1)
    {
        const int next = white+1;
        if(data[next] > pivot)
        {
            blue--;
            swap(data,blue,next);
        }
        else if (data[next] == pivot)
        {
            white++;
        }
        else
        {
            white++;
            red++;
            swap(data, next, red);
        }
    }
}

void quicksort (vector <Track>& data, int first, int last)
{//	              
	assert(0<=first);
//	                                                                        
if(first >= last)
    return;
else
{
    int red, blue;
    dnf(data,first,last,red,blue);
    quicksort(data, first, red);
    quicksort(data,blue,last);
}
}

/*           
          
           */

/*           
            
           */
int largest(vector<Track>& track, int low, int high)
{//             
    assert(high >= 0 && low >= 0);
//                                                                           
    if(low >= high)
        return low;
    else
    {
        const int pos = largest(track, low+1, high);
        if(track[low] > track[pos])
            return low;
        else
            return pos;
    }
}
/*
                                                    
                
                                  
                                                                             
                         
     
                        
                                 
                       
     
               
 */

void sortsort(vector<Track>& track, int n)
{//              
    assert(n >= 0);
//                                
    while(n>1)
    {
        int pos = largest(track, 0 , n-1);
        swap(track, pos, n-1);
        n--;
    }
}
/*           
          
           */

//	                        
bool bubble (vector<Track>& data, Slice s )
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

void bubble_sort (vector<Track>& data, int length )
{
    while ( !bubble ( data, mkSlice (0, length-1 ) ) )
        length-- ;
}

//                   
vector<Track> copyvector(vector<Track>& songs, int slice)
{//	              
assert (true);
//	               
//	                                                          
    int i = 0;
    vector<Track> copied;
    while(i <= slice)
    {
        copied.push_back(songs[i]);
        i++;
    }
    return copied;
}

void stars(int comparisons)
{//	              
	assert (true);
//	               
//	                                                                  
    while(comparisons > 99999)
    {
        cout << '*';
        comparisons = comparisons - 100000;
    }
    if(comparisons)
    {
        cout << ".\n";
    }
}
/*                                                                       
                                      
                   
                                                                      
                                           
                                          
                                                                       */
enum SortingMethod {InsertionSort,SelectionSort,BubbleSort,QuickSort, Sort, NoOfSortingMethods};
string methods [] = {"insertion", "selection", "bubble", "quick", "sort"} ;

SortingMethod get_sorting_method ()
{
    cout << "What sorting method do you want to use? " << endl ;
    for (int m = 0; m < NoOfSortingMethods; m++)
        cout << m+1 << ": " << methods[m] << " sort" << endl ;
    int choice ;
    cin >> choice ;
    choice = max (1, min (choice, static_cast<int>(NoOfSortingMethods))) ;
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
    SortingMethod m = get_sorting_method () ;
    cout << "Sorting tracks with " << methods[m] << " sort" << endl;
    compare_counter = 0;
    switch (m)
    {
        case InsertionSort:
        insertion_sort(songs, NO_OF_SONGS);
        break ;
        case SelectionSort:
        selection_sort(songs, NO_OF_SONGS);
        break ;
        case BubbleSort:
        bubble_sort(songs, NO_OF_SONGS);
        break;
        case QuickSort:
        quicksort(songs, 0, songs.size()-1);
        break ;
        case Sort:
        sortsort(songs, songs.size());
        break;
        default:        cout << "Huh?" << endl ;
    }
    //                                 
    //                                                            
    show_all_tracks (songs,NO_OF_SONGS);
	return 0;
}

