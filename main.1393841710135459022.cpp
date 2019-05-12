#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>

using namespace std;

//                       

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

bool operator<(const Length& a, const Length& b)
{
    return a.minutes < b.minutes || (a.minutes == b.minutes && a.seconds < b.seconds);
}

bool operator==(const Length& a, const Length& b)
{
    return a.minutes == b.minutes && a.seconds == b.seconds;
}

bool operator<(const Track& a, const Track& b)
{

    return (a.artist < b.artist) || (a.artist == b.artist && a.cd < b.cd) ||
    (a.artist == b.artist && a.cd == b.cd && a.track_no < b.track_no);
}

bool operator==(const Track& a, const Track& b)
{
    return (a.artist == b.artist) && (a.cd == b.cd) && (a.year == b.year) && (a.track_no == b.track_no);
}

bool operator>(const Track& a, const Track& b)
{
	return !(a < b) && !(a == b);
}

bool operator<=(const Track& a, const Track& b)
{
	return (a < b) || (a == b);
}

bool operator>=(const Track& a, const Track& b)
{
	return b <= a ;
}

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
        {
            songs.push_back(song);
        }
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

void show_all_tracks (vector<Track>& songs, int no_of_songs)
{//               
    assert (no_of_songs >= 0) ;
/*                 
                                                                  
*/
    for (int i = 0 ; i < no_of_songs; i++)
        cout << i+1 << ". " << songs[i] << endl ;
}

void swap (vector<Track>& data, int i, int j)
{//              
    assert (i >= 0 && j >= 0);
/*                
                                                    
*/
    const Track HELP = data[i];
    data[i] = data[j];
    data[j] = HELP;
}

void dnf (vector<Track>& data, int first, int last, int& red, int& blue)
{//              
    assert (first >= 0 && last < data.size());
/*                
                                                                    
                                                                                                   
*/
    red = first-1;
    blue = last+1;
    int white = last+1;
    const Track PIVOT = data[first+(last-first)/2];
    while (red < white-1)
    {   const int NEXT = white-1;
        if (data[NEXT] < PIVOT)
        {   red++;
            swap(data, red, NEXT);
        }
        else if (data[NEXT] == PIVOT)
            white--;
        else
        {
            white--; blue--;
            swap(data, NEXT, blue);
        }
    }
}

void dnftime (vector<Track>& data, int first, int last, int& red, int& blue)
{//              
    assert (first >= 0 && last < data.size());
/*                
                                                                    
                                                                                                   
                  
*/
    red = first-1;
    blue = last+1;
    int white = last+1;
    const Track PIVOT = data[first+(last-first)/2];
    while (red < white-1)
    {   const int NEXT = white-1;
        if (data[NEXT].time < PIVOT.time)
        {   red++;
            swap(data, red, NEXT);
        }
        else if (data[NEXT].time == PIVOT.time)
            {
                white--;
            }
        else
        {
            white--; blue--;
            swap(data, NEXT, blue);
        }
    }
}

void quicksort (vector<Track>& data, int first, int last, string sortingway)
{//              
    assert (true);
/*                
                                          
*/
    if (first >= last)
        return ;
    else
    {
        int red, blue;
        if (sortingway == "yes")
        {
            dnftime(data, first, last, red, blue);
            quicksort(data, first, red, "yes");
            quicksort(data, blue, last, "yes");
        }
        else if (sortingway == "no")
        {
            dnf(data, first, last, red, blue);
            quicksort(data, first, red, "no");
            quicksort(data, blue, last, "no");
        }
    }
}

int largest (vector<Track>& v, int low, int up)
{//              
    assert (low >= 0 && up >= 0);
/*                
                                                               
*/
    int pos = low;
    low++;
    while (low < up+1)
    {
        if (v[pos] < v[low])
            pos = low;
        low++;
    }
    return pos;
}

void sort (vector<Track>& v, int n)
{//              
    assert (true);
/*                
                                                 
*/
    while (n > 1)
    {
        const int POS = largest(v, 0, n-1);
        swap(v, POS, n-1);
        n--;
    }
}

int main()
{
    read_file("Tracks.txt");
    /*                      
                                                                                     
                      
                      
                                                        
     
                                                                          
                          
     
                                                    
                                           
    */
    /*        
                                
                                           
    */
    return 0;
}

