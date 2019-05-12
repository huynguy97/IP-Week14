//             
//                        
//                    

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>
#include <algorithm>
#include <string.h>

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

const int MAX_NO_OF_SONGS = 6000;
vector<Track> songs ;

/*                                                                       
                                
                                                               
                                                                         
                                                                       */
bool operator<(const Length& a, const Length& b)
{
    if (a.minutes == b.minutes)
        return a.seconds < b.seconds;
    else return a.minutes < b.minutes;
}

bool operator==(const Length& a, const Length& b)
{
    return (a.minutes == b.minutes && a.seconds == b.seconds) ;   /*                                                 */
}

bool operator>(const Length& a, const Length& b)
{
    return b < a ;
}

bool operator<=(const Length& a, const Length& b)
{
    return !(b < a) ;
}

bool operator>=(const Length& a, const Length& b)
{
    return b <= a ;
}

bool operator<(const Track& a, const Track& b)
{
    /*
                            
     
                         
          
                                 
              
                                               
                                          
                                  
                                     
   */
    return a.time < b.time ;
}

bool operator==(const Track& a, const Track& b)
{
    //                                                                                               
    return a.time == b.time;
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
int read_songs (ifstream& infile, vector <Track>& songs)
{//               
    assert (infile.is_open ()) ;
/*                 
                                                                              
                                                           
*/
    int i = 0 ;
    do {
        Track song ;
        infile >> song ;

        songs.push_back(song);
        i++;
    }
    while (!infile.eof() && i < MAX_NO_OF_SONGS);

    return i-1 ;
}

int read_file (string filename)
{//               
    assert (filename.size() > 4) ;
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

//                                                                           
void show_all_tracks (vector <Track> songs, int no_of_songs)
{//               
    assert (no_of_songs < MAX_NO_OF_SONGS) ;
/*                 
                                                                  
*/
    for (int i = 0 ; i < no_of_songs ; i++)
    {
        cout << i+1 <<". "<< songs[i] << endl ;
    }
}

/*                                                                       
                                          
                                                                       */

/*         
          
         */

void swap (vector <Track>& songs, int  pos1, int pos2)
{
    //     
    assert(pos1 >= 0 && pos1 < songs.size());
    //                                               
    Track temp;
    temp = songs[pos1];
    songs[pos1] = songs [pos2];
    songs[pos2] = temp;
}

void dnf (vector<Track>& songs, int first, int last, int& red, int& blue)
{
    //     
    assert(songs.size() > 0);
    //                                                              
    red = first-1;         //               
    blue = last+1;         //                 
    int white = last+1;    //                  
    const Track PIVOT = songs [first+(last-first) / 2];
    while (red < white - 1) //                 
    {
        const int NEXT = white - 1; //            
        if (songs[NEXT] < PIVOT) //               
        {
            red++; //                       
            swap (songs, red, NEXT) ;
        }
        else if (songs[NEXT] == PIVOT) //                 
            white-- ; //                      
        else //                
        {
            white--;
            blue--; //                     
            swap (songs, NEXT, blue);
        }
    }
}

void quicksort (vector<Track>& songs, int first, int last)
{
    //     
    assert (0 <= first && last <= songs.size()) ;
    //                                             
    if (first >= last)
        return;
    else
    {
        int red, blue ;
        dnf(songs, first, last, red, blue) ;
        quicksort (songs, first, red) ;
        quicksort (songs, blue, last) ;
    }
}

/*         
         
         */
void special_dnf (vector<Track>& songs, int first, int last, int& red, int& blue)
{
    //     
    assert(songs.size() >= 0);
    //                                                                          
    //                                           
    red = first - 1;                     //               
    blue = last + 1;                     //                 
    int white = first - 1;               //                 
    const Track PIVOT = songs [first+(last-first)/2];
    while (white < blue - 1)             //                 
    {
        const int NEXT = blue - 1;      //            
        if (songs[NEXT] < PIVOT)        //               
        {
            red++;                     //               
            white++;                   //                 
            swap(songs, red, NEXT);    //                       
        }
        else if (songs[NEXT] == PIVOT)  //                 
        {
            white++;                    //                  
            swap(songs, NEXT, white);   //                                   
        }

        else                            //                
        {
            blue--;                    //                  
            swap (songs, NEXT, blue);  //                                 
        }
    }
}

void special_quicksort (vector<Track>& songs, int first, int last)
{
    //     
    assert (0 <= first && last < songs.size()) ;
    //                                             
    if (first >= last)
        return;
    else
    {
        int red, blue ;
        special_dnf(songs, first, last, red, blue) ;
        special_quicksort (songs, first, red) ;
        special_quicksort (songs, blue, last) ;
    }
}

/*                                                               
                                                              
                                                               */
typedef int El;

void swap_p3 (vector <El>& v, int  pos1, int pos2)
{
    //     
    assert(pos1 >= 0 && pos1 <= pos2);
    assert(pos2 > 0 && pos2 < v.size());
    //                                                             
    El temp;
    temp = v[pos1];
    v[pos1] = v[pos2];
    v[pos2] = temp;
}

int largest(vector<El>&v, int low, int up)
{
    //     
    assert(low >= 0 && low < v.size());
    assert(low <= up);
    //                                                                     
    int pos = low;

    int i = low;
    while(i < up)
    {
        if (v[pos] < v[i])
            pos = i;
        i++;
    }
    return pos;
}

void sort(vector<El>& v, int n)
{
    //     
    assert(v.size() > 0);
    assert(n == v.size());
    //                                                                                           
    while(n > 1)
    {
        const int POS = largest(v, 0, n) ;
        swap_p3 (v, POS, n-1) ;
        n--;
    }
}

/*                                                                       
                                      
                   
                                           
                                       
                                          
                                                                       */

void quickdnf(int num_songs)
{
    //     
    assert(num_songs > 0);
    //                                                                                  
    int first = 0;
    int last = num_songs - 1;

    quicksort(songs,first,last);
    show_all_tracks(songs,num_songs);

}

void quickdnf_alt(int num_songs)
{
    //     
    assert(num_songs > 0);
    //                                                                                              
    int first = 0;
    int last = num_songs - 1;

    special_quicksort(songs, first, last);
    show_all_tracks(songs, num_songs);
}

void iterative_sort()
{
    //     
    assert(true);
    //                                                               
    vector <El> v = {   68, 35, 53, 59, 45, 77, 72, 51, 58, 28, 82, 83, 90, 80, 43, 81, 55, 73, 20,
                        11, 3, 2, 16, 67, 88, 87, 23, 84, 86, 30, 25, 18, 37,  69, 21, 24, 89,  5, 31,
                        46, 19, 48, 29, 65, 32, 37, 74, 7, 63,17, 70, 47, 33, 27, 13, 10, 75, 36,
                        85, 38, 57, 42, 9, 76, 26, 6,78, 61, 79, 50, 15, 4, 34, 54, 40, 22, 56,
                        12, 49, 39, 64, 1, 66, 71, 44, 60, 41, 8, 62, 14, 52
                    };

    sort(v,v.size());

    //                       
    for (int i = 0 ; i < v.size(); i++)
        cout << v[i] << " ";
}

int main()
{
    bool run = true;

    const int NO_OF_SONGS = read_file ("Tracks.txt");

    if (NO_OF_SONGS < 0)
    {
        cout << "Reading file failed." << endl;
    }

    while(run == true)
    {
        int input;
        /*
                                                                   
                                                                                     
                                                     
                                                      
                                                       
        */
        cout << endl;
        cout << "Which part of the assignment would you like to execute?" << endl;
        cout << "1: PART 1 - standard DNF quicksort" << endl;
        cout << "2: PART 2 - alternative DNF quicksort" << endl;
        cout << "3: PART 3 - iterative sorting algorithm" << endl;
        cout << "4: Exit" << endl;

        cin >> input;

        cout << endl;

        switch (input) {
            case 1 :
                quickdnf(NO_OF_SONGS);
                break;
            case 2:
                quickdnf_alt(NO_OF_SONGS);
                break;
            case 3:
                iterative_sort();
                break;
            case 4 :
                cout << endl;
                cout << "Exiting..." << endl;
                run = false;
                break;
            default :
                cout << "Input not accepted!" << endl;
                break;
        }
        cout << endl;
    }

    return 0;
}

