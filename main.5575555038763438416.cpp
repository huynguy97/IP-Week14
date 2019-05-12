#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>

//                            
//                        

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

const int MAX_NO_OF_SONGS = 6000;           //                                
vector<Track> data;              //                                     

bool operator<(const Length& a, const Length& b)
{
    if (a.minutes == b.minutes)
    {
        return a.seconds < b.seconds;
    }
    else
        return a.minutes < b.minutes ;
}

bool operator==(const Length& a, const Length& b)
{
    return (a.minutes == b.minutes && a.seconds == b.seconds );
}

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
    return a.artist < b.artist ;
}

bool operator==(const Track& a, const Track& b)
{
    return (a.artist == b.artist && a.cd == b.cd && a.year == b.year && a.track_no == b.track_no);
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
int read_songs (ifstream& infile, vector<Track>& data)
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
            data.push_back (song) ;
            no_of_read_songs++;
        }

//                                     
    }
    while (infile );
    return no_of_read_songs ;
}

int size(vector<Track>& a)
{
    return static_cast<int>(a.size());
}

int read_file (string filename)
{//               
    assert (size (data) == 0) ;
/*                 
                                                                              
                                                                                             
                                        
*/
    ifstream songsDBS (filename.c_str());
    if (!songsDBS)
    {
        cout << "Could not open '" << filename << "'." << endl;
        return -1;
    }
    cout << "Reading '" << filename << "'." << endl;
	const int NO_OF_SONGS = read_songs (songsDBS, data);
	songsDBS.close();
	cout << " Read " << NO_OF_SONGS << " tracks." << endl;
	return NO_OF_SONGS;
}

void show_all_tracks (vector<Track>& data, int no_of_songs)
{//               
    assert (no_of_songs < MAX_NO_OF_SONGS) ;
/*                 
                                                                
*/
    for (int i = 0 ; i < no_of_songs; i++)
        cout << i+1 << ". " << data[i] << endl ;
}

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
//                                                                        
// 
//                 
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
void dnf (vector<Track>& data, int first, int last, int& red, int& blue)
{
    //               
    assert (first >= 0 && last < data.size()) ;
/*                 
                                                                 
*/
    red = first-1;              //               
    blue= last+1;               //                 
    int white= last+1;//                  
    const Track pivot = data [first+(last-first)/2];
    while(red< white- 1)        //                 
    {
        const int NEXT = white- 1;//            
        if(data[NEXT]  < pivot)//                   
        {
            red++;              //                      
            swap (data, red, NEXT);
        }
        else if(data[NEXT]  == pivot)//                  
            white-- ;           //                      
        else                    //                    
        {
            white--;
            blue--;             //                    
            swap (data, NEXT,  blue);
        }
    }
}

//                     
void quicksort(vector<Track>& data, int first, int last)
{
//     
    assert(0 <= first && last < size(data)) ;
    //                                          
    if (first >= last)
        return;
    else
    {
        int red, blue;
        dnf (data, first, last, red,  blue);
        quicksort(data, first, red);
        quicksort(data, blue, last);
    }
}

//                                         
//                                                                               
// 
//                     
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
void dnf_length (vector<Track>& data, int first, int last, int& red, int& blue)
{
    //               
    assert (first >= 0 && last < data.size()) ;
/*                 
                                                                 
*/
    red = first-1;              //               
    blue= last+1;               //                 
    int white= last+1;          //                  
    const Track pivot = data [first+(last-first)/2];
    while(red < white - 1)        //                   
    {
        const int NEXT = white- 1;//            
        if(data[NEXT].time  < pivot.time)//                    
        {
            red++;                 //                       
            swap (data, red, NEXT);
        }
        else if(data[NEXT].time  == pivot.time)//                   
            white-- ;           //                        
        else                    //                     
        {
            white--;
            blue--;             //                     
            swap (data, NEXT,  blue);
        }
    }
}

//                     
void quicksort_length(vector<Track>& data, int first, int last)
{
//     
    assert(0 <= first && last < size(data)) ;
    //                                          
    if (first >= last)
        return;
    else
    {
        int red, blue;
        dnf_length(data, first, last, red,  blue);
        quicksort_length(data, first, red);
        quicksort_length(data, blue, last);
    }
}

//       
void sort(vector<Track>& v, int n)
{
    //               
    assert (n >= 0 && n < data.size()) ;
/*                 
                      
*/
    while(n > 1)
    {
        //                      
        int POS = 0;
        for (int i = 0; i < n; i++)
        {
            if (v[POS] < v[i])
            {
                POS = i;
            }
        }

        //             
        swap (v, POS, n-1) ;
        n--;
    }
}

int main()
{
    read_file("Tracks.txt");
    quicksort(data, 0, data.size()-1);
    //                                         
    //                          
    show_all_tracks(data, data.size()-1);
    return 0;
}

