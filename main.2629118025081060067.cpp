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

vector<Track> songs;

/*                                                                             
                                           
                                                       
                                                                             */

bool operator< (const Length& a, const Length& b)
{
    if (a.minutes < b.minutes)
        return true;
    if (a.minutes == b.minutes && a.seconds < b.seconds)
        return true;
    return false;
}

bool operator== (const Length& a, const Length& b)
{
    return a.minutes == b.minutes && a.seconds == b.seconds;
}

bool compare_strings(const string& a, const string& b)
{//                
    assert (true);
//                 
//                                  
    if (a.compare(b) == 0)
        return false;

    char letter_a = a[0];
    char letter_b = b[0];
    int i = 1;

    while (letter_a == letter_b)
    {
        letter_a = a[i];
        letter_b = b[i];
        i++;
    }
    return a<b ;
}

bool operator== (const Track& a, const Track& b)
{
    if (a.artist == b.artist && a.cd == b.cd && a.year == b.year && a.track_no == b.track_no)
        return true;
    return false;
}

bool operator<(const Track& a, const Track& b)
{
    /*
                                             
                    
                                                            
                    
                                                                
                    
                                                                                            
                    
                 
    */

    if (a.time < b.time)
        return true;
    if (a.time == b.time && compare_strings(a.artist, b.artist) )
        return true;
    if (a.time == b.time && a.artist == b.artist && compare_strings(a.cd, b.cd))
        return true;
    if (a.time == b.time && a.artist == b.artist && a.cd == b.cd && a.year < b.year)
        return true;
    if (a.time == b.time && a.artist == b.artist && a.cd == b.cd && a.year == b.year && a.track_no < b.track_no)
        return true;
    return false;
}

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

/*                                                                             
                            
                                                                             */

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
        {
            songs.push_back(song);
            no_of_read_songs++;
        }
    }
    while (infile);
    return no_of_read_songs ;
}

int read_file (ifstream& songsDBS)
{//               
    assert (songs.size() == 0) ;
/*                 
                                                                              
                                                                                             
                                        
*/
    string filename;
    cout << "Please enter the filename of the song database you would like to order: ";
    cin  >> filename;
    songsDBS.open(filename.c_str());
    if (!songsDBS.is_open())
    {
        cout << "File could not be opened" << endl;
        return -1;
    }
	const int NO_OF_SONGS = read_songs (songsDBS);
	songsDBS.close();
	return NO_OF_SONGS;
}

void show_tracks (vector<Track>& songs)
{//               
    assert (true);
/*                 
                                                                  
*/
    for (int i = 0 ; i < songs.size(); i++)
        cout << i+1 << ". " << songs[i] << endl ;
}

/*                                                                             
                           
                                                                             */

void swap (vector<Track>& songs, int first, int last)
{//               
    assert(first < songs.size() && last < songs.size());
/*                 
                                                                              
*/
    const Track help = songs[first];
    songs[first]     = songs[last];
    songs[last]      = help;
}

void dnf (vector<Track>& songs, int first, int last, int& red, int& blue)
{//               
    assert(first < songs.size() && last < songs.size());
/*                 
                                                                                 
*/
    red       = first-1;
    blue      = last+1;
    int white = last+1;

    const Track pivot = songs[first + (last-first)/2];

    while (red < white-1)
    {
        int next = white-1;
        if (songs[next] < pivot)
        {
            red++;
            swap(songs, red, next);
        }
        else if (songs[next] == pivot)
            white--;
        else
        {
            white--;
            blue--;
            swap(songs, next, blue);
        }
    }
}

void quicksort (vector<Track>& songs, int first, int last)
{//               
    assert(first < songs.size() && last+1 <= songs.size());
/*                 
                                                                        
                                   
*/
    if (first >= last)
        return;
    else
    {
        int red, blue;
        dnf(songs, first, last, red, blue);
        quicksort(songs, first, red);
        quicksort(songs, blue, last);
    }
}

/*                                                                             
                      
                                                                             */

void dnf_adjusted (vector<Track>& songs, int first, int last, int& red, int& blue)
{//               
    assert(first < songs.size() && last < songs.size());
/*                 
                                                                                 
                                                               
*/
    red       = first-1;
    blue      = last+1;
    int white = first-1;

    const Track pivot = songs[first + (last-first)/2];

    while (blue > white+1)
    {
        int next = white+1;
        if (songs[next] < pivot)
        {
            red++;
            white++;
            swap(songs, red, next);
        }
        else if (songs[next] == pivot)
            white++;
        else
        {
            blue--;
            swap(songs, next, blue);
        }
    }
}

void quicksort_adjusted (vector<Track>& songs, int first, int last)
{//               
    assert(first < songs.size() && last+1 <= songs.size());
/*                 
                                                                        
                                                                       
*/
    if (first >= last)
        return;
    else
    {
        int red, blue;
        dnf_adjusted(songs, first, last, red, blue);
        quicksort_adjusted(songs, first, red);
        quicksort_adjusted(songs, blue, last);
    }
}

/*                                                                             
                                 
                                                                             */

int largest (vector<Track>& songs, int low, int up)
{//               
    assert( up < songs.size() && low <= up );
/*                 
                                                                    
                                  
*/
    vector<Track> stack;
    while (low <= up)
    {
        stack.push_back(songs[low]);
        low++;
    }

    int LARGEST = stack.size()-1;
    int ATTEMPT;

    while (stack.size() > 0)
    {
        ATTEMPT = stack.size()-1;
        if (stack[ATTEMPT] > stack[LARGEST])
            LARGEST = ATTEMPT;
        stack.pop_back();
    }
    return LARGEST;
}

void sort (vector<Track>& songs, int n)
{//               
    assert (n <= songs.size());
/*                 
                                                                                            
*/
    vector<Track> stacks;
    int LARGEST;
    int COUNTER = 0;

    while (COUNTER < n)
    {
        stacks.push_back(songs[COUNTER]);
        COUNTER++;
    }
    while (stacks.size() > 0)
    {
        LARGEST = largest(stacks, 0, stacks.size()-1);
        swap(stacks, LARGEST, stacks.size()-1);
        swap(songs, LARGEST, stacks.size()-1);
        stacks.pop_back();
    }
}

int main()
{
    cout << "PROGRAM TO READ AND ORDER DATABASES OF SONGS." << endl << endl;
    ifstream input;
    read_file(input);

    int number;
    cout << "Would you like to use quicksort (1), adjusted quicksort (2) or sort (3) to order the input: ";
    cin  >> number;

    switch(number)
    {
        case 1:  quicksort(songs, 0, songs.size()-1);          break;
        case 2:  quicksort_adjusted(songs, 0, songs.size()-1); break;
        case 3:  sort(songs, songs.size());                    break;

        default: cout << "Incorrect input!" << endl;           break;
    }
    show_tracks(songs);
    return 0;
}

