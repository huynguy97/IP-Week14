#include <iostream>
#include <vector>
#include <cassert>
#include <iostream>
#include <fstream>

//                                                            

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

//                                
vector<Track> songs;              //                                     
vector<Track> artists;
vector<Track> data;

bool sortByLength = true;
/*                                                                       
                                
                                                               
                                                                         
                                                                       */
bool operator < (const Length& a, const Length& b)
{
    return ((b.minutes * 60 + b.seconds) > (a.minutes * 60 + a.seconds));
}

bool operator == (const Length& a, const Length& b)
{
    return ((a.minutes * 60 + a.seconds) == (b.minutes * 60 + b.seconds));
}

bool operator<(const Track& a, const Track& b)
{

    if (sortByLength)
    {
        if (a.time == b.time)
        {
            if (a.artist == b.artist)
            {
                if (a.title == b.title)
                {
                    return ( a.cd < b.cd );
                }
                return a.title < b.title;
            }
            return a.artist < b.artist;
        }
        return a.time < b.time;
    }
    else
    {

        if (a.artist == b.artist)
        {
            if (a.year == b.year )
            {
                if ( a.cd == b.cd )
                {
                    //                                                                                                                 
                    return (a.track_no < b.track_no);
                }
                return (a.cd < b.cd);
            }
            return (a.year < b.year);
        }
        return a.artist < b.artist;
    }
}

bool operator==(const Track& a, const Track& b)
{

    return (a.artist == b.artist && a.cd == b.cd && a.track_no == b.track_no && a.year == b.year) ;   /*                                                 */
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

//                                                                                                        
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

//                                                                           
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
            songs.push_back(song) ;
    }
    while (infile);
    return songs.size() ;
}

int read_file (string filename)
{
    //               
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
    cout << "Read " << NO_OF_SONGS << " tracks." << endl;
    return NO_OF_SONGS;
}

//                                                                           
void show_all_tracks (vector<Track>& songs, int no_of_songs)
{
    //               
    assert (no_of_songs <= songs.size()) ;
    /*                 
                                                                      
    */
    for (int i = 0 ; i < no_of_songs; i++)
        cout << i+1 << ". " << songs[i] << endl ;
}

//                                                                                                    

void swap ( vector<Track>& artists, int a, int b)
{
    //             
    assert (true);
    //              
    //                                                                                              
    Track c = artists[a];
    artists[a] = artists[b];
    artists[b] = c;
}

void quicksort(vector<Track>& artists, int left, int right)
{
    //             
    assert (true);
    //              
    //                           

    //          
    int middle;
    int i;
    int j;
    middle = left + (right - left) / 2;
    Track pivot = artists[middle];

    while (i < right || j > left)
    {
        while (artists[i] < pivot)
        {
            i++;
        }
        while (artists[j] > pivot)
        {
            j--;
        }

        if (i <= j)
        {
            swap(artists, i, j);
            i++;
            j--;
        }
        else
        {
            if (i < right)
                quicksort(artists, i, right);
            if (j > left)
                quicksort(artists, left, j);
            //       
        }
    }
}

void dnf(vector<Track>& songs, int first, int last, int& red, int& blue)
{
    //             
    assert(true);
    //              
    //                                                           
    red = first - 1;
    blue = last + 1;
    int white = last + 1;
    const Track PIVOT = songs[first + (last-first)/2];
    while (red < white - 1)
    {
        const int NEXT = white - 1;
        if(songs[NEXT] < PIVOT)
        {
            red++;
            swap(songs, red, NEXT);
        }
        else if(songs[NEXT] == PIVOT)
            white--;
        else
        {
            white --;
            blue--;
            swap(songs, NEXT, blue);
        }
    }
}

void quicksort2(vector<Track>& songs, int first, int last)
{
//             
    assert(0<=first && last < songs.size());
//              
//                                                                   

    if (first >= last)
        return;

    else
    {

        int red;
        int blue;
        dnf(songs, first, last, red, blue);
        quicksort2(songs, first, red);
        quicksort2(songs, blue, last);

    }
}

//                                                                         
//      

/*
                                                                               
 
                    
                    
                         
                                                      
                            
     
                                   
                               
         
                  
                     
                                   
         
                                     
                    
            
         
                     
                   
                                    
         
     
 

                                                                 
 
               
                                           
                

                      
               

        
     

                
                 
                                           
                                      
                                      

     
 

*/

//                                                                
//      
//                                                                                     

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
    cout << "What do you want to sort?\n1: artist \n2: length" << endl;
    int choice;
    cin >> choice;
    if ( choice == 2)
    {
        sortByLength = true; //                            
    }
    if(choice == 1)
    {
        sortByLength = false; //                             
    }
    cout << "Sorting tracks with quick sort" << endl;
    int size = songs.size();
    quicksort2(songs, 0, size - 1);
    show_all_tracks(songs, NO_OF_SONGS);
    /*                                  
     
                                    
     
    */
    cout << "Sorted." << endl;
}

