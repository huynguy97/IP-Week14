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
	int    track;						//             
	string title;                           //            
	string tags;                            //                            
	Length time;							//             
	string country;                         //                                         
};

typedef vector<Track> MuziekDB;         //                                          
MuziekDB songs;
int globalcounter;
int tracknr;
bool sortArtistB = true;
/*                                                                       
                                
                                                               
                                                                         
                                                                       */
bool operator < (const Length& a, const Length&b)
{
    //               
    assert(true);
    //                
    //              
    if (a.minutes == b.minutes)
    {
        return a.seconds< b.seconds;
    }
    else return a.minutes< b.minutes;

}

bool operator == (const Length&a, const Length&b)
{
    //               
    assert(true);
    //                
    //               
    return a.minutes == b.minutes &&
            a.seconds == b.seconds;
}

bool operator<(const Track& a, const Track& b)
{
    //               
    assert(true);
    //                
    //              
    //                                              
    //                           
    globalcounter++;
    if(sortArtistB)
    {
        if (a.artist ==  b.artist)
        {
            if (a.cd == b.cd)
            {
                return a.track < b.track;
            }
            else return a.cd < b.cd ;
        }
        else return a.artist < b.artist;
    }
    else
    {
        if (a.time ==  b.time)
        {
            if (a.artist == b.artist)
            {
                if (a.title == b.title)
                {
                    return a.cd < b.cd;
                }
                else return a.title < b.title;
            }
            else return a.artist < b.artist;
        }
        else return a.time < b.time;
    }
}

bool operator==(const Track& a, const Track& b)
{
    //               
    assert(true);
    //                
    //               
    globalcounter++;
    if(sortArtistB)
    {
        return  a.track == b.track &&
                a.artist== b.artist &&
                a.cd == b.cd ;
    }
    else{
        return  a.time == b.time &&
                a.artist== b.artist &&
                a.track == b.track &&
                a.cd == b.cd ;
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

/*                                                                       
                            
                                                                       */
istream& operator>> (istream& in, Length& lengte)
{
    char colon ;
    in >> lengte.minutes >> colon >> lengte.seconds ;
    return in ;
}

ostream& operator<< (ostream& out, const Length lengte)
{
    out << lengte.minutes << ':' ;
    if (lengte.seconds < 10)
        out << '0' ;
    out << lengte.seconds ;
    return out ;
}

istream& operator>> (istream& infile, Track& track)
{
    string dummy;
    getline(infile,track.artist);       //       
    getline(infile,track.cd);           //   
    infile >> track.year ;              //     
    getline(infile, dummy) ;            //                      
    infile >> track.track ;             //         
    getline(infile, dummy) ;            //                      
    getline(infile,track.title);        //            
    getline(infile,track.tags);         //           
    infile >> track.time ;              //           
    getline(infile, dummy) ;            //                      
    getline(infile,track.country);      //        
    getline(infile, dummy) ;            //                      
    return infile ;
}

ostream& operator<< (ostream& out, const Track track)
{
    out << track.artist << " " << track.cd << " [" << track.track << "] (" << track.time << ")" ;
    return out ;
}

int lees_liedjes(ifstream& infile, MuziekDB& songs)
{
    int aantal_ingelezen_liedjes = 0 ;
    do
    {
        while (infile)
        {
            Track track;
            infile >> track ;
            songs.push_back(track);
            tracknr++;
        }
    }
    while (infile);
    return songs.size() ;
}

int lees_bestand (string filename)
{
    ifstream nummersDBS (filename.c_str());
    if (!nummersDBS)
    {
        cout << "wasn't able to open '" << filename << "'." << endl;
        return -1;
    }
    cout << "Lees '" << filename << "' in." << endl;
    int aantal = lees_liedjes (nummersDBS, songs);
    nummersDBS.close();
    return aantal;
}

void toon_MuziekDB (MuziekDB& songs, int aantalLiedjes)
{
    for (int i = 0 ; i < aantalLiedjes; i++)
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
    Slice s = { from, to } ;
    return s ;
}

bool valid_slice (Slice s)
{
    return 0 <= s.from && s.from <= s.to ;
}

bool is_sorted (vector<Track>& tracks, Slice s)
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
    {
        if (tracks[i] > tracks[i+1])
            sorted = false ;
    }

    return sorted;
}

int find_position ( vector<Track>& tracks, Slice s, Track y )
{
//	              
    assert (valid_slice(s) && is_sorted(tracks,s)) ;    //                             
//	                                          
    for ( int i = s.from ; i <= s.to ; i++ )
        if ( y <= tracks [i] )
            return i ;
    return s.to+1;
}

int find_position2(vector<Track>& tracks, Slice s, Track y)
{
//	              
    //                                                                                   
//	                                          
    for ( int i = s.to; i >= s.from; i-- )
        if ( y >= tracks [i] )
            return i+1;
    return s.from;
}
void shift_right ( vector<Track>& tracks, Slice s )
{
//	              
    assert (valid_slice (s)) ;	//                                 
//	                                 	  	                  
//			    	                 	  	                    
//						   
//			    	               		  	                
    for ( int i = s.to+1 ; i > s.from ; i-- )
        tracks [i]  = tracks [i-1] ;
}

void insert ( vector<Track>& tracks, int& length, Track y )
{
    const int pos = find_position (tracks, mkSlice (0, length-1), y) ;
    if (pos < length)
        shift_right ( tracks, mkSlice (pos, length-1) ) ;
    tracks [pos] = y ;
    length++;
}

void insert2 ( vector<Track>& tracks, int& length, Track y )
{
    const int pos = find_position2 (tracks, mkSlice (0, length-1), y) ;
    if (pos < length)
        shift_right ( tracks, mkSlice (pos, length-1) ) ;
    tracks [pos] = y ;
    length++;
}

void swap (vector<Track>& tracks, int  i, int  j )
{
//	              
    assert ( i >= 0 && j >= 0 ) ;	//                          
    //                           
//                                                                        
    const Track help = tracks [i];
    tracks [i] = tracks [j] ;
    tracks [j] = help;
}

//	                            
void insertion_sort ( vector<Track>& tracks, int length )
{
    int sorted = 1 ;
    while ( sorted < length )
    {
        insert ( tracks, sorted, tracks[sorted] ) ;
    }
}

void insertion_sort2 ( vector<Track>& tracks, int length )
{
    int sorted = 1 ;
    while ( sorted < length )
    {
        insert2 ( tracks, sorted, tracks[sorted] ) ;
    }
}

//	                            
int smallest_value_at ( vector<Track>& tracks, Slice s )
{
//	              
    assert (valid_slice (s)) ;	//                        
//	                                                              
//	                                                   
    int  smallest_at = s.from ;
    for ( int index = s.from+1 ; index <= s.to ; index++ )
        if ( tracks [index] < tracks [smallest_at] )
            smallest_at = index ;
    return smallest_at ;
}

void selection_sort ( vector<Track>& tracks, int length )
{
    for ( int unsorted = 0 ; unsorted < length ; unsorted++ )
    {
        const int k = smallest_value_at (tracks, mkSlice (unsorted, length-1));
        swap ( tracks, unsorted, k ) ;
    }
}

//	                         
bool bubble ( vector<Track>& tracks, Slice s )
{
//	              
    assert (valid_slice(s));	//                            
//	               
//	                                                          
//	                                          
    bool is_sorted = true ;
    for ( int i = s.from ; i < s.to ; i++)
        if ( tracks [i] > tracks [i+1])
        {
            swap ( tracks, i, i+1 ) ;
            is_sorted = false ;
        }
    return is_sorted ;
}

void bubble_sort ( vector<Track>& tracks, int length )
{
    while ( !bubble ( tracks, mkSlice (0, length-1 ) ) )
        length-- ;
}

//       
void dnf (vector<Track>& data, int first, int last, int& red, int& blue)
{
    //              
    assert(first < last);
    //               
    //                                 
    red = first-1; //               
    blue = last+1; //                 
    int white = last+1; //                  
    const Track PIVOT = data [first+(last-first)/2];
    while (red < white - 1) //                 
    {
        const int NEXT = white - 1; //            
        if (data[NEXT] < PIVOT) //               
        {
            red++; //                       
            swap (data, red, NEXT) ;
        }
        else if (data[NEXT] == PIVOT) //                 
            white-- ; //                      
        else //                
        {
            white--;
            blue--; //                     
            swap (data, NEXT, blue);
        }
    }
}

//       
void dnfAdjusted (vector<Track>& data, int first, int last, int& red, int& blue)
{
    //    
    assert(first < last);
    //      
    //                                  
    red = first-1; //               
    blue = last+1; //                 
    int white = first-1; //                 
    const Track PIVOT = data [first+(last-first)/2];
    while (blue > white + 1) //                 
    {
        const int NEXT = white + 1; //             
        if (data[NEXT] < PIVOT) //               
        {
            red++; //                       
            white++;
            swap (data, red, NEXT) ;
        }
        else if (data[NEXT] == PIVOT) //                 
            white++ ; //                      
        else //                
        {
            blue--; //                     
            swap (data, NEXT, blue);
        }
    }
}

void quicksort (vector<Track>& data, int first, int last)
{
//     
    assert (0 <= first && last < data.size()) ;
//                                           
    if (first >= last) return ;
    else
    {
        int red, blue ;
        dnf (data, first, last, red, blue) ;
        quicksort (data, first, red) ;
        quicksort (data, blue, last) ;
    }
}

/*                                                                       
                                      
                   
                                                                                  
                                           
                                          
                                                                       */
enum SortingMethod {InsertionSort,InsertionSort2,SelectionSort,BubbleSort,QuickSort,NoOfSortingMethods};
string methods [] = {"insertion","New Insertion", "selection", "bubble", "quick"} ;

SortingMethod get_sorting_method ()
{
    cout << "What sorting method do you want to use? " << endl ;
    for (int m = 0; m < NoOfSortingMethods; m++)
        cout << m+1 << ": " << methods[m] << " sort" << endl ;
    int choice ;
    cin >> choice ;
    return static_cast<SortingMethod>(choice-1) ;
}

void globalcounterdisplay(ofstream& toFile)
{
    //               
    assert(true);
    //                
    //                                    

    while(globalcounter - 100000 >=0)
    {
        toFile << "*" ;
        globalcounter -= 100000 ;
    }
    if (globalcounter > 0)
        toFile <<"." << endl;

}

void sortArtist(int m, int NO_OF_SONGS)
{
    //               
    assert(true);
    //                
    //                           
    switch (m)
    {
        case InsertionSort: insertion_sort(songs,NO_OF_SONGS)   ; break ;
        case InsertionSort2:insertion_sort2(songs,NO_OF_SONGS)  ; break ;
        case SelectionSort: selection_sort(songs,NO_OF_SONGS)   ; break ;
        case BubbleSort:    bubble_sort   (songs,NO_OF_SONGS)   ; break ;
        case QuickSort:     quicksort(songs, 0, NO_OF_SONGS-1)    ; break ;
        default:        cout << "Huh?" << endl ;
    }
    cout << "File sorted." << endl;
    toon_MuziekDB (songs,NO_OF_SONGS) ;
}

void sortLength(int m, int NO_OF_SONGS)
{
    //               
    assert(true);
    //                
    //                           
    sortArtistB = false;
    sortArtist(m, NO_OF_SONGS);
}

void showGrowth(int m)
{
    //               
    assert(true);
    //                
    //                                                         
    ofstream toFile;
    toFile.open("output.txt");
    for (int x = 99; x < songs.size(); x += 100)
    {
        globalcounter = 0;
        MuziekDB songs2 = songs ;
        switch (m)
        {
        case InsertionSort:
            insertion_sort(songs2,x) ;
            break ;
        case InsertionSort2:
            insertion_sort2(songs2, x);
        case SelectionSort:
            selection_sort(songs2,x) ;
            break ;
        case BubbleSort:
            bubble_sort   (songs2,x) ;
            break ;
        case QuickSort:
            quicksort(songs2, 0, x-1) ;
            break;
        default:
            cout << "Huh?" << endl ;
        }
        globalcounterdisplay(toFile);
    }
    cout << "Done writing to file" << endl;
}

int sortBy()
{
    //               
    assert(true);
    //                
    //                                                               
    //                 
    int NO_OF_SONGS = lees_bestand ("Tracks.txt");
    if (NO_OF_SONGS < 0)
    {
        cout << "Error while reading file, program terminates" << endl;
        return NO_OF_SONGS;
    }
    int n;
    do
    {
        cout << "What do you want to show? \n 1: Sort by Artist. \n 2: Sort by Length. \n 3: show Growth. " << endl;
        cin >> n;
    }
    while(n < 1 || n > 3);
    SortingMethod m = get_sorting_method () ;
    cout << "Sorting with " << methods[m] << "sort" << endl;
    switch(n)
    {
    case (1):
        sortArtist(m, NO_OF_SONGS);
        break ;
    case (2):
        sortLength(m, NO_OF_SONGS);
        break ;
    default :
        showGrowth(m);
    }
    return n;
}

int main()
{
    sortBy();
    return 0;
}

/* 
      
                           
 
                    
                                    
     
                        
                     
     
             
 

                                
 
                                    
     
                             
                          
     
 

*/

