//                         
//                  

#include <iostream>
#include <cstring>
#include <vector>
#include <string>
#include <assert.h>
#include <fstream>
#include <algorithm>

using namespace std;

struct Length
{
	int minutes;							//               
	int seconds;							//                 
};
struct Music
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
vector <Music> Track;

bool operator<(const Length& a, const Length& b)
{
     if (a.minutes == b.minutes)
        return (a.seconds < b.seconds);
        else return a.minutes < b.minutes;
}

/*                                              
 
                            
 */

bool operator<(const Music& a, const Music& b)
{
     return (a.track_no < b.track_no) && (a.artist == b.artist) && (a.cd == b.cd);
}

bool operator==(const Music& a, const Music& b)
{
    return (a.artist == b.artist) && (a.cd == b.cd);
}

bool operator>(const Length& a, const Length& b)
{
	return (b < a) ;
}

bool operator>=(const Length& a, const Length& b)
{
	return !(b > a) ;
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

istream& operator>> (istream& infile, Music& track)
{//               
    assert (true) ;
/*                 
                                                                                                                   
                                      
*/
    getline(infile, track.artist);       //       
    getline(infile, track.cd);           //   
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

ostream& operator<< (ostream& out, const Music track)
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

void show_all_tracks (vector<Music>& songs, int no_of_songs)
{//               
    assert (no_of_songs < MAX_NO_OF_SONGS) ;
/*                 
                                                                  
*/
    for (int i = 0 ; i < no_of_songs; i++)
        cout << i+1 << ". " << songs[i] << endl ;
}

int read_vec (ifstream& InF, vector <Music>& Track)
{//              
    assert(InF.is_open());
 //               
 //                                                        
    int no_of_read_songs = 0 ;
    do {
        Music song ;
        InF >> song ;
        if (InF)
            Track.push_back(song);
        no_of_read_songs++;
    }
    while (InF && no_of_read_songs < MAX_NO_OF_SONGS);
    return no_of_read_songs;
}

int read_file (string filename)
{//               
    assert (Track.size() == 0) ;
/*                 
                                                                              
                                                                                             
                                        
*/
    ifstream songsDBS (filename.c_str());
    if (!songsDBS)
    {
        cout << "Could not open '" << filename << "'." << endl;
        return -1;
    }
    cout << "Reading '" << filename << "'." << endl;
	const int NO_OF_SONGS = read_vec(songsDBS, Track);
	songsDBS.close();
	cout << " Read " << NO_OF_SONGS << " tracks." << endl;
	return NO_OF_SONGS;
}

void DNF1(vector <Music>& Track, int first, int last, int& red, int& blue)
{//              
    assert( 0<=first && last < Track.size());
 //               
 //                                   
    red = first - 1;
    blue = last + 1;
    int white = first - 1;
    const Music PIVOT = Track[first+(last-first)/2];
    while (red < white+1)
    {
        const int NEXT = white+1;
        if (Track[NEXT].track_no<PIVOT.track_no && Track[NEXT].artist == PIVOT.artist && Track[NEXT].cd == PIVOT.cd)
        {
            red++;
            swap(Track[red], Track[NEXT]);
        }
        else if (Track[NEXT].track_no==PIVOT.track_no && Track[NEXT].artist == PIVOT.artist && Track[NEXT].cd == PIVOT.cd)
        {
            white++;
        }
        else
        {
            blue--;
            swap(Track[NEXT], Track[blue]);
        }
    }
}

void DNF2(vector <Music>& Track, int first, int last, int& red, int& blue)
{//              
    assert( 0<=first && last < Track.size());
 //               
 //                                     
    red = first - 1;
    blue = last + 1;
    int white = last + 1;
    const Music PIVOT = Track[first+(last-first)/2];
    while (red < white-1)
    {
        const int NEXT = white-1;
        if (Track[NEXT].time<PIVOT.time)
        {
            red++;
            swap(Track[red], Track[NEXT]);
        }
        else if (Track[NEXT].time>PIVOT.time)
        {
            blue--;
            white--;
            swap(Track[NEXT], Track[blue]);
        }
        else
        {
            white--;
        }
    }
}

void QuickSort(vector <Music>& Track, int first, int last)
{//              
    assert( 0 <= first && last < Track.size());
 //               
 //                                
    if  (first >= last) return;
    else
    {
        int red, blue;
        DNF2(Track, first, last, red, blue);
        QuickSort(Track, first, red);
        QuickSort(Track, blue, last);
    }
}

void swap (vector <int>& Track, int ele, int next)
{
    //             
    assert(ele >= 0 && next >= 0);
    //              
    //                                
    int temp = Track[ele];
    Track[ele] = Track[next];
    Track[next] = temp;
}

int largest (vector <int>& v, int low, int up)
{//             
    assert (low >= 0 && up >=0);
 //                                       
    vector <int> stack;
    int POS;
    while (low<up)
    {
        while (v[low] <= v[POS])
            const int POS = up-1;
        return low;
    }
    return low;
}

void sortt (vector <int>& v, int n)
{//             
    assert (n >= 0);
 //                                         
    vector <int> stack;
    while (n > 1)
    {
        const int POS = largest(v, 0, n-1);
        swap (v, POS, n-1);
        n--;
    }

}

int main()
{
    string fname;
    ifstream infile;
    const int NO_OF_SONGS = read_file("Tracks.txt");
	if (NO_OF_SONGS < 0)
	{
        cout << "Reading file failed. Program terminates." << endl;
	    return NO_OF_SONGS;
    }
    //                                    
    QuickSort(Track, 0, Track.size()-1);
    show_all_tracks(Track, NO_OF_SONGS);
}

