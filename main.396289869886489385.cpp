/*                                                                    
                                              
            
                                                                                                            
                                  
                              
                                                           
                                                                    
                                                          
                                                               
                                                                     */

//                                                     
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
vector<Track> Tracklist;              //                                     
int counter;
int counter2 = 0;
vector<string> growth;
/*                                                                       
                                
                                                                  
                                                                         
                                                                       */
bool operator< (const Length& c, const Length& d) {
    return ((c.minutes == d.minutes && c.seconds < d.seconds) || (c.minutes < d.minutes)) ;

}
bool operator== (const Length& c, const Length& d){
    return c.minutes == d.minutes && c.seconds == d.seconds;
}
bool operator<(const Track& a, const Track& b)
{
    counter++;
    if (a.time == b.time) {
        if (a.artist == b.artist) {
            if (a.cd == b.cd) {
                if (a.year == b.year) {
                    return a.track_no < b.track_no;
                } else {
                    return a.year < b.year;
                }
            } else {
                return a.cd < b.cd;
            }
        } else {
            return a.artist < b.artist;
        }
    } else {
        return a.time < b.time;
    }
}

bool operator==(const Track& a, const Track& b)
{
    counter++;
    if (a.artist == b.artist) {
        if (a.cd == b.cd) {
            if (a.year == b.year) {
                if (a.track_no == b.track_no) {
                    return true;
                }
            }
        }
    }
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

int minimum(int a, int b){
    if (a<b) {
        return a;
    } else {
        return b;
    }

}

int maximum (int a, int b) {
    if (a>b) {
        return a;
    } else {
        return b;
    }
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
int read_songs (ifstream& infile, vector<Track>& tracklist)
{//               
    assert (infile.is_open ()) ;
/*                 
                                                                              
                                                           
*/
    int no_of_read_songs = 0 ;
    do {
        Track song ;
        infile >> song ;
        if (infile)
            tracklist.push_back(song);
        no_of_read_songs++;
    }
    while (infile);
    return no_of_read_songs ;
}

int read_file (string filename)
{//               

/*                 
                                                                              
                                                                                             
                                        
*/
    ifstream songsDBS (filename.c_str());
    if (!songsDBS)
    {
        cout << "Could not open '" << filename << "'." << endl;
        return -1;
    }
    cout << "Reading '" << filename << "'." << endl;
    const int NO_OF_SONGS = read_songs (songsDBS, Tracklist);
    songsDBS.close();
    cout << " Read " << NO_OF_SONGS << " tracks." << endl;
    return NO_OF_SONGS;
}

//                                                                           
void show_all_tracks (vector <Track> tracklist, int no_of_songs)
{//               

/*                 
                                                                  
*/
    for (int i = 0 ; i < tracklist.size(); i++)
        cout << i+1 << ". " << tracklist[i] << endl ;
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

bool is_sorted (vector <Track>& tracklist, Slice s)
{//	              
    assert (valid_slice(s)) ;	//                           
//	               
//	                 	                                
//						                                
//						   
//						                            
    bool sorted = true ;
    for (int i = s.from; i < s.to && sorted; i++)
        if (tracklist[i] > tracklist[i+1])
            sorted = false ;
    return sorted ;
}

int find_position ( vector <Track>& tracklist, Slice s, Track y )
{//	              
    assert (valid_slice(s) && is_sorted(tracklist,s)) ;    //                           
//	                                          
    for ( int i = s.from ; i <= s.to ; i++ )
        if ( y <= tracklist[i] )
            return i ;
    return s.to+1;
}

void shift_right ( vector <Track>& tracklist, Slice s )
{//	              
    assert (valid_slice (s)) ;	//                               
//	                               	  	                
//			    	               	  	                  
//						   
//			    	             		  	              
    for ( int i = s.to+1 ; i > s.from ; i-- )
        tracklist [i]  = tracklist [i-1] ;
}

void insert ( vector <Track>& tracklist, int& length, Track y )
{//               
    Slice s = mkSlice(0,length-1) ;
    assert (length >= 0 && is_sorted (tracklist, s)) ;
/*                 
                                                                                     
                                   
*/

    counter2++;
    string step;
    step = "";
    if (counter2 %100 == 0) {
        for(int i = counter; i >= 100000; i = i - 100000) {
            step.push_back('*');

        }
        if (counter %100000 != 0 && counter != 0) {
            step.push_back('.');
        }

        growth.push_back(step);
    }
    const int POS = find_position (tracklist, mkSlice (0, length-1), y) ;
    if (POS < length)
        shift_right ( tracklist, mkSlice (POS, length-1) ) ;
    tracklist [POS] = y;
    length++;
}

void swap (vector <Track>& tracklist, int  i, int  j )
{//	              
    assert ( i >= 0 && j >= 0 ) ;	//                         
    //                         
//                                                                
    counter2++;
    string step;
    step = "";
    if (counter2 %100 == 0) {
        for(int i = counter; i >= 100000; i = i - 100000) {
            step.push_back('*');

        }
        if (counter %100000 != 0 && counter != 0) {
            step.push_back('.');
        }

        growth.push_back(step);
    }
    const Track HELP = tracklist [i];
    tracklist [i] = tracklist [j] ;
    tracklist [j] = HELP;
}

//	                           
void insertion_sort (vector <Track>& tracklist, int length )
{
    counter = 0;
    int sorted = 1 ;
    while ( sorted < length )
    {   insert ( tracklist, sorted, tracklist[sorted] ) ;
    }

}

//	                           
int smallest_value_at ( vector <Track>& tracklist, Slice s )
{//	              
    assert (valid_slice (s)) ;	//                        
//	                                                            
//	                                               
    int smallest_at = s.from ;
    for ( int index = s.from+1 ; index <= s.to ; index++ )
        if ( tracklist [index] < tracklist [smallest_at] )
            smallest_at = index ;
    return smallest_at ;
}

void selection_sort ( vector <Track>& tracklist, int length )
{
    counter = 0;
    for ( int unsorted = 0 ; unsorted < length ; unsorted++ )
    {   const int k = smallest_value_at (tracklist, mkSlice (unsorted, length-1));
        swap ( tracklist, unsorted, k ) ;
    }

}

//	                        
bool bubble ( vector <Track>& tracklist, Slice s )
{//	              
    assert (valid_slice(s));	//                          
//	               
//	                                                    
//	                                        
    counter2++;
    string step;
    step = "";
    if (counter2 %100 == 0) {
        for(int i = counter; i >= 100000; i = i - 100000) {
            step.push_back('*');

        }
        if (counter %100000 != 0 && counter != 0) {
            step.push_back('.');
        }

        growth.push_back(step);
    }

    bool is_sorted = true ;
    for ( int i = s.from ; i < s.to ; i++)
        if ( tracklist [i] > tracklist[i+1])
        {	swap ( tracklist, i, i+1 ) ;
            is_sorted = false ;
        }
    return is_sorted ;
}

void bubble_sort ( vector <Track>& tracklist, int length )
{
    counter = 0;
    while ( !bubble ( tracklist, mkSlice (0, length-1 ) ) ) {
        length--;
    }

}

void dnf (vector<Track>& data, int first, int last, int& red, int& blue) {

    //              
    assert (first >= 0 && last < data.size());
   //                       
    red = first - 1;
    blue = last + 1;
    int white = last + 1;
    const Track PIVOT = data [first +(last-first)/2];
    while (red < white - 1) {
        const int NEXT = white - 1;
        if(data[NEXT] < PIVOT) {
            red++;
         //                       
            swap(data,red,NEXT);
        } else if(data[NEXT] == PIVOT) {
            white--;
        } else {
            white--;
            blue--;
            swap(data, NEXT, blue);
        }
    }
    //                    
}

void dnf2 (vector<Track>& data, int first, int last, int& red, int& blue) {
    //                                                          
    //              
    assert (first >= 0 && last < data.size());
    red = first - 1;
    blue = last + 1;
    int white = first - 1;
    const Track PIVOT = data [first +(last-first)/2];
    while (blue > white + 1) {
        const int NEXT = white + 1;
        if(data[NEXT] < PIVOT) {
            red++;
            white++;
            swap(data,red,NEXT);
        } else if(data[NEXT] == PIVOT) {
            white++;
        } else {
            blue--;
            swap(data, NEXT, blue);
        }
    }
   //                     
}
void quicksort3 (vector<Track>& data, int first, int last) {
    //                         
    int red, blue;
    while (!first >= last) {
        x = dnf()

    }
}

void quicksort2 (vector<Track>& data, int first, int last) {
    //              
   //                                                            
    //                                         
    //               
    //                                    

    if (first >= last) {
        return;
    } else {
        int red, blue;
        dnf2(data, first, last, red, blue);
        quicksort2 (data, first, red);
        quicksort2(data, blue, last);
    }
}

void quicksort (vector<Track>& data, int first, int last) {
    //              
    //                                                           
    //                                         
    //               
    //                                    

    if (first >= last) {
        return;
    } else {
        int red, blue;
        dnf(data, first, last, red, blue);
        quicksort (data, first, red);
        quicksort(data, blue, last);
    }
}

/*                                                                       
                                      
                   
                                                                      
                                           
                                          
                                                                       */
enum SortingMethod {InsertionSort,SelectionSort,BubbleSort, QuickSort, QuickSort2};
string methods [] = {"insertion", "selection", "bubble", "quick", "quick2"} ;

SortingMethod get_sorting_method ()
{
    cout << "What sorting method do you want to use? " << endl ;
    for (int m = 0; m < 5; m++)
        cout << m+1 << ": " << methods[m] << " sort" << endl ;
    int choice ;
    cin >> choice ;
    choice = maximum (1, minimum (choice, 5)) ;
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
    cout << Tracklist.size() << endl;
    switch (m)
    {
        case InsertionSort: insertion_sort(Tracklist,NO_OF_SONGS) ; break ;
        case SelectionSort: selection_sort(Tracklist,NO_OF_SONGS) ; break ;
        case BubbleSort:    bubble_sort   (Tracklist,NO_OF_SONGS) ; break ;
        case QuickSort :    quicksort(Tracklist, 0, Tracklist.size() - 1); break;
        case QuickSort2:    quicksort2(Tracklist, 0, Tracklist.size() - 1); break;
        //                                        
    }
    cout << "Tracks sorted." << endl;
    show_all_tracks (Tracklist,NO_OF_SONGS) ;
    cout << "counter is: " << counter;
    for (int i = 0; i < growth.size(); i++){
        cout << growth[i] << "\n";
    }
    return 0;
}

