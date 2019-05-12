#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>
#include <algorithm>

//                         
//                    
using namespace std;

int counter;
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

int size(vector<Track>& songs)
{
    return static_cast<int>(songs.size());
}

bool operator<(const Length a, const Length b)
{
    if(a.minutes==b.minutes)
    {
        return a.seconds<b.seconds;
    }
    return a.minutes<b.minutes;
}

bool operator>=(const Length& a, const Length& b)
{
    return !(b<a);
}

bool operator==(const Length a, const Length b)
{
    if(a.minutes==b.minutes&&a.seconds==b.seconds)
        return true;
    return false;
}

bool operator<(const Track& a, const Track& b) //                        
{
    counter++;
    if(a.time==b.time)
        if(a.artist==b.artist)
            if(a.title==b.title)
                return a.cd<b.cd;
            else
                return a.title<b.title;
        else
            return a.artist<b.artist;
    else
        return a.time<b.time;
    return false;
}

bool operator==(const Track& a, const Track& b)
{
    counter++;
    if(a.artist==b.artist&&a.cd==b.cd&&a.title==b.title&&a.time==b.time)
                return true ;
    return false;
}

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

int read_file(string filename)
{
    assert(true);
    ifstream infile;
    infile.open(filename);
    while(infile)
    {
        Track song;
        infile >> song;
        songs.push_back(song);
        if(song.artist == "")
            songs.pop_back();
    }
    infile.close();
    return size(songs);
}

//                                                                           
void show_all_tracks (vector<Track>& songs)
{//               
    assert (true) ;
/*                 
                                                                  
*/
    for (int i = 0 ; i < size(songs); i++)
        cout << songs[i] << endl ;
}

void swap (vector<Track>& songs, int  i, int  j )
{//	              
	assert ( i >= 0 && j >= 0 ) ;	//                         
						            //                         
//                                                                
	const Track HELP = songs [i];
	songs [i] = songs [j] ;
	songs [j] = HELP;
}

void dnf(vector<Track>& songs, int first, int last, int& red, int& blue)
{
    assert(0 <= first && last < size(songs));
    //                                               
    red = first -1;
    blue = last+1;
    int white = first-1;
    const Track PIVOT = songs[first+((last-first)/2)];
    //              
    while(red < white - 1)
    {
        const int NEXT = white +1 ;
        if(songs[NEXT]<PIVOT)
        {
            white++;
            red++;
            swap(songs, red, NEXT);
        }
        else if(songs[NEXT]==PIVOT)
        {
            white++;
        }
        else
        {
            blue--;
            swap(songs, NEXT, blue);
        }
    }
}

void quicksort(vector<Track>& songs, int first, int last)
{
    assert(0 <= first && last < size(songs));
    //                                         
    if(first >= last)
        return;
    else
    {
        //                                    
        int red;
        int blue;
        dnf(songs, first,last, red, blue);
        quicksort(songs, first, red);
        quicksort(songs, blue, last);
    }
}

int largest(vector<Track>& songs, int low, int up)
{
    assert(0<=low && up < size(songs));
    //                                                       
    int current = up;
    while(low < up)
    {
        if(songs[low]>songs[current])
            current = low;
        low++;
    }
    return current;
}

void sort(vector<Track>& songs)
{
    int n = size(songs);
    while(n > 1)
    {
        int POS = largest(songs, 0, n-1);
        swap(songs, POS, n-1);
        n--;
    }
}

int main()
{
    const int NUMBER_OF_SONGS= read_file("Tracks.txt");
    //                                       
    sort(songs);
    show_all_tracks(songs);
    return 0;
}

