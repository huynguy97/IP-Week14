#include <iostream>
#include <fstream>
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

vector<Track> songs;

/*                                                                       
                                
                                                               
                                                                         
                                                                       */

//                           
/*                                              
 
                                  
                                                                                          
                                                                                                 
                                   
                                 
                           
                                     
                               
           
                                       
     
 

                                               
 
                                                                                                        
 */

bool operator<(const Length& a, const Length& b)
{
    if( !(a.minutes == b.minutes) ){
        return a.minutes < b.minutes;
    } else{
        return a.seconds < b.seconds;
    }
}

bool operator==(const Length& a, const Length& b)
{
    return (a.minutes == b.minutes) && (a.seconds == b.seconds);
}

//                           
bool operator<(const Track& a, const Track& b)
{
    if( !(a.time == b.time) ){
        return a.time < b.time;
    } else if( !(a.artist == b.artist) ){
        //                                                                                
        //                                                                                       
        return a.artist < b.artist;
    } else if( !(a.title == b.title) ){
        return a.title < b.title;
    } else{
        return a.cd < b.cd;
    }
}

bool operator==(const Track& a, const Track& b)
{    
    return (a.time == b.time) && (a.artist == b.artist) && (a.title == b.title) && (a.cd == b.cd);
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
    int no_of_read_songs = 0 ;
    do {
        Track song ;
        infile >> song ;
        if (infile){
            songs.push_back(song);
            no_of_read_songs++;
        }
    }
    while(infile);
    return no_of_read_songs ;
}

int read_file (string filename)
{
    //               
    assert( songs.size() == 0);
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
{
    //               
    assert(true);
    /*                 
                                                                      
    */
    for (int i = 0 ; i < no_of_songs; i++){
        cout << i+1 << ". " << songs[i] << endl ;
    }
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

bool is_sorted ( vector<El>& data, Slice s )
{
    //	              
	assert(valid_slice(s));	//                           
    //	               
    //	                 	                                
    //						                                
    //						   
    //						                            
	bool sorted = true;
	for (int i = s.from; i < s.to && sorted; i++){
		if (data[i] > data[i+1]){
			sorted = false;
		}
	}
	return sorted;
}

int find_position ( vector<El>& data, Slice s, El y )
{
    //	              
	assert(valid_slice(s) && is_sorted(data,s));    //                           
    //	                                          
	for (int i = s.from; i <= s.to; i++){
		if( y <= data[i] ){
			return i;
		}
	}
	return s.to+1;
}

int find_position_reverse ( vector<El>& data, Slice s, El y )
{
    //                
    assert(valid_slice(s) && is_sorted(data,s));    //                           
    //                                            
    for (int i = s.to; i >= s.from; i--){
        if( y >= data[i] ){
            return i+1;
        }
    }
    return s.from;
}

void shift_right ( vector<El>& data, Slice s )
{
    //	              
	assert(valid_slice(s));	//                               
    //	                               	  	                
    //			    	               	  	                  
    //						   
    //			    	             		  	              
	for (int i = s.to+1; i > s.from; i--){
		data[i] = data[i-1];
	}
}

void insert ( vector<El>& data, int& length, El y )
{
    //               
    Slice s = mkSlice(0,length-1);
    assert(length >= 0 && is_sorted(data, s));
    /*                 
                                                                                         
                                       
    */
    //                                                                                              
	//                                          
    const int POS = find_position_reverse(data, s, y);
	if (POS < length)
		shift_right( data, mkSlice(POS, length-1) );
	data [POS] = y;
	length++;
}

void swap ( vector<El>& data, int  i, int  j )
{
    //	              
	assert( i >= 0 && j >= 0 );	//                         
						            //                         
    //                                                                
	const El HELP = data[i];
	data[i] = data [j];
	data[j] = HELP;
}

//	                           
void insertion_sort ( vector<El>& data, int length )
{
	int sorted = 1 ;
    while( sorted < length ){
        insert( data, sorted, data[sorted] );
    }
}

//	                           
int smallest_value_at ( vector<El>& data, Slice s )
{
    //	              
	assert(valid_slice(s));	//                        
    //	                                                            
    //	                                               
	int smallest_at = s.from;
	for ( int index = s.from+1 ; index <= s.to ; index++ ){
		if( data[index] < data[smallest_at] ){
			smallest_at = index;
		}
	}
	return smallest_at;
}

void selection_sort ( vector<El>& data, int length )
{
    for( int unsorted = 0 ; unsorted < length ; unsorted++ ){
        const int k = smallest_value_at( data, mkSlice(unsorted, length-1) );
	    swap(data, unsorted, k) ;
	}
}

//	                        
bool bubble ( vector<El>& data, Slice s )
{
    //	              
	assert(valid_slice(s));	//                          
    //	               
    //	                                                    
    //	                                        
	bool is_sorted = true;
	for (int i = s.from; i < s.to; i++){
	    if ( data[i] > data[i+1] ){
            swap(data, i, i+1);
			is_sorted = false ;
		}
	}
	return is_sorted ;
}

void bubble_sort ( vector<El>& data, int length )
{
    while( !bubble( data, mkSlice(0, length-1) ) ){
        length--;
    }
}

enum SortingMethod {InsertionSort,SelectionSort,BubbleSort,DNFQuickSort,NonRecursiveSort,NoOfSortingMethods};
string methods [] = {"insertion", "selection", "bubble", "dnf+quicksort", "non-recursive"} ;

int minimum ( int a, int b )
{
    if( a < b ){
        return a;
    } else{
        return b;
    }
}

int maximum ( int a, int b )
{
    if( a > b ){
        return a;
    } else{
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
    choice = maximum(1, minimum (choice, NoOfSortingMethods));
    return static_cast<SortingMethod>(choice-1) ;
}

/*                                                
                        
                                                    */

void dnf(vector<El>& data, int first, int last, int& red, int& blue)
{
    //              
    assert(first >= 0);
    assert(last <= data.size());
    /*                 
                                                                                                                
                                                                                                            
    */
    red = first - 1;
    blue = last + 1;
    int white = last + 1;
    const El pivot = data[first+(last-first)/2];
    while(red < white - 1){
        const int next = white - 1;
        if(data[next] < pivot){
            red++;
            swap(data, red, next);
        } else if(data[next] == pivot){
            white--;
        } else{
            white--;
            blue--;
            swap(data, next, blue);
        }
    }
}

void dnf_adjusted(vector<El>& data, int first, int last, int& red, int& blue)
{
    //              
    assert(first >= 0);
    assert(last <= data.size());
    /*                 
                                                                                                                
                                                                                                            
    */
    red = first - 1;
    blue = last + 1;
    //                                                                                                          
    int white = first - 1;
    const El pivot = data[first+(last-first)/2];
    while(white < blue - 1){
        const int next = white + 1;
        if(data[next] < pivot){
            //                                                       
            red++;
            white++;
            swap(data, red, next);
        } else if(data[next] == pivot){
            //                                                    
            white++;
        } else{
            //                                                                                    
            blue--;
            swap(data, next, blue);
        }
    }
}

void dnf_quick_sort(vector<El>& data, int first, int last)
{
    //              
    assert(first >= 0);
    assert(last <= (int)data.size());
    /*                 
                                                   
    */
    if(first >= last){
        return;
    } else{
        int red, blue;
        dnf_adjusted(data, first, last, red, blue);
        dnf_quick_sort(data, first, red);
        dnf_quick_sort(data, blue, last);
    }
}

int largest(vector<El>& data, int low, int up)
{
    //              
    assert(low >= 0);
    assert(up <= data.size());
    /*                 
                                                                     
    */
    //                                                                                         
    //                                             
    //                                                                                 
    //                                              
    /*
                      
                    
                             
              
     
                  
                            
                                    
                         
                                  
                      
               
                      
         
     
               
    */
    int pos = data.size() - 1;
    for(int i = data.size() - 1; i > 0; i--){
        if(data[i] > data[pos]){
            pos = i;
        }
    }
    return pos;
}

void sort(vector<El>& data, int length)
{
    //             
    assert(length <= data.size());
    /*                 
                                        
    */
    while(length > 1){
        const int pos = largest(data, 0, length-1);
        swap(data, pos, length-1);
        length--;
    }
}

/*                                                                       
                                      
                   
                                                                                       
                                           
                                          
                                                                       */

//                         

int main ()
{
	const int NO_OF_SONGS = read_file("Tracks.txt");
	if (NO_OF_SONGS < 0){
        cout << "Reading file failed. Program terminates." << endl;
	    return NO_OF_SONGS;
    }
    SortingMethod m = get_sorting_method();
    cout << "Sorting tracks with " << methods[m] << " sort" << endl;
    switch (m){
        case InsertionSort:     insertion_sort(songs, NO_OF_SONGS) ; break ;
        case SelectionSort:     selection_sort(songs, NO_OF_SONGS) ; break ;
        case BubbleSort:        bubble_sort   (songs, NO_OF_SONGS) ; break ;
        case DNFQuickSort:      dnf_quick_sort(songs, 0, NO_OF_SONGS-1) ; break ;
        case NonRecursiveSort:  sort(songs, NO_OF_SONGS) ; break ;
        default:        cout << "Huh?" << endl ;
    }
    cout << "Tracks sorted." << endl;
    show_all_tracks (songs, NO_OF_SONGS);
    return 0;	
}

