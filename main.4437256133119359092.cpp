#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>

using namespace std;

//                           
//                           

struct Length {
	int minutes;							//               
	int seconds;							//                 
};
struct Track {
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

bool operator<(const Length& a, const Length& b) {
//              
    assert(true);
/*                
                                              
*/
    if(a.minutes > b.minutes) {
        return false;
    } else if (a.minutes < b.minutes) {
        return true;
    } else {
        return (a.seconds < b.seconds);
    }
}

bool operator==(const Length& a, const Length& b) {
//              
    assert(true);
/*                
                                               
*/
    return (a.minutes == b.minutes && a.seconds == b.seconds);
}

bool operator!=(const Length& a, const Length& b) {
//              
    assert(true);
/*                
                                               
*/
    return (!(a == b));
}

bool operator<(const Track& a, const Track& b) {
//              
    assert(true);
/*                
                                       
*/
    return (a.time < b.time);
}

bool operator==(const Track& a, const Track& b) {
//              
    assert(true);
/*                
                                        
*/
    return (a.time == b.time);
}

//	                                 
bool operator>(const Track& a, const Track& b) {
//              
    assert(true);
/*                
                                       
*/
	return b < a;
}

bool operator<=(const Track& a, const Track& b) {
//              
    assert(true);
/*                
                                        
*/
	return !(b < a);
}

bool operator>=(const Track& a, const Track& b) {
//              
    assert(true);
/*                
                                        
*/
	return b <= a;
}

/*                                                                       
                            
                                                                       */
istream& operator>> (istream& in, Length& length) {
//               
    assert (true) ;
/*                 
                                                                                                      
*/
    char colon ;
    in >> length.minutes >> colon >> length.seconds ;
    return in ;
}

ostream& operator<< (ostream& out, const Length length) {
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

template <typename El>
int size(vector<El> v) {
//              
    assert(true);
/*                
                                                
*/
    return static_cast<int>(v.size());
}

void skip_to_next_newline (istream& infile) {
//               
    assert (true) ;
/*                 
                                                                        
*/
    string remains ;
    getline (infile, remains) ;
}

istream& operator>> (istream& infile, Track& track) {
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
ostream& operator<< (ostream& out, const Track track) {
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
int read_songs (ifstream& infile, vector<Track>& songs) {
//               
    assert (infile.is_open ()) ;
/*                 
                                                                              
                                                           
*/
    int no_of_read_songs = 0 ;
    do {
        Track song ;
        infile >> song ;
        if (infile)
            songs.push_back(song) ;
            no_of_read_songs++ ;
    } while (infile);
    //                                                                                                
    no_of_read_songs--;

    return no_of_read_songs ;
}

int read_file (string filename) {
//               
    assert (size(songs) == 0) ;
/*                 
                                                                              
                                                                                             
                                        
*/
    ifstream songsDBS (filename.c_str());
    if (!songsDBS) {
        cout << "Could not open '" << filename << "'." << endl;
        return -1;
    }
    cout << "Reading '" << filename << "'." << endl;
	const int NO_OF_SONGS = read_songs (songsDBS, songs);
	songsDBS.close();
	cout << " Read " << NO_OF_SONGS << " tracks." << endl;
	return NO_OF_SONGS;
}

void show_all_tracks (vector<Track> songs, int no_of_songs) {
//               
    assert (true) ;
/*                 
                                                                  
*/
    for (int i = 0 ; i < no_of_songs; i++)
        cout << i+1 << ". " << songs[i] << endl ;
}

template <typename El>
void swap(vector<El>& songs, int a, int b) {
    //    
    assert(true);
    //                                   
    const El temp = songs[a];
    songs[a] = songs[b];
    songs[b] = temp;
}
/*      */
void dnf(vector<Track>& songs, int first, int last, int& red, int& blue) {
    //    
    assert(true);
    //                                                                                                                                                  
    red = first - 1;
    blue = last + 1;
    int white = last + 1;
    const Track PIVOT = songs[first+(last-first)/2];
    while (red < white - 1) {
        const int NEXT = white - 1;
        if (songs[NEXT] < PIVOT) {
            red++;
            swap(songs,red,NEXT);
        }
        else if (songs[NEXT] == PIVOT) {
            white--;
        }
        else {
            white--;
            blue--;
            swap(songs,NEXT,blue);
        }        
    }
}

void quicksort(vector<Track>& songs, int first, int last) {
    //    
    assert(first >= 0 && last < size(songs));
    //                                
    if (first >= last) return;
    else {
        int red, blue;
        dnf(songs,first,last,red,blue);
        quicksort(songs,first,red);
        quicksort(songs,blue,last);
    }
}
/*      */
void dnfFLIPPED(vector<Track>& songs, int first, int last, int& red, int& blue) {
    //    
    assert(true);
    //                                                                                                                                                  
    red = first - 1;
    blue = last + 1;
    int white = first + 1;
    const Track PIVOT = songs[first+(last-first)/2];
    while (red < white + 1) {
        const int NEXT = white - 1;
        if (songs[NEXT] < PIVOT) {
            red++;
            swap(songs,red,NEXT);
        }
        else if (songs[NEXT] == PIVOT) {
            white++;
        }
        else {
            white++;
            blue--;
            swap(songs,NEXT,blue);
        }        
    }
}

void quicksortFLIPPED(vector<Track>& songs, int first, int last) {
    //    
    assert(first >= 0 && last < size(songs));
    //                                
    if (first >= last) return;
    else {
        int red, blue;
        dnfFLIPPED(songs,first,last,red,blue);
        quicksortFLIPPED(songs,first,red);
        quicksortFLIPPED(songs,blue,last);
    }
}
/*      */
int largest(vector<int>& v, int low, int up) {
    if(low >= up) return low;
    else {
        const int POS = largest(v, low+1, up);
        if(v[low] > v [POS]) return low;
        else return POS;
    }
}

void sort(vector<int>& v, int n) {
    if(n > 1) {
        const int POS = largest(v, 0, n-1);
        swap(v, POS, n-1);
        sort(v, n-1);
    }
}

int largest_iterative(vector<int>& v, int low, int up) {
    int largest = low;
    for(int i = low; i <= up; i++) {
        if(v[i] > v[largest]) {
            largest = i;
        }
    }
    return largest;
}
void sort_iterative(vector<int>& v, int n) {
    while(n > 1) {
        const int POS = largest_iterative(v, 0, n-1);
        swap(v, POS, n-1);
        n--;
    }
}

int main() {
    //                      
    const int NO_OF_SONGS = read_file("Tracks.txt");
	if (NO_OF_SONGS < 0) {
        cout << "Reading file failed." << endl;
	    return NO_OF_SONGS;
    }
    quicksort(songs, 0, size(songs)-1);
    //                                          
    cout << "Sorting tracks with quicksort." << endl;
    show_all_tracks (songs, NO_OF_SONGS);
    cout << "Tracks sorted." << endl;

	return 0;
    //               
    /*
                                                      
                                   
                          
                           
                         
       
                 
                                   
                          
                           
                         
     
                 
                                           
                          
                          
                         
     
                 
             
    */
}
