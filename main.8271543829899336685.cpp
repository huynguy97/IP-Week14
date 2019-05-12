/*
                              
                          
                            
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>

using namespace std;

struct Length {
    int minutes;                            //               
    int seconds;                            //                 
};

struct Track {
    string artist;                          //            
    string cd;                              //         
    int year;                            //                   
    int track_no;                        //             
    string title;                           //            
    string tags;                            //                            
    Length time;                            //             
    string country;                         //                                         
};

struct Slice {
    int first;
    int last;
};

vector<Track> songs;

const int MAX_NO_OF_SONGS = 6000;

bool operator<(const Length& a, const Length& b) {
    return a.minutes < b.minutes || (a.minutes == b.minutes && a.seconds < b.seconds);
}

bool operator>(const Length& a, const Length& b) {
    return b < a;
}

bool operator==(const Length& a, const Length& b) {
    return a.minutes == b.minutes && a.seconds == b.seconds;
}

bool operator<(const Track& a, const Track& b) {
    //                                                                                                   
    //                                                                        

    return a.time < b.time;

    /*                        
                    
                            
                     

                    
                    
                    
                     

                                   */
}

bool operator==(const Track& a, const Track& b) {
    //                                                                        
    return a.time == b.time;
}

//	                                 
bool operator>(const Track& a, const Track& b) {
    return b < a;
}

bool operator<=(const Track& a, const Track& b) {
    return !(b < a);
}

bool operator>=(const Track& a, const Track& b) {
    return b <= a;
}

/*                                                                                       
            
                                                                                         */
istream& operator>>(istream& in, Length& length) {//               
    assert (true);
/*                 
                                                                                                      
*/
    char colon;
    in >> length.minutes >> colon >> length.seconds;
    return in;
}

ostream& operator<<(ostream& out, const Length length) {//               
    assert (true);
/*                 
                                                                       
*/
    out << length.minutes << ':';
    if (length.seconds < 10)
        out << '0';
    out << length.seconds;
    return out;
}

void skip_to_next_newline(istream& infile) {//               
    assert (true);
/*                 
                                                                        
*/
    string remains;
    getline(infile, remains);
}

istream& operator>>(istream& infile, Track& track) {//               
    assert (true);
/*                 
                                                                                                                   
                                      
*/
    getline(infile, track.artist);       //       
    getline(infile, track.cd);           //   
    infile >> track.year;              //     
    skip_to_next_newline(infile);
    infile >> track.track_no;          //             
    skip_to_next_newline(infile);
    getline(infile, track.title);        //            
    getline(infile, track.tags);         //           
    infile >> track.time;              //           
    skip_to_next_newline(infile);
    getline(infile, track.country);      //        
    skip_to_next_newline(infile);
    return infile;
}

//                                                                                                        
ostream& operator<<(ostream& out, const Track track) {//               
    assert (true);
/*                 
                                                                                
*/
    out << track.artist << endl;
    out << track.cd << endl;
    out << track.year << endl;
    out << track.track_no << endl;
    out << track.title << endl;
    out << track.tags << endl;
    out << track.time << endl;
    out << track.country << endl;
    out << endl;
    return out;
}

//                                                                           
int read_songs(ifstream& infile, vector<Track>& songs) {//               
    assert (infile.is_open());
/*                 
                                                                              
                                                           
*/
    int no_of_read_songs = 0;
    do {
        Track song;
        infile >> song;
        if (infile) {
            songs.push_back(song);
            ++no_of_read_songs;
        }
    } while (infile && no_of_read_songs < MAX_NO_OF_SONGS);
    return no_of_read_songs;
}

int read_file(string filename) {//               
    assert (songs.size() == 0);
/*                 
                                                                              
                                                                                             
                                        
*/
    ifstream songsDBS(filename.c_str());
    if (!songsDBS) {
        cout << "Could not open '" << filename << "'." << endl;
        return -1;
    }
    cout << "Reading '" << filename << "'." << endl;
    const int NO_OF_SONGS = read_songs(songsDBS, songs);
    songsDBS.close();
    cout << " Read " << NO_OF_SONGS << " tracks." << endl;
    return NO_OF_SONGS;
}

//                                                                           
void show_all_tracks(vector<Track>& songs, int no_of_songs) {//               
    assert (no_of_songs < MAX_NO_OF_SONGS);
/*                 
                                                                  
*/
    for (int i = 0; i < no_of_songs; i++)
        cout << i + 1 << ": " << songs[i].track_no << " " << songs[i].time << endl;
}

/*                                                                                                                     
                 
                                                                                                                      */

void swap(vector<Track>& songs, int a, int b) {
    //               
    assert(a >= 0 && a < songs.size());
    assert(b >= 0 && b < songs.size());
    //                
    //                                             

    Track c = songs[a];
    songs[a] = songs[b];
    songs[b] = c;
}

void dnf(vector<Track>& songs, int& red, int& blue, int first, int last) {
    //               
    assert(0 <= first && last < songs.size());
    //                
    //                              
    //                                                                          

    red = first - 1;
    int white = last + 1;
    blue = last + 1;

    const Track pivot = songs[first + (last - first) / 2];
    while (red < white - 1) {
        const int next = white - 1;
        if (songs[next] < pivot) {
            red++;
            swap(songs, red, next);
        } else if (songs[next] == pivot) {
            white--;
        } else {
            white--;
            blue--;
            swap(songs, next, blue);
        }
    }
}

void dnf2(vector<Track>& songs, int& red, int& blue, int first, int last) {
    //               
    assert(0 <= first && last < songs.size());
    //                
    //                              
    //                                                                          

    blue = last + 1;
    int white = first - 1;
    red = first - 1;

    const Track pivot = songs[first + (last - first) / 2];
    while (white < blue - 1) {
        const int next = white + 1;
        if (songs[next] > pivot) {
            --blue;
            swap(songs, blue, next);
        } else if (songs[next] == pivot) {
            ++white;
        } else {
            ++white;
            ++red;
            swap(songs, next, red);
        }
    }
}

void quicksort(vector<Track>& songs, int first, int last) {
    //               
    assert(0 <= first && last < songs.size());
    //                
    //                                                                           

    if (first < last) {
        int red, blue;
        dnf(songs, red, blue, first, last);
        quicksort(songs, first, red);
        quicksort(songs, blue, last);
    }
}

void quicksortIT(vector<Track>& songs, int first, int last) {
    //               
    assert(0 <= first && last < songs.size());
    //                
    //                                                                            

    vector<Slice> queue;
    queue.push_back({first, last});

    int red, blue;

    while (!queue.empty()) {
        Slice slice = queue[queue.size() - 1];
        queue.pop_back();

        if (slice.first < slice.last) {
            dnf(songs, red, blue, slice.first, slice.last);
            queue.push_back({slice.first, red});
            queue.push_back({blue, slice.last});
        }
    }
}

int main() {
    string filename = "Tracks.txt";
    read_file(filename);

    //                                      
    quicksortIT(songs, 0, songs.size() - 1);

    show_all_tracks(songs, songs.size());

    return 0;
}

