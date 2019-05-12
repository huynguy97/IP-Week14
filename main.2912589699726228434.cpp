//                                                          
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>

using namespace std;

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

const int MAX_NO_OF_SONGS = 6000;
vector<Track> songs;
int counter = 0;

bool operator<(const Track& a, const Track& b)
{
/*
             
                             
                         
                                 
                                               
                                        
                                
                                    
*/

    counter++;
    if (a.time.minutes == b.time.minutes)
        if(a.time.seconds == b.time.seconds)
            if (a.artist == b.artist)
                if (a.title == b.title)
                    return a.cd < b.cd;
                else return a.title < b.title;
            else return a.artist < b.artist;
        else return a.time.seconds < b.time.seconds;
    return a.time.minutes < b.time.minutes;

}

bool operator==(const Track& a, const Track& b)
{
    counter++;
    return a.artist == b.artist && a.cd == b.cd && a.year == b.year && a.track_no == b.track_no;

 //             
 //                                                                                                                                             
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

int size (vector<Track>& data)
{ return static_cast<int> (data.size()); }

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
            {songs.push_back(song);
            no_of_read_songs++;}
    }
    while (infile && no_of_read_songs < MAX_NO_OF_SONGS);
    return no_of_read_songs ;
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
	cout << "Read " << NO_OF_SONGS << " tracks." << endl;
	return NO_OF_SONGS;
}

void show_all_tracks (vector<Track>& songs, int no_of_songs)
{//               
    assert (no_of_songs < MAX_NO_OF_SONGS) ;
/*                 
                                                                  
*/
    for (int i = 0 ; i < no_of_songs; i++)
        cout << i+1 << ". " << songs[i] << endl ;
}

int minimum (int a, int b)
{
    if (a < b)
        return a;
    return b;
}

int maximum (int a, int b)
{
    if (a > b)
        return a;
    return b;
}

void swap(vector<Track>& songs, int i, int j)
{
//               
    assert (i >= 0 && j >= 0 && i < songs.size() && j< songs.size());
//                
//                                               

    const Track Help = songs [i];
    songs[i] = songs[j];
    songs[j] = Help;
}

void dnf(vector<Track>& songs, int first, int last, int& red, int& blue)
{
//               
    assert (first >= 0 && last >= 0 && first < songs.size() && last < songs.size());
//                
//                                                                                       

    red = first - 1;
    blue = last + 1;
    int white = last + 1;
    const Track PIVOT = songs[first + (last - first) / 2];
    while (red < white - 1)
    {
        const int NEXT = white - 1;
        if (songs[NEXT] < PIVOT)
        {
            red++;
            swap (songs, red, NEXT);
        }
        else if (songs[NEXT] == PIVOT)
            white--;
        else
        {
            white--;
            blue--;
            swap (songs, NEXT, blue);
        }
    }
}

void dnf_adjusted (vector<Track>& songs, int first, int last, int& red, int& blue)
{
//               
    assert (first >= 0 && last >= 0 && first < songs.size() && last < songs.size());
//                
//                                                                                       

    red = first - 1;
    blue = last + 1;
    int white = first - 1;
    const Track PIVOT = songs[first + (last - first) / 2];
    while (white < blue - 1)
    {
        const int NEXT = white + 1;
        if (songs[NEXT] > PIVOT)
        {
            blue--;
            swap (songs, blue, NEXT);
        }
        else if (songs[NEXT] == PIVOT)
            white++;
        else
        {
            white++;
            red++;
            swap (songs, NEXT, red);
        }
    }
}

void quicksort (vector<Track>& songs, int first, int last)
{
//               
    assert (0 <= first && last < size(songs));
//                
//                                      

    if (first >= last)
        return ;
    else
    {
        int red;
        int blue;
        dnf_adjusted(songs, first, last, red, blue);
        quicksort (songs, first, red);
        quicksort (songs, blue, last);
    }
}

/*
                                                
 
                    
                      
     
                                
                                  
                                 
            
                                 
                      
     

                            
     
                                     
                                     
                  
         
                             
         
            
         
                              
                           
         
     
                    
 

                                    
 
                 
     
                                               
                              
                  
     
 
*/

int main()
{
	const int NO_OF_SONGS = read_file ("Tracks.txt");
	if (NO_OF_SONGS < 0)
	{
        cout << "Reading file failed. Program terminates." << endl;
	    return NO_OF_SONGS;
    }
    int first = 0;
    int last = size(songs) - 1;
    quicksort(songs, first, last);
    show_all_tracks(songs, NO_OF_SONGS);
}

