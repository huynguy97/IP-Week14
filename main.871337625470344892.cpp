#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>
#include <algorithm>
#define NDEBUG

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

vector<Track> songs;
int counter = 0;

/*                       
                                
                                                               
                                                                         
                       */

bool operator<(const Length& a, const Length& b)
{
    //              
    assert(true);
    //                                              
    if (a.minutes < b.minutes)
        return true;
    if (a.minutes == b.minutes && a.seconds < b.seconds)
        return true;

    return false;
}

bool operator==(const Length& a, const Length& b)
{
    //              
    assert(true);
    //                
    return (a.minutes == b.minutes && a.seconds == b.seconds);
}

bool operator<(const Track& a, const Track& b)
{
    //              
    assert(true);
    //                
    counter++;
    if (a.time == b.time)
        if(a.cd == b.cd)
            if(a.track_no == b.track_no)
                if(a.year == b.year)
                    return a.track_no < b.track_no;
                else return a.year < b.year;
            else return a.track_no < b.track_no;
        else return a.cd < b.cd;
    else return a.time < b.time;
}

bool operator==(const Track& a, const Track& b)
{
    //              
    assert(true);
    //                
    counter++;
    if(a.time == b.time && a.artist == b.artist && a.cd == b.cd && a.year == b.year)
        return true;
    else if(a.track_no == b.track_no)
        return true;
}

//	                                 
bool operator>(const Track& a, const Track& b)
{
    //              
    assert(true);
    //                
    return b < a ;
}

bool operator<=(const Track& a, const Track& b)
{
    //              
    assert(true);
    //                
    return !(b < a) ;
}

bool operator>=(const Track& a, const Track& b)
{
    //              
    assert(true);
    //                
    return b <= a ;
}

int min(int a, int b)
{
    //              
    assert(true);
    //                
    if(a<b)
    {
        return a;
    }
    else{
        return b;
    }
}
int max(int a, int b)
{
    //              
    assert(true);
    //                
    if(a>b)
    {
        return a;
    }
    else{
        return b;
    }
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
        no_of_read_songs++;
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
void show_all_tracks (vector<Track>& songs, int no_of_songs)
{//               
    assert (true) ;
/*                 
                                                                  
*/
    for (int i = 0 ; i < no_of_songs; i++)
        cout << i+1 << ". " << songs[i] << endl ;
}

void show_vector (vector<int>& songs) {
    for (int i = 0; i < songs.size(); i++) {
        cout << songs[i] << "  ";
    }
    cout << endl;
};

void swap (vector<Track>& data, int el_1, int el_2) {
    data.push_back(data[el_1]);
    data[el_1] = data[el_2];
    data[el_2] = data[data.size()-1];
    data.pop_back();
}

void dnf (vector<Track>& data, int first, int last, int& red, int& blue) {
  red = first-1;
  blue = last+1;
  int white = last+1;
  const Track PIVOT = data[first+(last-first)/2];
  while (red < white -1) {
      const int NEXT = white -1;
      if (data[NEXT] < PIVOT) {
          red++;
          swap(data, red, NEXT);
      }
      else if (data[NEXT] == PIVOT) {
          white--;
      }
      else {
          white--;
          blue--;
          swap(data, NEXT, blue);
      }
  }
};

void quicksort (vector<Track>& data, int first, int last) {
  if (first >= last)
      return;
  else {
      int red, blue;
      dnf(data,first, last, red, blue);
      quicksort(data, first, red);
      quicksort(data, blue, last);
  }
};

int main()
{
    //              
    assert(true);
    //                                                                                           

    const int NO_OF_SONGS = read_file ("Tracks.txt");
    if (NO_OF_SONGS < 0)
    {
        cout << "Reading file failed. Program terminates." << endl;
        return NO_OF_SONGS;
    }
    ofstream output;
    output.open("output.txt");

    quicksort(songs, 0, songs.size()-1);

    show_all_tracks(songs,200);

    return 0;
}

/*         
                         
                
                            
                    
                               
                            
                                    
                        
                                
*/

/*         
                     
                        
                                        
                                    
                                                   
                                            
                                                
                                
                                
 */
