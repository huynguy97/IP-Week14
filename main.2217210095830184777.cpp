//                      
//                  

/*                                                                    
                                              
            
                                                                                                            
                                  
                              
                                                           
                                                                    
                                                          
                                                               
                                                                     */
#define NDEBUG

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
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

const int MAX_NO_OF_SONGS = 6000;           //                                
vector<Track> songs ;              //                                     
int counter=0;
/*                                                                       
                                
                                                               
                                                                         
                                                                       */
bool operator <(const Length& a, const Length& b)
{
    /*              
                                                          
                                                                 
    */
    if (a.minutes == b.minutes)
        return a.seconds < b.seconds;
    else
        return a.minutes < b.minutes;
}

bool operator==(const Length& a, const Length& b)
{

    return a.minutes==b.minutes && a.seconds==b.seconds;
}

bool operator<(const Track& a, const Track& b)
{
    /*              
                                                            
                                                                         
                                          

    */
    counter++;
    return a.time < b.time;

    //                    
    /*
                                
                         
                                 
                                               
                                                      
                 
                                             
                 
                                  
             

             
                                       

            */

    if(a.artist == b.artist)
    {
        if(a.cd == b.cd)
        {
            if (a.track_no == b.track_no)
            {
                return false;
            }
            else
                return a.track_no < b.track_no;
        }
        else
            return a.cd < b.cd ;
    }
    else
        return a.artist < b.artist;

}

/*                                                 */

bool operator==(const Track& a, const Track& b)
{
    /*              
                                                 
                                                       
                                                         

    */
    counter++;
    //                    
    //                                                                                          
    return a.time == b.time ;
    //                                                          
}

//	                                 
bool operator>(const Track& a, const Track& b)
{
    /*              
                                                            
                                                                         
                                          
    */
    return b < a;

}

bool operator<=(const Track& a, const Track& b)
{
    //          
    return !(b < a) ;
}

bool operator>=(const Track& a, const Track& b)
{
    //          
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

//                                                                                                        
ostream& operator<< (ostream& out, const Track track)
{
    //               
    assert (true) ;
    /*                 
                                                                                    
    */
    out << "Artist: " << track.artist   << endl ;
    out << "Album: " << track.cd       << endl ;
    out << "Year: " << track.year     << endl ;
    out << "Track number: " << track.track_no << endl ;
    out << "Title: " << track.title    << endl ;
    out << "Tags: " << track.tags     << endl ;
    out << "Time: " << track.time     << endl ;
    out << "Country: "<< track.country  << endl ;
    out << endl ;
    return out ;
}

//                                                                           
int read_songs (ifstream& infile, vector<Track> &songs)
{
    //               
    assert (infile.is_open ()) ;
    /*                 
                                                                                  
                                                               
    */
    int no_of_read_songs = 0 ;
    do
    {
        Track song ;
        infile >> song ;
        if (infile)
            songs.push_back(song) ;
    }
    while (infile);
    return songs.size();
}

int read_file (string filename)
{
    //               
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
void show_all_tracks (vector<Track> &songs)
{
    //               
    assert (true) ;
    /*                 
                                                                      
    */
    for(int i = 0; i<songs.size(); i++)
        cout << songs[i];
}

/*                                                                       
                                                         
                                                                       */
struct Slice
{
    int from ;  //             
    int to ;  //           
} ;

Slice mkSlice (int from, int to)
{
    //               
    assert (0 <= from && from <= to);
    /*                 
                                                  
    */ Slice s = { from, to } ;
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

typedef int El ;                //                                                       

bool is_sorted (vector<Track> &songs, Slice s)
{
    //               
    assert (valid_slice(s)) ; //                            
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

int find_position ( vector<Track> &songs, Slice s, Track y )
{
    //               
    assert (valid_slice(s) && is_sorted(songs,s)) ;    //                            
//                                           
    for ( int i = s.from ; i <= s.to ; i++ )
        if ( y <= songs [i] )
            return i ;
    return s.to+1;
}

void shift_right ( vector<Track> &songs, Slice s )
{
    //               
    assert (valid_slice (s)) ; //                                
//                                                      
//                                               
//         
//                                          
    for ( int i = s.to+1 ; i > s.from ; i-- )
        songs [i]  = songs [i-1] ;
}

void insert ( vector<Track> &songs, int& length, Track y )
{
    //               
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

void swap (vector<Track> &songs, int  i, int  j )
{
    //               
    assert ( i >= 0 && j >= 0 ) ; //                          
    //                          
//                                                                    
    const Track HELP = songs [i];
    songs [i] = songs [j] ;
    songs [j] = HELP;
}

//                            
void insertion_sort ( vector<Track> &songs, int length )
{
    int sorted = 1 ;
    while ( sorted < length )
    {
        insert ( songs, sorted, songs[sorted] ) ;
    }
}

//                            
int smallest_value_at ( vector<Track> &songs, Slice s )
{
    //               
    assert (valid_slice (s)) ; //                        
//                                                              
//                                                  
    int smallest_at = s.from ;
    for ( int index = s.from+1 ; index <= s.to ; index++ )
        if ( songs [index] < songs [smallest_at] )
            smallest_at = index ;
    return smallest_at ;
}

void selection_sort ( vector<Track> &songs, int length )
{
    for ( int unsorted = 0 ; unsorted < length ; unsorted++ )
    {
        const int k = smallest_value_at (songs, mkSlice (unsorted, length-1));
        swap ( songs, unsorted, k ) ;
    }
}

//                         
bool bubble ( vector<Track> &songs, Slice s )
{
    //               
    assert (valid_slice(s)); //                           
//                
//                                                        
//                                          
    bool is_sorted = true ;
    for ( int i = s.from ; i < s.to ; i++)
        if ( songs [i] > songs [i+1])
        {
            swap ( songs, i, i+1 ) ;
            is_sorted = false ;
        }
    return is_sorted ;
}

void bubble_sort ( vector<Track> &songs, int length )
{
    while ( !bubble ( songs, mkSlice (0, length-1 ) ) )
        length-- ;
}

void print_stars()
{
    int x;
    int punt;
    x = counter / 100000;
    punt = counter % 100000;
    for (int i = 0; i < x; i++)
        cout << "*";
    if (punt != 0)
        cout << ".";
    cout << endl;
}
/*                                                                       
                                      
                   
                                                                      
                                           
                                          
                                                                       */
enum SortingMethod {InsertionSort,SelectionSort,BubbleSort,NoOfSortingMethods};
string methods [] = {"insertion", "selection", "bubble"} ;

int maximum(int a, int b)
{
    if (a>=b)
        return a;
    else
        return b;
}

int minimum(int a, int b)
{
    if (a<=b)
        return a;
    else
        return b;
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

void DNF (vector<Track>& songs, int first, int last, int& red, int& blue)
{
    //              
    assert (true);
    /*                                                                                                      
                                                                                                                                                                 
                                            
    */

    red = first - 1;
    blue = last + 1;
    int white = last + 1;
    const Track MIDDLE = songs[first+(last-first)/2];
    while (red < white - 1)
    {
        const int NEXT = white - 1;
        if (songs[NEXT] < MIDDLE)
        {
            red++;
            swap(songs, red, NEXT);
        }
        else if (songs[NEXT] == MIDDLE)
            white--;
        else
        {
            white--;
            blue--;
            swap(songs, NEXT, blue);
        }
    }
    for (int i = 0; i < 40; i++)
     {
        cout << songs[i];
        cout << "Read " << i << " songs" << endl;
     }
}

void DNF_adjust (vector<Track>& songs, int first, int last, int& red, int& blue)
//                                                    
{
    //              
    assert (true);
    /*                                                                                                      
                                                                                                                                                                 
                                            
    */

    red = first - 1;
    blue = last + 1;
    int white = red + 1;
    const Track MIDDLE = songs[first+(last-first)/2];
    while (red < white - 1)
    {
        const int NEXT = white - 1;
        if (songs[NEXT] < MIDDLE)
        {
            red++;
            swap(songs, red, NEXT);
        }
        else if (songs[NEXT] == MIDDLE)
        {
            //        
            swap(songs, white, NEXT);
        }
        else //                       
        {
            blue--;
            swap(songs, NEXT, blue);
        }
    }
    for (int i = 0; i < 40; i++)
     {
        cout << songs[i];
        cout << "Read " << i + 1 << " songs\n" << "Adjusted" << endl;
     }
}

void quicksort (vector<Track>& songs, int first, int last)
{
    //              
    assert (0 <= first && last < 40);
    //               
    //                                          
    if (first >= last)
    {
        cout << "returned" << endl;
        return ;
    }
    else
    {
        int red, blue;
        DNF(songs, first, last, red, blue);
        quicksort(songs, first, red);
        quicksort(songs, blue, last);
    }

}
void quicksort_adjust (vector<Track>& songs, int first, int last)
{
    //              
    assert (0 <= first && last < 40);
    //               
    //                                          
    if (first >= last)
    {
        cout << "returned" << endl;
        return ;
    }
    else
    {
        int red, blue;
        DNF_adjust(songs, first, last, red, blue);
        quicksort_adjust(songs, first, red);
        quicksort_adjust(songs, blue, last);
    }
}
/*                                                   
 
                  
                   
        
     
                                              
                            
                       
                        
     
 
                                                           
 
                     
     

     
 
                                        
 
              
     
                                            
                          
                      
     
 
                                              
 
                  
     
                                            
                          
     
              
                                  
 
*/
int main()
{
    /*
                                                         
                            
         
                                                                       
                               
         

                                                 

                                                                        

                    
            
                                                                              
                                                                              
                                                                              
                                                       
            

                                                  
         
                                    
                          
                          
                                    
         
                                                                                  

                           
                                   

        */
    vector<Track> songs;
    ifstream infile;
    infile.open("Tracks.txt");
    read_songs(infile, songs);
    int first = 0, last = 40;
    int red,blue;

    //                                   
    quicksort_adjust(songs, first, last);
    return 0;

}

