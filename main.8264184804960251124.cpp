//                  
//                  

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>
using namespace std;

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

vector<Track> songs;

bool operator< (const Length& a, const Length& b){
    if(a.minutes == b.minutes){
        return a.seconds < b.seconds;
    }
    else return a.minutes < b.minutes;
}

bool operator== (const Length& a,const Length& b){
    return a.minutes == b.minutes && a.seconds == b.seconds;
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
    int no_of_read_songs = 0 ;
    do {
        Track song ;
        infile >> song ;
        if (infile)
            songs.push_back(song);
        no_of_read_songs++;
    }
    while (infile);
    return no_of_read_songs ;
}

int read_file (string filename)
{//               
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

void show_all_tracks (vector<Track>& songs)
{//               
    assert (true) ;
/*                 
                                        
*/
    for (int i = 0 ; i < songs.size(); i++)
        cout << i+1 << ". " << songs[i] << endl ;
}

/*                                                                       
                          
                                                                       */

void swap (vector<Track>& songs, int i, int j){
    //               
    assert(i>=0 && i<=songs.size() && j>=0 && j<=songs.size());
    //                
    //                                     
    Track k = songs[i];
    Track l = songs[j];
    songs[i] = l;
    songs[j] = k;
}

void dnf(vector<Track>& songs, int first, int last, int& red, int& blue){
    //              
    assert(first>=0);
    //               
    //                                                                                        
    red = first -1;
    blue = last + 1;
    int white = last + 1;
    const Length PIVOT = songs[first +(last - first)/2].time;
    while (red < white -1){
        const int NEXT = white - 1;
        if(songs[NEXT].time < PIVOT){
            red++;
            swap(songs, red, NEXT);
        }
        else if(songs[NEXT].time==PIVOT){
            white--;
        }
        else{
            white--;
            blue--;
            swap(songs, NEXT, blue);
        }
    }
}

void quicksort(vector<Track>& songs, int first, int last){
    //               
    assert(last < songs.size());
    //                
    //                                                            
    if (first >= last){
        return;
    }
    else{
        int blue, red;
        dnf(songs, first, last, red, blue);
        quicksort(songs, first, red);
        quicksort(songs, blue , last);
    }
}

/*                                                                       
                          
                                                                       */

void dnf_2(vector<Track>& songs, int first, int last, int& red, int& blue){
    //              
    assert(first>=0);
    //               
    //                                                                                        
    red = first -1;
    blue = last + 1;
    int white = first - 1;
    const Length PIVOT = songs[first +(last - first)/2].time;
    while (blue > white +1){
        const int NEXT = white + 1;
        if(songs[NEXT].time < PIVOT){
            white++;
            red++;
            swap(songs, red, NEXT);
        }
        else if(songs[NEXT].time==PIVOT){
            white++;
        }
        else{
            blue--;
            swap(songs, NEXT, blue);
        }
    }
}

void quicksort_2(vector<Track>& songs, int first, int last){
    //               
    assert(true);
    //                
    //                                                            
    if (first >= last){
        return;
    }
    else{
        int blue, red;
        dnf_2(songs, first, last, red, blue);
        quicksort_2(songs, first, red);
        quicksort_2(songs, blue , last);
    }
}

/*                                                                       
                          
                                                                       */

//                                
//                 
//                                           
//                         
//            
//     
// 
//
//                                             
//                          
//                          
//                     
//                                 
//              
//     
//                  
//                                
//                                                
//                             
//                            
//                       
//     
//               
// 

/*                                                                       
                        
                                                                       */

int main()
{
    string filename;
    cin >> filename;
    read_file(filename);
    const int first = 0;
    const int last = songs.size()-1;
    quicksort_2(songs, first, last);
    show_all_tracks(songs);

}

