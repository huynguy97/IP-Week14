#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>
#define NDEBUG

using namespace std;

//                                       
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

vector<Track> songs;              //                                     
int global_operation_counter = 0;

bool operator<(const Length& a, const Length& b)
{
    if (a.minutes == b.minutes)
        return a.seconds < b.seconds;
    else return a.minutes < b.minutes;
}

bool operator==(const Length& a, const Length& b)
{
    if (a.minutes == b.minutes)
        return a.seconds == b.seconds;
    else return a.minutes == b.minutes;
}

//	                                  
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
    global_operation_counter++;
    /*
                             
                          
                                 
                                               
                                        
                                
                                    
    */
    if (a.time == b.time)
        if (a.artist == b.artist)
            if (a.title == b.title)
                return a.cd < b.cd;
            else return a.title < b.title;
        else return a.artist < b.artist;
    else return a.time < b.time;
}

bool operator==(const Track& a, const Track& b)
{
    global_operation_counter++;
    /*
                             
                         
                                 
                                                
                                         
                                 
                                     
    */
    if (a.time == b.time)
        if (a.artist == b.artist)
            if (a.title == b.title)
                return a.cd == b.cd;
            else return a.title == b.title;
        else return a.artist == b.artist;
    else return a.time == b.time;
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
            no_of_read_songs++;
        }
             //                                                                                       
    }
    while (infile);
    return no_of_read_songs ;
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
    //                                                
	const int NO_OF_SONGS = read_songs (songsDBS, songs);
	songsDBS.close();
	//                                                      
	return NO_OF_SONGS;
}

void show_all_tracks (vector<Track> songs, int no_of_songs)
{//               
    //                                        
/*                 
                                                                  
*/
    for (int i = 0 ; i < no_of_songs; i++)
        cout << i+1 << ". " << songs[i].artist << "," << songs[i].cd << "," << songs[i].year << "," << songs[i].track_no << "," << songs[i].title << "," << songs[i].tags << "," << songs[i].time << "," << songs[i].country << "," << endl;
}

void display_operations()
{//	              
	assert(true);
//	               
//                                                                                            
    int remainder = global_operation_counter;
    while (remainder > 100000)
    {
        cout << "*";
        remainder -= 100000;
    }
    if (remainder > 0)
        cout << ".";
    cout << endl;
}

void display_vector(vector<Track>& data)
{   //               
    assert(true);
    //                
    /*
                                                                                                                   
    */
    for (int i = 0; i < data.size(); i++)
    {
        cout << data[i];
    }
}

void _swap(vector<Track>& data, int a, int b)
{   //               
    assert(a < data.size() && b < data.size());
    //                
    /*
                                                                                    
    */
    Track temp_a = data[a];
    data[a] = data[b];
    data[b] = temp_a;
}

void dnf (vector<Track>& data, int first, int last, int& red, int& blue)
{   //     
    assert(first >= 0);
    //                                                  
    red = first - 1;                    //               
    blue = last + 1;                    //                 
    int white = last + 1;               //                  
    const Track PIVOT = data[first + (last - first) / 2];
    while (red < white - 1)             //                 
    {
        const int NEXT = white - 1;     //            
        if (data[NEXT] < PIVOT)         //               
        {
            red++;                      //                       
            _swap(data, red, NEXT);
        }
        else if (data[NEXT] == PIVOT)   //                 
            white--;                    //                      
        else                            //                
        {
            white--;
            blue--;                     //                     
            _swap(data, NEXT, blue);
        }
    }
}

void dnf_v2 (vector<Track>& data, int first, int last, int& red, int& blue)
{   //     
    assert(first >= 0);
    //                                                  
    red = first - 1;
    blue = last + 1;
    int white = first - 1;
    const Track PIVOT = data[first + (last - first) / 2];
    while (white < blue - 1)
    {
        const int NEXT = blue - 1;
        if (data[NEXT] < PIVOT)
        {
            red++;
            white++;
            _swap(data, red, white);
            _swap(data, red, NEXT);
        }
        else if (data[NEXT] == PIVOT)
        {
            white++;
            _swap(data, NEXT, white);
        }
        else
        {
            blue--;
        }
    }
}

void quicksort (vector<Track>& data, int first, int last)
{   //     
    assert (0 <= first);
    //                                           
    if (first >= last)
        return;
    else
    {
        int red, blue;
        dnf_v2(data, first, last, red, blue);
        quicksort(data, first, red);
        quicksort(data, blue, last);
    }
}

int largest_recursive (vector<Track>& v, int low, int up)
{
    if (low >= up)
        return low;
    else
    {
        const int POS = largest_recursive(v, low+1, up);
        if (v[low] > v[POS])
            return low;
        else
            return POS;
    }
}

void sort_recursive (vector<Track>& v, int n)
{
    if (n > 1)
    {
        const int POS = largest_recursive(v, 0, n-1);
        _swap(v, POS, n-1);
        sort_recursive(v, n-1);
    }
}

int largest_iterative (vector<Track>& v, int low, int up)
{
    int j = low;
    for (int i = low; i <= up; i++)
    {
        if (v[j] < v[i])
        {
            j = i;
        }
    }
    return j;
}

void sort_iterative (vector<Track>& v, int n)
{
    while (n > 1)
    {
        const int POS = largest_iterative(v, 0, n-1);
        _swap(v, POS, n-1);
        n--;
    }
}

int main()
{
    const int NO_OF_SONGS = read_file("Tracks.txt");

    quicksort(songs, 0, NO_OF_SONGS - 1);
    //                                   
    //                                   
    display_vector(songs); //                                               
    return 0;
}

