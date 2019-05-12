#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>

//                                                       

using namespace std;

bool Time = false;

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
vector<Track> Songs;

bool operator<(const Track& a, const Track& b)
{
    //                       
    assert(true);
    //                                                                                               
    if (Time) {
        if (a.time.minutes < b.time.minutes)
            return true;
        else if (a.time.minutes == b.time.minutes)
            if (a.time.seconds < b.time.seconds)
                return true;
            else
                return false;
        else
            return false;
    }
    else {
        if (a.artist == b.artist)
            if (a.cd == b.cd)
                return a.track_no < b.track_no;
            else
                return a.cd < b.cd;
        else
            return a.artist < b.artist;
    }
}

bool operator==(const Track& a, const Track& b)
{
    //                       
    assert(true);
    //                                                                                               
    if (Time){
        if (a.time.minutes == b.time.minutes)
            return a.time.seconds == b.time.seconds;
    }
    else {
        if (a.artist == b.artist)
            if (a.cd == b.cd)
                return a.track_no == b.track_no;
    }
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

int read_songs (ifstream& infile, vector<Track>& SongList) {//               
    assert (infile.is_open());
/*                 
                                                                              
                                                           
*/
    int no_of_read_songs = 0;
    do {
        Track song;
        infile >> song;
        if (infile) {
            SongList.push_back(song);
            no_of_read_songs++;
        }
    } while (infile && no_of_read_songs < MAX_NO_OF_SONGS);
    return no_of_read_songs;
}

int read_file (string filename) {//               
/*                 
                                                                              
                                                                                             
                                        
*/
    ifstream songsDBS(filename.c_str());
    if (!songsDBS) {
        cout << "Could not open '" << filename << "'." << endl;
        return -1;
    }
    cout << "Reading '" << filename << "'." << endl;
    const int NO_OF_SONGS = read_songs(songsDBS, Songs);
    songsDBS.close();
    cout << " Read " << NO_OF_SONGS << " tracks." << endl;
    return NO_OF_SONGS;
}

void show_all_tracks (vector<Track> SongList)
    {//               
/*                 
                                                                  
*/
    for (Track song: SongList)
        cout << song << endl;
}

void SwapSongs (vector<Track>& SongList, int i, int j){
    //                               
    assert (i < SongList.size() && j < SongList.size());
    //                                        
    Track Temp = SongList[i];
    SongList[i] = SongList[j];
    SongList[j] = Temp;
}

void DNF(vector<Track>& SongList, int First, int Last, int& Red, int& Blue){
    //                                          
    assert(First<=Last);
    //                                                        
    Red = First-1;
    Blue = Last+1;
    int White = First-1;
    const Track PIVOT = SongList[First+(Last-First)/2];
    while (Blue < White+1){
        const int NEXT = White-1;
        if (SongList[NEXT] < PIVOT){
            Blue--;
            SwapSongs(SongList, Blue, NEXT);
        }
        else if (SongList[NEXT] == PIVOT)
            White++;
        else{
            White++; Red++;
            SwapSongs(SongList, NEXT, Red);
        }
    }
}

void QuickSort(vector<Track>& SongList, int From, int To) {
    //                                                         
    assert(true);
    //                                                  
    if (From >= To)
        return;
    else {
        int red, blue;
        DNF(SongList, From, To, red, blue);
        QuickSort(SongList, From, red);
        QuickSort(SongList, blue, To);

    }
}

void swap(vector<int>& V, int pos, int opos){
    //                               
    assert (pos < V.size() && opos < V.size());
    //                                        
    int temp = V[pos];
    V[pos] = V[opos];
    V[opos] = temp;
}

int largest(vector<int>& V, int low, int up){
    //                                           
    assert(low<=up);
    //                               
    int Largest;
    for (int i = low; i < up; i++){
        if (V[i] > V[Largest])
            i = Largest;
    }
    return Largest;
}

void sort(vector<int>& V, int N){
    //                           
    assert(true);
    //                                            
    while (N > 1){
        const int POS = largest(V, 0, N-1);
        swap(V, POS, N-1);
        N -= 1;
    }
}

int main() {
    read_file("Tracks.txt");
    Time = false;
    cout << Songs[0].time.seconds << Songs[0].time.minutes << endl;
    QuickSort(Songs, 0, Songs.size()-1);
    show_all_tracks(Songs);

    return 0;
}

