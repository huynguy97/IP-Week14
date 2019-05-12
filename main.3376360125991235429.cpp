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
vector<Track> songs;              //                                     
int counter;

/*                                                                       
                                
                                                               
                                                                         
                                                                       */
bool operator<(const Length& a, const Length& b)
{
    if(a.minutes==b.minutes)
        return a.seconds < b.seconds;
    return a.minutes < b.minutes;
}

bool operator==(const Length& a, const Length& b)
{
    return a.minutes==b.minutes && a.seconds==b.seconds;
}

bool operator<(const Track& a, const Track& b)
{
    counter++;
//                
/*
                                                                                
                      
                              
                                               
                                      
                                
                                    
*/
//                
/*
                      
                              
                                
                           
                                        
                                      
                              
*/
//                                                 
return a.time < b.time;
}

bool operator==(const Track& a, const Track& b)
{
    counter++;
//                
//                                                                                                                                                  
//                
//                                                                                  
//                                                 
return a.time==b.time;

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
        {
            songs.push_back(song) ;
            no_of_read_songs++;
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
//                                                    
	const int NO_OF_SONGS = read_songs (songsDBS, songs);
	songsDBS.close();
//	                                                      
	return NO_OF_SONGS;
}

int maximum(int a, int b)
{
    //              
    assert(true);
    //               
    //                                               

    if(a<b)
        return b;
    return a;
}
int minimum(int a, int b)
{
    //              
    assert(true);
    //               
    //                                                
    if(a<b)
        return a;
    return b;
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

typedef Track El ;                //                                                       

bool is_sorted (vector<El>& data, Slice s)
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

int find_position ( vector<El>& data, Slice s, El y )
{//	              
	assert (valid_slice(s) && is_sorted(data,s)) ;    //                           
//	                                          

//                 
/*
	                                        
		                    
			          
	              
*/
//                

	for ( int i = s.to ; i >= s.from ; i-- )
		if ( y > data [i] )
			return i+1 ;
	return s.from;

}

void shift_right ( vector<El>& data, Slice s )
{//	              
	assert (valid_slice (s) && s.to<=data.size() ) ;	//                               
//	                               	  	                
//			    	               	  	                  
//						   
//			    	             		  	              
	for ( int i = s.to+1 ; i > s.from ; i-- )
		data [i]  = data [i-1] ;
}

void insert ( vector<El>& data, int& length, El y )
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

void swap (vector<El>& data, int  i, int  j )
{//	              
	assert ( i >= 0 && j >= 0 ) ;	//                         
						            //                         
//                                                                
	const El HELP = data [i];
	data [i] = data [j] ;
	data [j] = HELP;
}

//	                            
void insertion_sort ( vector<El>& data, int length )
{
	int sorted = 1 ;
    while ( sorted < length )
    {   insert ( data, sorted, data[sorted] ) ;
    }
}

//	                           
int smallest_value_at ( vector<El>& data, Slice s )
{//	              
	assert (valid_slice (s) && s.to<data.size()) ;	//                        
//	                                                            
//	                                               
	int smallest_at = s.from ;
	for ( int index = s.from+1 ; index <= s.to ; index++ )
		if ( data [index] < data [smallest_at] )
			smallest_at = index ;
	return smallest_at ;
}

void selection_sort ( vector<El>& data, int length )
{	for ( int unsorted = 0 ; unsorted < length ; unsorted++ )
	{   const int k = smallest_value_at (data, mkSlice (unsorted, length-1));
	    swap ( data, unsorted, k ) ;
	}
}

//	                        
bool bubble ( vector<El>& data, Slice s )
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

void bubble_sort ( vector<El>& data, int length )
{
    while ( !bubble ( data, mkSlice (0, length-1 ) ) )
        length-- ;
}

/*                                                                       
                                      
                   
                                                                      
                                           
                                          
                                                                       */
enum SortingMethod {InsertionSort,SelectionSort,BubbleSort,HeapSort,QuickSort,WhileSort,NoOfSortingMethods};
string methods [] = {"insertion", "selection", "bubble", "heap", "quick","while"} ;

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

void stars_to_output(int n)
{
    //              
    assert(n>=0);
    //               
    //                                                               
    //                           
    //                        
    int i = n/100000;
    for(int j=0;j<i;j++)
        cout << '*';
    if(n%100000 != 0)
        cout << '.';
    cout << endl;
}

void push_up(vector<El>& my_vector, int i)
{
    //             
    assert(0<=i&&i<my_vector.size());
    //               
    //                                                                                               
    while(0<i && my_vector[(i-1)/2]<my_vector[i])
    {
        swap(my_vector, (i-1)/2, i);
        i = (i-1)/2;
    }
}

void build_heap(vector<El>& my_vector, int length)
{
    //             
    assert(length<=my_vector.size());
    //               
    //                                                                               
    for(int i = 0; i<length; i++)
        push_up(my_vector, i);
}

int max_index(vector<El>& my_vector, int i, int j)
{
    //              
    assert(0<=i && 0<=j && i<my_vector.size() && j<my_vector.size());
    //              
    //                                                                        
    if(my_vector[i]<my_vector[j])
        return j;
    return i;
}

void push_down(vector<El>& my_vector, int length)
{
    //             
    assert(length>0 && my_vector.size()>0 && length <= my_vector.size());
    //               
    //                                                                               
    int i =0;
    while( 2*i+2<length && my_vector[i] < my_vector[ max_index(my_vector, 2*i+1, 2*i+2)] )
    {
        i = max_index(my_vector, 2*i+1, 2*i+2);
        swap(my_vector, i, (i-1)/2);
    }
    if(2*i+2==length && my_vector[i]<my_vector[2*i+1]) //                                                  
        swap( my_vector, i, 2*i+1);
}

void pick_heap(vector<El>& my_vector,int length)
{
    //             
    assert(length<=my_vector.size());
    //               
    //                                                             
    //                                                                            
    for(int unsorted = length; unsorted>1; unsorted--)
    {
        swap(my_vector, 0, unsorted-1);
        push_down(my_vector, unsorted-1);
    }
}

void heap_sort(vector<El>& my_vector, int length)
{
    //              
    assert(length<=my_vector.size());
    //               
    //                                                           
    build_heap(my_vector,length);
    pick_heap(my_vector,length);
}
/*
                                  
                                                                          
 
                  
                  
                       
                                               
                           
                                                              
                                                                                 
                      
     
                            
                                          
                                   
         
                                
                  
                                     
         
                                       
                    
            
         
                               
                    
                   
                                        
         
                                        
     
 
*/

void dnf( vector<El>& my_vector, int first, int last, int& red, int& blue)
{
    //         
    assert( first>=0&&last<my_vector.size() );
    //          
    //                                                     
    //                                                  
    red = first-1;
    blue = last+1;
    int white = first-1;
    const El PIVOT = my_vector[first+(last-first)/2];
//                         
//                                                            
//                                                                               
    while(white+1<blue)//                   
    {
        int next = white +1;
//                                        
        if( my_vector[next]<PIVOT )
        {
//                              
            red++;
            white++;
            swap(my_vector,red,next);
        }
        else if(my_vector[next]==PIVOT)
            white++;
        else
        {
//                             
            blue--;
            swap(my_vector, next, blue);
        }
//                                      
    }
}

void quick_sort(vector<El>& my_vector, int first, int last)
{
    //              
//                                                            
    assert( first >=0 && last<= static_cast<int>(my_vector.size()) );
    //               
    //                                                                                                   
    if(first>=last) return;
    else{
        int red, blue ;
        dnf(my_vector, first, last, red, blue);
        quick_sort(my_vector, first, red);
        quick_sort(my_vector, blue, last);
    }
}

int largest(vector<El>& my_vector, int low, int up)
{
    //         
    assert(low>=0 && up<= static_cast<int>( my_vector.size() ) );
    //          
    //                                                                                     
    vector<int> stck;
    while(low<up)//                
    {
        stck.push_back(low);
        low += 1;//          
    }
    int x;
    int pos_max = low;//      
    while(stck.size()>0)
    {
        x = stck[stck.size()-1];
        stck.pop_back();
        if(my_vector[pos_max]<my_vector[x])//      
            pos_max = x;
    }
    return pos_max;
}

void while_sort(vector<El>& my_vector, int n)
{
    //         
    assert(n<=my_vector.size());
    //          
    //                                          
    int pos;
    while(n>1)
    {
        pos = largest(my_vector,0,n-1);
        swap(my_vector, pos, n-1);
        n--;
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
    SortingMethod m = get_sorting_method () ;
    cout << "Sorting tracks with " << methods[m] << " sort" << endl;
    vector<Track> songs_copy;
    for(int i = NO_OF_SONGS;i<NO_OF_SONGS+1;i++)
//                                  
    {
        songs_copy = songs;//                                           
        counter = 0;
        switch (m)
        {
            case InsertionSort: insertion_sort(songs_copy,i)     ;  break ;
            case SelectionSort: selection_sort(songs_copy,i)     ;  break ;
            case BubbleSort:    bubble_sort   (songs_copy,i)     ;  break ;
            case HeapSort:      heap_sort     (songs_copy,i)     ;  break ;
            case QuickSort:     quick_sort    (songs_copy,0,i-1) ;  break ;
            case WhileSort:     while_sort    (songs_copy,i)     ;  break ;
            default:        cout << "Huh?" << endl ;
        }
//                                 
    }
    cout << "Tracks sorted." << endl;
    show_all_tracks (songs_copy,NO_OF_SONGS) ;
//                    
	return 0;
}
/*                                
                                                                            
                                                                          
      
                                                                           
      
                                                                                                                       
                                                                                                                      
                                                                                                        
                                                                                            
                                                                       
                                                        
                                                   
                                                                                                              
                                                                                                            
                                                        
*/

/*                               
                                                          
                      
                                                                          
        
                                                                           
        
                                                                                                                                                  
                                                                               
                                                                                                                                                                                 
                                                                            
                                                  

*/

/*
                                   
                                                                          
                    
                    
                  

                                                                           
                    
                    
                    

                                                                                                                          
                                                                                           
                                
                                                                                              

*/

