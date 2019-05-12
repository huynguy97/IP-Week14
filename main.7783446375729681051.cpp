/*                                                                    
                                              
            
                                                                                                            
                                  
                              
                                                           
                                                                    
                                                          
                                                               
                                                                     */
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>

using namespace std;
#define NDEBUG

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

int counter = 0;
vector<Track>songs;              //                                     

/*                                                                       
                                
                                                               
                                                                         
                                                                       */
//      
bool operator<(const Length& a, const Length& b)
{
    if(a.minutes == b.minutes){
        if(a.seconds < b.seconds){
            return true;
        }
        else {
            return false;
        }
    }
    else if(a.minutes < b.minutes){
        return true;
    }
    else {
        return false;
    }
}

bool operator==(const Length& a, const Length& b)
{
    if(a.minutes == b.minutes && a.seconds == b.seconds){
        return true;
    }
    else{
        return false;
    }
}

//                                     
/*
                                              
 
              
                     
                                 
                                        
                            
             
                 
                             
             
         
                                     
                        
         
             
                         
         
     
                          
                    
     
          
                     
     

 
*/

//          

bool operator<(const Track& a, const Track& b)
{
    counter++;
    if(a.time == b.time){
        if(a.artist == b.artist){
            if(a.title == b.title){
                if(a.cd < b.cd){
                    return true;
                }
                else{
                    return false;
                }
            }
            else if(a.title < b.title){
                return true;
            }
            else{
                return false;
            }
        }
        else if(a.artist < b.artist){
            return true;
        }
        else{
            return false;
        }
    }
    else if (a.time < b.time){
        return true;
    }
    else {
        return false;
    }

}

bool operator==(const Track& a, const Track& b)
{
    counter++;
    if(a.time == b.time){
        if(a.artist == b.artist){
            if(a.title == b.title){
                if (a.cd == b.cd){
                    return true;
                }
            }
        }
    }
    return false;
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
            songs.push_back(song) ;
            no_of_read_songs++;
    }
    while (infile);
    return no_of_read_songs-1 ;
}

int read_file (string filename)
{//               
    assert (true) ;
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

void swap_int (vector<int>& data, int  i, int  j )
{//	              
	assert ( i >= 0 && j >= 0 ) ;	//                         
						            //                         
//                                                                
	const int HELP = data [i];
	data [i] = data [j] ;
	data [j] = HELP;
}

//	                           
void insertion_sort (vector<Track>& data, int length )
{
    cout << length << endl;
	int sorted = 1 ;
    while ( sorted < length ){
        insert ( data, sorted, data[sorted] ) ;
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

/*                                                                       
                                      
                   
                                                                      
                                           
                                          
                                                                       */
int maximum(int a, int b)
{
    if (a > b){
        return a;
    }
    else{
        return b;
    }
}

int minimum(int a, int b)
{
    if (b > a){
        return a;
    }
    else{
        return b;
    }
}

enum SortingMethod {InsertionSort,SelectionSort,BubbleSort,QuickSort,QuickSort_adj,NoOfSortingMethods};
string methods [] = {"insertion", "selection", "bubble", "quick", "quick_adjusted"} ;

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

void dnf (vector<Track>& data, int first, int last, int& red, int& blue)
{
    //    
    assert(true);
    //                                                             

    red = first-1;
    blue = last+1;
    int white = last+1;
    const Track PIVOT = data [first+(last-first)/2];
    while (red < white - 1){
        const int NEXT = white - 1;
        if (data[NEXT] < PIVOT){
            red++;
            swap (data, red, NEXT);
        }
        else if (data[NEXT] == PIVOT)
            white--;
        else{
            white--;
            blue--;
            swap (data, NEXT, blue);
        }
    }
}

void dnf_adj(vector<Track>& data, int first, int last, int& red, int& blue)
{
    //    
    assert(true);
    //                                                             

    red = first-1;
    blue = last+1;
    int white = first-1;
    const Track PIVOT = data [first+(last-first)/2];
    while (blue > white + 1){
        const int NEXT = white + 1;
        if (data[NEXT] > PIVOT){
            blue--;
            swap (data, blue, NEXT);
        }
        else if (data[NEXT] == PIVOT)
            white++;
        else{
            white++;
            red++;
            swap (data, NEXT, red);
        }
    }
}

void quicksort (vector<Track>& data, int first, int last)
{
//     
    assert (0 <= first) ;
//                                           
    if (first >= last){
        return;
    }
    else{
        int red, blue;
        dnf(data, first, last, red, blue);
        quicksort (data, first, red);
        quicksort (data, blue, last);
    }
}

void quicksort_adj (vector<Track>& data, int first, int last)
{
//     
    assert (0 <= first) ;
//                                           
    if (first >= last){
        return;
    }
    else{
        int red, blue;
        dnf_adj(data, first, last, red, blue);
        quicksort_adj (data, first, red);
        quicksort_adj (data, blue, last);
    }
}

int largest_it(vector<int>& v, int low, int up)
{
    int largest = v[low];
    while(low <= up){
        if(v[low] >= v[up]){
            largest = v[low];
        }
        low++;
    }
    return largest;
}

void sort_it (vector<int>& v, int n)
{
    while (n > 1)
    {
        int POS = largest_it(v, 0, n-1);
        swap_int (v, POS, n-1);
    }
}

int main()
{
    //                         
    //                       
    //                                
    //                                                                                               

	const int NO_OF_SONGS = read_file ("Tracks.txt");
	if (NO_OF_SONGS < 0)
	{
        cout << "Reading file failed. Program terminates." << endl;
	    return NO_OF_SONGS;
    }
    SortingMethod m = get_sorting_method () ;
    cout << "Sorting tracks with " << methods[m] << " sort" << endl;

    switch (m)
    {
        case InsertionSort: insertion_sort(songs,NO_OF_SONGS) ; break ;
        case SelectionSort: selection_sort(songs,NO_OF_SONGS) ; break ;
        case BubbleSort:    bubble_sort   (songs,NO_OF_SONGS) ; break ;
        case QuickSort:     quicksort(songs, 0, songs.size()-1) ; break ;
        case QuickSort_adj: quicksort_adj(songs, 0, songs.size()-1) ; break ;
        default:        cout << "Huh?" << endl ;
    }
    cout << "Tracks sorted." << endl;
    show_all_tracks (songs,NO_OF_SONGS) ;
    cout << "Number of comparisons: " << counter << endl;
    while(counter > 100000){
        counter-=100000;
        cout << "*";
    }
    if(counter != 0){
        cout << ".";
    }
    cout << endl;

	return 0;
}

