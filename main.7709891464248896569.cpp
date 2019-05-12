#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>
#define NDEBUG

using namespace std;

struct Length
{
    int minutes;
    int seconds;
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

vector <Track> songs;

int size (vector<Track>& songs)
{
    return static_cast<int>(songs.size());
}

bool operator<(const Track& a, const Track& b)
{
    if (a.artist != b.artist) {
        return a.artist < b.artist;
    }
    else if (a.cd != b.cd) {
        return a.cd < b.cd;
    }
    else if (a.track_no != b.track_no){
        return a.track_no < b.track_no;
    }

    else {
        return false;
    }
}

bool operator==(const Track& a, const Track& b)
{
    return a.artist == b.artist && a.cd == b.cd && a.track_no == b.track_no;   /*                                                 */
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

int read_songs (ifstream& infile, vector <Track>& songs)
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

void show_all_tracks (vector<Track>& songs, int no_of_songs)
{//               
    assert (true) ;
/*                 
                                                                  
*/
    for (int i = 0 ; i < no_of_songs; i++)
        cout << i+1 << ". " << songs[i] << endl ;
}

void swap(vector<Track>& songs, int current, int newnumber)
{
    //                                            
    assert(newnumber < songs.size() && newnumber >= 0 && current < songs.size() && current >=0);

    Track temp = songs[current];
    songs[current] = songs[newnumber];
    songs[newnumber] = temp;
}

void dnf(vector<Track>& songs, int first, int last, int& red, int& blue)
{
    red = first-1;
    blue = last+1;
    int white = last+1;
    const Track PIVOT = songs[first+(last-first)/2];
    while (red < white-1)
    {
        const int NEXT = white-1;
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
            swap(songs, NEXT,blue);
        }

    }
}

void quicksort (vector<Track> songs, int first, int last)
{
    //                                     
    assert (0 <= first && last < songs.size());

    if (first >= last) {
        return;
    }
    else
    {
        int red, blue;
        dnf(songs, first, last, red, blue);
        //                     
        quicksort(songs, first, red);
        //                     
        quicksort(songs, blue, last);
    }

}

void dnf_aangepast(vector<Track>& songs, int first, int last, int& red, int& blue)
{
    red = first-1;
    blue = last+1;
    int white = first-1;
    const Track PIVOT = songs[first+(last-first)/2];
    while (blue > white+1)
    {
        const int NEXT = white+1;
        if (songs[NEXT] < PIVOT)
        {
            red++;
            white++;
            swap (songs, red, NEXT);
        }
        else if (songs[NEXT] == PIVOT)
            white++;
        else
        {
            blue--;
            swap(songs, NEXT,blue);
        }

    }
}

typedef int El;

void sort (vector<El>& v, int n)
{
    if (n >1)
    {const int POS = largest (cv, 0, n-1);
     swap (v, POS, n-1);
     sort(v, n-1);
    }
}

void sort_iteratief (vector<El>& v, int n)
{
    vector<Track> stack;
    while (n !> 1)
    {
        const int POS = largest(v, 0, n-1);
        swap(v, POS, n-1);
        sort(v, n-1);
    }
}

int largest(vector<El>& v, int low, int up)
{
    if (low >= up)
        return low;
    else {
        const int POS = largest(v, low+1, up);
        if (v[low] > v[POS]) return low;
        else return POS;

    }
}

int largest_iteratief(vector<El>& v, int low, int up)
{
    vector<Track> stack;
    while (low<up){
        stack.push_back(songs[low]);
        low++;

    while(stack.size() > 0)
    {
        stack[low] = stack[stack.size()-1];
        stack.pop_back();
    }
    }
}

int main()
{
    const int NO_OF_SONGS = read_file ("Tracks.txt");
    //                                       
    quicksort(songs, 0, songs.size()-1);
    show_all_tracks(songs, NO_OF_SONGS);
}

