#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>
#include <math.h>
#include <tuple>
#include <cctype>
#include <locale>
#include <algorithm>

using namespace std;

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

int size (vector<Track>& tracks)
{
    return static_cast<int> (tracks.size());
}

int size (vector<int>& vectors)
{
    return static_cast<int> (vectors.size());
}

//                                                   
bool operator < (const Length& a, const Length& b)
{
    int c=0,d=0;
    c=a.seconds+a.minutes*60;
    d=b.seconds+b.minutes*60;
    return c<d;
}

bool operator == (const Length& a, const Length& b)
{
    int c=0, d=0;
    c=a.seconds+a.minutes*60;
    d=b.seconds+b.minutes*60;
    return c<d;
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

//                                                  

/*
        
                                              
 
                                                                                             
 

                                               
 
                                                                                              
 
*/

//      

bool operator<(const Track& a, const Track& b)
{
    return tie(a.time, a.artist, a.title, a.cd) < tie(b.time, b.artist, b.title, b.cd);
}

bool operator==(const Track& a, const Track& b)
{
    return tie(a.time, a.artist, a.title, a.cd) == tie(b.time, b.artist, b.title, b.cd);
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

void swap (vector<Track>& data, int  i, int  j )
{//	              
	assert ( i >= 0 && j >= 0 ) ;	//                         
						            //                         
//                                                                
	const Track HELP = data [i];
	data [i] = data [j] ;
	data [j] = HELP;
}

void swap (vector<int>& data, int  i, int  j )
{//	              
	assert ( i >= 0 && j >= 0 ) ;	//                         
						            //                         
//                                                                
	const int HELP = data [i];
	data [i] = data [j] ;
	data [j] = HELP;
}

//        
//                    
int largest(vector<int>& data, int low, int up)
{
    //              
	assert ( low >= 0 && up >= 0 );
    //                                                                     
    if (low >= up)
    {
        return low;
    }
    else
    {
        const int POS = largest(data, low+1, up);
        if (data[low] > data[POS])
        {
            return low ;
        }
        else
        {
            return POS ;
        }
    }
}

void sort (vector<int>& data, int n)
{
    //              
	assert (n>=0);
    //                                                                                                                    
    if (n > 1)
    {
        const int POS = largest(data, 0, n-1);
        swap (data, POS, n-1);
        sort(data, n-1) ;
    }
}

//                    
int largest_i(vector<int>& data, int till)
{
    //              
	assert ( till>=0 );
    //                                                                     
    int compare= data[0], remember=0;
    for (int i=1; i<till; i++)
    {
        if (compare <= data[i])
        {
            compare=data[i];
            remember=i;
        }
    }
    return remember;
}

void sort_i (vector<int>& data, int n)
{
    //              
	assert (n>=0);
    //                                                                                                                   
    while (n>1)
    {
        int POS= largest_i(data, n);
        swap (data, POS, n-1);
        n--;
    }
}

void show_intvector (vector<int> tester, int sizes)
{
    //              
	assert (sizes>0);
    //                                                                              
    for (int i=0; i<sizes; i++)
    {
        cout << tester[i] << " " ;
    }
    cout << endl;
}
//                 

int read_songs (ifstream& infile, vector<Track>& songs)
{//               
    assert (infile.is_open ()) ;
/*                 
                                                                              
                                                           
*/
    int no_of_read_songs=0;
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

int read_file (string filename, vector<Track>& songs)
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
    cout << "Reading '" << filename << "'." << endl;
	const int NO_OF_SONGS = read_songs (songsDBS, songs);
	songsDBS.close();
	cout << "Read " << NO_OF_SONGS << " tracks." << endl;
	return NO_OF_SONGS;
}

void show_all_tracks (vector<Track>& songs, int no_of_songs)
{//               
    assert (true) ;
/*                 
                                                                  
*/
    for (int i = 0 ; i < no_of_songs; i++)
        cout << i+1 << ". " << songs[i] << endl ;
}

bool is_sorted(vector<Track>& data, int from, int to)
{
    //              
	assert (from>=0 && to>=0);
    //                                                                                             
    for (int i=from; i<=to; i++)
    {
        if (i==to)
        {
            return true;
        }
        else
        {
            if (data[i]>data[i+1])
            {
                return false;
            }
        }
    }
}

bool is_sorted2(vector<int>& data, int from, int to)
{
    //              
	assert (from>=0 && to>=0);
    //                                                                                             
    for (int i=from; i<=to; i++)
    {
        if (i==to)
        {
            return true;
        }
        else
        {
            if(data[i]>data[i+1])
            {
                return false;
            }
        }
    }
}

void dnf (vector<Track>& data, int first, int last, int& red, int& blue)
{
    //               
    assert(first >= 0);
    /*                
                                                                                                                                                              
    */
    red= first-1;                               //               
    blue= last+1;                               //                 
    int white= last+1;                          //                  
    const Track PIVOT = data [first+(last-first)/2];
    while ((white-1)>red)                     //                 
    {
        const int NEXT = white - 1;             //            
        if (data[NEXT] < PIVOT)                 //               
        {
            red++;
            swap (data, red, NEXT);             //                       
        }
        else if (data[NEXT] == PIVOT)           //                 
        {
            white--;                            //                      
        }
        else                                    //                
        {
            white--;
            blue--;
            swap (data, NEXT, blue);            //                     
        }
    }
}

void quicksort (vector<Track>& data, int first, int last)
{
    //                
    assert (first >= 0 && last < size(data));
    //                                                      
    if (last<=first)
    {
        return;
    }
    else
    {
        int red, blue;
        dnf(data, first, last, red, blue);
        quicksort (data, first, red);
        quicksort (data, blue, last);
    }
}

void dnf2(vector<Track>& data, int first, int last, int& red, int& blue)
{
    //               
    assert(first >= 0);
    /*                
                                                                                                                                                              
    */
    red= first-1;                               //               
    blue= last+1;                               //                 
    int white= first-1;                          //                 
    const Track PIVOT = data [first+(last-first)/2];
    while (blue>white+1)                      //                 
    {
        const int NEXT = white + 1;             //            
        if (data[NEXT] < PIVOT)                 //               
        {
            red++;
            white++;
            swap (data, red, NEXT) ;            //                       
        }
        else if (data[NEXT] == PIVOT)           //                 
        {
            white++;                            //                      
        }
        else                                    //                
        {
            blue--;
            swap (data, NEXT, blue);            //                      
        }
    }
}

void quicksort2 (vector<Track>& data, int first, int last)
{
    //                                      
    assert (first >= 0 && last < size(data));
    //                                                      
    if (last<=first)
    {
        return;
    }
    else
    {
        int red, blue;
        dnf2(data, first, last, red, blue);
        quicksort2 (data, first, red);
        quicksort2 (data, blue, last);
    }
}
enum SortingMethod {Quicksort1,Quicksort2,Large_sorter,NoOfSortingMethods};
string methods [] = {"Quick", "Quick", "larger "} ;

SortingMethod get_sorting_method ()
{
    //              
	assert (true);
    //                                                                                         
    cout << "What sorting method do you want to use? " << endl ;
    for (int m = 0; m < NoOfSortingMethods; m++)
        cout << m+1 << ": " << methods[m] << "sort" << m+1 << endl ;
    int choice ;
    cin >> choice ;
    choice = max (1, min(choice,3)) ;
    return static_cast<SortingMethod>(choice-1) ;
}

int main ()
{
    //        
    vector<Track> songs;
	const int NO_OF_SONGS = read_file ("Tracks.txt", songs);
	if (NO_OF_SONGS < 0)
	{
        cout << "Reading file failed. Program terminates." << endl;
	    return NO_OF_SONGS;
    }
    vector<int> tester={1,2,2,3,5,3,2,56,34,6,77,34,2,3,5,2,12,5,2,3,5,656,42,65,0};
    SortingMethod m = get_sorting_method () ;
    //                             
    switch (m)
    {
        case Quicksort1     : quicksort(songs, 0, NO_OF_SONGS-1); break;
        case Quicksort2     : quicksort2(songs, 0, NO_OF_SONGS-1); break;
        case Large_sorter   : sort_i(tester,size(tester)); break;
        default         : cout << "Huh?" << endl ;
    }
    if (is_sorted2(tester, 0, size(tester)-1))
    {
        show_intvector(tester, size(tester));
    }
    else if (is_sorted(songs, 0, NO_OF_SONGS-1))
    {
        cout << "Tracks sorted." << endl;
        show_all_tracks(songs, NO_OF_SONGS);
    }
    else
    {
        cout << "Sorting tracks failed" << endl;
    }
    return 1;
}

