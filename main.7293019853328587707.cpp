#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>
#define NDEBUG

/*
                                                      
*/

using namespace std;

struct Length
{
	int minutes;
	int seconds;
};
struct Track
{
	string artist;
	string cd;
	int    year;
	int    track_no;
	string title;
	string tags;
	Length time;
	string country;
};

int counter = 0;

/*                                             */

bool operator<(const Track& a, const Track& b)
{
    counter++;

    if (a.artist == b.artist)
    {
        if (a.cd == b.cd)
        {
            if (a.year == b.year)
            {
                return a.track_no < b.track_no;
            }
            else
                return a.year < b.year;
        }
        else
            return a.cd < b.cd;
    }
    else
        return a.artist < b.artist;
}

bool operator==(const Track& a, const Track& b)
{
    counter++;

    return a.artist == b.artist && a.cd == b.cd && a.year == b.year && a.track_no == b.track_no ;
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

bool operator<(const Length& a, const Length& b)
{
    counter++;

    if (a.minutes != b.minutes)
    {
        return a.minutes < b.minutes;
    }
    else
    {
        return a.seconds < b.seconds;
    }
}

bool operator>(const Length& a, const Length& b)
{
    return b < a;
}

bool operator==(const Length& a, const Length& b)
{
    counter++;

    return a.minutes == b.minutes && a.seconds == b.seconds;
}

bool operator<=(const Length& a, const Length& b)
{
	return !(b < a) ;
}

bool operator>=(const Length& a, const Length& b)
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

/*                                                */

int read_songs (ifstream& infile, vector<Track>& songsvector)
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
            songsvector.push_back(song);
        }
    }
    while (infile);
    return songsvector.size();
}

int read_file (string filename, vector<Track>& songsvector)
{//               
    assert (songsvector.size() == 0) ;
/*                 
                                                                              
                                                                                             
                                        
*/
    ifstream songsDBS (filename.c_str());
    if (!songsDBS)
    {
        cout << "Could not open '" << filename << "'." << endl;
        return -1;
    }
    cout << "Reading '" << filename << "'." << endl;
	const int NO_OF_SONGS = read_songs (songsDBS, songsvector);
	songsDBS.close();
	cout << "Read " << NO_OF_SONGS << " tracks." << endl;
	return NO_OF_SONGS;
}

void show_all_tracks (vector<Track>& songsvector, int no_of_songs)
{//               
    assert (no_of_songs >= 0) ;
/*                 
                                                                  
*/
    for (int i = 0 ; i < no_of_songs; i++)
        cout << i+1 << ". " << songsvector[i] << endl ;
}

/*                                                     */

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

bool is_sorted (vector<Track>& vect, Slice s)
{//	              
	assert (valid_slice(s)) ;	//                           
//	               
//	                 	                                
//						                                
//						   
//						                            
	bool sorted = true ;
	for (int i = s.from; i < s.to && sorted; i++)
		if (vect[i].time > vect[i+1].time)
			sorted = false ;
	return sorted ;
}

void shift_right (vector<Track>& vect, Slice s )
{//	              
	assert (valid_slice (s)) ;	//                               
//	                               	  	                
//			    	               	  	                  
//						   
//			    	             		  	              
	for ( int i = s.to+1 ; i > s.from ; i-- )
		vect[i] = vect[i-1] ;
}

void swap (vector<Track>& vect, int  i, int  j)
{//	              
	assert ( i >= 0 && j >= 0 ) ;	//                         
						            //                         
//                                                                
	const Track HELP = vect [i];
	vect [i] = vect [j];
	vect [j] = HELP;
}

/*                                             */

void quicksort (vector<Track>& songsvector, int from, int to)
{
    if (from >= to)
        return;

    Slice bert = mkSlice(from, to);

    if (is_sorted(songsvector, bert))
        return;

    //                              

    int no_left = 0;
    int no_pivot = 1;
    int no_right = 0;

    int pivot_location = from;

    for (int i = from + 1; i <= to; i++)
    {
        if (songsvector[i].time == songsvector[pivot_location].time)
        {
            Track temp = songsvector[i];
            Slice ernie = mkSlice(pivot_location + no_pivot - 1, i - 1);
            shift_right(songsvector, ernie);
            songsvector[pivot_location+1] = temp;
            no_pivot++;
        }
        else if (songsvector[i].time > songsvector[pivot_location].time)
        {
            no_right++;
        }
        else
        {
            Track temp = songsvector[i];
            Slice ernie = mkSlice(pivot_location, i - 1);
            shift_right(songsvector, ernie);
            pivot_location++;
            songsvector[pivot_location-1] = temp;
            no_left++;
        }
    }

    quicksort(songsvector, from, from + no_left - 1);       //          
    quicksort(songsvector, from + no_left + no_pivot, to);         //           

    return;
}

void DNF (vector<Track>& songsvector, int from, int to)
{
    Slice bert = mkSlice(from, to);

    if (is_sorted(songsvector, bert))
        return;

    int no_left = 0;
    int no_pivot = 1;
    int no_right = 0;

    int pivot_location = from;

    for (int i = to; i > pivot_location; i--)
    {
        if (songsvector[i].time == songsvector[pivot_location].time)
        {
            Track temp = songsvector[i];
            Slice ernie = mkSlice(pivot_location + no_pivot - 1, i - 1);
            shift_right(songsvector, ernie);
            songsvector[pivot_location+1] = temp;
            no_pivot++;
            pivot_location++;
        }
        else if (songsvector[i].time > songsvector[pivot_location].time)
        {
            no_right++;
        }
        else
        {
            Track temp = songsvector[i];
            Slice ernie = mkSlice(pivot_location - no_pivot + 1, i - 1);
            shift_right(songsvector, ernie);
            pivot_location++;
            songsvector[pivot_location - no_pivot] = temp;
            no_left++;
        }
    }
}

/*                                             */
/*
                                             
 
                            
                             

                    
     
                                     
         
                                     
                                   
         
              
     
               
 

                         
 
                         

                 
     
                                         

                         

            
     
 
*/

int main()
{
    vector<Track> songsvector = {};

	const int NO_OF_SONGS = read_file ("Tracks.txt", songsvector);
	if (NO_OF_SONGS < 0)
	{
        cout << "Reading file failed. Program terminates." << endl;
	    return NO_OF_SONGS;
    }

    quicksort(songsvector, 0, NO_OF_SONGS - 1);

    cout << "Tracks sorted." << endl;
    show_all_tracks (songsvector,NO_OF_SONGS) ;

	return 0;
}

