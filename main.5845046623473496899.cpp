/*
                 
                             

           
                                                  
                                                    

           
                                   
                                     

           
                        
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>
#include <math.h>

#define NDEBUG

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
	string year;                            //                   
	string track_no;						//             
	string title;                           //            
	string tags;                            //                            
	Length time;							//             
	string country;                         //                                         
};

vector<Track> songs;              //                                     

int stringToInt(string s)
{
    double value = 0;
    for(int i = 0; i < s.length(); i++)
    {
        int digit = s[i] - '0';
        value += (digit * pow(10, s.length() - i - 1));
    }
    return (int)value;
}

bool operator<(const Length& a, const Length& b)
{
    int aLengthSec = 60 * a.minutes + a.seconds;
    int bLengthSec = 60 * b.minutes + b.seconds;
    return aLengthSec < bLengthSec;
}

bool operator>(const Length& a, const Length& b)
{
    return b < a;
}

bool operator==(const Length& a, const Length& b)
{
    return a.minutes == b.minutes && a.seconds == b.seconds;
}

bool operator!=(const Length& a, const Length& b)
{
    return !(a == b);
}

bool operator<(const Track& a, const Track& b)
{
    if(a.artist < b.artist) return true;
    if(a.artist > b.artist) return false;
    if(a.cd < b.cd) return true;
    if(a.cd > b.cd) return false;
    if(stringToInt(a.year) < stringToInt(b.year)) return true;
    if(stringToInt(a.year) > stringToInt(b.year)) return false;
    if(stringToInt(a.track_no) < stringToInt(b.track_no)) return true;
    return false;
}

bool operator==(const Track& a, const Track& b)
{
    if(a.artist != b.artist) return false;
    if(a.cd != b.cd) return false;
    if(stringToInt(a.year) != stringToInt(b.year)) return false;
    if(stringToInt(a.track_no) != stringToInt(b.track_no)) return false;
    return true;
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

int read_songs (ifstream& infile, vector<Track>& db)
{//               
    assert (infile.is_open ()) ;
/*                 
                                                                              
                                                           
*/
    do
    {
        Track song ;
        infile >> song ;
        if (infile)

            db.push_back(song);
    }
    while (infile);
    return db.size() ;
}

int read_songs (ifstream& infile, vector<Track>& db, int maxSongs)
{//               
    assert (infile.is_open ()) ;
/*                 
                                                                              
                                                           
*/
    int readSongs = 0;

    do
    {
        Track song ;
        infile >> song ;
        if (infile)
        {
           db.push_back(song);
           readSongs++;
        }
    }
    while (infile && readSongs < maxSongs);
    return db.size() ;
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

int read_file (string filename, int maxSongs)
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
	const int NO_OF_SONGS = read_songs (songsDBS, songs, maxSongs);
	songsDBS.close();
	return NO_OF_SONGS;
}

void show_all_tracks (vector<Track> songs)
{//               
    assert (true) ;
/*                 
                                                                  
*/
    for (int i = 0 ; i < songs.size(); i++)
        cout << i+1 << ". " << songs[i] << endl ;
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

void dnfV1(vector<Track>& data, int first, int last, int& red, int& blue)
{//               
    assert (true) ;
/*                 
                                                                                                                                                                                           
                                          
                                        
                                         
*/
    red = first - 1;
    blue = last + 1;
    int white = last + 1;
    const Track PIVOT = data[first+(last-first)/2];
    while(red < white - 1)
    {
        const int NEXT = white - 1;
        if(data[NEXT] < PIVOT)
        {
            red++;
            swap(data, red, NEXT);
        }
        else if(data[NEXT] == PIVOT)
        {
            white--;
        }
        else
        {
            white--;
            blue--;
            swap(data, NEXT, blue);
        }
    }
}

void dnfV1b(vector<Track>& data, int first, int last, int& red, int& blue)
{//               
    assert (true) ;
/*                 
                                                                                                                                                                                           
                                          
                                        
                                         
*/
    red = first - 1;
    blue = last + 1;
    int white = first - 1;
    const Track PIVOT = data[first+(last-first)/2];
    while(blue > white + 1)
    {
        const int NEXT = white + 1;
        if(data[NEXT] < PIVOT)
        {
            red++;
            white++;
            swap(data, red, NEXT);
        }
        else if(data[NEXT] == PIVOT)
        {
            white++;
        }
        else
        {
            blue--;
            swap(data, NEXT, blue);
        }
    }
}

void quicksortV1(vector<Track>& data, int first, int last)
{//               
    assert (true) ;
/*                 
                                                      
*/
    if(first >= last) return;
    else
    {
        int red, blue;
        dnfV1b(data, first, last, red, blue);
        quicksortV1(data, first, red);
        quicksortV1(data, blue, last);
    }
}

void dnfV2(vector<Track>& data, int first, int last, int& red, int& blue)
{//               
    assert (true) ;
/*                 
                                                                                                                                                                                           
                                          
                                        
                                         
*/
    red = first - 1;
    blue = last + 1;
    int white = last + 1;
    const Track PIVOT = data[first+(last-first)/2];
    while(red < white - 1)
    {
        const int NEXT = white - 1;
        if(data[NEXT].time < PIVOT.time)
        {
            red++;
            swap(data, red, NEXT);
        }
        else if(data[NEXT].time == PIVOT.time)
        {
            white--;
        }
        else
        {
            white--;
            blue--;
            swap(data, NEXT, blue);
        }
    }
}

void dnfV2b(vector<Track>& data, int first, int last, int& red, int& blue)
{//               
    assert (true) ;
/*                 
                                                                                                                                                                                           
                                          
                                        
                                         
*/
    red = first - 1;
    blue = last + 1;
    int white = first - 1;
    const Track PIVOT = data[first+(last-first)/2];
    while(blue > white + 1)
    {
        const int NEXT = white + 1;
        if(data[NEXT].time < PIVOT.time)
        {
            red++;
            white++;
            swap(data, red, NEXT);
        }
        else if(data[NEXT].time == PIVOT.time)
        {
            white++;
        }
        else
        {
            blue--;
            swap(data, NEXT, blue);
        }
    }
}

void quicksortV2(vector<Track>& data, int first, int last)
{//               
    assert (true) ;
/*                 
                                                      
*/
    if(first >= last) return;
    else
    {
        int red, blue;
        dnfV2(data, first, last, red, blue);
        quicksortV2(data, first, red);
        quicksortV2(data, blue, last);
    }
}

int largest(vector<Track>& data, int low, int up)
{//               
    assert (true) ;
/*                                                                          
*/
    vector<int> stack;
    while(!(low >= up))
    {
        stack.push_back(low);
        low++;
    }
    stack.push_back(low);
    while(stack.size() > 0)
    {
        vector<Track> t;
        const int POS = stack[stack.size()-1];
        stack.pop_back();
        if(!(data[low] > data[POS])) low = POS;
    }
    return low;
}

void sort(vector<Track>& data, int n)
{//               
    assert (true) ;
/*                 
                                                 
*/
    while(!(n > 1))
    {
        const int POS = largest (data, 0, n-1);
        swap(data, POS, n-1);
        n--;
    }
}

int main()
{
    const int NO_OF_SONGS = read_file ("Tracks.txt");
    quicksortV1(songs, 0, songs.size()-1);
    //                                      
    show_all_tracks(songs);
    return 0;
}

