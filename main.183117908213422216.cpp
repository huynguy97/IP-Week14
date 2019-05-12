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

bool operator<(const Track& a, const Track& b)
{
    if (a.artist == b.artist)
    {
        if (a.cd == b.cd)
            return a.track_no < b.track_no;
        return a.cd < b.cd;
    }
    return a.artist < b.artist;    /*                                                 */
}

bool operator==(const Track& a, const Track& b)
{
    if (a.artist == b.artist)
    {
        if (a.cd == b.cd)
            return a.track_no == b.track_no;
        return a.cd == b.cd;
    }
    return a.artist == b.artist;   /*                                                 */
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

bool operator== (Length a, Length b)
{
    if (a.minutes == b.minutes)
        return (a.seconds == b.seconds);
    return false;
}

bool operator< (Length a, Length b)
{
    if (a.minutes < b.minutes)
        return true;
    if (a.minutes == b.minutes)
        return (a.seconds < b.seconds);
    return false;
}

bool operator<= (Length a, Length b)
{
    return !(b < a) ;
}

bool operator> (Length a, Length b)
{
    return b < a ;
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
    cout << "Reading '" << filename << "'." << endl;

	const int NO_OF_SONGS = read_songs (songsDBS, songs);
	songsDBS.close();
	cout << " Read " << NO_OF_SONGS << " tracks." << endl;
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

//                                          

/*                                           */

void dnf1 (vector<Track>& songs, int first, int last, int& red, int& blue)
{
    //                       
    assert(0 <= first && last < static_cast<int> (songs.size()));
    //                                                                  
    red = first - 1;
    blue = last + 1;
    int white = last + 1;
    const Track PIVOT = songs[first + (last - first)/2];
    while (red < white - 1)
    {
        const int NEXT = white - 1;
        if (songs[NEXT] < PIVOT)
        {
            red++;
            swap(songs, red, NEXT);
        }
        else if (songs[NEXT] == PIVOT)
            white--;
        else
        {
            white--;
            blue--;
            swap(songs, NEXT, blue);
        }
    }
}

void quicksort1 (vector<Track>& songs, int first, int last)
{
    //    
    assert(0 <= first && last < static_cast<int> (songs.size()));
    //                                                                                           
    if (first >= last)
        return;
    else
    {
        int red, blue;
        dnf1(songs, first, last, red, blue);
        quicksort1(songs, first, red);
        quicksort1(songs, blue, last);
    }
}

/*                           */

void dnf2 (vector<Track>& songs, int first, int last, int& red, int& blue)
{
    //                       
    assert(0 <= first && last < static_cast<int> (songs.size()));
    //                                                                  
    red = first - 1;
    blue = last + 1;
    int white = last + 1;
    const Length PIVOT = songs[first + (last - first)/2].time;
    while (red < white - 1)
    {
        const int NEXT = white - 1;
        if (songs[NEXT].time < PIVOT)
        {
            red++;
            swap(songs, red, NEXT);
        }
        else if (songs[NEXT].time == PIVOT)
            white--;
        else
        {
            white--;
            blue--;
            swap(songs, NEXT, blue);
        }
    }
}

void quicksort2 (vector<Track>& songs, int first, int last)
{
    //    
    assert(0 <= first && last < static_cast<int> (songs.size()));
    //                                                                                           
    if (first >= last)
        return;
    else
    {
        int red, blue;
        dnf2(songs, first, last, red, blue);
        quicksort2(songs, first, red);
        quicksort2(songs, blue, last);
    }
}

/*                                                      */

void dnf3 (vector<Track>& songs, int first, int last, int& red, int& blue)
{
    //                       
    assert(0 <= first && last < static_cast<int> (songs.size()));
    //                                                                  
    red = first - 1;
    blue = last + 1;
    int white = first - 1;
    const Track PIVOT = songs[first + (last - first)/2];
    while (white < blue -1)
    {
        const int NEXT = white + 1;
        if (songs[NEXT] < PIVOT)
        {
            white++;
            red++;
            swap(songs, red, NEXT);
        }
        else if (songs[NEXT] == PIVOT)
            white++;
        else
        {
            blue--;
            swap(songs, NEXT, blue);
        }
    }
}

void quicksort3 (vector<Track>& songs, int first, int last)
{
    //    
    assert(0 <= first && last < static_cast<int> (songs.size()));
    //                                                                                           
    if (first >= last)
        return;
    else
    {
        int red, blue;
        dnf3(songs, first, last, red, blue);
        quicksort3(songs, first, red);
        quicksort3(songs, blue, last);
    }
}

/*                                             

                                           
 
              
                           
     
                                
         
                   
                
         
            
                
     
               
 

                               
 
                  
     
                                           
                          
     
 

*/
//                                           
int minimum (int a, int b)
{
    if (a<b)
        return a;
    return b;
}
int maximum (int a, int b)
{
    if (a<b)
        return b;
    return a;
}

enum SortingMethod {DNF_on_Artist_Album_Track, DNF_on_Length, DNF_in_reverse, NoOfSortingMethods};
string methods [] = {"artist, album and track", "length", "artist, album and track through the reversed algorithm" } ;

SortingMethod get_sorting_method ()
{
    cout << "What way do you want to sort? " << endl ;
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
    cout << "Sorting tracks on " << methods[m] << "." << endl;
    switch (m)
    {
        case DNF_on_Artist_Album_Track: quicksort1 (songs, 0, songs.size()-1) ; break ;
        case DNF_on_Length:             quicksort2 (songs, 0, songs.size()-1) ; break ;
        case DNF_in_reverse:            quicksort3 (songs, 0, songs.size()-1) ; break ;
        default:                        cout << "Huh?" << endl ;
    }
    cout << "Tracks sorted." << endl;
    cout << "Do you want to print the list? (y/n)" << endl;
    char thisinput;
    cin >> thisinput;
    while (!(thisinput=='y' || thisinput=='n'))
    {
        cout << "Wrong input, please retry. (y/n)" << endl;
        cin >> thisinput;
    }
    if (thisinput == 'y')
        show_all_tracks (songs,NO_OF_SONGS) ;

    return 0;
}

