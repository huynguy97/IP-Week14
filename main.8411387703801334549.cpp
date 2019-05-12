#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>

//                     
//                            

using namespace std;

/*                                        */

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

typedef Track El;

/*                                           */
bool operator<(const Length& a, const Length& b)
{
    //               
    assert (true);
    //                                                                        
    if (a.minutes == b.minutes)
        return a.seconds < b.seconds;
    return a.minutes < b.minutes;
}

bool operator==(const Length& a, const Length& b)
{
    //               
    assert (true);
    //                                                                                              
    return (a.minutes == b.minutes && a.seconds == b.seconds);
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

bool operator<(const Track& a, const Track& b)
{
    //               
    assert (true);
    //                                                                                                         
   //                         
    if (a.artist == b.artist)
        {if (a.cd == b.cd)
            {if (a.year == b.year)
                return a.track_no < b.track_no;
            else return a.year < b.year;}
        else return a.cd < b.cd;}
    return a.artist < b.artist ;
}

bool operator==(const Track& a, const Track& b)
{
    //               
    assert (true);
    //                                                                                                     
    //                         
    return (a.artist == b.artist && a.cd == b.cd && a.year == b.year && a.track_no == b.track_no);
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

/*                                                */

int size (vector<El>& data)
{
    return static_cast<int> (data.size());
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

int read_songs (ifstream& infile, vector<El>& songs)
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
                songs.push_back(song);
                no_of_read_songs++;
            }
    }
    while (infile);
    return no_of_read_songs ;
}

int read_file (string filename, vector<El>& songs)
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
	cout << "Read " << NO_OF_SONGS << " tracks." << endl;
	return NO_OF_SONGS;
}

void show_all_tracks (vector<El> songs, int no_of_songs)
{//               
    assert (size (songs) >= 0) ;
/*                 
                                                                  
*/
    for (int i = 0 ; i < no_of_songs; i++)
        cout << i+1 << ". " << songs[i] << endl ;
}

/*                                               */

void swap (vector<El>& songs, int first, int last)
{
    //               
    assert (0<= first && last<size(songs));
    //                                                                                    
    const El help = songs[first];
    songs[first] = songs[last];
    songs[last] = help;
}

void dnf (vector<El>& songs, int first, int last, int& red, int& blue)
{
    //               
    assert (0<= first && last<size(songs));
    //                                             
    red = first-1;
    blue = last+1;
    int white = first-1;
    const El pivot = songs[first+(last-first)/2];
    while (blue> white+ 1)
    {
        const int NEXT = white +1;
        if (songs[NEXT]<pivot)
        {
            red++;
            white++;
            swap(songs, red, NEXT);
        }
        else if (songs[NEXT]==pivot)
            white++;
        else
        {
            blue--;
            swap (songs, NEXT, blue);
        }
    }
}

void quicksort (vector<El>& songs, int first, int last)
{
    //               
    assert (0<= first && last < size(songs));
    //                                                   
    if (first>=last)
        return;
    else
    {
        int red;
        int blue;
        dnf (songs, first, last, red, blue);
        quicksort (songs, first, red);
        quicksort (songs, blue, last);
    }
}

int main()
{
    vector<El> songs;
    const int NO_OF_SONGS = read_file ("Tracks.txt", songs);
	if (NO_OF_SONGS < 0)
	{
        cout << "Reading file failed. Program terminates." << endl;
	    return NO_OF_SONGS;
    }
    quicksort (songs, 0, NO_OF_SONGS-1);
    show_all_tracks (songs,NO_OF_SONGS);
    cout << "Tracks sorted." << endl;
    return 0;
}

/*                                                        

                                            
 
                    
                  
     
                              
                             
             
     
                         
     
                               
                     
                      
                   
                    
     
 

                               
 
               
     
                                         
                        
            
     
           
 
                                                        */

