//                                                                          
//     

//                                                   
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

#define NDEBUG

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
vector<Track> songs;                        //                                     

int ultimusCounterusXIV = 0; //                                                                       

/*                                                                       
                                
                                                               
                                                                         
                                                                       */
int size(vector<Track>& a)
{
    return static_cast<int>(a.size());
}

int maximum(int a, int b)
{
    return max(a, b);
}

int minimum(int a, int b)
{
    return min(a, b);
}

bool operator<(const Track& a, const Track& b)
{
    ultimusCounterusXIV += 1;

    if ( a.time.minutes < b.time.minutes )
    {
        return true;
    }
    else if (a.time.minutes == b.time.minutes)
    {
        if ( a.time.seconds < b.time.seconds )
        {
            return true;
        }
        else if (a.time.seconds == b.time.seconds)
        {
            if ( a.artist < b.artist )
            {
                return true;
            }
            else if ( a.artist == b.artist )
            {
                if (a.title < b.title )
                {
                    return true;
                }
                else if (a.title == b.title )
                {
                    if ( a.cd < b.cd )
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool operator==(const Track& a, const Track& b)
{
    ultimusCounterusXIV += 1;

    return a.time.minutes == b.time.minutes && a.time.seconds == b.time.seconds && a.artist == b.artist && a.title == b.title && a.cd == b.cd;
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
int read_songs (ifstream& infile, vector<Track>& songs )
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
	//                     
	for (int i = s.from; i < s.to && sorted; i++)
		if (data[i] > data[i+1]) {
                //                                                
        sorted = false;}

			//                
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
    assert (length >= 0 && is_sorted (data, s));
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
void insertion_sort ( vector<Track>& data, int length )
{
	int sorted = 1 ;
    while ( sorted < length )
    {
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

//                    

void dnf (vector<Track>& data, int first, int last, int& red, int& blue)
{
	red = first-1;
	blue = last+1;
	int white = last+1;

	const Track PIVOT = data[first+(last-first)/2];
	while (red < white - 1)
	{
		const int NEXT = white - 1;
		if(data[NEXT] < PIVOT)
		{
			red++;
			swap(data, red, NEXT);
		}
		else if (data[NEXT] == PIVOT)
			white--;
		else
		{
			white--;
			blue--;
			swap(data, NEXT, blue);
		}
	}
}

void quicksort (vector<Track>& data, int first, int last)
{
	//               
	assert(0 <= first && last < size (data));
	//                
	if (first >= last) {
        return;
	}
	else
	{
		int red, blue;
		dnf(data, first, last, red, blue);
		quicksort(data, first, red);
		quicksort(data, blue, last);
	}
}

void dnf2 (vector<Track>& data, int first, int last, int& red, int& blue) //                      
{
	red = first-1;
	blue = last+1;
	int white = last-1;

	const Track PIVOT = data[first+(last-first)/2];
	while (blue > white - 1)
	{
		const int NEXT = white + 1;
		if(data[NEXT] < PIVOT)
		{
			red++;
			swap(data, red, NEXT);
		}
		else if (data[NEXT] == PIVOT)
			white++;
		else
		{
			white++;
			blue--;
			swap(data, NEXT, blue);
		}
	}
}

void quicksort2 (vector<Track>& data, int first, int last) //                            
{
	//               
	assert(0 <= first && last < size (data));

	//                
	if (first >= last)
        return;
	else
	{
		int red, blue;
		dnf(data, first, last, red, blue);
		quicksort(data, first, red);
		quicksort(data, blue, last);
	}
}

int largest (vector<Track>& v, int low, int up)
{
    vector<Track> stack;
    while (low < up)
    {
        stack.push_back(v[low]);
        low++;
    }

    while(stack.size() > 0)
    {
        stack[low] = stack[stack.size()-1];
        stack.pop_back();
    }

    return low;
}

void sort (vector<Track>& v, int n)
{
    while (n <= 1)
    {
        const int POS = largest (v, 0, n-1);
		swap (v, POS, n-1);
		n--;
    }
}

/*                                                                       
                                      
                   
                                                                      
                                           
                                          
                                                                       */
enum SortingMethod {InsertionSort,SelectionSort,BubbleSort,QuickSort,QuickSort2,NoOfSortingMethods};
string methods [] = {"Insertion", "Selection", "Bubble", "Quicksort", "Quicksort adapted to part 2"} ;

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
    SortingMethod m = get_sorting_method () ;
    cout << "Sorting tracks with " << methods[m] << " sort" << endl;

    for (int i = 100; i < 5799; i+=100)
    {
        vector<Track> songs2 = songs;
        switch (m)
        {
            case InsertionSort: insertion_sort(songs2,i) ; break ;
            case SelectionSort: selection_sort(songs2,i) ; break ;
            case BubbleSort:    bubble_sort   (songs2,i) ; break ;
            case QuickSort:     quicksort   (songs2,0,i) ; break ;
            case QuickSort2:    quicksort2  (songs2,0,i) ; break ;
            default:        cout << "Huh?" << endl ;
        }
        Slice s = {0, i};
        assert(is_sorted(songs2, s));

        while (ultimusCounterusXIV >= 100000)
        {
            ultimusCounterusXIV -= 100000;
            cout << "*" ;
            if (ultimusCounterusXIV < 100000)
            {
                cout << ".";
                ultimusCounterusXIV = 0;
            }
        }
        cout << endl;
    }
    quicksort(songs, 0, size(songs)-1);
    cout << "Tracks sorted." << endl;
    show_all_tracks (songs,NO_OF_SONGS) ;
	return 0;
}

