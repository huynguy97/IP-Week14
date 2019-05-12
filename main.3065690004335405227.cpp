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
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

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

vector<Track> songs;              //                                     
int MAX_NO_OF_SONGS = 100000;

/*                                                                       
                                
                                                               
                                                                         
                                                                       */
// 
bool operator<(const Track& a, const Track& b)
{
    if (a.artist == b.artist)
        if (a.cd == b.cd)
            if (a.year == b.year)
                return a.track_no < b.track_no;
            else return a.year < b.year;
        else return a.cd < b.cd;
    else return a.artist < b.artist;
}

bool operator==(const Track& a, const Track& b)
{
    return (a.artist == b.artist && a.cd == b.cd &&
            a.year == b.year && a.track_no == b.track_no);
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
        {
            songs.push_back(song);
            no_of_read_songs++;
        }
    }
    while (infile && no_of_read_songs < MAX_NO_OF_SONGS);
    return no_of_read_songs;
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

//                                                                           
void show_all_tracks (vector<Track> songs)
{//               
    assert (songs.size() < MAX_NO_OF_SONGS) ;
/*                 
                                                                  
*/
    for (int i = 0 ; i < songs.size(); i++)
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

typedef Track El ;                //                                                       

bool is_sorted (vector<El>& data, Slice s)
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

int find_position (vector<El>& data, Slice s, El y )
{//	              
	assert (valid_slice(s) && is_sorted(data,s)) ;    //                           
//	                                          
	for ( int i = s.from ; i <= s.to ; i++ )
		if ( y <= data [i] )
			return i ;
	return s.to+1;
}

void shift_right (vector<El>& data, Slice s )
{//	              
	assert (valid_slice (s));	//                               
//	                               	  	                
//			    	               	  	                  
//						   
//			    	             		  	              
	for (int i = s.to+1; i>s.from; i--)
		data[i] = data[i-1];
}

void swap (vector<El>& data, int  i, int  j )
{//	              
	assert ( i >= 0 && j >= 0 ) ;	//                         
						            //                         
//                                                                
	const El HELP = data [i];
	data [i] = data [j] ;
	data [j] = HELP;
}

void sortDNF (vector<El>& data, int first, int last, int& red, int& blue)
{
    assert(first >= 0 && first <= last && last < data.size());
    //                                                                          
    //                                                                           
    red = first-1;
    blue = last+1;
    int white = last+1;
    const El PIVOT = data[(first+last)/2];
    int NEXT;
    while (red < white-1)
    {
        NEXT = white - 1;
        if(data[NEXT] < PIVOT)
        {
            red++;
            swap(data, red, NEXT);
        }
        else if(data[NEXT] > PIVOT)
        {
            white--;
            blue--;
            swap(data, NEXT, blue);
        }
        else
            white--;
    }
}

void QuickSort (vector<El>& data, int first, int last)
{
    assert(first >= 0 && first <= last && last < data.size());
    //                                              
    if (first >= last)
        return;
    else
    {
    int red, blue;
    sortDNF(data, first, last, red, blue);
    QuickSort(data, first, red);
    QuickSort(data, blue, last);
    }
}

void sortDNFB (vector<El>& data, int first, int last, int& red, int& blue)
{
    assert(first >= 0 && first <= last && last < data.size());
    //                                                                          
    //                                                                           
    red = first-1;
    blue = last+1;
    int white = first+1;
    const El PIVOT = data[(first+last)/2];
    int NEXT;
    while (white < blue-1)
    {
        NEXT = white + 1;
        if(data[NEXT] < PIVOT)
        {
            white++;
            red++;
            swap(data, red, NEXT);
        }
        else if(data[NEXT] > PIVOT)
        {
            blue--;
            swap(data, NEXT, blue);
        }
        else
            white++;
    }
}

void QuickSortB (vector<El>& data, int first, int last)
{
    assert(first >= 0 && first <= last && last < data.size());
    //                                              
    if (first >= last)
        return;
    else
    {
    int red, blue;
    sortDNFB(data, first, last, red, blue);
    QuickSortB(data, first, red);
    QuickSortB(data, blue, last);
    }
}

int largest(vector<El> data, int low, int up)
{
    assert(low <= up);
    //                                                                                              
    int POS;
    vector<int> S;
    while(!low >= data.size()-1)
    {
        S.push_back(low);
        low++;
    }
    POS = low;
    while (S.size() > 0)
    {
        low = S[S.size()-1];
        S.pop_back();
        if (data[low] > data[POS])
            POS = low;
    }
    return POS;
}

void sort (vector<El> data, int n)
{
    assert(n > 0);
    //                                                              
    int POS;
    while (n>1)
    {
        POS = largest(data, 0, n-1);
        swap(data, POS, n-1);
        n--;
    }
}

/*                                                                       
                                      
                   
                                                                      
                                           
                                          
                                                                       */
int main()
{
    int i = 0;
	const int NO_OF_SONGS = read_file ("Tracks.txt");
	if (NO_OF_SONGS < 0)
	{
        cout << "Reading file failed. Program terminates." << endl;
	    return NO_OF_SONGS;
    }
    cout << songs.size() << endl;
    cout << "Sorting tracks with QuickSort" << endl;
    QuickSortB(songs, 0, songs.size());
    cout << "Tracks sorted." << endl;
    show_all_tracks (songs);
	return 0;
}

