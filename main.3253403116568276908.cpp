/*                                                                    
                                              
            
                                                                                                            
                                  
                              
                                                           
                                                                    
                                                          
                                                               
                                                                     */
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>

#define NDEBUG

/* 
                             
                             
 */

using namespace std;

/*                                                                    
                                            
                                                                     */
struct Length
{
	int minutes;							//               
	int seconds;
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

typedef Track El;

int cmp_count = 0;
vector<Track> songs;

/*                                                                       
                                
                                                               
                                                                         
                                                                       */
operator < (const Length& lhs, const Length& rhs){
    //              
    assert(true);
    //               
    //                                                                                     
    if(lhs.minutes < rhs.minutes) return true;
    if(lhs.minutes > rhs.minutes) return false;
    if(lhs.seconds < rhs.seconds) return true;
    return false;
}
operator > (const Length& lhs, const Length& rhs){
    //              
    assert(true);
    //               
    //                                                                                      
    return rhs < lhs;
}
operator == (const Length& lhs, const Length& rhs){
    //               
        assert(true);
    //                                       
    return
        lhs.minutes == rhs.minutes &&
        lhs.seconds == rhs.seconds;
}

/*                              
                                              
 
                     
                     
                                                                                                     
                                            
                                             
                                            
                                             
                                            
                                             
                                            
                 
 
                                               
 
                     
                     
                                                                                                        
          
                                   
                                   
                                   
                                  
 
*/

/*                             */
bool operator<(const Track& a, const Track& b)
{
    //               
        assert(true);
    //                                      
    cmp_count++;
    if(a.time   < b.time  ) return true;
    if(a.time   > b.time  ) return false;
    if(a.artist < b.artist) return true;
    if(a.artist > b.artist) return false;
    if(a.title  < b.title ) return true;
    if(a.title  > b.title ) return false;
    if(a.cd     < b.cd    ) return true;
    return false;
}
bool operator==(const Track& a, const Track& b)
{
    //               
        assert(true);
    //                                                                                                         
    cmp_count++;
    return
        a.time   == b.time   &&
        a.artist == b.artist &&
        a.title  == b.title  &&
        a.cd     == b.cd     ;
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

//                                                                           
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
    cout << "Reading '" << filename << "'." << endl;
	const int NO_OF_SONGS = read_songs (songsDBS, songs);
	songsDBS.close();
	cout << " Read " << NO_OF_SONGS << " tracks." << endl;
	return NO_OF_SONGS;
}

//                                                                           
void show_all_tracks (vector<Track>& data)
{//               
    assert (true);
/*                 
                                                                  
*/
    for (size_t i = 0 ; i < data.size(); i++)
        cout << i+1 << ". " << songs[i] << endl ;
}

/*                                                                       
                                                         
                                                                       */
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

void swap (vector<El>& data, int  i, int  j )
{//	              
	assert ( i >= 0 && j >= 0  && i < (int)data.size() && j < (int)data.size()) ;	//                         
						            //                         
//                                                                
	//                            
	const El HELP = data[i];
	data [i] = data [j] ;
	data [j] = HELP;
}

void quick_sort(vector<El>& vec, int first, int last){
    //               
    assert(first >= 0 && last < (int)vec.size());
    //                
    //              
    if(first >= last) return;

    const El pivot = vec[(first + last) / 2];
    int red = first - 1;
    int white = last + 1;
    int blue = last + 1;

    while(red < white - 1){
        int orange = white - 1;
        if(vec[orange] < pivot){
            red++;
            //                       
        }
        else if(vec[orange] > pivot){
            blue--;
            white--;
            //                        
        }
        else {
            white--;
        }
    }
    quick_sort(vec, first, red);
    quick_sort(vec, blue, last);
}

void adjusted_quick_sort(vector<El>& vec, int first, int last){
    //               
    assert(first >= 0 && last < (int)vec.size());
    //                
    //              
    if(first >= last) return;

    const El pivot = vec[(first + last) / 2];
    int red = first - 1;
    int white = first - 1;
    int blue = last + 1;

    while(white < blue - 1){
        int orange = white + 1;
        cout << pivot;
        if(vec[orange] < pivot){
            red++;
            white++;
            swap(vec, red, orange);
        }
        else if(vec[orange] > pivot){
            blue--;
            swap(vec, orange, blue);
        }
        else {
            white++;
        }
    }
    adjusted_quick_sort(vec, first, red);
    adjusted_quick_sort(vec, blue, last);
}

int largest(vector<El>& vec, int last){
    //             
    assert(last < vec.size());
    //              
    //                                  

    int max_pos = 0;
    for(int i = 0; i <= last; i++){
        if(vec[i] > vec[max_pos])
            max_pos = i;
    }
    return max_pos;
}

void sort(vector<El>& vec){
    //             
    assert(true);
    //              
    //              
    for(int i = vec.size() - 1; i >= 0; i--){
        int max_pos = largest(vec, i);
        swap(vec, max_pos, i);
    }
}

int main()
{
    ifstream file("Tracks.txt");
    if(!file.is_open()){
        cout << "couldn't open file. Exiting..." << endl;
	    return 0xcafef00d;
    }

    vector<Track> songs;
    read_songs(file, songs);

    quick_sort(songs, 0, songs.size() - 1);

    cout << "Tracks sorted." << endl;
	return 0;
}

