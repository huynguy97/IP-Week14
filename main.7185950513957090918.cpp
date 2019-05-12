#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>
#define NDEBUG

//             
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

vector<Track> songs;

int size (vector<Track>& data)
{
    return static_cast<int>(data.size());
}

bool operator<(const Length& a, const Length& b)
{
    if(a.minutes == b.minutes)
    {
        return a.seconds < b.seconds;
    }
    return a.minutes < b.minutes;
}

bool operator==(const Length& a, const Length& b)
{
    return a.seconds == b.seconds && a.minutes == b.minutes;
}

bool operator<(const Track& a, const Track& b)
{
    if(a.time == b.time)
    {
        if(a.artist == b.artist)
        {
            if(a.title == b.title)
            {
                return a.cd < b.cd;
            }
            return a.title < b.title;
        }
        return a.artist < b.artist;
    }
    return a.time < b.time;
}

bool operator==(const Track& a, const Track& b)
{
    return a.artist == b.artist && a.cd == b.cd && a.time == b.time && a.title == b.title;   /*                                                 */
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

void swap (vector<Track>& data, int  i, int  j )
{//	              
	assert ( i >= 0 && j >= 0 ) ;	//                         
						            //                         
//                                                                
	const Track HELP = data [i];
	data [i] = data [j] ;
	data [j] = HELP;
}

//                                                                           
int read_songs ()
{//               
    assert (true) ;
/*                 
                                                                              
                                                           
*/
    ifstream infile;
    infile.open("Tracks.txt");
    int i = 0;
    do {
        Track song;
        infile >> song ;
        if (infile)
        {
            i++;
            songs.push_back(song) ;
        }
    }
    while (infile);
    return size(songs) ;
}

/*                                                    
*/
void show_all_tracks (vector<Track>& songs, int no_of_songs)
{//               
    assert (true) ;
/*                 
                                                                  
*/
    for (int i = 0 ; i < no_of_songs; i++)
        cout << i+1 << ". " << songs[i] << endl ;
}

void dnf (int first, int last, int& red, int& blue)
{
    assert(0 <= first && last <size(songs));
    /*         
                                                                                                     
    */

    red = first - 1;
    blue = last + 1;
    int white = last + 1;
    const Track PIVOT = songs[first + (last - first)/2];
    while (red < white -1)
    {
        const int NEXT = white - 1;
        if(songs[NEXT] < PIVOT)
        {
            red++;
            swap(songs, red, NEXT);
        }
        else if(songs[NEXT] == PIVOT)
        {
            white--;
        }
        else
        {
            white--;
            blue--;
            swap(songs, NEXT, blue);
        }
    }
}

void dnf_reverse (int first, int last, int& red, int& blue)
{
    assert(0 <= first && last <size(songs));
    /*         
                                                                                                     
    */

    red = first - 1;
    blue = last + 1;
    int white = first - 1;
    const Track PIVOT = songs[first + (last - first)/2];
    while (blue > white + 1)
    {
        const int NEXT = white + 1;
        if(songs[NEXT] < PIVOT)
        {
            red++;
            white++;
            swap(songs, red, NEXT);
        }
        else if(songs[NEXT] == PIVOT)
        {
            white++;
            swap(songs, white, NEXT);
        }
        else
        {
            blue--;
            swap(songs, NEXT, blue);
        }
    }
}

void quicksort(int first, int last)
{
    assert(0 <= first && last <size(songs));
    /*         
                               
    */

    if(first >= last)
    {
        return;
    }
    else
    {
        int red;
        int blue;
        dnf(first, last, red, blue);
        quicksort(first, red);
        quicksort(blue, last);
    }
}

int largest(vector<Track>& data, int low, int up)
{
    assert(low >= 0 && up >= 0);
    /*         
                                                                         
    */

    vector<int> stack;

    while(low < up)
    {
        stack.push_back(low);
        low++;
    }
    int pos = low;
    while(stack.size() > 0)
    {
        int x = stack[stack.size() - 1];
        stack.pop_back();

        if(data[x] > data[pos])
        {
            pos = x;
        }
    }
    return pos;
}

void sort(vector<Track>& data, int n)
{
    assert(n > 0);
    /*         
                                                
    */

    while(n > 1)
    {
        int pos = largest(data, 0, n);
        swap(data, pos, n);
        n--;
    }
}

int main()
{
    read_songs();
    sort(songs, 100);
    show_all_tracks(songs, 100);
}

