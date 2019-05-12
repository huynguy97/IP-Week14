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
vector<Track> songs;

/*                                                                       
                                
                                                               
                                                                         
                                                                       */
bool operator< (const Length& a, const Length& b)
{
    //              
    assert(true);
    //                                                                                
    int rt_a = a.minutes*60 + a.seconds;
    int rt_b = b.minutes*60 + b.seconds;
    return rt_a < rt_b;
}

bool operator== (const Length& a, const Length& b)
{
    //              
    assert(true);
    //                                                                            
    int rt_a = a.minutes*60 + a.seconds;
    int rt_b = b.minutes*60 + b.seconds;
    return rt_a == rt_b;
}

bool operator!= (const Length& a, const Length& b)
{
    //              
    assert(true);
    //                                                                                
    int rt_a = a.minutes*60 + a.seconds;
    int rt_b = b.minutes*60 + b.seconds;
    return rt_a != rt_b;
}

//                      
bool operator<(const Track& a, const Track& b)
{
    //              
    assert(true);
    //                                                                                                                  
    //                                                   
    if(a.artist >= b.artist)
    {
        if(a.artist == b.artist && a.cd >= b.cd)
        {
            if(a.cd == b.cd && a.year >= b.year)
            {
                if(a.year == b.year && a.track_no >= b.track_no)
                    return false;
            }
        }
    }
    return true;
}

bool operator==(const Track& a, const Track& b)
{
    //              
    assert(true);
    //                                                                                                               
    if(a.artist != b.artist)
        return false;
    if(a.cd != b.cd)
        return false;
    if(a.year != b.year)
        return false;
    if(a.track_no != b.track_no)
        return false;
    return true;
}
/*
                         
                                              
 
                    
                 
                                                                                                                                
                           
 

                                               
 
                    
                 
                                                                                                                            
                            
 
*/
//	                                 
bool operator>(const Track& a, const Track& b)
{
    //              
    assert(true);
    //                                                                                                                  
	return b < a ;
}

bool operator<=(const Track& a, const Track& b)
{
    //              
    assert(true);
    //                                                                                                      
    //                        
	return !(b < a) ;
}

bool operator>=(const Track& a, const Track& b)
{
    //              
    assert(true);
    //                                                                                                     
    //                        
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
    return songs.size();
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

void show_all_tracks (vector<Track>& songs, int no_of_songs)
{//               
    assert (no_of_songs < MAX_NO_OF_SONGS) ;
/*                 
                                                                  
*/
    for (int i = 0 ; i < no_of_songs; i++)
        cout << i+1 << ". " << songs[i] << endl ;
}

/*                                                                       
                                   
                                                                       */

void swap_songs(vector<Track>& songs, int a, int b)
{
    //              
    assert(a >= 0 && b >= 0);
    //                                                                                    
    Track help;
    help = songs[a];
    songs[a] = songs[b];
    songs[b] = help;
}

void dnf (vector<Track>& songs, int first, int last, int& red, int& blue)
{
    //              
    assert(true);
    //                                                                                           
    //                                                                                                           
    //                                                                                                             
    //                                                                                                              
    red = first-1;
    blue = last+1;
    int white = last+1;
    const Track PIVOT = songs[first+(last-first)/2];
    while(red < white-1)
    {
        const int NEXT = white-1;
        if(songs[NEXT] < PIVOT)
        {
            red++;
            swap_songs(songs, red, NEXT);
        }
        else if(songs[NEXT] == PIVOT)
            white--;
        else
        {
            white--;
            blue--;
            swap_songs(songs, NEXT, blue);
        }
    }
}

void quicksort(vector<Track>& songs, int first, int last)
{
    //              
    assert(first >= 0 && last < songs.size());
    //                                                                                                  
    if(first >= last)
        return;
    else
    {
        int red;
        int blue;
        dnf(songs, first, last, red, blue);
        quicksort(songs, first, red);
        quicksort(songs, blue, last);
    }
}

void dnf_2 (vector<Track>& songs, int first, int last, int& red, int& blue)
{
    //              
    assert(true);
    //                                                                                                                 
    //                                                                                                                 
    //                                                                        
    //                                                                                                             
    //                                                                                                              
    red = first-1;
    blue = last+1;
    int white = first-1;
    const Track PIVOT = songs[first+(last-first)/2];
    while(white < blue-1)
    {
        const int NEXT = white+1;
        if(songs[NEXT] < PIVOT)
        {
            white++;
            red++;
            swap_songs(songs, red, NEXT);
        }
        else if(songs[NEXT] == PIVOT)
            white++;
        else
        {
            blue--;
            swap_songs(songs, NEXT, blue);
        }
    }
}

void quicksort_2(vector<Track>& songs, int first, int last)
{
    //              
    assert(first >= 0 && last < songs.size());
    //                                                                                                                        
    if(first >= last)
        return;
    else
    {
        int red;
        int blue;
        dnf_2(songs, first, last, red, blue);
        quicksort_2(songs, first, red);
        quicksort_2(songs, blue, last);
    }
}

void swap_1(vector<int>& v, int a, int b)
{
    //              
    assert(a >= 0 && b >= 0);
    //                                                                                  
    int help;
    help = v[a];
    v[a] = v[b];
    v[b] = help;
}

void show_vector(vector<int> v)
{
    //              
    assert(true);
    //                                                                      
    int length = v.size();
    for(int i = 0; i < length-1; i++)
        cout << v[i] << ", ";
    cout << v[length-1];
}

int largest(vector<int>& v, int low, int up)
{
    //              
    assert(low >= 0 && up >= 0);
    //                                                                            
    vector<int> stacks;
    while(low < up)
    {
        stacks.push_back(low);
        low++;
    }
    int POS = low;
    while(stacks.size() > 0)
    {
        low = stacks[stacks.size()-1];
        stacks.pop_back();
        if(v[low] > v[POS])
            POS = low;
        else
            POS = POS;
    }
    return POS;
}

void sort_1(vector<int>& v, int n)
{
    //              
    assert(n < v.size()+1);
    //                                     
    while(n > 1)
    {
        const int POS = largest (v, 0, n-1);
        swap_1(v, POS, n-1);
        n--;
    }
}

int main()
{
    //                                        
	const int NO_OF_SONGS = read_file ("Tracks.txt");
	if (NO_OF_SONGS < 0)
	{
        cout << "Reading file failed. Program terminates." << endl;
	    return NO_OF_SONGS;
    }
    //      
    quicksort(songs, 0, songs.size());
    //      
    quicksort_2(songs, 0, songs.size()-1);
    show_all_tracks (songs,NO_OF_SONGS) ;
    //      
    vector<int> v = {4,2,6,4,5,4,3,1};
    sort_1(v,v.size());
    show_vector(v);
	return 0;
}

