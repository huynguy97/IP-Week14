#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>

using namespace std;

//                 
//                                               

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

/*                                                                       
                         
                                                                       */

bool operator<(const Track& a, const Track& b)
//                                         
{
    if(a.artist == b.artist)
        if(a.cd == b.cd)
            if(a.year == b.year)
                return(a.track_no < b.track_no);
            else return (a.year < b.year);
        else return (a.cd < b.cd);
    return (a.artist < b.artist);
}

bool operator<(const Length& a, const Length& b)
//                                         
{
    if (a.minutes == b.minutes)
        return (a.seconds < b.seconds);
    else return a.minutes < b.minutes;

}

bool operator==(const Track& a, const Track& b)
//                                                    
//                         
{
    return (a.artist == b.artist &&
            a.cd == b.cd &&
            a.year == b.year &&
            a.track_no == b.track_no);
}

bool operator== (const Length& a, const Length& b)
//                                         
{
    return (a.minutes == b.minutes &&
            a.seconds == b.seconds);
}

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
{
    //               
    assert (true) ;
    /*                 
                                                                                                          
    */
    char colon ;
    in >> length.minutes >> colon >> length.seconds ;
    return in ;
}

ostream& operator<< (ostream& out, const Length length)
{
    //               
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
{
    //               
    assert (true) ;
    /*                 
                                                                            
    */
    string remains ;
    getline (infile, remains) ;
}

istream& operator>> (istream& infile, Track& track)
{
    //               
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
{
    //               
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

int read_songs (ifstream& in, vector<Track>& songs)
{
    //               
    assert (in.is_open ()) ;
    /*                 
                                                                                                 
                                                               
    */
    int no_of_read_songs = 0 ;

    while(in)
    {
        Track track = {};
        in >> track;
        songs.push_back(track);
        no_of_read_songs ++;
    }
    songs.pop_back();
    no_of_read_songs--;
    return no_of_read_songs ;
}

int read_file (string filename, vector<Track>& songs)
{
    //               
    assert (true) ;
    //                          
    /*                 
                                                                                  
                                                                                                 
                                            
    */
    ifstream songsDBS (filename.c_str());
    if (!songsDBS)
    {
        cout << "Could not open '" << filename << "'." << endl;
        return -1;
    }
    cout << "Reading '" << filename << "'" << endl;
    const int NO_OF_SONGS = read_songs (songsDBS, songs);
    songsDBS.close();
    cout << "Read " << NO_OF_SONGS << " tracks" << endl;
    return NO_OF_SONGS;
}

//                                                                           
void show_all_tracks (int no_of_songs, vector<Track>& songs)
{
    //               
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
{
    //	              
    assert (0 <= from && from <= to);
    /*                 
                                                  
    */	Slice s = { from, to } ;
    return s ;
}

bool valid_slice (Slice s)
{
    //               
    assert (true) ;
    /*                 
                                                                                          
    */
    return 0 <= s.from && s.from <= s.to ;
}

typedef Track El;                //                                                       

bool is_sorted (Slice s, vector<Track>& songs)
{
    //	              
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

int find_position (Slice s, El y, vector<Track>& songs)
{
    //	              
    assert (valid_slice(s) && is_sorted(s, songs)) ;    //                           
//	                                          
    for ( int i = s.from ; i <= s.to ; i++ )
        if ( y <= songs[i] )
            return i ;
    return s.to+1;
}

void shift_right (Slice s, vector<Track>& songs)
{
    //	              
    assert (valid_slice (s)) ;	//                               
//	                               	  	                
//			    	               	  	                  
//						   
//			    	             		  	              
    for ( int i = s.to+1 ; i > s.from ; i-- )
        songs [i]  = songs [i-1] ;
}

void insert (int& length, El y, vector<Track>& songs)
{
    //               
    Slice s = mkSlice(0,length-1) ;
    assert (length >= 0 && is_sorted (s, songs)) ;
    /*                 
                                                                                         
                                       
    */
    const int POS = find_position (mkSlice (0, length-1), y, songs) ;
    if (POS < length)
        shift_right (mkSlice (POS, length-1), songs) ;
    songs [POS]= y ;
    length++;
}

void swap (vector<Track>& songs, int  i, int  j )
{
    //	              
    assert ( i >= 0 && j >= 0 ) ;	//                         
    //                         
//                                                                
    const Track HELP = songs [i];
    songs [i] = songs [j] ;
    songs [j] = HELP;
}

//	                           
void insertion_sort (int length, vector<Track>& songs)
{
    int sorted = 1 ;
    while ( sorted < length )
    {
        insert (sorted, songs[sorted], songs) ;
    }
}

//	                           
int smallest_value_at (Slice s, vector<Track>& songs)
{
    //	              
    assert (valid_slice (s)) ;	//                        
//	                                                            
//	                                               
    int smallest_at = s.from ;
    for ( int index = s.from+1 ; index <= s.to ; index++ )
        if ( songs [index] < songs [smallest_at] )
            smallest_at = index ;
    return smallest_at ;
}

void selection_sort (int length, vector<Track>& songs)
{
    for ( int unsorted = 0 ; unsorted < length ; unsorted++ )
    {
        const int k = smallest_value_at (mkSlice (unsorted, length-1), songs);
        swap (songs, unsorted, k ) ;
    }
}

//	                        
bool bubble (Slice s, vector<Track>& songs)
{
    //	              
    assert (valid_slice(s));	//                          
//	               
//	                                                    
//	                                        
    bool is_sorted = true ;
    for ( int i = s.from ; i < s.to ; i++)
        if ( songs [i] > songs [i+1])
        {
            swap (songs, i, i+1 ) ;
            is_sorted = false ;
        }
    return is_sorted ;
}

void bubble_sort (int length, vector<Track>& songs)
{
    while ( !bubble (mkSlice (0, length-1 ), songs) )
        length-- ;
}

/*                                                                       
                                                         
                                                                       */

void DNF (vector<Track>& songs, int first, int last, int& red, int& blue)
{
//                                                                 
//   
assert ((last > first) && (last >=0) && (first >= 0));
//    
//                                                              
//                                                                               

    red         = first -1;
    blue        = last +1;
    int white   = last +1;

    const Track PIVOT = songs[first+(last-first)/2];

    while (red < (white -1))
    {
        const int NEXT = white -1;
        if (songs[NEXT]/*     */ < PIVOT/*     */)
        {
            red++;
            swap(songs, red, NEXT);
        }
        else if (songs[NEXT]/*     */ == PIVOT/*     */)
        {
            white--;
        }
        else
        {
            white--;
            blue--;
            swap(songs, NEXT, blue);
        }
    }
}

void DNF2 (vector<Track>& songs, int first, int last, int& red, int& blue)
{
//                                                                 
//   
assert ((last > first) && (last >=0) && (first >= 0));
//    
//                                                              
//                                                                                

    red         = first - 1;
    blue        = last + 1;
    int white   = first - 1;

    const Track PIVOT = songs[first+(last-first)/2];

    while (blue > (white  + 1))
    {
        const int NEXT = white + 1;
        if (songs[NEXT]/*     */ > PIVOT/*     */)
        {
            blue--;
            swap(songs, blue, NEXT);
        }
        else if (songs[NEXT]/*     */ == PIVOT/*     */)
        {
            white++;
        }
        else
        {
            white++;
            red++;
            swap(songs, NEXT, red);
        }
    }
}

void quicksort (vector<Track>& songs, int first, int last)
{
    //   
    assert((0 <= first) && (last < (int)songs.size())) ;
    //    
    //                                    
    if (first >= last) return;
    else
    {
        int red;
        int blue;
        DNF(songs, first, last, red, blue);
        quicksort (songs, first, red);
        quicksort (songs, blue, last);

    }
}

void quicksort2 (vector<Track>& songs, int first, int last)
{
    //   
    assert((0 <= first) && (last < (int)songs.size())) ;
    //    
    //                                    
    if (first >= last) return;
    else
    {
        int red;
        int blue;
        DNF2(songs, first, last, red, blue);
        quicksort2 (songs, first, red);
        quicksort2 (songs, blue, last);

    }
}

//      
/*
                                
 
                
     
                                         
                        
            
     
 

                                            
 
                       
     
              
     
                       
     
                   
     
        
     
                   
     
 
*/
/*                                                                       
                                      
                   
                                                                      
                                           
                                          
                                                                       */

enum SortingMethod {InsertionSort,SelectionSort,BubbleSort,Quicksort,Quicksort2,NoOfSortingMethods};
string methods [] = {"insertion", "selection", "bubble", "quick", "quick (DNF reversed)"} ;

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
    string infile = "tracks.txt" ;
    //                                       
    //                      
    vector <Track> songs;
    int NO_OF_SONGS = read_file (infile, songs);
    int blue = 0;
    int red = 0;

    if (NO_OF_SONGS < 0)
    {
        cout << "Reading file failed. Program terminates." << endl;
        return NO_OF_SONGS;
    }
    SortingMethod m = get_sorting_method () ;
    cout << "Sorting tracks with " << methods[m] << " sort" << endl;
    switch (m)
    {
    case InsertionSort:
        insertion_sort(NO_OF_SONGS, songs) ;
        break ;
    case SelectionSort:
        selection_sort(NO_OF_SONGS, songs) ;
        break ;
    case BubbleSort:
        bubble_sort   (NO_OF_SONGS, songs) ;
        break ;
    case Quicksort:
        quicksort     (songs, 0, NO_OF_SONGS -1) ;
        break ;
    case Quicksort2:
        quicksort2     (songs, 0, NO_OF_SONGS -1) ;
        break ;
    default:
        cout << "Huh?" << endl ;
    }
    cout << "Tracks sorted." << endl;
    show_all_tracks (NO_OF_SONGS, songs) ;

    return 0;
}

