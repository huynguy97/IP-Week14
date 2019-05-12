#define NDEBUG

/*                                                                    
                                              
            
                                                                                                            
                                  
                              
                                                           
                                                                    
                                                          
                                                               
                                                                     */
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

/*                                                                    
                                            
                                                                     */
struct Length
{
    int minutes;                            //               
    int seconds;                            //                 
};
struct Track
{
    string artist;                          //            
    string cd;                              //         
    int    year;                            //                   
    int    track_no;                        //             
    string title;                           //            
    string tags;                            //                            
    Length time;                            //             
    string country;                         //                                         
};

const int MAX_NO_OF_SONGS = 6000;           //                                
vector<Track>songs(MAX_NO_OF_SONGS);              //                                     
int counter = 0;

/*                                                                       
                                
                                                               
                                                                         
                                                                       */
bool operator< (const Length& a, const Length& b)
{
//               
//                                                                                                  
    if(a.minutes == b.minutes)
        return (a.seconds<b.seconds);
    else return (a.minutes < b.minutes);
}

bool operator> (const Length& a, const Length& b)
{
//               
//                                                                                                  
    return (!(a<b));
}

bool operator== (const Length& a, const Length& b)
{
//              
//                                                               
    return((a.minutes == b.minutes) && (a.seconds == b.seconds));
}

bool operator<(const Track& a, const Track& b)
{
    //                                                                                                                                                
//               
//                                                                                                          
    counter++;
   /*                          
     
                         
         
                                 
                                               
                                        
         
                                  
     
                                  
    */
    return(a.time < b.time);

}

bool operator==(const Track& a, const Track& b)
{
//                                                                                                                                                
//               
//                                                             
    counter++;
    return (/*                          
                              
                                  
                                          */
             (a.time == b.time));   /*                                                 */
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

int size (vector<Track>& v)
{
    return static_cast<int>(v.size());
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
            songs[no_of_read_songs++] = song ;
    }
    while (infile && no_of_read_songs < size(songs));
    return no_of_read_songs ;
}

int read_file (string filename, vector<Track>& songs)
{//               
    assert (size (songs) > 0) ;
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
{//               
    assert (no_of_songs < MAX_NO_OF_SONGS) ;
/*                 
                                                                  
*/
    for (int i = 0 ; i < no_of_songs; i++)
        cout  << songs[i] << endl ;
}

/*                                                                       
                                                         
                                                                       */
typedef Track El ;                //                                                       

void swap (vector<El>& data, int  i, int  j )
{//                  
    assert ( i >= 0 && j >= 0 ) ;    //                         
                                    //                         
//                                                                
    const El HELP = data [i];
    data [i] = data [j] ;
    data [j] = HELP;
}

void dnf (vector<El>& data, int first, int last, int& lastred, int& firstblue)
{
    //               
    assert(first <= last);
    //                                                              
    lastred = first-1;
    firstblue = last+1;
    int firstwhite = last+1;
    const El PIVOT = data[first+(last-first)/2];
    while(lastred < firstwhite -1)
    {
        const int NEXT = firstwhite-1;
        if(data[NEXT] < PIVOT)
        {
            lastred++;
            swap(data,lastred,NEXT);
        }
        else if(data[NEXT] == PIVOT)
            firstwhite--;
        else
        {
            firstwhite--;
            firstblue--;
            swap(data,NEXT,firstblue);
        }
    }
}

void dnfadjusted(vector<El> data, int first, int last, int& lastred, int& firstblue)
{
    //               
    assert(first <= last);
    //                                                                                                             
    lastred = first-1;
    firstblue = last+1;
    int white = first-1;
    const El PIVOT = data[first+(last-first)/2];
    while(firstblue> white+1)
    {
        const int NEXT = white + 1;
        if(data[NEXT] < PIVOT){
            lastred++;
            white++;
            swap(data,lastred,NEXT);
        }

        else if ( data[NEXT] == PIVOT)
        {
            white++;
        }
        else
        {
            firstblue--;
            swap(data,NEXT,firstblue);
        }
    }
}

void quicksort(vector<El>& data, int first, int last)
{
    //              
    assert(0 <= first && last < size(data));
    //                                                   
    if(first >= last) return;
    else
    {
        int lastred;
        int firstblue;
        dnf(data,first,last,lastred,firstblue);
        quicksort(data,first,lastred);
        quicksort(data,firstblue,last);
    }
}

int largest (vector<int>& v, int low, int up)
{
//               
assert(low =< up);
//                                                          
int largest = low;
for (int i = low; i <= up; i++)
    {
        for (int k = low; k<=up; k++)
            {
                if (v[i] > v[k] && v[i] > v[largest])
                    largest = i;
            }
    }
return largest;
}

void swap2 (vector<int>& data, int  i, int  j )
{//                  
    assert ( i >= 0 && j >= 0 ) ;    //                         
                                    //                         
//                                                                
    const int HELP = data [i];
    data [i] = data [j] ;
    data [j] = HELP;
}

void sort(vector<int>& v)
{
    //               
    assert(true);
    //                                                       
    for(int i = v.size()-1; i>1 ; i--)
    {
        int POS = largest(v,0,i);
        swap2(v,POS,i);
    }
}

/*                                                                       
                                      
                   
                                                                      
                                           
                                          
                                                                       */

void output_file(ofstream& outfile, int& counter)
{
//               
assert(true);
//                                                                                                                   
    string outfilename;
    cout << "Enter an Output File name: ";
    cin >> outfilename ;
    cout << endl;
    outfile.open(outfilename.c_str());
}

int main()
{
//                                                                             
    const int NO_OF_SONGS = read_file ("Tracks.txt",songs );
    if (NO_OF_SONGS < 0)
    {
        cout << "Reading file failed. Program terminates." << endl;
        return NO_OF_SONGS;
    }

    quicksort(songs,0,NO_OF_SONGS-1);
    show_all_tracks(songs, NO_OF_SONGS);

}

