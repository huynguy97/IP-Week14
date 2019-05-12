//                                                                     

#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>

using namespace std;

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

const int MAX_NO_OF_SONGS = 6000;           //                                
vector<Track> songs;              //                                     

int size (vector<Track> songs){
    return static_cast<int> (songs.size());
}

int counter = 0;

/*                                                                       
                                
                                                               
                                                                         
                                                                       */
bool operator==(const Length& a, const Length& b)
{
    return a.minutes == b.minutes && a.seconds == b.seconds;
}

bool operator<(const Length& a, const Length& b)
{
    if (a.minutes == b.minutes)
    {
        return a.seconds < b.seconds;
    }
    else
    {
        return a.minutes < b.minutes;
    }
}

bool operator<(const Track& a, const Track& b) {
    //             
    //              
    //                                                                                                        
    counter++;
    if (a.time == b.time) {
        if (a.artist == b.artist) {
            if (a.cd == b.cd) {
                if (a.year == b.year) {
                    return a.track_no < b.track_no;
                } else {
                    return a.year < b.year;
                }
            } else {
                return a.cd < b.cd;
            }
        } else {
            return a.artist < b.artist;    /*                                                 */
        }
    }
    return a.time < b.time;
}

bool operator==(const Track& a, const Track& b)
{
    //             
    //               
    //                                                                           
    counter++;
    return a.time == b.time && a.artist == b.artist && a.cd ==b.cd && a.year == b.year && a.track_no == b.track_no;   /*                                                 */

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

//                                                                           
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
    }
    while (infile && no_of_read_songs < MAX_NO_OF_SONGS);
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

//                                                                           
void show_all_tracks (vector<Track>& songs, int no_of_songs)
{//               
    assert (no_of_songs < MAX_NO_OF_SONGS) ;
/*                 
                                                                  
*/
    for (int i = 0 ; i < no_of_songs; i++)
        cout << i+1 << ". " << songs[i] << endl ;
}

void dnf_rowb(vector<Track>& data, int first, int last, int& red, int& blue) {
    assert(first >= 0 && last < data.size());
    //                                                                                                        

    red = first - 1;
    blue = last + 1;
    int white = last + 1;
    const Track PIVOT = data[first + (last - first) / 2];

    while (red < white - 1) {
        const int NEXT = white - 1;

        if (data[NEXT] < PIVOT) {
            red++;
            swap(data[red], data[NEXT]);
        } else if (data[NEXT] == PIVOT) {
            white--;
        } else {
            white--;
            blue--;
            swap(data[NEXT], data[blue]);
        }
    }
}

void dnf_rwob(vector<Track>& data, int first, int last, int& red, int& blue) {
    assert(first >= 0 && last < data.size());
    //                                                                                                        

    red = first - 1;
    blue = last + 1;
    int white = first - 1;
    const Track PIVOT = data[first + (last - first) / 2];

    while (white < blue - 1) {
        const int NEXT = blue - 1;

        if (data[NEXT] < PIVOT) {
            red++;
            white++;
            swap(data[red], data[NEXT]);
            if(white != red) {
                swap(data[white], data[NEXT]);
            }
        } else if (data[NEXT] == PIVOT) {
            white++;
            swap(data[NEXT], data[white]);
        } else {
            blue--;
        }
    }
}

void dnf(vector<Track>& data, int first, int last, int& red, int& blue) {
    //                      
#ifdef USE_RWOB_DNF
    dnf_rwob(data, first, last, red, blue);
#else
    dnf_rowb(data, first, last, red, blue);
#endif
}

void quicksort(vector<Track>& data, int first, int last) {
    assert (first >= 0 && last < static_cast<int>(data.size()));
    //                                           

    if (first >= last) return;

    int red, blue;
    dnf(data, first, last, red, blue);
    quicksort(data, first, red);
    quicksort(data, blue, last);
}

void quicksort(vector<Track>& data) {
    //                      

    quicksort(data, 0, static_cast<int>(data.size()) - 1);
}

//                       

int largest(vector<Track>& v, int low, int up) {
    assert(low >= 0 && up < v.size());
    //                                                                   

    int largest = low;
    while(low <= up) {
        largest = v[low] > v[largest] ? low : largest;
        ++low;
    }
    return largest;
}

void sort(vector<Track>& v, int n) {
    assert(n == v.size());
    //                   

    for(int i = n - 1; i > 0; --i) {
        swap(v[i], v[largest(v, 0, i)]);
    }
}

void test_quicksort(int no_of_songs) {
    //                                                                 

    vector<int> vec(no_of_songs);

    for(auto i = 0; i < no_of_songs; ++i) {
        generate_n(vec.begin(), vec.size(), rand);

        quicksort(vec(no_of_songs));

        if(!is_sorted(vec.cbegin(), vec.cend())) {
            cerr << "Sort failed on iteration " << i << endl;

            for(auto x : vec) {
                cerr << x << endl;
            }

            exit(EXIT_FAILURE);
        }
    }

    cout << "All iterations sorted successfully" << endl;
}

void test_sort(int no_of_songs) {
    //                                                                 

    vector<int> vec(no_of_songs);

    for(auto i = 0; i < no_of_songs; ++i) {
        generate_n(vec.begin(), vec.size(), rand);

        sort(vec(no_of_songs), static_cast<int>(vec.size()));

        if(!is_sorted(vec.cbegin(), vec.cend())) {
            cerr << "Sort failed on iteration " << i << endl;

            for(auto x : vec) {
                cerr << x << endl;
            }

            exit(EXIT_FAILURE);
        }
    }

    cout << "All iterations sorted successfully" << endl;
}

int main() {

    const int NO_OF_SONGS = read_file ("Tracks.txt");
    if (NO_OF_SONGS < 0) {
        cout << "Reading file failed. Program terminates." << endl;
        return NO_OF_SONGS;
    }
    cout << "Testing quicksort" << endl;
    test_quicksort(NO_OF_SONGS);

    cout << "Testing DNF sort" << endl;
    test_sort(NO_OF_SONGS);

    show_all_tracks (songs,NO_OF_SONGS) ;

    return EXIT_SUCCESS;
}
