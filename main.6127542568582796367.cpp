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

int size(vector<Track>& v)
{
    return static_cast<int>(v.size());
}

//                     

//                                                 
//  
bool operator<(const Track& a, const Track& b)
{
    //               
    if(a.artist == b.artist)
        if(a.cd == b.cd)
            if(a.year == b.year)
                if(a.track_no == b.track_no)
                    return a.title < b.title;
                else return a.track_no < b.track_no;
            else return a.year < b.year;
        else return a.cd < b.cd;
    else return a.artist < b.artist;
}

bool operator==(const Track& a, const Track& b)
{
    //               
    return (a.artist == b.artist) &&
            (a.cd == b.cd) &&
            (a.year == b.year) &&
            (a.track_no == b.track_no) &&
            (a.title == b.title);
}
//                                                            

//                 
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

//
istream& operator>> (istream& infile, Track& track)
{//               
    assert (true) ;
/*                 
                                                                                                                   
                                      
*/
    string to_ignore;

    getline(infile,track.artist);       //       
    getline(infile,track.cd);           //   
    infile >> track.year ;              //     
    getline (infile, to_ignore) ;
    infile >> track.track_no ;          //             
    getline (infile, to_ignore) ;
    getline(infile,track.title);        //            
    getline(infile,track.tags);         //           
    infile >> track.time ;              //           
    getline (infile, to_ignore) ;
    getline(infile,track.country);      //        
    getline (infile, to_ignore) ;
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

//
int read_songs (ifstream& infile, vector<Track>& songs)
{//               
    assert (infile.is_open ()) ;
/*                 
                                                                              
                                                           
*/
    //                          
    do {
        Track song ;
        infile >> song ;
        if (infile)
            songs.push_back(song);
    }
    while (infile);
    return songs.size();
}

//
int read_file (vector<Track>& songs, string filename)
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
    const int NO_OF_SONGS = read_songs (songsDBS, songs);
	songsDBS.close();
	return NO_OF_SONGS;
}

void show_all_tracks (vector<Track>& songs)
{//               
    assert (true) ;
/*                 
                                                                  
*/
    const int no_of_songs = size(songs) -1;
    for (int i = 0 ; i <= no_of_songs; i++)
        cout << i+1 << ". " << songs[i] << endl ;
}

//
int read_tracks(vector<Track>& songs)
{//            
    assert(true);
/*             
                                                                                                        
                           
*/
    songs.clear();
    const int NO_OF_SONGS = read_file (songs, "Tracks.txt");
	if (NO_OF_SONGS < 0)
	{
        cout << "Reading file failed. Program terminates." << endl;
	    return NO_OF_SONGS;
	}
	return NO_OF_SONGS;
}

void swap(vector<Track>& data, int a, int b)
{//            
    assert(a >=0 && b >= 0);
    //             
    //                                             

    Track temp = data[a];
    data[a] = data[b];
    data[b] = temp;
}

//               
void dnf(vector<Track>& data, int first, int last, int& red, int& blue)
{//            
    assert(first >= 0 && last >= 0);
    //             
    //                                                        
    //                                                        

    red = first-1;
    blue = last+1;
    int white = last+1;
    const Track PIVOT = data[first+(last-first)/2];
    while(red < white -1)
    {
        const int NEXT = white - 1;
        if(data[NEXT] < PIVOT)
        {
            red++;
            swap(data, red, NEXT);
        }
        else if(data[NEXT] == PIVOT)
            white--;
        else
        {
            white--;
            blue--;
            swap(data, NEXT, blue);
        }
    }
}

void quicksort(vector<Track>& data, int first, int last)
{//            
    assert(first >= 0 && last >= 0);
    //              
    //                                                                         

    if(first >= last)
        return;
    else
    {
        int red;
        int blue;
        dnf(data, first, last, red, blue);
        quicksort(data, first, red);
        quicksort(data, blue, last);
    }
}

//       
void dnf2(vector<Track>& data, int first, int last, int& red, int& blue)
{//             
    assert(first >= 0 && last >= 0);
    //             
    //                                                        
    //                                                        

    red = first-1;
    blue = last+1;
    int white = first-1;
    const Track PIVOT = data[first+(last-first)/2];
    while(white < blue -1)
    {
        const int NEXT = white +1;
        if(data[NEXT] < PIVOT)
        {
            white++;
            red++;
            swap(data, red, NEXT);
        }
        else if(data[NEXT] == PIVOT)
            white++;
        else
        {
            blue--;
            swap(data, NEXT, blue);
        }
    }
}

void quicksort2(vector<Track>& data, int first, int last)
{//             
    assert(first >= 0 && last >= 0);
    //              
    //                                                                         

    if(first >= last)
        return;
    else
    {
        int red;
        int blue;
        dnf2(data, first, last, red, blue);
        quicksort2(data, first, red);
        quicksort2(data, blue, last);
    }
}

//       
int largest_iteration(vector<Track>& v, int low, int up)
{//            
    assert(low >= 0 && up >= 0);
    //              
    //                                                                                                    

    int largest = low;
    while(low < up){
        low++;
        if(v[low] > v[largest])
            largest = low;
    }
    return largest;
}

void sort_iteration(vector<Track>& v, int n)
{//             
    assert(n >= 0);
    //              
    //                                                                     

    while(n > 1)
    {
        const int POS = largest_iteration(v, 0, n-1);
        swap(v, POS, n-1);
        n--;
    }
}

int largest(vector<Track>& v, int low, int up)
{//            
    assert(low >= 0 && up >= 0);
    //              
    //                                                                                                    

    if(low >= up)
        return low;
    else{
        const int POS = largest(v, low+1, up);
        if(v[low] > v[POS])
            return low;
        else
            return POS;
    }
}

void sort(vector<Track>& v, int n)
{//             
    assert(n >= 0);
    //              
    //                                                                     

    if(n > 1)
    {
        const int POS = largest(v, 0,n-1);
        swap(v, POS, n-1);
        sort(v, n-1);
    }
}

//                                                    
//                                                    

int main()
{
    vector<Track> songs;
    read_tracks(songs);
    //                            
    //                                    
    //                         
    sort_iteration(songs, size(songs));
    show_all_tracks(songs);
    return 0;
}

