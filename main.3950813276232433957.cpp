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
int size (vector<Track> vec) { return vec.size(); }

/*                                                                       
                                
                                                               
                                                                         
                                                                       */
bool operator==(const Length& a, const Length& b)
{//              
    assert(true);
/*                
                                                              */
    if (a.minutes == b.minutes)
        if (a.seconds == b.seconds)
            return true;
    return false;
}

bool operator<(const Length& a, const Length& b)
{//              
    assert(true);
/*                
                                       */
    if (a.minutes == b.minutes)
        return a.seconds < b.seconds;
    return a.minutes < b.minutes;
}

bool operator<(const Track& a, const Track& b);

bool operator==(const Track& a, const Track& b)
{//              
    assert(true);
/*                
                                                                 */
    bool are_equal = false;
    if (a.artist == b.artist)
        if (a.cd == b.cd)
            if((int)a.year == (int)b.year)
                if( (int) a.track_no == (int) b.track_no)
                    if (a.title == b.title)
                        if (a.tags == b.tags)
                            if (a.time == b.time)
                                if (a.country == b.country)
                                    are_equal = true;
    return are_equal ;   /*                                                 */
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

int read_songs (ifstream& infile, vector<Track>& songs )
{//               
    assert (infile.is_open ()) ;
/*                 
                                                                              
                                                           
*/
    do {
        Track song ;
        infile >> song ;
        if (infile)
            songs.push_back(song) ;
    }
    while (infile);
    return songs.size() ;
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
	const int NO_OF_SONGS = read_songs (songsDBS, songs);
	songsDBS.close();
	return NO_OF_SONGS;
}

void show_all_tracks (vector<Track> songs)
{//               
    assert (true) ;
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
	assert (from <= to);
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

bool is_sorted ( vector<El>& data , Slice s)
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

int find_position ( vector<El>& data, Slice s, El y )
{//	              
	assert (valid_slice(s) && is_sorted(data,s)) ;    //                           
//	                                          
	for ( int i = s.from ; i <= s.to ; i++ )
		if ( y <= data [i] )
			return i ;
	return s.to+1;
}

void shift_right ( vector<El>& data, Slice s )
{//	              
	assert (valid_slice (s)) ;	//                               
//	                               	  	                
//			    	               	  	                  
//						   
//			    	             		  	              
	for ( int i = s.to+1 ; i > s.from ; i-- )
		data [i]  = data [i-1] ;
}

void insert ( vector<El>& data, int& length, El y )
{//               
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

void swap ( vector<El>& data, int  i, int  j )
{//	              
	assert ( i >= 0 && j >= 0 ) ;	//                         
						            //                         
//                                                                
	const El HELP = data [i];
	data [i] = data [j] ;
	data [j] = HELP;
}

/*                                                                       
                      
                                                                       */
//       
//                            
void dnf (vector<El>& data, Slice orange, int& red, int& blue)
{//               
    assert(true);
/*                 
                                                               */
    red = orange.from -1; //               
    blue = orange.to+1; //                 
    const El PIVOT = data[orange.from+(orange.to-orange.from)/2];

    while(orange.from - orange.to <= 0) //                 
    {   const int NEXT = orange.to;
        if(data[NEXT] < PIVOT)
        {
            orange.from++;
            red++;
            swap(data, red, NEXT);
        }
        else if (data[NEXT] == PIVOT)
            orange.to--;
        else
        {
            orange.to--;
            blue--;
            swap(data, NEXT, blue);
        }
    }
}
//                            
void dnf_part2 (vector<El>& data, Slice orange, int& red, int& blue)
{//               
    assert(true);
/*                 
                                                                */
    red = orange.from -1; //               
    blue = orange.to+1; //                 
    const El PIVOT = data[orange.from+(orange.to-orange.from)/2];

    while(orange.from - orange.to <= 0) //                 
    {   const int NEXT = orange.from;
        if(data[NEXT] < PIVOT)
        {
            orange.from++;
            red++;
            swap(data, red, NEXT);
        }
        else if (data[NEXT] == PIVOT)
            orange.from++;
        else
        {
            orange.to--;
            blue--;
            swap(data, NEXT, blue);
        }

        //                     
        //                                                
        //                                                  
    }
}

//                  	             
void quicksort (vector<El>& data, Slice orange)
{//               
    assert(true);
/*                 
                                         */
    if (orange.from >= orange.to)
        return;
    else
    {
        int red, blue;
        dnf_part2(data, orange, red, blue);
        quicksort(data, mkSlice(orange.from, red));
        quicksort(data, mkSlice(blue, orange.to));
    }
}

/*                 
        
                                              
                 
                 
                  
                                      */ /*
                               
                           
                                                           
         
                           
     
                               
  */

//                 
//      
bool operator<(const Track& a, const Track& b)
{//              
    assert(true);
/*                
                                       */
   return a.time < b.time;
}

/*                  
      
                   */
/*                    
                                           

                               
 
           
     
                                           
                          
                     
     
 

                                           
 
                  
                   
        
     
                                              
                           
                       
            
                       
      
  */

/*                    
         
                               
 
               
     
                                           
                          
            
     
 

             
                                           
 
                           
                      
                               
                                
              
     
                      
  */

//                  	             
int main()
{//               
    assert(true);
/*                 
                                                                                     */
    read_file("Tracks.txt");
    Slice orange = mkSlice(0, size(songs)-1);
    quicksort(songs, orange);

    show_all_tracks(songs);

    /*
                                                                                                     
                                                

                            
                                        

                               

                                           
                            
    */
    return 0;
}

