//                      
//                     

#define NDEBUG
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>
#include <algorithm>

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

const int MAX_NO_OF_SONGS = 6000;           //                                
vector<Track> songs;                        //                                     

typedef int Numbers;
vector<Numbers> v = {7, 5, 16, 8};

bool operator<(const Track& a, const Track& b)
{
/*                          
                    
                            
                     
                    
                    
                    
                     
                                    */      //                                                     

    if (a.time.minutes < b.time.minutes)
        return true;
    else if (a.time.minutes == b.time.minutes && a.time.seconds < b.time.seconds)
        return true;
    else
        return false;                       //                      
}

bool operator==(const Track& a, const Track& b)
{
    return (a.artist == b.artist &&
    a.cd == b.cd &&
    a.year == b.year &&
    a.track_no == b.track_no)
    ;
}

bool operator<(const Length& a, const Length& b)
{
    if (a.minutes == b.minutes)
        return a.seconds < b.seconds;
    else return a.minutes < b.minutes;
}

bool operator==(const Length& a, const Length& b)
{
    return a.minutes == b.minutes &&
    a.seconds == b.seconds;
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
            songs.push_back(song);
            no_of_read_songs++;
    }
    while (infile && no_of_read_songs < MAX_NO_OF_SONGS);
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
	cout << "Read " << NO_OF_SONGS << " tracks." << endl;
	return NO_OF_SONGS;
}

void show_all_tracks (vector<Track>& songs, int no_of_songs)
{//               
    assert (no_of_songs < MAX_NO_OF_SONGS) ;
/*                 
                                                                  
*/
    for (int i = 1 ; i < no_of_songs; i++)
        cout << i << ". " << songs[i] << endl ;
}

void dnf (vector<Track>& data, int first, int last, int& red, int& blue) {
    assert (data.size() >= 0);
    //                                                          
    red = first - 1;
    blue = last + 1;
    int white = last + 1;
    const Track PIVOT = data [first+(last-first)/2];
    while (red < white - 1)
    {
        const int NEXT = white - 1;
        if (data[NEXT] < PIVOT) {
            red++;
            swap(data[red], data[NEXT]);
        }
        else if (data[NEXT] == PIVOT)
            white--;
        else {
            white--;
            blue--;
            swap(data[NEXT], data[blue]);
        }
    }
}

void dnf2 (vector<Track>& data, int first, int last, int& red, int& blue) {
    assert (data.size() >= 0);
    //                                                                                                             
    red = first - 1;
    blue = last + 1;
    int white = first - 1;
    const Track PIVOT = data [first+(last-first)/2];
    while (blue > white + 1)
    {
        const int NEXT = white + 1;
        if (data[NEXT] > PIVOT) {
            blue--;
            swap(data[blue], data[NEXT]);
        }
        else if (data[NEXT] == PIVOT)
            white++;
        else {
            white++;
            red++;
            swap(data[NEXT], data[red]);
        }
    }
}

void quicksort(vector<Track>& data, int first, int last){
    assert (data.size() >= 0);
    //                                 
    if (first >= last)
        return;
    else {
        int red;
        int blue;
        dnf2 (data, first, last, red, blue);
        quicksort (data, first, red);
        quicksort (data, blue, last);
    }
}

int largest (vector<Numbers>& v, int low, int up) {
    typedef int A;
    vector<A> stack;
    int largest_value = low;
    while (low < up) {
        stack.push_back(low);
        low++;
    }
    while (stack.size() > 0) {
        low = stack.size() - 1;
        if (v[low] > v[largest_value]) {
            largest_value = low;
        }
        stack.pop_back();
    }
    return largest_value;
}

void sort (vector<Numbers>& v, int n) {
    while (n > 1) {
        n--;
        const int POS = largest (v, 0, n);
        swap (v[POS], v[n]);
    }
}

int main (){
    const int NO_OF_SONGS = read_file ("Tracks.txt");
	if (NO_OF_SONGS < 0)
	{
        cout << "Reading file failed. Program terminates." << endl;
	    return NO_OF_SONGS;
	}
	cout << songs.size();
    quicksort (songs, 0, songs.size() - 1);
    cout << " Tracks sorted." << endl;
    show_all_tracks (songs,NO_OF_SONGS) ;
    sort (v, v.size());
    for (int i = 0; i < v.size(); i++){
        cout << v[i] << endl;
    }
	return 0;
}

