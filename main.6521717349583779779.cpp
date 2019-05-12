#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#define NDEBUG
#include <cassert>

//                             
//                        

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

const int MAX_NO_OF_SONGS = 5891;           //                                
vector<Track> songs (MAX_NO_OF_SONGS);              //                                     

bool operator<(const Track& a, const Track& b)
{
    //                           
    if(a.artist == b.artist){
        if(a.year == b.year){
            if(a.cd == b.cd){
                return a.track_no < b.track_no ;
            }
        }
    }
    return false;   /*                                                 */
}

bool operator<(const Length& a, const Length& b)
{
    //                                                                                    
    return (a.minutes * 60) + a.seconds < (b.minutes * 60) + b.seconds;
}

bool operator==(const Track& a, const Track& b)
{
    if(a.artist == b.artist){
        if(a.year == b.year){
            if(a.cd == b.cd){
                return a.track_no == b.track_no ;
            }
        }
    }
    return false;    /*                                                 */
}

bool operator==(const Length& a, const Length& b)
{
    //                                                                                    
    return (a.minutes * 60) + a.seconds == (b.minutes * 60) + b.seconds;
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
{
    //               
    assert (true) ;
    /*                 
                                                                                                          
    */
    char colon ;
    in >> length.minutes >> colon >> length.seconds ;
    return in ;
}

ostream& operator<< (ostream& out, const Length length)
{
    //               
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
{
    //               
    assert (true) ;
    /*                 
                                                                            
    */
    string remains ;
    getline (infile, remains) ;
}

istream& operator>> (istream& infile, Track& track)
{
    //               
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
{
    //               
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

//                                                                           
int read_songs (ifstream& infile, vector<Track>& songs)
{
    //               
    assert (infile.is_open ()) ;
    /*                 
                                                                                  
                                                               
    */
    int no_of_read_songs = 0 ;
    do
    {
        Track song ;
        infile >> song ;
        if (infile)
            songs[no_of_read_songs++] = song ;
    }
    while (infile && no_of_read_songs < MAX_NO_OF_SONGS);
    return no_of_read_songs ;
}

int read_file (string filename)
{
    //               
    assert (true) ;
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

//                                                                           
void show_all_tracks (vector<Track> songs, int no_of_songs)
{
    //               
 //                                           
    /*                 
                                                                      
    */
    for (int i = 0 ; i < no_of_songs; i++)
        cout << i+1 << ". " << songs[i] << endl ;
}

void swap (vector<Track>& data, int  i, int  j )
{
    //	              
    assert ( i >= 0 && j >= 0 ) ;	//                         
    //                         
//                                                                
    const Track HELP = data [i];
    data [i] = data [j] ;
    data [j] = HELP;
}

int track_length(Track track)
{
    //              
    assert(true);
    //              
    //                                                          
    return(track.time.minutes*60)+track.time.seconds;
}

void dnf (vector<Track>& tracks, int first, int last, int& red, int& blue, bool time)
{

    //             
    assert(first>=0 && last>=0);
    /*               
                                                           
    */
    red = first - 1;
    blue = last + 1;
    int white = first - 1;
    const int pivot = time ? track_length(tracks[first+(last-first)/2]) : tracks[first+(last-first)/2].track_no;

    while(white<blue-1)
    {
        const int next = white + 1;
        if((!time && tracks[next].track_no<pivot) || (time && track_length(tracks[next])<pivot))
        {
            red++;
            swap(tracks, red, next);
            white++;
        }
        else if((!time && tracks[next].track_no==pivot) || (time && track_length(tracks[next])==pivot)){
            white++;
        }
        else
        {
            blue--;
            swap(tracks, blue, next);
        }
    }
}

void quicksort (vector<Track>& tracks, int first, int last, bool time)
{
    //             
    assert(first>=0 && last>=0);
    /*
                  
                                                                                   
    */
    if(first >= last)
        return;
    else{
        int red;
        int blue;
        dnf(tracks, first, last, red, blue, time);
        quicksort(tracks, first, red, time);
        quicksort(tracks, blue, last, time);
    }
}

void sort_albums(vector<vector<Track>>& albumList, vector<Track>& songs){
    //             
    assert(true);
    //              
    //                                              
    vector<Track> currentAlbum;

    for(int i = 0; i < songs.size(); i++){
        string album = songs[i].cd;

        bool addedToAlbum = false;

        for(int j = 0; j < albumList.size(); j++){
            if(albumList[j][0].cd == album){
                addedToAlbum = true;
                albumList[j].push_back(songs[i]);
            }
        }

        if(!addedToAlbum){
            vector<Track> newAlbum;
            newAlbum.push_back(songs[i]);
            albumList.push_back(newAlbum);
        }
    }
}

void show_albums_sorted(int NO_OF_SONGS)
{
    //            
    assert(NO_OF_SONGS>=0);
    //             
    //                                                                 
    vector<vector<Track>> albumList;
    sort_albums(albumList, songs);

    for(int i = 0; i < albumList.size(); i++){
        quicksort(albumList[i], 0, albumList[i].size() - 1, false);
    }

    songs.clear();

    for(int i = 0; i < albumList.size(); i++){
        for(int j = 0; j < albumList[i].size(); j++){
            songs.push_back(albumList[i][j]);
        }
    }
    show_all_tracks (songs, NO_OF_SONGS) ;
}

void swap_int (vector<int>& data, int  i, int  j )
{
    //	              
    assert ( i >= 0 && j >= 0 ) ;	//                         
    //                         
//                                                                
    const int HELP = data [i];
    data [i] = data [j] ;
    data [j] = HELP;
}

int largest(vector<int>& v, int low, int up)
{
    vector<vector<int>> Stack;
    while(low<up)
    {
        Stack.push_back(v);
        low++;
    }
    while(Stack.size()>0)
    {
        v = Stack[Stack.size()-1];
        Stack.pop_back();
    }
    return low;
}

void sort(vector<int>& v, int n)
{
    while(n>1)
    {
        const int POS = largest(v, 0, n-1);
        swap_int(v, POS, n-1);
        n--;
    }
}

int main()
{
    const int NO_OF_SONGS = read_file ("Tracks.txt");
    if (NO_OF_SONGS < 0)
    {
        cout << "Reading file failed. Program terminates." << endl;
        return NO_OF_SONGS;
    }

    //        
    quicksort(songs, 0, songs.size()-1, true);
    show_all_tracks(songs, NO_OF_SONGS);

    //                                                                                                  
    //                                

    return 0;
}

