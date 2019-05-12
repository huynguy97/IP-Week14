//                                      
//                                       

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

vector<Track> songs;

/*                                                                       
                                             
                                                                       */

//                                           
bool operator<(const Track& a, const Track& b)
{
    return (a.artist < b.artist || (a.artist == b.artist && a.cd < b.cd) || (a.artist == b.artist && a.cd == b.cd && a.year < b.year) ||
           (a.artist == b.artist && a.cd == b.cd && a.year == b.year && a.track_no < b.track_no));
}

bool operator==(const Track& a, const Track& b)
{
    return (a.artist == b.artist && a.cd == b.cd && a.year == b.year && a.track_no == b.track_no )  ;
}

//                     
/*
                                                
 
                                                                                           
 

                                                 
 
                                                              
 

                                              
 
                                                                                                                                               
                                                                                            
 

                                               
 
                                                                                              
 
*/

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

int size (vector<Track>&v)
{
    return static_cast<int> (v.size ());
}

int read_songs (ifstream& infile, vector<Track>& songs)
{//               
    assert (infile.is_open ()) ;
/*                 
                                                                              
                                                           
*/

    do {
        Track song ;
        infile >> song ;
        if (infile)
            songs.push_back(song) ;
    }
    while (infile);
    return size(songs) ;
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

void show_all_tracks (vector<Track> songs)
{//               
    assert (size(songs)>0) ;
/*                 
                                                                  
*/
    for (int i = 0 ; i < size(songs); i++)
        cout << i+1 << ". " << songs[i] << endl ;
}

/*                                                                       
                                         
                                                                       */

void swap (vector<Track>& songs, int  i, int  j)
{
    //	              
	assert ( i >= 0 && j >= 0 ) ;
    //                                                                

	const Track HELP = songs [i] ;
	songs [i] = songs [j] ;
	songs [j] = HELP ;
}

/*                                                                       
                                 
                                                                       */

void dnf_1 (vector<Track>& songs, int first, int last, int& red, int& blue)
{
    //           
    assert (0 <= first && last < size (songs)) ;
    /*             
                                                                                      
                                            
    */

    red = first - 1 ;
	blue = last + 1 ;
	int white = last + 1 ;

	const Track PIVOT = songs [first + (last - first) / 2] ;

	while (red < white - 1)
	{
	    const int NEXT = white - 1 ;
		if (songs[NEXT] < PIVOT)
		{
		    red++ ;
			swap (songs, red, NEXT) ;
		}
		else if (songs[NEXT] == PIVOT)
			white-- ;
		else
		{
		    white-- ; blue-- ;
			swap (songs, NEXT, blue) ;
		}
	}
}

/*                                                                       
                                 
                                                                       */

void dnf_2 (vector<Track>& songs, int first, int last, int& red, int& blue)
{
     //           
    assert (0 <= first && last < size (songs)) ;
    /*             
                                                                                      
                                            
    */

    red = first - 1 ;
	blue = last + 1 ;
	int white = first - 1 ;

	const Track PIVOT = songs [first + (last - first) / 2] ;

	while (white < blue - 1)
	{
	    const int NEXT = white + 1 ;
		if (songs[NEXT] < PIVOT)
		{
		    red++ ; white++ ;
			swap (songs, red, NEXT) ;
		}
		else if (songs[NEXT] == PIVOT)
			white++ ;
		else
		{
		    blue-- ;
			swap (songs, NEXT, blue) ;
		}
	}
}

/*                                                                       
                                     
                                                                       */

void quicksort (vector<Track>& songs, int first, int last)
{
    //             
    assert (0 <= first && last < size (songs)) ;
    //      	                                    

    if (first >= last) return ;
    else
    {
        int red, blue ;

        //                            
        //                                       

        dnf_2 (songs, first, last, red, blue) ;

        quicksort (songs, first, red) ;
        quicksort (songs, blue, last) ;
    }
}

/*                                                                       
                                       
                                                                       */

int size_int (vector<int>& v)
{
    return static_cast<int> (v.size ());
}

int largest(vector<Track>& songs, int low, int up)
{
    //            
    assert(low < up && low >= 0 && up < size(songs)) ;
    /*
                  
                                                                               
    */

    vector<int> stack ;

    while (low < up)
    {
        stack.push_back(low) ;
        low++ ;
    }

    int POS = low ;

    while (size_int(stack) > 0)
    {
        if (songs[stack[size_int(stack) - 1]] > songs[POS])
            POS = stack[size_int(stack) - 1] ;
        stack.pop_back() ;
    }

    return POS ;
}

void sort(vector<Track>& songs, int n)
{
    //             
    assert (true) ;
    //      	                                    

    while (n>1)
    {
        const int POS = largest(songs, 0, n-1) ;
        swap(songs, POS, n-1) ;
        n -- ;
    }
}

int main()
{
    string filename ;

    cout << "Please insert a filename: " ; getline(cin, filename) ;
    read_file(filename) ;

    //                                      

    int n = size(songs) ;
    sort(songs, n) ;

    show_all_tracks(songs) ;

    return 0;
}

