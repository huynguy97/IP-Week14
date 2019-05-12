/*                                                                    
                                              
            
                                                                                                            
                                  
                              
                                                           
                                                                    
                                                          
                                                               
                                                                     */

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>
#include <algorithm>
#include <sstream>

using namespace std;

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

const int MAX_NO_OF_SONGS = 6000;
vector <Track> total_songs;

/*                                                                       
                                
                                                               
                                                                         
                                                                       */

bool operator<(const Track& a, const Track& b)
{
    if (a.artist == b.artist)
    {
        if (a.cd == b.cd)
        {
            if (a.year == b.year)
            {
                return a.track_no < b.track_no;
            }
            else
                return a.year < b.year;
        }
        else
            return a.cd < b.cd;
    }
    else
        return a.artist < b.artist ;    //                                                
}

bool operator==(const Track& a, const Track& b)
{
    return a.artist == b.artist && a.cd == b.cd && a.year == b.year && a.track_no == b.track_no;   //                                                
}
/*
                                              
 
                                         
     
                                             
         
                                     
             
                                       
                 
                                       
                 
                    
                                             
             
                
                                           
         
            
                                                   
     
                                           
 

                                               
 
                                                                                                                                              
 
*/
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

istream& operator>> (istream& in, Track& track)
{//               
    assert (true) ;
/*                 
                                                                                                                   
                                      
*/
    string linebreak;
    getline(in, linebreak);
    if (linebreak.empty()) {
        getline(in, track.artist);
        if (track.artist.empty()) {
            return in;
        }
    } else {
        track.artist = linebreak;
    }
    getline(in, track.cd);
    string yearstring;
    getline(in, yearstring);
    track.year = stoi(yearstring);
    string tracknumstring;
    getline(in, tracknumstring);
    track.title = stoi(tracknumstring);
    getline(in, track.title);
    getline(in, track.tags);
    Length length;
    string l;
    stringstream ss;
    getline(in, l);
    ss << l;
    ss >> length;
    track.time = length;
    getline(in, track.country);
    return in;
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
int read_songs (ifstream& infile, vector<Track>& total_songs)
{//               
    assert (infile.is_open ()) ;
/*                 
                                                                              
                                                           
*/
    Track track;
    int count = 0;
    while (infile >> track) {
        count++;
        total_songs.push_back(track);
    }
    return count;
}

int read_file (string filename)
{//               
    assert (total_songs.size() == 0);
/*                 
                                                                              
                                                                                             
                                        
*/
    ifstream songsDBS(filename.c_str());
    if (!songsDBS) {
        cout << "Could not open '" << filename << "'." << endl;
        return -1;
    }
    cout << "Reading '" << filename << "'." << endl;
    const int NO_OF_SONGS = read_songs(songsDBS, total_songs);
    songsDBS.close();
    cout << "Read " << NO_OF_SONGS << " tracks." << endl;
    return NO_OF_SONGS;
}

void show_all_tracks (vector <Track>& total_songs, int no_of_songs)
{//               
    assert (no_of_songs < MAX_NO_OF_SONGS) ;
/*                 
                                                                  
*/
    for (int i = 0 ; i < no_of_songs; i++)
        cout << i+1 << ". " << total_songs[i] << endl ;
}

/*                                                                       
                                                         
                                                                       */

void swap (vector <Track>& total_songs, int  i, int  j )
{//	              
    assert ( i >= 0 && j >= 0 ) ;	//                         
    //                         
//                                                                
    const Track HELP = total_songs [i];
    total_songs [i] = total_songs [j] ;
    total_songs [j] = HELP;
}

//      
void dnf (vector<Track>& data, int first, int last , int& red, int& blue)
{
    red = first - 1;
    blue = last + 1;
    int white = last + 1;
    const Track PIVOT = data[first + (last - first)/2];
    while (red < white-1)
    {
        const int NEXT = white - 1;
        if (data[NEXT] < PIVOT)
        {
            red++;
            swap(data, red, NEXT);
        }
        else if (data[NEXT] == PIVOT)
        {
            white--;
        }
        else
        {
            white--;
            blue--;
            swap(data, NEXT, blue);
        }
    }
}

//      
void dnf_adjusted (vector<Track>& data, int first, int last, int& red, int& blue)
{
    red = first - 1;
    blue = last + 1;
    int white = first-1;
    const Track PIVOT = data[first + (last - first)/2];
    while (blue > white+1)
    {
        const int NEXT = white + 1;
        if (data[NEXT] < PIVOT)
        {
            red++;
            white++;
            swap(data, red, NEXT);
        }
        else if (data[NEXT] == PIVOT)
        {
            white++;
        }
        else
        {
            blue--;
            swap(data, NEXT, blue);
        }
    }
}

void quick_sort (vector<Track>& data, int first, int last)
{ //              
    assert(0 <= first && last < data.size());
  //               
  //                      
    if (first >= last)
        return;
    else
    {
        int red;
        int blue;
        dnf_adjusted(data, first, last, red, blue);
        quick_sort (data, first, red);
        quick_sort(data, blue, last);
    }
}

/*
        
           
                                            
 
                  
                   
        
     
                                              
                            
                       
            
                       
     
 

           
                                                     
 
                          
                    
     
                                   
     
               
                                
     
                                            
                             
                   
     
              
 

           
                               
 
              
     
                                           
                          
                     
     
 

           
                                         
 
                        
                 
     
                                                      
                           
                              
     
                              
     
                                      
     
 
*/
/*                                                                       
                                      
                   
                                                                      
                                           
                                          
                                                                       */

int main()
{
    const int NO_OF_SONGS = read_file ("Tracks.txt");
    if (NO_OF_SONGS < 0)
    {
        cout << "Reading file failed. Program terminates." << endl;
        return NO_OF_SONGS;
    }
    quick_sort(total_songs, 1, total_songs.size()-1);
    cout << "Tracks sorted." << endl;
    show_all_tracks (total_songs,NO_OF_SONGS) ;
    return 0;
}
