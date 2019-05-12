#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
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

const int MAX_NO_OF_SONGS = 6000;           //                                
vector<Track> songs;                           //                                     
int counter=0;

/*                                                                       
                                
                                                               
                                                                         
                                                                       */
bool operator<(const Length& a, const Length& b)
{
    return (a.minutes*60+a.seconds)<(b.minutes*60+b.seconds);
}

bool operator==(const Length& a, const Length& b)
{
    return (a.minutes*60+a.seconds)==(b.minutes*60+b.seconds);
}

bool operator<(const Track& a, const Track& b)
{
    counter++;
    if(a.artist!=b.artist) return a.artist < b.artist ;
    if(a.cd!=b.cd) return a.cd < b.cd;
    return a.track_no<b.track_no;
}

bool operator==(const Track& a, const Track& b)
{
    counter++;
    return (a.artist == b.artist && a.cd==b.cd && a.track_no==b.track_no) ;   /*                                                 */
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
            no_of_read_songs++;
    }
    while (infile && no_of_read_songs < MAX_NO_OF_SONGS);
    return no_of_read_songs ;
}

int read_file (string filename)
{//               
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
	cout << " Read " << NO_OF_SONGS << " tracks." << endl;
	return NO_OF_SONGS;
}

void show_all_tracks (vector<Track> songs, int no_of_songs)
{//               
    assert (no_of_songs < MAX_NO_OF_SONGS) ;
/*                 
                                                                  
*/
    for (int i = 0 ; i < no_of_songs; i++)
        cout << i+1 << ". " << songs[i] << endl ;
}

//              

void dnf(vector<Track>& data, int first, int last, int& red, int& blue){
    assert(true);

//                                                                                                          

    red = first - 1;
    blue = last+1;
    int white = first - 1;
    const Track PIVOT = data[first+(last-first)/2];
    while(white<blue-1){
        const int NEXT = white+1;
        if(data[NEXT]<PIVOT){
            red++;
            white++;
            swap(data[red], data[NEXT]);
        }else if(data[NEXT]==PIVOT){
            white++;
        }else{
            blue--;
            swap(data[NEXT], data[blue]);
        }
    }
}

void quicksort(vector<Track>& data, int first, int last){
    assert(0<=first && last<data.size()+1);

//                                                                         

    if(first>=last) return;
    else{
        int red, blue;
        dnf(data, first, last, red, blue);
        quicksort(data, first, red);
        quicksort(data, blue, last);
    }
}

int largest(vector<Track>& data, int low, int up){
    assert(true);

//                                                                        

    int maxEl = low;
    while(low<up){
        if(data[low]>data[maxEl]) maxEl = low;
        low++;
    }
    return maxEl;
}

void sort(vector<Track>& data, int n){
    assert(true);

//                                                                 
    while(n>1){
        const int POS = largest(data, 0, n);
        swap(data[POS], data[n]);
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
    cout << "Choose an option for sorting the tracks: \n 1: Quicksort(Recursive) \n 2: Using largest and sort functions (Iterative)" << endl;

    string input;
    cin>>input;

    if(input=="1"){
        quicksort(songs, 0, songs.size());
    }else if (input=="2"){
        sort(songs,songs.size());
    }else{
        cout<< "This is not an option, bye bye.";
        return 0;
    }

    show_all_tracks(songs, songs.size());
    return 0;
}

