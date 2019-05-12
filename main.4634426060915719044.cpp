/*
                         
                    
*/

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

//                                                                              
vector <Track> songs;              //                                     

int size (vector<Track>& songs)
{
    return static_cast<int> (songs.size());
}

int size(vector<int>& c)
{
    return static_cast<int> (c.size());
}

int less_than = 0;
int equalto = 0;
int slice = 0;
/*                                                                       
                                
                                                               
                                                                         
                                                                       */
bool operator<(const Length& a, const Length& b)
{
//               
    assert (true) ;
/*                 
                                                                                                           
*/
    if(a.minutes == b.minutes)
    {
        return a.seconds < b.seconds;
    }
    else return a.minutes < b.minutes;
}

bool operator== (const Length& a, const Length& b)
{
//               
    assert (true) ;
/*                 
                                                                                                       
*/
    if(a.minutes == b.minutes)
    {
        return a.seconds == b.seconds;
    }
    return false;
}

bool operator<(const Track& a, const Track& b)
{
//               
    assert (true) ;
/*                 
                                                                                                                
*/
    less_than++;
    /*                        
     
                        
         
                                 
             
                                               
             
                                         
         
                                
     
                                    
        */
    if(a.time == b.time)
    {
        if(a.artist == b.artist)
        {
            if (a.title == b.title)
            {
                return a.cd < b.cd;
            }
            else return a.title < b.title ;
        }
        else return a.artist < b.artist;
    }
    else return a.time < b.time;
}

bool operator==(const Track& a, const Track& b)
{

//               
    assert (true) ;
/*                 
                                                                                                            
*/
    equalto++;
    /*                        
     
                        
         
                                 
             
                                             
                 
                                
                 
             
         
     
        
     
                     
     
    */
    if (a.time == b.time)
    {
        if(a.artist == b.artist)
        {
            if (a.title == b.title)
            {
                return a.cd == b.cd ;
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
            songs.push_back(song);
            no_of_read_songs++;
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
void show_all_tracks (vector <Track> songs, int no_of_songs)
{//               
    assert (true) ;
/*                 
                                                                  
*/
    for (int i = 0 ; i < no_of_songs; i++)
        cout << i+1 << ". " << songs[i] << endl ;
}

/*                                                                       
                                                         
                                                                       */
void counter (int less_than, int equalto)
{
    int total = 0;
    total = less_than + equalto;
    while(total >= 100000)
    {
        total = total - 100000;
        cout << "*";
    }
    cout <<"."<< endl;
}

void countslice(int less_than, int equalto, int& slice)
{
    slice++;
    if (slice - 100 == 0)
    {
        counter(less_than, equalto);
        slice = 0;
    }
}

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

int find_position ( vector<Track>& data, Slice s, Track y )
{//	              
	assert (valid_slice(s) && is_sorted(data,s)) ;    //                           
//	                                          
	for ( int i = s.from ; i <= s.to ; i++ )
		if ( y <= data [i] )
			return i ;
	return s.to+1;
}

void shift_right ( vector <Track>& data, Slice s )
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
	countslice(less_than, equalto, slice);
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
void insertion_sort ( vector<Track>& data , int length )
{
	int sorted = 1 ;
    while ( sorted < length )
    {
        insert ( data, sorted, data[sorted] ) ;
    }
}

//	                           
int smallest_value_at ( vector<Track>& data , Slice s )
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

void selection_sort ( vector<Track>& data , int length )
{	for ( int unsorted = 0 ; unsorted < length ; unsorted++ )
   {
    countslice(less_than, equalto, slice);
	   const int k = smallest_value_at (data, mkSlice (unsorted, length-1));
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
        {countslice(less_than, equalto, slice);
	    if ( data [i] > data [i+1])
		{	swap ( data, i, i+1 ) ;
			is_sorted = false ;
		}
        }
	return is_sorted ;
}

void bubble_sort ( vector<Track>& data , int length )
{
    while ( !bubble ( data, mkSlice (0, length-1 ) ) )
        length-- ;
}

void dnf(vector<Track>& data, int first, int last, int& red, int& blue)
{
    //	              
	assert (true);
//	               
//                                                      
    red = first-1;
    blue = last+1;
    int white = last+1;
    const Track pivot = data [first+(last-first)/2];
    while(red < white-1)
    {
        const int next = white-1;
        if(data[next] < pivot)
        {
            red++;
            swap(data, red, next);
        }
        else if(data[next] == pivot)
        {
            white--;
        }
        else
        {
            white--;
            blue--;
            swap(data, next, blue);
        }
    }
}

void dnfREVERSE(vector<Track>& data, int first, int last, int& red, int& blue)
{
    //	              
	assert (true);
    //	               
    //                
    red = first-1;
    blue = last+1;
    cout << "red: " << red << endl;
    cout << "blue: " << blue << endl;
    int white = first-1;    //                  
    const Track pivot = data [first+(last-first)/2];
    while(white+1 < blue)   //                 
    {
        const int next = white+1; //             
        if(data[next] > pivot)    //               
        {
            red++;
            white++;
            swap(data, red, next);
        }
        else if(data[next] == pivot)  //                 
        {
            white++;
        }
        else
        {
            blue--;
            swap(data, next, blue);  //               
        }
    }

}

void quicksort(vector<Track>& data, int first, int last)
{
    //	              
	assert (true);
//	               
//                                             
    if(first >= last)
    {
        return;
    }
    else
    {
        int red = 0;
        int blue = 0;
        dnf(data, first, last, red, blue);
        quicksort(data, first, red);
        quicksort(data, blue, last);
    }
}

int largest(vector<Track>& v, int low, int up)
{
    //	              
	assert (true);
    //	               
    //                     
    vector<int> stack;
    int lower = low;
    int highest = up;

    while(up > lower)
    {
        stack.push_back(lower);
        lower++;
    }
    while(size(stack) > 0)
    {
        if(v[size(stack)-1] > v[highest])
        {
            highest = size(stack)-1;
        }
        stack.pop_back();
    }
    return highest;
}

void largestsort(vector<Track>& v,int n)
{
//	              
	assert (true);
//	               
//                                            
    while(n > 1)
    {
        int POS = largest(v, 0, n-1);
        swap(v, POS, n-1);
        n--;
    }
}

/*                                                                       
                                      
                   
                                                                      
                                           
                                          
                                                                       */
enum SortingMethod {InsertionSort,SelectionSort,BubbleSort,QuickSort,LargestSort,NoOfSortingMethods};
string methods [] = {"insertion", "selection", "bubble", "quick", "largest"} ;

int minimum (int choice, int options)
{
   if (options < choice)
   {
      return options;
   }
    else
    {
        return choice;
    }
}
int maximum (int choice, int options)
{
   if (options > choice)
   {
      return options;
   }
    else
    {
        return choice;
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

    SortingMethod m = get_sorting_method () ;
    cout << "Sorting tracks with " << methods[m] << " sort" << endl;
    switch (m)
    {
        case InsertionSort: insertion_sort(songs,NO_OF_SONGS) ; break ;
        case SelectionSort: selection_sort(songs,NO_OF_SONGS) ; break ;
        case BubbleSort:    bubble_sort   (songs,NO_OF_SONGS) ; break ;
        case QuickSort:     quicksort     (songs,0,NO_OF_SONGS-1); break;
        case LargestSort:   largestsort   (songs,NO_OF_SONGS) ; break ;
        default:        cout << "Huh?" << endl ;
    }
    cout << "Tracks sorted." << endl;
    show_all_tracks (songs,NO_OF_SONGS) ;
    cout << "operator < is called " << less_than << " times." <<endl;
    cout << "operator = is called " << equalto << " times." <<endl;
	return 0;
}

