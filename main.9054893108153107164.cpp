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

enum Assignment {PartOne, PartTwo};

struct Slice
{
    int from;
    int to;
};

struct Length
{
    int minutes;
    int seconds;
};

struct Track
{
    string artist;
    string cd;
    int year;
    int track_no;
    string title;
    string tags;
    Length time;
    string country;
};

vector<Track> songs;
vector<Slice> slices;

//                               
//                      
//                               
bool operator<(const Length& a, const Length& b)
{
    if(a.minutes < b.minutes)
        return true;
    else if(a.minutes == b.minutes)
        return a.seconds < b.seconds;
    return false;
}

bool operator==(const Length& a, const Length& b)
{
    if(a.minutes == b.minutes)
        return a.seconds == b.seconds;
    return false;
}

//                                  
bool operator>(const Length& a, const Length& b)
{
    return b < a;
}

bool operator<=(const Length& a, const Length& b)
{
    return !(b < a);
}

bool operator>=(const Length& a, const Length& b)
{
    return b <= a;
}

bool operator==(const Track& a, const Track& b)
{
    return a.artist == b.artist && a.cd == b.cd && a.track_no == b.track_no;
}

bool operator<(const Track& a, const Track& b)
{
    if(a.artist == b.artist)
        {
            if(a.cd == b.cd)
            {
                if(a.track_no == b.track_no)
                        return false;
                return a.track_no < b.track_no;
            }
            return a.cd < b.cd;
        }
    return a.artist < b.artist;
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

int size(vector<Track>& a)
{
    return static_cast<int>(a.size());
}

//                                                                            
//             
//                                                                            

istream& operator>> ( istream& in, Length& length )
{//               
    assert (true) ;
/*                 
                                                                                                      
*/
    char colon ;
    in >> length.minutes >> colon >> length.seconds ;
    return in ;
}

ostream& operator<< ( ostream& out, const Length length )
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

void skip_to_next_newline ( istream& infile )
{//               
    assert (true) ;
/*                 
                                                                        
*/
    string remains ;
    getline (infile, remains) ;
}

istream& operator>> ( istream& infile, Track& track )
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
ostream& operator<< ( ostream& out, const Track track )
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

int read_songs ( ifstream& infile, vector<Track>& songs )
{//               
    assert (infile.is_open ()) ;
/*                 
                                                                              
                                                           
*/
    int no_of_read_songs = 0 ;
    Slice temp;
    do {
        Track song ;
        infile >> song ;
        if (infile)
            {
                songs.push_back(song);
                no_of_read_songs++;
            }
        if(no_of_read_songs%100 == 0)
            {
                temp = {0, no_of_read_songs-1};
                slices.push_back(temp);
            }
    }
    while (infile);
    return no_of_read_songs ;
}

int read_file ( string filename )
{//               
    assert (size(songs) == 0) ;
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

void show_all_tracks ( vector<Track>& data, int no_of_songs )
{
    //              
    assert (true) ;
    /*               
                                                                  
    */
    for (int i = 0 ; i < no_of_songs; i++)
        cout << i+1 << ". " << songs[i] << endl ;
}

//                                                                            
//                        
//                                                                            

void swap(vector<Track>& songs, int i, int j)
{
    //             
    assert(size(songs) >= 0);
    assert(i >= 0 && j >= 0);
    assert(i <= size(songs) && j <= size(songs));
    //              
    //                                                                         
    //                    
    const Track HELP = songs[i];
    songs[i] = songs[j];
    songs[j] = HELP;
}

void dnf_track_no(vector<Track>& songs, int& red, int& blue,
                  int first, int last, Assignment part)
{
    //             
    assert(size(songs) >= 0);
    assert(first >= 0 && last >= 0);
    assert(first <= size(songs) && last <= size(songs));
    //              
    //                                                                                      
    //                                    
    //                                                                                   
    //                                                                                     
    //                                                                                        
    //                                                                                           
    //                                                                        

    red = first - 1;
    blue = last + 1;
    const Track PIVOT = songs[first+(last-first)/2];
    if(part == PartOne)
    {
        int white = last + 1;
        while(red < white - 1)
        {
            const int NEXT = white - 1;
            if(songs[NEXT] < PIVOT)
            {
                red++;
                swap(songs, red, NEXT);
            }
            else if(songs[NEXT] == PIVOT)
                white--;
            else
            {
                white--;
                blue--;
                swap(songs, NEXT, blue);
            }
        }
    }
    else
    {
        int white = first - 1;
        while(blue > white + 1)
        {
            const int NEXT = white + 1;
            if(songs[NEXT] > PIVOT)
            {
                blue--;
                swap(songs, NEXT, blue);
            }
            else if(songs[NEXT] == PIVOT)
                white++;
            else
            {
                white++;
                red++;
                swap(songs, red, NEXT);
            }
        }
    }
}

void quicksort_track_no(vector<Track>& songs, int first, int last, Assignment part)
{
    //    
    assert(size(songs) >= 0);
    assert(first >= 0);
    assert(last >= -1);
    assert(last < size(songs) && first < size(songs));
    //     
    //                                                                                 
    //                                                                  
    //                                                              
    //                                                                        

    if(first >= last)
        return;
    else
    {
        int red, blue;
        dnf_track_no(songs, red, blue, first, last, part);
        quicksort_track_no(songs, first, red, part);
        quicksort_track_no(songs, blue, last, part);
    }
}

void dnf_time(vector<Track>& songs, int& red, int& blue, int first, int last, Assignment part)
{
    //             
    assert(size(songs) >= 0);
    assert(first >= 0 && last >= 0);
    assert(size(songs) >= first && size(songs) >= last);
    //              
    //                                                                                      
    //                                    
    //                                                                                   
    //                                                                            
    //                                                                                
    //                                                                                           
    //                                                                        

    red = first - 1;
    blue = last + 1;
    const Track PIVOT = songs[first+(last-first)/2];
    if(part == PartOne)
    {
        int white = last + 1;
        while(red < white - 1)
        {
            const int NEXT = white - 1;
            if(songs[NEXT].time < PIVOT.time)
            {
                red++;
                swap(songs, red, NEXT);
            }
            else if(songs[NEXT].time == PIVOT.time)
                white--;
            else
            {
                white--;
                blue--;
                swap(songs, NEXT, blue);
            }
        }
    }
    else
    {
        int white = first - 1;
        while(blue > white + 1)
        {
            const int NEXT = white + 1;
            if(songs[NEXT].time > PIVOT.time)
            {
                blue--;
                swap(songs, NEXT, blue);
            }
            else if(songs[NEXT].time == PIVOT.time)
                white++;
            else
            {
                white++;
                red++;
                swap(songs, red, NEXT);
            }
        }
    }
}

void quicksort_time(vector<Track>& songs, int first, int last, Assignment part)
{
    //    
    assert(size(songs) >= 0);
    assert(first >= 0 && last >= 0);
    assert(last < size(songs));
    assert(first <= size(songs));
    //     
    //                                                                                 
    //                                                                               
    //                                                                         
    //                                

    if(first >= last)
        return;
    else
    {
        int red, blue;
        dnf_time(songs, red, blue, first, last, part);
        quicksort_time(songs, first, red, part);
        quicksort_time(songs, blue, last, part);
    }
}

int vectorsize_int(vector<int>& v)
{
    return static_cast<int>(v.size());
}
void swap(vector<int>& v, int i, int j)
{
    //             
    assert(vectorsize_int(v) >= 0);
    assert(i >= 0 && j >= 0);
    assert(vectorsize_int(v) >= i && vectorsize_int(v) >= j);
    //               
    //                                                     
    const int HELP = v[i];
    v[i]=v[j];
    v[j]=HELP;
}

int largest(vector<int>& v, int up)
{
    //             
    assert(vectorsize_int(v) >= 0);
    assert(vectorsize_int(v) >= up);
    //               
    //                                                            

    struct Largest {int pos; int value;};
    Largest large = {up, v[up]};
    int low = up - 1;
    while(low >= 0)
    {
        if (v[low] > large.value)
        large = {low, v[low]};
        low--;
    }
    return large.pos;
}

void sort(vector<int>& v, int n)
{
    //              
    assert(vectorsize_int(v) >= 0);
    assert(n >= 0);
    assert(vectorsize_int(v) + 1 >= n);
    //               
    //                                             

    Slice slice = {0, n-1};
    while(slice.to > 0)
    {
        int index_largest = largest(v, slice.to);
        swap(v, index_largest, slice.to);
        slice.to--;
    }
}

int main()
{
    //          
    const int NO_OF_SONGS = read_file("Tracks.txt");
    if(NO_OF_SONGS < 0)
    {
        cout << "boooooo" << endl;
        return NO_OF_SONGS;
    }
    cout << NO_OF_SONGS << endl;
    //             
    //                                                                                
    cout << "PART 1 or 2:\n";
    quicksort_track_no(songs, 0, size(songs)-1, PartTwo);
    cout << "Tracks sorted by artist -> album -> track number: \n";
    //                                    

    quicksort_time(songs, 0, size(songs)-1, PartTwo);
    cout << "Tracks sorted by time: \n";
    //                                    

    //       
    vector<int> test = {14,12,15,16,88,3,753,9,1,6,55,31,65,78};
    sort(test, vectorsize_int(test));
    cout << "PART 3:\nSorted vector is: ";
    for(int i = 0; i < vectorsize_int(test)-1; i++)
        cout << test[i] << ", ";
    cout << test[vectorsize_int(test)-1] << endl;
    return 0;
}

