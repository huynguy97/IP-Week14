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
Track songs [MAX_NO_OF_SONGS];              //                                     
vector<Track> tracklist;
int operatorcount=0;

bool operator<(const Length& a, const Length& b)
{
    if(a.minutes<b.minutes)
        return true;
    else if(a.minutes==b.minutes && a.seconds<b.seconds)
        return true;
    else
        return false;
}

bool operator==(const Length& a, const Length& b)
{
    if(a.minutes==b.minutes && a.seconds==b.seconds)
        return true;
    else
        return false;
}

bool operator<(const Track& a, const Track& b)
{
    /*                                                      */
    if(a.artist == b.artist)
    {
        if(a.cd == b.cd)
        {
            if(a.year == b.year)
                return a.track_no < b.track_no;
            else
                return a.year < b.year;
        }
        else
            return a.cd < b.cd;
    }
    else
        return a.artist<b.artist;
}

bool operator==(const Track& a, const Track& b)
{
    //                                                
    if(a.artist == b.artist && a.cd==b.cd && a.year==b.year)
                return a.track_no == b.track_no;
    else
        return false;
}

//
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

void fill_tracklist()
{//               
    assert(true);
/*                                                                      
*/
    int i=0;
    while(songs[i].artist[0]!=NULL)
    {
        tracklist.push_back(songs[i]);
        i++;
    }
}

void show_tracklist()
{//               
    assert(true);
/*                                                                 
*/
    for(int i=0; i<tracklist.size(); i++)
    {
        cout << "Track no. " << i+1 << endl;
        cout << tracklist[i] << endl;
    }
}

//                                                                           
int read_songs (ifstream& infile)
{//               
    assert (infile.is_open ()) ;
/*                 
                                                                              
                                                           
*/
    int no_of_read_songs = 0 ;
    do {
        Track song ;
        infile >> song ;
        if (infile)
            tracklist.push_back(song);
    }
    while (infile && no_of_read_songs < MAX_NO_OF_SONGS);
    return tracklist.size() ;
}

int read_file (string filename)
{//               
    //                            
/*                 
                                                                              
                                                                                             
                                        
*/
    ifstream songsDBS (filename.c_str());
    if (!songsDBS)
    {
        cout << "Could not open '" << filename << "'." << endl;
        return -1;
    }
    cout << "Reading '" << filename << "'." << endl;
	const int NO_OF_SONGS = read_songs (songsDBS);
	songsDBS.close();
	//                                                      
	return NO_OF_SONGS;
}

//                                                                           
void show_all_tracks (Track songs [MAX_NO_OF_SONGS], int no_of_songs)
{//               
    assert (no_of_songs < MAX_NO_OF_SONGS) ;
/*                 
                                                                  
*/
    for (int i = 0 ; i < no_of_songs; i++)
        cout << i+1 << ". " << songs[i] << endl ;
}

void swaptracks(int a, int b)
{//               
    assert(a>=0 && a<tracklist.size() && b>=0 && b<tracklist.size());

/*                                                                  
*/
    Track HELP = tracklist[a];
    tracklist[a]=tracklist[b];
    tracklist[b]=HELP;
}

bool tracktimesmaller(Track a, Track b)
{//               
    assert(true);
/*                                                                                                                                        
*/
    if(a.time == b.time)
    {
        if(a.artist == b.artist)
        {
            if(a.title == b.title)
                return a.cd <= b.cd;
            else
                return a.title < b.title;
        }
        else
            return a.artist < b.artist;
    }
    else
        return a.time<b.time;
}

bool tracktimeequal(Track a, Track b)
{//               
    assert(true);
/*                                                                     
*/
    return a.time==b.time;
}

void dnf_tracktime(int first, int last, int& red, int& blue)
{//                                                                                               
    assert(first>=0 && last<tracklist.size());
/*                                                                                      
*/
    //                                                           
    if(first==last)
        return;
    red = first-1;
    blue= last+1;
    int white = last+1;
    const Track PIVOT = tracklist[first+(last-first)/2];
    while(red<white-1)
    {
        const int NEXT = white-1;
        if(tracktimesmaller(tracklist[NEXT], PIVOT))
        {
            red++;
            swaptracks(red, NEXT);
        }
        else if(tracktimeequal(tracklist[NEXT], PIVOT))
            white--;
        else
        {
            white--; blue--;
            swaptracks(NEXT, blue);
        }
    }
    //                                                                                            
}

void quicksort_tracktime(int first, int last)
{//                                                          
    assert(first>=0 && last<tracklist.size());
/*                                                                                     
*/
    assert(0<=first && last<tracklist.size());

    if(first>=last)
        return;
    else
    {
        int red, blue;
        dnf_tracktime(first, last, red, blue);
        //                                                                   
        if(red>=first)
            quicksort_tracktime(first, red);
        //                                                                   
        if(blue<=last)
            quicksort_tracktime(blue, last);
    }
}

void dnf_reg(int first, int last, int& red, int& blue)
{//                                                                                               
    assert(first>=0 && last<tracklist.size());
/*                                                                                                        
*/
    //                                                           
    if(first==last)
        return;
    red = first-1;
    blue= last+1;
    int white = last+1;
    const Track PIVOT = tracklist[first+(last-first)/2];
    while(red<white-1)
    {
        const int NEXT = white-1;
        if(tracklist[NEXT]<PIVOT)
        {
            red++;
            swaptracks(red, NEXT);
        }
        else if(tracklist[NEXT]==PIVOT)
            white--;
        else
        {
            white--; blue--;
            swaptracks(NEXT, blue);
        }
    }
    //                                                                                            
}

void quicksort_reg(int first, int last)
{//                                                          
    assert(first>=0 && last<tracklist.size());
/*                                                                                     
*/
    assert(0<=first && last<tracklist.size());

    if(first>=last)
        return;
    else
    {
        int red, blue;
        dnf_reg(first, last, red, blue);
        //                                                                   
        if(red>=first)
            quicksort_reg(first, red);
        //                                                                   
        if(blue<=last)
            quicksort_reg(blue, last);
    }
}

void dnf2(int first, int last, int& red, int& blue)
{   //              
    assert(true);
    //                                                                                                        
    if(first==last)
        return;
    red = first-1;
    blue= last+1;
    int white = first-1;
    const Track PIVOT = tracklist[first+(last-first)/2];
    while(blue>white+1)
    {
        const int NEXT = white+1;
        if(tracklist[NEXT]<PIVOT)
        {
            white++;
            red++;
            swaptracks(red, NEXT);
        }
        else if(tracklist[NEXT]==PIVOT)
            white++;
        else
        {
            blue--;
            swaptracks(NEXT, blue);
        }
    }
}

void quicksort2(int first, int last)
{   //              
    assert(0<=first && last<tracklist.size());
    //                                                                                      
    if(first>=last)
        return;
    else
    {
        int red, blue;
        dnf2(first, last, red, blue);
       //                                                                    
        if(red>=first)
            quicksort2(first, red);
      //                                                                     
        if(blue<=last)
            quicksort2(blue, last);
    }
}

bool check_if_sorted_reg()
{//               
    assert(true);
/*                                                                                             
*/
    for(int c=0; c<tracklist.size()-1; c++)
        if(tracklist[c]>tracklist[c+1])
            return false;
    return true;
}

bool check_if_sorted_tracktime()
{//               
    assert(true);
/*                                                                                    
*/
    for(int c=0; c<tracklist.size()-1; c++)
        if(tracktimesmaller(tracklist[c+1], tracklist[c]) && !tracktimeequal(tracklist[c], tracklist[c+1]))
            {   cout << "Track " << c+1 << " is larger than " << c << endl;
                return false;}
    return true;
}

void sort_swap(vector<Track>& v, int a, int b)
{//               
    assert(true);
/*                                                                                                                                                          
                                                                                                                         
*/
    Track HELP = v[a];
    v[a]=v[b];
    v[b]=HELP;
}

int largest(vector<Track>& v, int low, int up)
{//               
    assert(true);
/*                                                                                             
*/
    int current=low;
    while(low<up)
    {
        if(v[low]>v[current])
            current=low;
        low++;
    }
    return current;
}

void sort(vector<Track>& v, int n)
{//               
    assert(true);
/*                                                                                                                                                 
                                               
*/
    while(n>1)
    {
        int POS=largest(v, 0, n-1);
        sort_swap(v, POS, n-1);
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
    cout << "Tracklist contains " << tracklist.size() << " elements" << endl << endl;

    cout << "Sorting tracklist by artist, cd and tracknr..." << endl;
    quicksort_reg(0, tracklist.size()-1);
    //                 
    if(check_if_sorted_reg())
        cout << "Tracklist sorted by regular parameters" << endl;
    else
        cout << "Tracklist not sorted successfully" << endl;

    cout << endl;

    cout << "Sorting tracklist by time..." << endl;
    quicksort_tracktime(0, tracklist.size()-1);
    //                 
    if(check_if_sorted_tracktime())
        cout << "Tracklist sorted by time" << endl;
    else
        cout << "Tracklist not sorted successfully" << endl;

    cout << endl;

    cout << "Sorting tracklist by artist, cd and tracknr but with moved blocks..." << endl;
    quicksort2(0, tracklist.size()-1);
    //                 
    if(check_if_sorted_reg())
        cout << "Tracklist sorted by regular parameters" << endl;
    else
        cout << "Tracklist not sorted successfully" << endl;
    return 0;
}

