#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <cstring>
#include <string>
#include <cstdlib>
#include <algorithm>

using namespace std;

//                             

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

vector<Track> tracklist;

/*                                           
                                             
                                             
*/
bool operator<(const Length& a, const Length& b)
{
    int timea = a.minutes*60 + a.seconds,
        timeb = b.minutes*60 + b.seconds;

    if (timea < timeb)
        return true;

    return false;
}

bool operator==(const Length& a, const Length& b)
{
    int timea = a.minutes*60 + a.seconds,
        timeb = b.minutes*60 + b.seconds;

    if (timea == timeb)
        return true;

    return false;
}

//                      
bool operator==(const Track& a, const Track& b)
{
    //                                                                                                                                                
    if (a.time == b.time)                                                                       //                 
        return true;

    return false;
}

bool operator<(const Track& a, const Track& b)
{
    //                                                                                                                                                
    if (a.time < b.time)                                                                        //                 
        return true;

    return false;
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
    getline(infile, track.artist);       //       
    getline(infile, track.cd);           //   
    infile >> track. year ;              //     
    skip_to_next_newline(infile) ;
    infile >> track. track_no ;          //             
    skip_to_next_newline(infile) ;
    getline(infile, track.title);        //            
    getline(infile, track.tags);         //           
    infile >> track.time ;               //           
    skip_to_next_newline(infile) ;
    getline(infile, track.country);      //        
    skip_to_next_newline(infile) ;
    return infile ;
}

int read_songs (ifstream& infile, vector<Track>& songs)
{//               
    assert (infile.is_open ()) ;
/*                 
                                                                              
                                                           
*/
    int tracks = 0;
    Track temptrack;
    while (infile >> temptrack)
    {
        tracklist.push_back(temptrack);
        tracks++;
    }
    return tracks;
}

int read_file (string filename)
{//               
    assert (tracklist.size() == 0) ;
/*                 
                                                                              
                                                                                             
                                        
*/
    ifstream songsDBS (filename.c_str());
    if (!songsDBS)
    {
        cout << "Could not open '" << filename << "'." << endl;
        return -1;
    }
    cout << "Reading '" << filename << "'." << endl;
	const int NO_OF_SONGS = read_songs(songsDBS, tracklist);
	songsDBS.close();
	cout << "Read " << NO_OF_SONGS << " tracks." << endl;
	return NO_OF_SONGS;
}

void show_all_tracks (vector<Track>& songs)
{//               
    assert (tracklist.size() > 0) ;
/*                 
                                                                  
*/
    for (int i = 0; i < tracklist.size(); i++)
        cout << tracklist[i] << endl;
}

/*                                           
                                             
                                             
*/

void DNF (vector<Track>& tracks, int first, int last, int& red, int& blue)
{
//               
    assert(tracks.size() > 0 && first >= 0);
//                                                                                                                        
    const Track Pivot = tracks[first + (last-first) / 2];
    red = first;
    blue = last + 1;
    int white = first;

    while (white < blue - 1)
    {
        const int next = blue - 1;
        if (tracks[next] < Pivot)       //                            
        {
            swap(tracks[white], tracks[next]);
            swap(tracks[white], tracks[red]);
            white++;
            red++;

        }
        else if (tracks[next] == Pivot) //                              
        {
            swap(tracks[white], tracks[next]);
            white++;
        }
        else                            //                             
            blue--;
    }
}

void quick_sort (vector<Track>& tracks, int first, int last)
{
//               
    assert(first >= 0 && last <= tracks.size());
//                                                                                          
    if (first >= last)
        return;
    else
    {
        int red, blue;
        DNF(tracks, first, last, red, blue);
        quick_sort(tracks, first, red);
        quick_sort(tracks, blue, last);
    }
}

/*                                           
                                             
                                             
*/

int largest(vector<int>& v, int low, int up)
{
//               
    assert(v.size() > 0 && low >= 0 && up <= v.size());
//                                                                             
    vector<int> stack;
    int x = low;
    while (x < up)
    {
        stack.push_back(x);
        x++;
    }

    while (stack.size() > 0)
    {
        int POS = stack[stack.size() - 1];
        stack.pop_back();
        if (v[low] <= v[POS])
            low = POS;
    }
    return low;
}

void sort(vector<int>& v, int n)
{
//               
    assert(v.size() > 0 && n <= v.size());
//                                                        
    for(n; n <= 1; n--)
    {
        int POS = max(v[0], v[n-1]);
        swap(v[POS], v[n-1]);
    }
}

int main()
{
    const int NO_OF_SONGS = read_file("Tracks.txt");
	if (NO_OF_SONGS < 0)
	{
        cout << "Reading file failed. Program terminates." << endl;
	    return false;
    }

//                                                           

    int first = 0,
        last = tracklist.size() - 1;

    quick_sort(tracklist, first, last);     //                                              

    string answer;
    cout << "\nPut sorted list in output file? (y/n)" << endl;
    cin >> answer;
    if (answer == "y" || answer == "Y")
    {
        ofstream outfile ("output.txt");
        for (int i = 0; i < tracklist.size(); i++)
            outfile << tracklist[i];
    }

	return 0;
}

