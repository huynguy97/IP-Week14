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

vector<Track> songs;
int comp_count = 0;

int minimum (int a, int b){
    if (a <= b) {
        return a;
    }
    return b;
}

int maximum (int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}

int size(vector<Track> vect) {
    return static_cast<int>(vect.size());
}

bool operator< (const Length& a, const Length& b ){
    if (a.minutes < b.minutes) {
        return true;
    } else if (a.minutes == b.minutes) {
        if (a.seconds < b.seconds) {
            return true;
        } else return false;
    } else return false;
}

bool operator== (const Length& a, const Length& b) {
    return a.minutes == b.minutes && a.seconds == b.seconds;
}

bool operator<(const Track& a, const Track& b)
{
    comp_count = comp_count + 1;
    if (a.artist < b.artist) {
        return true;
    } else if (a.artist == b.artist) {
        if (a.cd < b.cd) {
            return true;
        } else if (a.cd == b.cd) {
            if (a.track_no < b.track_no) {
                return true;
            } else if (a.track_no == b.track_no) {
                return false;
                } else return false;
            } else return false;
        } else return false;
}

bool operator==(const Track& a, const Track& b)
{   comp_count = comp_count + 1;
    return a.time == b.time && a.artist == b.artist && a.title == b.title && a.cd == b.cd ;
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
            songs.push_back(song);
            no_of_read_songs = no_of_read_songs + 1;
    }
    while (infile);
    return no_of_read_songs-1 ;
}

int read_file (string filename)
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

void show_all_tracks (vector<Track> songs, int no_of_songs)
{//               
    assert (true) ;
/*                 
                                                                  
*/
    for (int i = 0 ; i < no_of_songs; i++)
        cout << i+1 << ". " << songs[i] << endl ;
}

struct Slice
{
	int from ; 	//             
	int to ; 	//           
} ;

Slice mkSlice (int from, int to)
{//	              
	assert (0 <= from && from <= to);
/*                 
                                              
*/	Slice s = { from, to } ;
	return s ;
}

bool valid_slice (Slice s)
{//               
    assert (true) ;
/*                 
                                                                                      
*/
	return 0 <= s.from && s.from <= s.to ;
}

//                                                                                          

bool is_sorted (vector<Track>& data, Slice s)
{//	              
	assert (valid_slice(s)) ;	//                           
//	               
//	                 	                                
//						                                
//						   
//						                            
	bool sorted = true ;
	for (int i = s.from; i < s.to && sorted; i++)
		if (data[i] > data[i+1])
			sorted = false ;
	return sorted ;
}

int find_position (vector<Track>& data, Slice s, Track y )
{//	              
	assert (valid_slice(s) && is_sorted(data,s)) ;    //                           
//	                                          
	for ( int i = s.from ; i <= s.to ; i++ )
		if ( y <= data [i] )
			return i ;
	return s.to+1;
}

void shift_right (vector<Track>& data, Slice s )
{//	              
	assert (valid_slice (s)) ;	//                               
//	                               	  	                
//			    	               	  	                  
//						   
//			    	             		  	              
	for ( int i = s.to+1 ; i > s.from ; i-- )
		data [i]  = data [i-1] ;
}

void insert (vector<Track>& data, int& length, Track y )
{//               
    assert (true);
    Slice s = mkSlice(0,length-1) ;
    assert (length >= 0 && is_sorted (data, s)) ;
/*                 
                                                                                     
                                   
*/
	const int POS = find_position (data, mkSlice (0, length-1), y) ;
	if (POS < length)
		shift_right ( data, mkSlice (POS, length-1) ) ;
	data [POS] = y ;
	length++;
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

void dnf_part_1_by_number (vector<Track>& data_vector, int first, int last, int& red, int& blue) {
    assert (first >= 0 && last >= 0);
    //                                                                                                                                         
    red = first - 1;
    blue = last + 1;
    int white = last + 1;
    const Track MID = data_vector[first + (last - first)/2];
    while (red < white - 1) {
        const int NEXT = white - 1;      //                                  
        if (data_vector[NEXT] < MID) {
            red = red + 1;
            swap(data_vector, red, NEXT);
        } else if (data_vector[NEXT] == MID) {
            white = white - 1;
        } else {
            white = white - 1;
            blue = blue - 1;
            swap(data_vector, NEXT, blue);
        }
    }
}

void dnf_part_1_by_length (vector<Track>& data_vector, int first, int last, int& red, int& blue) {
    assert (first >= 0 && last >= 0);
    //                                                                                                                                         
    red = first - 1;
    blue = last + 1;
    int white = last + 1;
    const Track MID = data_vector[first + (last - first)/2];
    while (red < white - 1) {
        const int NEXT = white - 1;      //                                  
        if (data_vector[NEXT].time < MID.time) {
            red = red + 1;
            swap(data_vector, red, NEXT);
        } else if (data_vector[NEXT].time == MID.time) {
            white = white - 1;
        } else {
            white = white - 1;
            blue = blue - 1;
            swap(data_vector, NEXT, blue);
        }
    }
}

void dnf_part_2_by_number (vector<Track>& data_vector, int first, int last, int& red, int& blue) {
    assert (first >= 0 && last >= 0);
    //                                                                                                                                          
    red = first - 1;                    //                 
    blue = last + 1;                    //                   
    int white = first - 1;
    const Track MID = data_vector[first + (last - first)/2];
    while (blue > white + 1) {
        const int NEXT = white + 1;      //                                  
        if (data_vector[NEXT] < MID) {
            red = red + 1;
            white = white + 1;
            swap(data_vector, red, NEXT);
        } else if (data_vector[NEXT] == MID) {
            white = white + 1;
        } else {
            blue = blue - 1;
            swap(data_vector, NEXT, blue);
        }
    }
}

void dnf_part_2_by_length (vector<Track>& data_vector, int first, int last, int& red, int& blue) {
    assert (first >= 0 && last >= 0);
    //                                                                                                                                          
    red = first - 1;
    blue = last + 1;
    int white = first - 1;
    const Track MID = data_vector[first + (last - first)/2];
    while (blue > white + 1) {
        const int NEXT = white + 1;      //                                  
        if (data_vector[NEXT].time < MID.time) {
            red = red + 1;
            white = white + 1;
            swap(data_vector, red, NEXT);
        } else if (data_vector[NEXT].time == MID.time) {
            white = white + 1;
        } else {
            blue = blue - 1;
            swap(data_vector, NEXT, blue);
        }
    }
}

void quicksort_part_1_by_number(vector<Track>& data_vector, int first, int last) {
    assert (first >= 0 && last >= 0);
    //                                                                                                                                             
    if (first >= last) {
        return;
    } else {
        int red, blue;
        dnf_part_1_by_number(data_vector, first, last, red, blue);
        quicksort_part_1_by_number(data_vector, first, red);
        quicksort_part_1_by_number(data_vector, blue, last);
    }
}

void quicksort_part_1_by_length(vector<Track>& data_vector, int first, int last) {
    assert (first >= 0 && last >= 0);
    //                                                                                                                                             
    if (first >= last) {
        return;
    } else {
        int red, blue;
        dnf_part_1_by_length(data_vector, first, last, red, blue);
        quicksort_part_1_by_length(data_vector, first, red);
        quicksort_part_1_by_length(data_vector, blue, last);
    }
}

void quicksort_part_2_by_number(vector<Track>& data_vector, int first, int last) {
    //                                                                                                                                              
    assert (true);
    if (first >= last) {
        return;
    } else {
        int red, blue;
        dnf_part_2_by_number(data_vector, first, last, red, blue);
        quicksort_part_2_by_number(data_vector, first, red);
        quicksort_part_2_by_number(data_vector, blue, last);
    }
}

void quicksort_part_2_by_length(vector<Track>& data_vector, int first, int last) {
    assert (true);
    //                                                                                                                                              
    if (first >= last) {
        return;
    } else {
        int red, blue;
        dnf_part_2_by_length(data_vector, first, last, red, blue);
        quicksort_part_2_by_length(data_vector, first, red);
        quicksort_part_2_by_length(data_vector, blue, last);
    }
}

void swap_int (vector<int>& v, int x, int y) {   //                                            
    assert (x >= 0 && y >= 0);
    //                                           
    const int HELP = v[x];
    v[x] = v[y];
    v[y] = HELP;
}

int largest (vector<int>& v, int low, int up) {
    assert (true);
    //                                                                 
    vector<int> the_stack;
    while (low < up) {
        the_stack.push_back(low);
        if (v[low + 1] > v[up]) {
            const int POS = low + 1;
        } else {
            const int POS = up;
        }
    }
    while (the_stack.size() > 0) {
        the_stack.pop_back();
    }
    return low;
}

void sort (vector<int>& v, int n) {
    assert (true);
    //                                                      
    while (n <= 1) {
        const int POS = largest(v, 0, n - 1);
        swap_int(v, POS, n - 1);
    }
}

int main()
{
    char crit_choice_char = ' ';
    char dir_choice_char = ' '; //                                                       
	const int NO_OF_SONGS = read_file ("Tracks.txt");
	if (NO_OF_SONGS < 0)
	{
        cout << "Reading file failed. Program terminates." << endl;
	    return NO_OF_SONGS;
    }
    vector<Track> copy_vect = songs;
    cout << endl << "Choose sorting criteria:" << endl << "By number: press n" << endl << "By length: press l" << endl << endl << "Choice: ";
    cin >> crit_choice_char;
    cout << endl;
    if (crit_choice_char == 'n' || crit_choice_char == 'N') {   //                                             
        cout << endl << "Choose orientation of orange:" << endl << "Left of white: press l" << endl << "Right of white: press r" << endl << endl << "Choice: ";
        cin >> dir_choice_char;
        if (dir_choice_char == 'l' || dir_choice_char == 'L') {
            cout << "Sorting..." << endl;
            quicksort_part_1_by_number(songs, 0, size(songs) - 1);
        }
        if (dir_choice_char == 'r' || dir_choice_char == 'R') {
            cout << "Sorting..." << endl;
            quicksort_part_2_by_number(songs, 0, size(songs) - 1);
        }
        if (dir_choice_char != 'l' && dir_choice_char != 'L' && dir_choice_char != 'r' && dir_choice_char != 'R') {
            cout << "Invalid choice!" << endl;
            return 5;
        }
    }
    if (crit_choice_char == 'l' || crit_choice_char == 'L') {   //                                                   
        cout << endl << "Choose orientation of orange:" << endl << "Left of white: press l" << endl << "Right of white: press r" << endl << endl << "Choice: ";
        cin >> dir_choice_char;
        if (dir_choice_char == 'l' || dir_choice_char == 'L') {
            cout << "Sorting..." << endl;
            quicksort_part_1_by_length(songs, 0, size(songs) - 1);
        }
        if (dir_choice_char == 'r' || dir_choice_char == 'R') {
            cout << "Sorting..." << endl;
            quicksort_part_2_by_length(songs, 0, size(songs) - 1);
        }
        if (dir_choice_char != 'l' && dir_choice_char != 'L' && dir_choice_char != 'r' && dir_choice_char != 'R') {
            cout << "Invalid choice!" << endl;
            return 5;
        }
    }
    if (crit_choice_char != 'n' && crit_choice_char != 'N' && crit_choice_char != 'l' && crit_choice_char != 'L') {
        cout << "Invalid choice!" << endl;
        return 5;
    }
    show_all_tracks(songs, NO_OF_SONGS);
    return 0;
}

