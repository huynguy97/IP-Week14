//                                            
//                                                 

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

vector<Track> songs;              //                                     

/*                                                                       
                                
                                                               
                                                                         
                                                                       */
bool operator<(const Length& a, const Length& b)
{
//                
    assert ( true );
/*                                             
                                                                                                      
                                                                      */
    if (a.minutes == b.minutes)
        return a.seconds < b.seconds ;
    else
        return a.minutes < b.minutes ;
}

bool operator==(const Length& a, const Length& b)
{
//                
    assert ( true );
/*                                                                                                                */
    return a.minutes == b.minutes && a.seconds == b.seconds ;
}

//                                   

/*
                                              
 
                  
                    
                     
                                                 
                                                                                                                   

                             
     
                         
         
                                 
                                                
                
                                        
         
            
                                
     
        
                                    
 
*/

//                                        

bool operator<(const Track& a, const Track& b)
{
//                
    assert ( true );
    //               
    //                                       
    //                                                                                                                   

    if (a.time == b.time)
    {
        if (a.artist == b.artist)
        {
            if (a.title == b.title)
                return a.cd < b.cd;
            else
                return a.title < b.title;
        }
        else
            return a.artist < b.artist ;
    }
    else
        return a.time < b.time ;
}

bool operator==(const Track& a, const Track& b)
{
    return a.artist == b.artist && a.cd  == b.cd && a.year == b.year && a.track_no == b.track_no;
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

int size (vector<Track>& v)
{
//                
    assert ( true );
/*                                                        */
    return static_cast<int> (v.size()) ;
}

//                                                                           
int read_songs (ifstream& infile, vector<Track>& songs)
{//               
    assert (infile.is_open ()) ;
/*                 
                                                                              
                                                           
*/
    Track track ;
    int no_of_read_songs = 0 ;
    do
    {
        infile >> track;
        if(infile)
        {
            songs.push_back(track) ;
        }
    }
    while (infile);
    no_of_read_songs = songs.size() ;
    return no_of_read_songs ;
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
    cout << "Reading " << filename << "." << endl;
	const int NO_OF_SONGS = read_songs (songsDBS, songs);
	songsDBS.close();
	cout << " Read " << NO_OF_SONGS << " tracks." << endl;
	return NO_OF_SONGS;
}

void show_all_tracks (vector<Track>& songs, int no_of_songs)
{//               
    assert (true) ;
/*                 
                                                                  
*/
    for (int i = 0 ; i < no_of_songs; i++)
        cout << i+1 << ". " << songs[i] << endl ;
}

void swap (vector<Track>& songs, int i, int j)
{
//                
assert (i <= songs.size() && j<= songs.size());
//                 
//                                                                                    
Track t = songs[i];
songs[i] = songs[j];
songs[j] = t;
}

void dnf1(vector<Track>& songs, int first, int last, int& red, int& blue){
    red = first -1;
    blue = last + 1;
    int white = last + 1;

    const Track PIVOT = songs[first+(last-first)/2];
    while (red < white - 1){
        const int NEXT  = white - 1;
        if(songs[NEXT] < PIVOT){
            red++;
            swap(songs, red, NEXT);
        }
        else if(songs[NEXT] == PIVOT){
            white--;
        }
        else {
            white--;
            blue--;
            swap(songs, NEXT, blue);
        }
    }
}

void dnf2(vector<Track>& songs, int first, int last, int& red, int& blue){
    red = first -1;
    blue = last + 1;
    int white = first - 1;

    const Track PIVOT = songs[first+(last-first)/2];
    while (blue > white + 1){
        const int NEXT  = white + 1;
        if(songs[NEXT] < PIVOT){
            red++;
            white++;
            swap(songs, red, NEXT);
        }
        else if(songs[NEXT] == PIVOT){
            white++;
        }
        else {
            blue--;
            swap(songs, NEXT, blue);
        }
    }
}

//                              

void Quicksort (vector<Track>& songs, int first, int last){
    //              
    assert (0 <= first && last < size(songs));
    //                                                                           
    if( first >= last) return ;
    else {
        int red, blue;
        dnf1(songs, first, last, red, blue);
        Quicksort(songs, first, red);
        Quicksort(songs, blue, last);
    }

}

//                        
/*
                                  
                                                
                   
                   
     
          
                                                  
                                    
                       
         
             
                       
         
     
 

                 
                                                  
                      
                          
                    
                             
              
     
                             
                                        
                                  
                                 
         
     
 
*/

/*
                               
                                       
               
                                               
                              
                         
     
 

                 
                                        
                 
                                               
                              
               
     
 
*/
//              

int main()
{
	const int NO_OF_SONGS = read_file ("Tracks.txt");
	if (NO_OF_SONGS < 0)
	{
        cout << "Reading file failed. Program terminates." << endl;
	    return NO_OF_SONGS;
    }

    Quicksort(songs, 0, size(songs)-1);
    cout << "Tracks sorted." << endl;

    show_all_tracks (songs,NO_OF_SONGS) ;

	return 0;
}

