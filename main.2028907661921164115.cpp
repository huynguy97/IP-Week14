/*                                                           
                             
                             
                                       
                                                           */

#include <iostream>
#include <vector>
#include <cassert>

#include <fstream>  //                                  
#include <string>   //                                      
//                                                                                                
#include <cstring>  //                                     

//                                                                                      

using namespace std;

/*                                                           
                       
                                                           */

struct Length
{
    int minutes;                            //               
    int seconds;                            //                 
};

struct Track
{
    string artist;                          //            
    string cd;                              //         
    int    year;                            //                   
    int    track_no;                        //             
    string title;                           //            
    string tags;                            //                            
    Length time;                            //             
    string country;                         //                                         
};

vector<Track> music ;

/*                                                                       
                                           
                                                                       */

/*                               */
bool operator<(const Length& a, const Length& b)
{
    if (a.minutes  ==   b.minutes)
            return (a.seconds   <   b.seconds);
    else    return (a.minutes    <  b.minutes);
}

bool operator==(const Length& a, const Length& b)
{
    if (a.minutes  ==   b.minutes)
        return (a.seconds   ==   b.seconds);
    else    return (a.minutes    !=  b.minutes);
}

//                                    
bool operator>(const Length& a, const Length& b)
{
    return b < a ;
}

bool operator<=(const Length& a, const Length& b)
{
    return !(b < a) ;
}

bool operator>=(const Length& a, const Length& b)
{
    return b <= a ;
}

bool operator!=(const Length& a, const Length& b)
{
    return a.minutes != b.minutes || a.seconds != b.seconds;
}

/*                              */
bool operator<(const Track& a, const Track& b)
{
//                         
//     
//                               
//     
    if (a.artist != b.artist)
    {
         return a.artist < b.artist;
    }
    else if (a.cd != b.cd)
    {
         return a.cd < b.cd;
    }
    else if (a.year != b.year)
    {
        return a.year < b.year;
    }
    else if (a.track_no != b.track_no)
    {
        return a.track_no < b.track_no;
    }
    return false;
}

bool operator==(const Track& a, const Track& b)
{
    return /*                    */a.artist == b.artist && a.cd == b.cd && a.year == b.year && a.track_no == b.track_no;
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

/*                                */
istream& operator>> (istream& in, Length& length)
{//               
    assert (true) ;
/*                 
                                                                                                      
*/
    char colon ;
    in >> length.minutes >> colon >> length.seconds ;
    return in ;
}

ostream& operator<< (ostream& out, const Length length)   //                          
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

/*                               */
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

int read_songs (ifstream& infile, vector<Track>& music)
{//               
    assert (infile.is_open ()) ;
/*                 
                                                                              
                                                           
*/
    int no_of_read_songs = 0 ;
    do {
        Track song ;
        infile >> song ;
//                                                
        if (infile)
        {
//                                                                                 
            music.push_back(song);
            no_of_read_songs++ ;
        }
    }
    while (infile);
    return no_of_read_songs ;
}

int read_file (string filename)
{//               
    assert (music.size() == 0) ;
/*                 
                                                                              
                                                                                             
                                        
*/
    ifstream songsDBS (filename.c_str());
    if (!songsDBS)
    {
        cout << "Could not open '" << filename << "'." << endl;
        return -1;
    }
    cout << "Reading '" << filename << "'." << endl;
    const int NO_OF_SONGS = read_songs (songsDBS, music);
    songsDBS.close();
    cout << " Read " << NO_OF_SONGS << " tracks." << endl;
    return NO_OF_SONGS;
}

void show_all_tracks (vector<Track>& data, int no_of_songs)
{//               
    assert (true) ;
/*                 
                                                          
*/
    for (int i = 0 ; i < no_of_songs; i++)
        cout << i+1 << ". " << data[i] << endl ;
}

/*                                                           
                                         
                                                           */

//                  
//                        
//                
//                                                                                                                                          
//                                                               

//           
vector<int> testvector {8, 9, 24, 1, 18, 65, 23, 7, 3};

//                
vector<int> data;

//                              
void show_vector (vector<int>& to_show)
{
    for (unsigned int i = 0; i < to_show.size(); i++)
    {
        cout << to_show[i] << ' ';
    }
    cout << endl << endl;
}

//             
void swapper(vector<Track>& data, int a, int b)
{   /*                  */
    assert (a >= 0 && b >= 0 && a < data.size() && b < data.size());  //                                                               
    /*                
                                                                                         
    */
    Track temp = data[a];
    data[a] = data[b];
    data[b] = temp;
}

//                   
void dnf (vector<Track>& data, int first, int last, int& red, int& blue)
{   /*                  */
    assert (true);
    /*                
                                                                                                                                                  
                                                                                                                    
                                                                                 
                                                                                                              
    */
    red = first-1;
    blue = last+1;
    int white = last+1;
    const Track PIVOT = data[first+(last-first)/2];
    while (red < white - 1)
    {
        const int NEXT = white -1;
        if (data[NEXT] < PIVOT)
        {
            red++;
            swapper(data, red, NEXT);
        }
        else if (data[NEXT] == PIVOT)
            white--;
        else
        {
            white--;
            blue--;
            swapper(data, NEXT, blue);
        }
    }
}

//         
void quicksort (vector<Track>& data, int first, int last)
{   /*                  */
    assert (0 <= first && last < (int) data.size());  //                                                                         
    /*                
                                                             
                                                                                                                    
                                                                                                           
    */
    if (first >= last)
        return;
    else
    {
        int red, blue;
        dnf (data, first, last, red, blue);
        quicksort(data, first, red);
        quicksort(data, blue, last);
    }
}

/*                                                           
                                    
                                                           */

//                                                                
//                                            

//                                             

void dnf_adjusted (vector<Track>& data, int first, int last, int& red, int& blue)
{   /*                  */
    assert (true);
    /*                
                                                                                                                                                  
                                                                                                                    
                                                                                 
                                                                                                              
    */
    red = first-1;
    blue = last+1;
    int white = first-1; //                         
    const Track PIVOT = data[first+(last-first)/2];
    while (blue > white + 1)
    {
        const int NEXT = white +1; //                                   
        if (data[NEXT] < PIVOT) //                                                                                           
        {
            red++;
            white++;
            swapper(data, red, NEXT);
        }
        else if (data[NEXT] == PIVOT) //                                         
            white++;
        else //                                                                      
        {
            blue--;
            swapper(data, NEXT, blue);
        }
    }
}

void quicksort_part_2 (vector<Track>& data, int first, int last)
{   /*                  */
    assert (0 <= first && last < (int) data.size());  //                                                                         
    /*                
                                                             
                                                                                                                    
                                                                                                           
    */
    if (first >= last)
        return;
    else
    {
        int red, blue;
        dnf_adjusted(data, first, last, red, blue);
        quicksort(data, first, red);
        quicksort(data, blue, last);
    }
}

/*                                                           
                                              
                                                           */

//                                                   
/*                 
                  
                */
//               
//
//                                            
// 
//                  
//                   
//        
//     
//                                              
//                            
//                       
//            
//                       
//     
// 
//
//                                
// 
//              
//     
//                                            
//                           
//                      
//     
// 
//
//
//                   
//                 
//                  
//                                                      
// 
//                      
//                       
//     
//                             
//                      
//     
//                  
//                            
//     
//                                     
//                         
//                            
//                      
//            
//                       
//     
// 
//
//                                          
// 
//            
//                 
//     
//                                                   
//                         
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

    quicksort(music, 0, music.size()-1);
    //                                           
    show_all_tracks(music, music.size());
    cout << "\n\n\nIt was nice to have known you, my dear friend." << endl;
    cout << "Goodbye to thee." << endl;
    cout << "*bows gracefully*" << endl;
    cout <<"\n\n\n PS. FIJNE VAKANTIE EN ALVAST EEN GELUKKIG NIEUWJAAR!" << endl;

//                                              
//                                                        

    return 0;
}

