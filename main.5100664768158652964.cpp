/*
                                              
*/
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
struct Length{
	int minutes;							//               
	int seconds;							//                 
};
struct Track{
	string artist;                          //            
	string cd;                              //         
	int    year;                            //                   
	int    track_no;						//             
	string title;                           //            
	string tags;                            //                            
	Length time;							//             
	string country;                         //                                         
};

struct Dnf_indices{
    int white;
    int blue;
};

vector<Track> songs ;              //                                     
bool cd_length; //                                                            

bool operator< (const Length& a, const Length& b) {
    if (a.minutes != b.minutes) return a.minutes < b.minutes;
    if (a.seconds != b.seconds) return a.seconds < b.seconds;
    return false;
}

bool operator== (const Length& a, const Length& b) {
    return a.minutes == b.minutes && a.seconds == b.seconds;
}

//	                                  
bool operator!= (const Length& a, const Length& b) {
    return !(a == b);
}

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

//                            
//                                                                   
//                                                    

bool operator<(const Track& a, const Track& b)
{
    //               
    assert(true);
    //                                                                                                     
    if (cd_length){
        if (a.time != b.time) return a.time < b.time;
        switch((a.artist).compare(b.artist)){
            case -1:    return true; break;
            case 1:     return false; break;
            default:    break;
        }
        switch((a.title).compare(b.title)){
            case -1:    return true; break;
            case 1:     return false; break;
            default:    break;
        }
        switch((a.cd).compare(b.cd)){
            case -1:    return true; break;
            case 1:     return false; break;
            default:    break;
        }
    } else {
        switch((a.artist).compare(b.artist)){
            case -1:    return true; break;
            case 1:     return false; break;
            default:    break;
        }
        switch((a.cd).compare(b.cd)){
            case -1:    return true; break;
            case 1:     return false; break;
            default:    break;
        }
        if (a.year != b.year) return a.year < b.year;
        if (a.track_no != b.track_no) return a.track_no < b.track_no;
    }
    return false;
}

bool operator==(const Track& a, const Track& b)
{
    //               
    assert(true);
    //                                                           
    if (cd_length) {
        return (a.artist == b.artist && a.cd == b.cd && a.title == b.title
                && a.time.minutes == b.time.minutes && a.time.seconds == b.time.seconds);
    } else {
        return (a.artist == b.artist && a.cd == b.cd
                && a.year == b.year && a.track_no == b.track_no);
    }
}

//	                                 
bool operator!=(const Track& a, const Track& b)
{
	return !(a == b) ;
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
        if (infile) {
            no_of_read_songs++;
            songs.push_back(song);
        }
    } while (infile);
    return no_of_read_songs ;
}

int read_file (string filename, vector<Track>& songs)
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
	cout << " Read " << NO_OF_SONGS << " tracks." << endl << endl;
	return NO_OF_SONGS;
}

void show_all_tracks (vector<Track>& songs)
{//               
    assert (true) ;
/*                 
                                                                  
*/
    for (unsigned int i = 0 ; i < songs.size(); i++)
        cout << i+1 << ". " << songs[i] << endl ;
}

//                                                             

void swap_songs(vector<Track>& songs, int i, int j){
    //                
    assert(i >= 0 && i < static_cast<int>(songs.size())
           && j >= 0 && j < static_cast<int>(songs.size()));
    //                                               
    Track temp = songs[i];
    songs[i] = songs[j];
    songs[j] = temp;
}

Dnf_indices dnf_rowb(vector<Track>& songs, int lower, int upper){
    //                
    assert(lower >= 0 && lower < static_cast<int>(songs.size())
           && upper >= 0 && upper < static_cast<int>(songs.size())
           && lower <= upper);
    //                                                                                              
    //                                                                           
    Track pivot = songs[(lower+upper)/2];
    int orange = lower;
    int white = upper+1;
    int blue = upper+1;
    while (white > orange){
        if (songs[white-1] == pivot){
            white -= 1;
        } else if (songs[white-1] < pivot){
            swap_songs(songs, white-1, orange);
            orange += 1;
        } else {
            swap_songs(songs, white-1, blue-1);
            blue -= 1;
            white -= 1;
        }
    }
    return {white-1, blue};
}

Dnf_indices dnf_rwob(vector<Track>& songs, int lower, int upper){
    //                
    assert(lower >= 0 && lower < static_cast<int>(songs.size())
           && upper >= 0 && upper < static_cast<int>(songs.size())
           && lower <= upper);
    //                                                                                              
    //                                                                        
    Track pivot = songs[(lower+upper)/2];
    int red = lower-1;
    int white = lower-1;
    int orange = upper;
    while (white < orange){
        if (songs[white+1] == pivot){
            white += 1;
        } else if (songs[white+1] < pivot){
            swap_songs(songs, white+1, red+1);
            red += 1;
            white += 1;
        } else {
            swap_songs(songs, white+1, orange);
            orange -= 1;
        }
    }
    return {red, white+1};
}

void quick_sort(vector<Track>& songs, int lower, int upper, bool mode){
    //                
    assert(lower >= 0 && lower < static_cast<int>(songs.size())
           && upper >= 0 && upper < static_cast<int>(songs.size()));
    //                                                     
    if (lower >= upper) return;
    Dnf_indices dnf;
    if (mode){
        dnf = dnf_rowb(songs, lower, upper);
    } else dnf = dnf_rwob(songs, lower, upper);
    quick_sort(songs, lower, dnf.white, mode);
    quick_sort(songs, dnf.blue, upper, mode);
}

//                                                    

void swap(vector<int>& v, int i, int j){
    int temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int largest_recursion(vector<int>& v, int low, int up){
    if ( low >= up) return low ;
    else { const int POS = largest_recursion(v, low+1, up) ;
    if (v [low] > v [POS])return low ;
    else return POS ;
    }
}

int largest_iteration(vector<int>& v, int low, int up){
    vector<int> v_stack;
    int output;
    int POS;
    while(low < up){
        v_stack.push_back(low);
        low += 1;
    }
    output = low;
    while (v_stack.size() > 0){
        POS = v_stack[v_stack.size()-1];
        v_stack.pop_back();
        if (v[output] > v[POS]){
            //                
        } else output = POS;
    }
    return output;
}

void sort_recursion(vector<int>& v, int n){
    if (n > 1){
        const int POS = largest_recursion(v, 0, n-1) ;
        swap(v, POS, n-1) ;
        sort_recursion(v, n-1) ;
    }
}

void sort_iteration(vector<int>& v, int n){
    int POS;
    while (n > 1){
        POS = largest_iteration(v, 0, n-1) ;
        swap(v, POS, n-1) ;
        n -= 1;
    }
}

//                                                 

int main()
{
    vector<Track> songs;
	const int NO_OF_SONGS = read_file ("Tracks.txt", songs);
	if (NO_OF_SONGS < 0){
	    cout << "Reading file failed. Program terminates." << endl;
	    return NO_OF_SONGS;
    }

    cout << "Sorting tracks by album with quick sort ROWB" << endl;
    cd_length = false;
    quick_sort(songs, 0, static_cast<int>(songs.size()-1), true);
    cout << "Tracks sorted." << endl;
    //                       

    cout << "Sorting tracks by length with quick sort RWOB" << endl;
    cd_length = true;
    quick_sort(songs, 0, static_cast<int>(songs.size()-1), false);
    cout << "Tracks sorted." << endl;
    //                       
	return 0;
}

