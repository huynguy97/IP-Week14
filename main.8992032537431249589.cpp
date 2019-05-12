#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>

//                                                         
//                                                   

using namespace std;

struct Length
{
    int minutes;
    int seconds;
};

struct Track
{
    string artist;
    string cd;
    int    year;
    int    track_no;
    string title;
    string tags;
    Length time;
    string country;
};

vector<Track> songs;

void swap (vector<Track>& data, int red, int next)
{
    //             
    assert(red>=0 && next>=0 &&red<data.size() && next<data.size() );
    //                                                                          

    Track a = data[red];
    data[red]=data[next];
    data[next]=a;
}

bool operator<(const Length& a, const Length& b)
{
    if(a.minutes<b.minutes)
        return true;
    else if(a.minutes==b.minutes && a.seconds<b.seconds)
        return true;
    else
        return false;
}

bool operator== (const Length& a, const Length& b)
{
    return (a.minutes==b.minutes && a.seconds==b.seconds);
}

//                                                  
/*
                                              
 
                         
                    
                                            
                    
                                                              
                    
                                                                                        
                    
        
                     
 

                                               
 
                                                                                                                                               
 

*/

//                                                             
bool operator<(const Track& a, const Track& b)
{
    if (a.time < b.time)
        return true;
    else if (a.time==b.time && a.artist < b.artist)
        return true;
    else if (a.time==b.time && a.artist==b.artist && a.title < b.title)
        return true;
    else if (a.time==b.time && a.artist==b.artist && a.title == b.title && a.cd < b.cd)
        return true;
    else
        return false;

}

bool operator==(const Track& a, const Track& b)
{
    return (a.time==b.time && a.artist==b.artist && a.title==b.title && a.cd==b.cd ) ;
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
{
    //               
    assert (true) ;
    /*                 
                                                                                                          
    */
    char colon ;
    in >> length.minutes >> colon >> length.seconds ;
    return in ;
}

ostream& operator<< (ostream& out, const Length length)
{
    //               
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
{
    //               
    assert (true) ;
    /*                 
                                                                            
    */
    string remains ;
    getline (infile, remains) ;
}

istream& operator>> (istream& infile, Track& track)
{
    //               
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
{
    //               
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
{
    //               
    assert (infile.is_open ()) ;
    /*                 
                                                                                  
                                                               
    */
    int no_of_read_songs = 0 ;
    do
    {
        Track song ;
        infile >> song ;
        if (infile)
            songs.push_back(song);
        no_of_read_songs++;
    }
    while (infile);
    return no_of_read_songs-1 ;
}

int read_file (string filename)
{
    //               
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

void show_all_tracks (vector<Track> songs, int no_of_songs)
{
    //               
    assert (no_of_songs <= songs.size()) ;
    /*                 
                                                                      
    */
    for (int i = 0 ; i < no_of_songs; i++)
        cout << i+1 << ". " << songs[i] << endl ;
}

/*                     */

/*                                                                        
 
                    
                                              
                                                                                                                         
                                                                                          

                 
                 
                      
                                                    
                        
     
                                 
                               
         
                  
                                    
         
                                     
                     
            
         
                    
                   
                                     
         
     
 
*/

/*                     */

void dnf (vector<Track>& data, int first, int last, int& red, int& blue)
{
    //              
    assert(0<=first && last<(int)data.size());
    //                                                                                                                   
    //                                                                                    

    red= first-1;
    blue= last+1;
    int white= first-1;
    const Track PIVOT = data [first+(last-first)/2];
    while(white< blue-1)
    {
        const int NEXT= white+1;
        if(data[NEXT]  < PIVOT)
        {
            red++;
            white++;
            swap (data,red,NEXT);

        }
        else if(data[NEXT]  == PIVOT)
        {
            white++ ;
        }
        else
        {
            blue--;
            swap (data, NEXT,  blue);
        }
    }

}

void quick_sort (vector<Track>& data, int first, int last)
{
    //             
    assert(0<=first && last<(int)data.size());
    //                                                   

    if (first>=last)
        return;
    else {
            int red, blue;
            dnf(data,first,last,red,blue);
            quick_sort(data,first,red);
            quick_sort(data,blue,last);
         }
}

int main()
{
    const int NO_OF_SONGS = read_file ("Tracks.txt");
    if (NO_OF_SONGS < 0)
    {
        cout << "Reading file failed. Program terminates." << endl;
    }
    quick_sort(songs,0,NO_OF_SONGS-1);
    show_all_tracks(songs,NO_OF_SONGS);

    return 0;
}

//       
/*

                              
 
              
     
                                         
                        
             
     
 

                                           
 
                      
                   
     
                             
              
     
                         
     
                                             
                         
                            
                      
     
               
 

*/

