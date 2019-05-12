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

const int MAX_NO_OF_SONGS = 6000;           //                                
vector<Track> songs;                        //                                     

/*                                                                       
                                
                                                               
                                                                         
                                                                       */
bool operator<(const Length& a, const Length& b)
{
    if (a.minutes == b.minutes)
    {
        return a.seconds < b.seconds;
    }
    else
    {
        return a.minutes < b.minutes;
    }
}
bool operator==(const Length& a, const Length& b)
{
    return a.minutes == b.minutes && a.seconds == b.seconds;
}

/*
                                              
 

                            
     
                         
         
                                
             

                                               

             
                
             
                                       
             
         
            
         
                               
         
     
        
     
                                                                                      
     

 

*/
bool operator< (const Track& a, const Track& b)
{

    if (a.time == b.time)
    {
        if (a.artist == b.artist)
        {
            if (a.title == b.title)
            {
                if (a.cd == b.cd)
                {
                   return a.track_no < b.track_no;
                }
                else
                {
                return a.cd < b.cd;
                }

            }
            else
            {
                return a.title < b.title;
            }

        }
        else
        {
            return a.artist == b.artist;
        }
    }
    else
    {
        return a.time < b.time;
    }

}

bool operator==(const Track& a, const Track& b)
{

    return a.artist == b.artist && a.cd == b.cd && a.country == b.country && a.tags == b.tags && a.time == b.time && a.title == b.title && a.track_no == b.track_no && a.year == b.year ;   /*                                                 */
    //                        
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

int size (vector<Track> v)
{
    return static_cast<int> (v.size());
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
    //                            
/*                 
                                                                              
                                                           
*/
    do {
        Track song ;
        infile >> song ;
        if (infile)
        {
            songs.push_back(song); //                                  

        }

    }
    while (infile); //                
    return size(songs) ;
}

int read_file (string filename)
{//               
    assert (size(songs) == 0) ;
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
void show_all_tracks (vector<Track> songs, int no_of_songs)
{//               
    assert (no_of_songs < MAX_NO_OF_SONGS) ;
/*                 
                                                                  
*/
    for (int i = 0 ; i < no_of_songs; i++)
    {
        cout << i+1 << ". " << songs[i] << endl ;
    }

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
void dnf (vector<Track>& songsDBS, int first, int last, int& red, int& blue)
{
    //              
    assert(first >= 0 && last <= size(songsDBS));

    //               
    //                                                                                                                                            

    //                
    red = first-1;
    blue = last+1;
    int white = last+1;
    const Track PIVOT = songsDBS[first+(last-first)/2];
    while (red < white-1)
    {
        const int NEXT = white-1;
        if (songsDBS[NEXT] < PIVOT)
        {
            red++;
            swap(songsDBS, red, NEXT);
        }
        else if (songsDBS[NEXT] == PIVOT)
        {
            white--;
        }
        else
        {
            white--;
            blue--;
            swap(songsDBS, NEXT, blue);
        }
    }
}
//                              
void dnf_alt (vector<Track>& songsDBS, int first, int last, int& red, int& blue)
{

    //              
    assert(first >= 0 && last <= size(songsDBS));

    //               
    //                                                                                                                                            

    //                
    red = first-1;
    blue = last+1;
    int white = first-1;
    const Track PIVOT = songsDBS[first+(last-first)/2];
    while (white < blue-1)
    {
        const int NEXT = white+1;
        if (songsDBS[NEXT] < PIVOT)
        {
            red++;
            white++;
            swap(songsDBS, red, NEXT);
        }
        else if (songsDBS[NEXT] == PIVOT)
        {

            white++;
        }
        else
        {

            blue--;
            swap(songsDBS, blue, NEXT);

        }
    }
}

void quicksort (vector<Track>& songsDBS, int first, int last)
{
    //              
    assert(first >= 0 && last <= size(songsDBS));

    //               
    //                                   

    //                
    if (first >= last)
    {
        return;
    }
    else
    {
        int red;
        int blue;
        dnf_alt(songsDBS, first, last, red, blue);
        quicksort(songsDBS, first, red);
        quicksort(songsDBS, blue, last);
    }
}

//                                           
void swap_it (vector<int>& data, int  i, int  j )
{//	              
	assert ( i >= 0 && j >= 0 ) ;	//                         
						            //                         
//                                                                
	const int HELP = data [i];
	data [i] = data [j] ;
	data [j] = HELP;
}

//                               
int largest_it (vector<int>& vec, int low, int up)
{
    //              
    assert(low >= 0 && up <= vec.size()-1);

    //               
    //                                                                     

    //                
    int pos = low+1;
    while (low < up)
    {
        if (vec[low] < vec[pos])
        {
            low++;

        }
        else if (pos <= up)
        {
            pos++;
        }
        else
        {
            return low;
        }

    }
    return pos;
}

//                            
void sort_it (vector<int>& vec, int n)
{

    //              
    assert(n <= vec.size()-1);

    //               
    //                                                      

    //                
    while (n > 1)
    {

        const int POS = largest_it(vec, 0, n);
        swap_it(vec, POS, n);
        n--;

    }
}
//                               
void print_vec (vector<int>& vec)
{
    //              
    assert(true);

    //               
    //                                                   

    //                
    cout << "[" ;
    for (int i = 0; i < vec.size()-1; i++)
    {
        cout << vec[i] << ","  ;
    }
    cout << vec[vec.size()-1] << "]" << endl;
}

int main()
{
    //                         
    read_file("Tracks.txt");
    quicksort(songs, 0, size(songs)-1);
    show_all_tracks(songs, size(songs)-1);

    //                                     
    vector<int> vec = {10,81,20,11};
    cout << "The unsorted vector:    ";
    print_vec(vec);
    sort_it(vec, vec.size()-1);
    cout << "The sorted vector:      ";
    print_vec(vec);

    return 0;
}

