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
//                                                    
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

bool operator< (const Length&a, const Length& b)
{
    if (a.minutes < b.minutes)
        return true;
    else if (a.minutes == b.minutes)
    {
        if (a.seconds < b.seconds)
            return true;
    }
    else return false;

}
bool operator== (const Length&a, const Length& b)
{
    if (a.minutes == b.minutes && a.seconds == b.seconds)
        return true ;
        return false;
}
bool operator<(const Track& a, const Track& b)
{//             
    assert(true);
    /*             
                                                                            
    */

    if (a.artist < b.artist)
    {
        return true;
    }
    else if(a.artist == b.artist)
    {
        if (a.cd < b.cd)
        {
            return true;
        }
        else if(a.cd == b.cd)
        {
            if (a.track_no < b.track_no)
            {
                return true;
            }
        }
    }
    return false;
}

/*                                              
 

                                        
     
                    
     
                                             
     
                                            
         
                        

         
     
                 
 */

bool operator==(const Track& a, const Track& b)
{//             
    assert(true);
    /*             
                                                                          
    */
     if(a.artist == b.artist && a.cd == b.cd && a.track_no == b.track_no)
        return true;
    return false;
}

/*                                               
 
                                                                             
                    
                 
 */

//	                                 
bool operator>(const Track& a, const Track& b)
{
    return b < a;
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
        {
            songs.push_back(song) ;
            no_of_read_songs++;
        }
    }
    while (infile);
    return no_of_read_songs ;
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
void show_all_tracks (vector<Track>& songs, int no_of_songs)
{//               
    assert (no_of_songs <=
 songs.size()) ;
/*                 
                                                                  
*/
    for (int i = 0 ; i < no_of_songs; i++)
        cout << i+1 << ". " << songs[i] << endl ;
}

/*                                                                       
                                                         
                                                                       */

void swap (vector<Track>& data, int  i, int  j )
{//	              
	assert ( i >= 0 && j >= 0 ) ;	//                         
						            //                         
//                                                                
	const Track HELP = data [i];
	data [i] = data [j] ;
	data [j] = HELP;
}

//                                                                      
void dnf (vector<Track>& omg, int first, int last, int& red, int& blue)
{//             
    assert(0 <= first && last < omg.size());
    /*             
                                                                                                                    
                                                                           
    */
    red = first -1;
    blue = last +1;
    int white = last +1;
    const Track PIVOT = omg[first+ (last - first)/2];
    while(red < white - 1)
    {
       const int NEXT = white -1;
        if(omg[NEXT] < PIVOT)
        {
            red++;
            swap(omg,red,NEXT);
        }
        else if (omg[NEXT]== PIVOT)
            white --;
        else
        {
            white--;
            blue--;
            swap(omg,blue,NEXT);
        }
    }
}
//                                                                     
void dnf1 (vector<Track>& omg, int first, int last, int& red, int& blue)
{//             
    assert(0 <= first && last < omg.size());
    /*             
                                                                                                                    
                                                                           
    */
    red = first -1;
    blue = last +1;
    int white = first -1 ;
    const Track PIVOT = omg[first+ (last - first)/2];
    while(blue > white + 1)
    {
       const int NEXT = white +1;
        if(omg[NEXT] < PIVOT)
        {
            white++;
            red++;
            swap(omg,red,NEXT);
        }
        else if (omg[NEXT]== PIVOT)
            white ++;
        else
        {
            blue--;
            swap(omg,blue,NEXT);
        }
    }
}

void Quicksort(vector<Track>& omg, int first, int last)
{//             
    assert(0 <= first && last < omg.size());
    /*             
                                         
    */
    if (first >= last) return;
    else
    {
        int red;
        int blue;
        dnf1(omg, first, last, red, blue);
        Quicksort(omg, first, red);
        Quicksort(omg, blue, last);
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

    int red,blue;
	dnf1(songs,0,songs.size()-1,red, blue);
    Quicksort(songs, 1, songs.size()-1);
    show_all_tracks(songs,songs.size()-1);
    return 0;
}
/*                 

                                             
 
                    

                    
     
                              
                          
     
               

                      
     
                             
                      
                              
                   
     
                   
 

                                 
 
                
     
                                             
                          
               
     
 
 */

