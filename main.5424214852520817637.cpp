#include <iostream>
#define NDEBUG
#include <cassert>
#include <string>
#include <istream>
#include <vector>
#include <fstream>
using namespace std;

//                                  
int globalcount = 0;

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

bool operator<(const Length& a, const Length& b)
{

    if(a.minutes == b.minutes)
    {
        return a.seconds < b.seconds;
    }
    else
        return (a.minutes < b.minutes);
}

bool operator==(const Length& a, const Length& b)
{

    return (a.minutes == b.minutes && a.seconds == b.seconds);
}

bool operator==(const Track& a, const Track& b)
{
    return (a.artist == b.artist && a.cd == b.cd && a.year == b.year && a.track_no == b.track_no && a.title == b.title && a.tags == b.tags && a.time == b.time && a.country == b.country);
}

bool operator<(const Track& a, const Track& b)
{
    return a.track_no < b.track_no; //               
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
{
    //               
    assert (true) ;
    /*                 
                                                                                                          
    */
    char colon;
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
    return infile;
}

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
int read_songs (ifstream& infile, vector<Track>& songs)
{
    //               
    //                
    /*                 
                                                                                  
                                                               
    */
    //                          
    Track song;
    do
    {

        infile >> song;
        songs.push_back(song);
        //           
        //                   

    }
    while (infile && song.artist != "\0");
    return songs.size();//                  
}
int read_file (string filename, vector<Track>& songs)
{
    //               
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
void show_all_tracks (vector<Track>&  songs, int no_of_songs)
{
    //               
    //                                        
    /*                 
                                                                      
    */
    for (int i = 0 ; i < no_of_songs; i++)
        cout << i+1 << ". \n" << songs[i] << endl ;
}

void swap_track(vector<Track>& data, int indexa, int indexb)
{
    assert(indexa >= 0 && indexa < data.size() && indexb >= 0 && indexb < data.size());
    //                                          
    Track placeholder = data[indexa];
    data[indexa] = data[indexb];
    data[indexb] = placeholder;
}

//                 

void dnf_track (vector<Track>& data, int first, int last, int& red, int& blue)
{
    assert(first < last && first >= 0 && last < data.size());
    //                                               
    red= first-1;
    blue= last+1;
    int white= last+1;
    const Track PIVOT = data[first+(last-first)/2];
    while(red<white-1)
    {
        globalcount++;
        const int NEXT = white-1;
        if(data[NEXT].track_no < PIVOT.track_no)
        {
            red++;
            swap_track(data, red, NEXT);
        }
        else if(data[NEXT].track_no == PIVOT.track_no)
            white--;
        else
        {
            white--;
            blue--;
            swap_track(data, NEXT, blue);
        }
    }
}

void quicksort_track (vector<Track>& data, int first, int last)
{
    assert(true);
    //                                                                                                        

    if(first >= last)
    {
        return;
    }
    int red, blue;
    dnf_track(data, first,last,red,blue);
    quicksort_track(data,first,red);
    quicksort_track(data,blue,last);
}

void quicksort_tracks(vector<Track>& Data, int n)
{
    assert(n < Data.size());
    //                                                  
    int cdsize = 0;
    for(int i = 0; i < n; i++)
    {
        if(Data[i].cd != Data[i+1].cd || Data[i].artist != Data[i+1].artist || i == n-1)
        {
            quicksort_track(Data,i-cdsize,i);
            cdsize = 0;
            i++;
        }
        cdsize++;
    }
}

//              

void dnf_time (vector<Track>& data, int first, int last, int& red, int& blue)
{
    assert(first < last && first >= 0 && last < data.size());
    //                                                      
    red= first-1;
    blue= last+1;
    int white= first-1;
    const Track PIVOT = data[first+(last-first)/2];
    while(blue > white+1)
    {
        globalcount++;
        const int NEXT = white+1;
        if(data[NEXT].time < PIVOT.time)
        {
            red++;
            white++;
            swap_track(data,red,NEXT);
        }
        else if(data[NEXT].time == PIVOT.time)
        {
            white++;
        }
        else
        {
            blue--;
            swap_track(data, NEXT, blue);
        }
    }
}
void quicksort_time (vector<Track>& data, int first, int last)
{
    assert(true);
    //                                                                                                               

    if(first >= last)
    {
        return;
    }
    int red, blue;
    dnf_time(data, first,last,red,blue);
    quicksort_time(data,first,red);
    quicksort_time(data,blue,last);
}

void sort_tracks(vector<Track>& data, int n)
{
    assert(n < data.size());
    //                                                                             
    for(int i = n; i >= 0; i--)
    {
        int largest = -1;
        int largestcd = -1;
        int indexlarge, samecdlarge;
        for(int j = 0; j < i; j++)
        {
            globalcount++;
            if(largestcd < data[j].track_no && data[j].cd == data[i+1].cd && data[j].artist == data[i+1].artist)
            {

                largestcd = data[j].track_no;
                samecdlarge = j;
            }
            else if(largest < data[j].track_no)
            {
                largest = data[j].track_no;
                indexlarge = j;
            }
        }
        if(largestcd == -1)
        {
            swap_track(data,indexlarge,i);
        }
        else
        {
            swap_track(data,samecdlarge,i);
        }
    }
}

void sort_time(vector<Track>& data, int n)
{
    assert(n < data.size());
    //                                         
    for(int i = n; i >= 0; i--)
    {
        Length largest = {0,0};
        int indexlarge;
        for(int j = 0; j < i; j++)
        {
            globalcount++;
            if(largest < data[j].time)
            {
                largest = data[j].time;
                indexlarge = j;
            }
        }
        swap_track(data,indexlarge,i);
    }
}

/*                                                                 */

//                             

int main()
{
    vector<Track> Data (0);
    const int first = 0;
    const int last = read_file ("Tracks.txt", Data)-1;
    int input;
    do
    {
        cout << "Select a sorting method by choosing a number: \n"
             << "(1)quicksort time\n"
             << "(2)quicksort track\n"
             << "(3)sort time\n"
             << "(4)sort track\n"
             << "(5)terminate program\n";
        cin >> input;
    }
    while(!(input == 1 || input == 2 || input == 3 || input == 4 || input == 5));

    if(input == 5)
    {
        return 0;
    }

    switch(input)
    {
       case 1: quicksort_time(Data,first,last); break;
       case 2: quicksort_tracks(Data,last); break;
       case 3: sort_time(Data,last); break;
       case 4: sort_tracks(Data,last); break;
       default: break;
    }
    show_all_tracks(Data,last);
    cout << "Completed in " << globalcount << " steps." << endl;
    return 0;
}

