//                       

#define NDEBUG

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

int counter;

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

/*                                                                       
                                
                                                               
                                                                         
                                                                       */
bool operator<(const Length a, const Length b)
{
    if(a.minutes < b.minutes)
        return true;
    else if(a.minutes > b.minutes)
        return false;

    if(a.seconds < b.seconds)
        return true;
    else if(a.seconds > b.seconds)
        return false;

    return false;
}

bool operator==(const Length a, const Length b)
{
    return a.minutes == b.minutes && a.seconds == b.seconds;
}

bool operator>(const Length a, const Length b)
{
    return !(a < b) && !(a == b);
}

bool operator<(const Track& a, const Track& b)
{
    counter++;

    if(a.time < b.time)
        return true;
    else if(a.time > b.time)
        return false;

    if(a.artist < b.artist)
        return true;
    else if(a.artist > b.artist)
        return false;

    if(a.title < b.title)
        return true;
    else if(a.title > b.title)
        return false;

    if(a.year < b.year)
        return true;
    else if(a.year > b.year)
        return false;

    if(a.track_no < b.track_no)
        return true;
    else if(a.track_no > b.track_no)
        return false;

    return false;
}

bool operator==(const Track& a, const Track& b)
{
    counter++;

    return a.time == b.time && a.artist == b.artist && a.title == b.title && a.year == b.year && a.track_no == b.track_no;
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

int read_songs (ifstream& infile, vector<Track>& songs )
{//               
    assert (infile.is_open ()) ;
/*                 
                                                                              
                                                           
*/
    int no_of_read_songs = 0 ;
    do {
        Track song;
        infile >> song;
        songs.push_back(song);
        no_of_read_songs++;
    }while (!infile.eof());

    songs.pop_back(); //                         
    no_of_read_songs--;
    return no_of_read_songs;
}

int read_file (string filename, vector<Track>& songs)
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

/*                                                                    
                  
                                                                     */

void swapper(vector<Track>& songs, int a, int b)
{//     
    assert(true);
//                                    

    Track temp = songs[a];

    songs[a] = songs[b];
    songs[b] = temp;
}

void dnf_rowb(vector<Track>& songs, int first, int last, int& red, int& blue)
{//               
    assert (true);
//                                   

    red = first - 1;
    blue = last + 1;
    int white = last + 1;

    const Track PIVOT = songs[first + (last-first) / 2];
    while(red < white - 1){
        const int NEXT = white - 1;
        if(songs[NEXT] < PIVOT){
            red++;
            swapper(songs, red, NEXT);
        }else if(songs[NEXT] == PIVOT){
            white--;
        }else{
            white--;
            blue--;
            swapper(songs, NEXT, blue);
        }
    }
}

void quicksort_rowb(vector<Track>& songs, int first, int last)
{//               
    assert (true);
//                             

    if(first >= last)
        return;
    else{
        int red, blue;
        dnf_rowb(songs, first, last, red, blue);
        quicksort_rowb(songs, first, red);
        quicksort_rowb(songs, blue, last);
    }
}

void dnf_rwob(vector<Track>& songs, int first, int last, int& red, int& blue)
{//               
    assert (true);
//                                   

    red = first - 1;
    blue = last + 1;
    int white = first - 1;

    const Track PIVOT = songs[first + (last-first) / 2];
    while(red < white + 1){
        const int NEXT = white + 1;
        if(songs[NEXT] < PIVOT){
            red++;
            swapper(songs, red, NEXT);
        }else if(songs[NEXT] == PIVOT){
            white++;
        }else{
            white++;
            blue--;
            swapper(songs, NEXT, blue);
        }
    }
}

void quicksort_rwob(vector<Track>& songs, int first, int last)
{//               
    assert (true);
//                             

    if(first >= last)
        return;
    else{
        int red, blue;
        dnf_rwob(songs, first, last, red, blue);
        quicksort_rwob(songs, first, red);
        quicksort_rwob(songs, blue, last);
    }
}

/*                                                                    
                         
                                                                     */

int largest_old(vector<Track>& songs, int low, int up)
{
    if(low >= up)
        return low;
    else{
        const int POS = largest_old(songs, low+1, up);
        if(songs[low] > songs[POS])
            return low;
        else
            return POS;
    }
}

void sort_old(vector<Track>& songs, int n)
{
    if(n > 1){
        const int POS = largest_old(songs, 0, n-1);
        swapper(songs, POS, n-1);
        sort_old(songs, n-1);
    }
}

/*                                                                    
                         
                                                                       
                                              
                                                                     */

int largest(vector<Track>& songs, int up)
{//     
    assert(true);
//                                 

    int largest = 0;

    bool changes = true;
    while(changes){
       changes = false;
       for(int i = 0; i < songs.size(); i++){
            if(songs[i] > songs[largest]){
                largest = i;
                changes = true;
            }
       }
    }
}

void sort(vector<Track>& songs)
{//     
    assert(true);
//                   

    for(int i = songs.size(); i > 0; i--){
        swapper(songs, i, largest(songs, i));
    }
}

/*                                                                    
               
                                                                     */

void show_all_tracks (vector<Track> songs)
{//               
    assert (true) ;
//                                                                                

    for (int i = 0 ; i < songs.size(); i++)
        cout << i+1 << ". " << songs[i] << endl ;
}

int main()
{
    vector<Track> songs;
	const int NUMBER_OF_SONGS = read_file ("Tracks.txt", songs);
	quicksort_rwob(songs, 0, NUMBER_OF_SONGS);
    //            

	show_all_tracks(songs);

	return 0;
}

