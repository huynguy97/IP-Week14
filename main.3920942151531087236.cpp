#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>

using namespace std;

/*
                                                  

                                                

                                                  

                                          
                                          

                                                  
*/

const char SORT_A_OR_B = 'B'; //                                                                                                

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

typedef Track El;

vector<Track> songs;                        //                                            

int size (vector<Track>& tracks)
{//               
    assert(true);
/*                 
                                                                            
*/  return static_cast<int>(tracks.size());
}

/*                                                                       
                                 
                                                               
                                                                         
                                                                       */
bool operator<(const Length& a, const Length& b)
{//               
    assert(true);
/*                 
                                                       
                             
*/  if (a.minutes == b.minutes)
        return a.seconds < b.seconds;
    else
        return a.minutes < b.minutes;
}

bool operator==(const Length& a, const Length& b)
{//               
    assert(true);
/*                 
                                                   
                             
*/  return (a.minutes == b.minutes) && (a.seconds == b.seconds);
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

/*                                                                       
                                
                                                               
                                                                         
                                                                       */
int counter = 0; //                                                                  

bool operator<(const Track& a, const Track& b)
{//               
    assert(true);
/*                 
                                                                                                               
                             
*/  counter++;

    //                               
    if (SORT_A_OR_B == 'B')
    {
        if (a.time == b.time)
        {
            if (a.artist == b.artist)
            {
                if (a.title == b.title)
                    return a.cd < b.cd;
                else
                    return a.title < b.title;
            } else {
                return a.artist < b.artist;
            }
        } else {
            return a.time < b.time;
        }
    }

    //                               
    if (SORT_A_OR_B == 'A')
    {
        if (a.artist == b.artist)
        {
            if (a.cd == b.cd)
            {
                if (a.year == b.year)
                    return a.track_no < b.track_no;
                else
                    return a.year < b.year;
            } else {
                return a.cd < b.cd;
            }
        } else {
            return a.artist < b.artist;
        }
    }
}

bool operator==(const Track& a, const Track& b)
{//               
    assert(true);
/*                 
                                                 
                             
*/  counter++;

//                               
    if (SORT_A_OR_B == 'B')
        return (a.time == b.time) && (a.artist == b.artist) && (a.title == b.title) && (a.cd == b.cd);

//                               
    if (SORT_A_OR_B == 'A')
        return (a.artist == b.artist) && (a.cd == b.cd) && (a.year == b.year) && (a.track_no == b.track_no);
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

int read_songs (ifstream& infile, vector<Track>& songs)
{//               
    assert (infile.is_open ()) ;
/*                 
                                                                              
                                                           
*/
    do {
        Track song ;
        infile >> song ;
        if (infile)
            songs.push_back(song);
    }
    while (infile);
    return size(songs) ;
}

int read_file (string filename)
{//               
    assert (true) ;
/*                 
                                                                              
                                                                                             
                                        
*/
    while (size(songs) > 0) { //                                
        songs.pop_back();
    }

    ifstream songsDBS (filename.c_str());
    if (!songsDBS)
    {
        cout << "Could not open '" << filename << "'." << endl;
        return -1;
    }
    //                                                
	const int NO_OF_SONGS = read_songs (songsDBS, songs);
	songsDBS.close();
	//                                                      
	return NO_OF_SONGS;
}

void show_all_tracks (vector<Track>& songs, int no_of_songs)
{//               
    assert (true) ;
/*                 
                                                                  
*/
    for (int i = 0; i < no_of_songs; i++)
        cout << i+1 << ". " << songs[i] << endl ;
}

/*                                                                    
                      
                                                                     */

void swap (vector<El>& data, int  i, int  j)
{//	              
	assert ( i >= 0 && j >= 0 ) ;	//                         
						            //                         
//                                                                
	const El HELP = data [i];
	data [i] = data [j] ;
	data [j] = HELP;
}

void dnf_1(vector<El>& data, int first, int last, int& red, int& blue)
{//               
    assert(first >= 0 && last < size(data));
/*                 
                                                                                                          
*/  red = first - 1;
    blue = last + 1;
    int white = last + 1;
    const El PIVOT = data[first + (last-first) / 2];
    while (red < white - 1)
    {
        const int NEXT = white - 1;
        if (data[NEXT] < PIVOT)
        {
            red++;
            swap(data, red, NEXT);
        } else if (data[NEXT] == PIVOT)
            white--;
        else
        {
            white--;
            blue--;
            swap(data, NEXT, blue);
        }
    }
}

void quicksort_1(vector<El>& data, int first, int last)
{//               
    assert(first >= 0 && last < size(data));
/*                 
                                                                      
*/  if (first >= last) return;
    else {
        int red, blue;
        dnf_1(data, first, last, red, blue);
        quicksort_1(data, first, red);
        quicksort_1(data, blue, last);
    }
}

void dnf_2(vector<El>& data, int first, int last, int& red, int& blue)
{//               
    assert(first >= 0 && last < size(data));
/*                 
                                                                                                          
                                                                       
*/  red = first - 1;
    blue = last + 1;
    int white = first - 1;
    const El PIVOT = data[first + (last-first) / 2];
    while (white < blue - 1)
    {
        const int NEXT = white + 1;
        if (data[NEXT] < PIVOT)
        {
            red++;
            white++;
            swap(data, red, NEXT);
        } else if (data[NEXT] == PIVOT)
            white++;
        else
        {
            blue--;
            swap(data, NEXT, blue);
        }
    }
}

void quicksort_2(vector<El>& data, int first, int last)
{//               
    assert(first >= 0 && last < size(data));
/*                 
                                                                      
*/  if (first >= last) return;
    else {
        int red, blue;
        dnf_2(data, first, last, red, blue);
        quicksort_2(data, first, red);
        quicksort_2(data, blue, last);
    }
}

/*                                                                    
                                          
                                                                     */

int size(vector<int>& tracks)
{//               
    assert(true);
/*                 
                                                                            
*/  return static_cast<int>(tracks.size());
}

int largest(vector<El>& v, int low, int up)
{//               
    assert(low >=0 && low <= up && up < size(v));
/*                 
                                                          
*/  vector<int> stack;
    while (!(low >= up))
    {
        stack.push_back(low);
        low++;
    }

    int output = low;

    while (size(stack) > 0)
    {
        low = stack[size(stack)-1];
        stack.pop_back();
        if (v[low] > v[output])
            output = low;
    }

    return output;

    //                  
    //              
    //                             
    //                                 
    //             
}

void sort1(vector<El>& v, int n)
{//               
    assert(true);
/*                 
                                            
*/  while(n > 1)
    {
        const int POS = largest(v, 0, n-1);
        swap(v, POS, n-1);
        n--;
    }
}

int main()
{
    const int NO_OF_SONGS = read_file("Tracks.txt");
    if (NO_OF_SONGS < 0)
    {
        cout << "Reading file failed. Program terminates." << endl;
        return NO_OF_SONGS;
    } else {;
        //                                     
        //                           
        sort1(songs, size(songs));
        show_all_tracks(songs, 20);
    }
    return 0;
}

