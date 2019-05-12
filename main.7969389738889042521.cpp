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
//                                                  

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

int size(vector<Track> data)
{
    return static_cast<int>(data.size());
}

vector<Track> songs;
int counter;

/*                                                                       
                                
                                                               
                                                                         
                                                                       */
bool operator<(const Length& a, const Length& b)
{
    if (a.minutes > b.minutes)
        return false;
    else if (a.minutes < b.minutes)
        return true;
    else
        return a.seconds < b.seconds;
}

bool operator>(const Length& a, const Length& b) {
    return b < a;
}

//     
bool operator<(const Track& a, const Track& b)
{
    counter++;
    if (a.artist > b.artist)
        return false;
    else if (a.artist < b.artist)
        return true;
    else if (a.cd < b.cd)
        return false;
    else if (a.cd > b.cd)
        return true;
    else if (a.year > b.year)
        return false;
    else if (a.year < b.year)
        return true;
    else
        return a.track_no < b.track_no;
}

/*
        
                                              
 
              
                        
                     
                             
                    
                                 
                     
                                 
                    
                               
                     
                               
                    
        
                           
 
*/

bool operator==(const Length& a, const Length& b)
{
    return a.minutes == b.minutes && a.seconds == b.seconds;
}

//     
bool operator==(const Track& a, const Track& b)
{
    counter++;
    return a.artist == b.artist && a.cd == b.cd && a.year == b.year && a.track_no == b.track_no;
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

int read_songs (ifstream& infile, vector<Track>& songs)
{//               
    assert (infile.is_open ()) ;
/*                 
                                                                              
                                                           
*/
    do {
        Track song ;
        infile >> song ;
        if (infile)
            songs.push_back(song);
    }
    while (infile);
    return songs.size();
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

void show_all_tracks(vector<Track>& songs)
{//               
    assert (true) ;
/*                 
                                                                   
*/
    for (int i = 0 ; i < songs.size(); i++)
        cout << i+1 << ". " << songs[i] << endl;
}

void swap (vector<Track>& data, int i, int j)
{//	              
	assert (i >= 0 && j >= 0 && i < data.size() && j < data.size());
//                                                                
	const Track HELP = data[i];
	data[i] = data[j] ;
	data[j] = HELP;
}

void dnf_adjusted(vector<Track>& data, int first, int last, int& red, int& blue)
{
    //             
    assert(first >= 0 && last < data.size());
    /*              
                                                                                                                      
                                                                          
                                                               
                                                                          
    */

    red = first - 1;
    blue = last + 1;
    int white = first - 1;

    const Track PIVOT = data[first + (last - first) / 2];
    while (white < blue - 1) {
        const int NEXT = white + 1;
        if (data[NEXT] < PIVOT) {
            red++;
            white++;
            swap(data, red, NEXT);
        } else if (data[NEXT] == PIVOT)
            white++;
        else {
            blue--;
            swap(data, NEXT, blue);
        }

    }
}

void quicksort_adjusted(vector<Track>& data, int first, int last)
{
    //             
    assert(first >= 0 && last < size(data));
    /*              
                                        
    */

    if (first >= last)
        return;

    int red, blue;
    dnf_adjusted(data, first, last, red, blue);
    quicksort_adjusted(data, first, red);
    quicksort_adjusted(data, blue, last);
}

void dnf(vector<Track>& data, int first, int last, int& red, int& blue)
{
    //             
    assert(first >= 0 && last < data.size());
    /*              
                                                                                                                      
                                                                          
                                                               
                                                                          
    */

    red = first - 1;
    blue = last + 1;
    int white = last + 1;

    const Track PIVOT = data[first + (last - first) / 2];
    while (red < white - 1) {
        const int NEXT = white - 1;
        if (data[NEXT] < PIVOT) {
            red++;
            swap(data, red, NEXT);
        } else if (data[NEXT] == PIVOT)
            white--;
        else {
            white--;
            blue--;
            swap(data, NEXT, blue);
        }

    }
}

void quicksort(vector<Track>& data, int first, int last)
{
    //             
    assert(first >= 0 && last < size(data));
    /*              
                                        
    */

    if (first >= last)
        return;

    int red, blue;
    dnf(data, first, last, red, blue);
    quicksort(data, first, red);
    quicksort(data, blue, last);
}

int largest(vector<Track>& v, int low, int up)
{
    int pos = low;
    vector<int> stack;
    while (low < up) {
        stack.push_back(low);
        low++;
    }

    int pos = low;

    while (stack.size() > 0) {
        low = stack[stack.size() - 1];
        stack.pop_back();
        if (v[low] > v[pos])
            pos = low;
    }

    return pos;
}

void sort(vector<Track>& v, int n)
{
    while (n > 1) {
        const int POS = largest(v, 0, n - 1);
        swap(v, POS, n - 1);
        n--;
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
    quicksort_adjusted(songs, 0, songs.size() - 1);
    cout << "Tracks sorted." << endl;
    show_all_tracks (songs);
	return 0;
}

