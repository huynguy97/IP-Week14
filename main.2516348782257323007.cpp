#include <iostream>
#include <vector>
#include <fstream>
#include <istream>
#include <string>
#include <cassert>

using namespace std;

//                                 

//       

/*
                                                                                                              
             

                                                                                                                
                                                                                                                     
                                                                                                      
*/

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

int size (vector<Track>& v)
{
//                
    assert (true);
//                 
//                                                       
    return static_cast<int> (v.size());
}

/*                             */
bool operator<(const Length& a, const Length& b)
{
    if (a.minutes == b.minutes)
        return a.seconds < b.seconds;
    else return a.minutes < b.minutes;
}

bool operator==(const Length& a, const Length& b)
{
    return a.minutes == b.minutes && a.seconds == b.seconds;
}

bool operator<(const Track& a, const Track& b)
{
    if (a.artist == b.artist)
        if (a.cd == b.cd)
            if (a.year == b.year)
                return a.track_no < b.track_no;
            else return a.year < b.year;
        else return a.cd < b.cd;
    else return a.artist < b.artist;

}

bool operator==(const Track& a, const Track& b)
{
    return (a.artist == b.artist && a.title == b.title && a.year == b.year && a.track_no == b.track_no) ;
}

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

void skip_to_WHITE_newline (istream& infile)
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
    skip_to_WHITE_newline(infile) ;
    infile >> track.track_no ;          //             
    skip_to_WHITE_newline(infile) ;
    getline(infile,track.title);        //            
    getline(infile,track.tags);         //           
    infile >> track.time ;              //           
    skip_to_WHITE_newline(infile) ;
    getline(infile,track.country);      //        
    skip_to_WHITE_newline(infile) ;
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
        {
            songs.push_back(song);
            no_of_read_songs++;
        }
    }
    while (infile);
    return no_of_read_songs ;
}

int read_file (string filename)
{//               
    assert (size (songs) >= 0) ;
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

void show_all_tracks (vector<Track>& songs, int no_of_songs)
{//               
    assert (no_of_songs <= size(songs)) ;
/*                 
                                                                  
*/
    for (int i = 0 ; i < no_of_songs; i++)
        cout << i+1 << ". " << songs[i] << endl ;
}

/*                                                                                                                  */

void swap(vector<Track>& data, int a, int b)
{
    //               
    assert(size(data) >= 0 && a >= 0 && a <= size(data) && b >= 0 && b <= size(data));
    /*                
                                                     */

    const Track temp = data[a];
    data[a] = data[b];
    data[b] = temp;
}

void dnf (vector<Track>& data, int first, int last, int& red, int& blue)
{
    //               
    assert(size(data) >= 0 && first >= 0 && last <= size(data));
    /*                
                                                  */

    red		= first-1;								//               
	blue		= last+1;								//                 
	int white	= last+1;								//                  
	const Track PIVOT = data [first+(last-first)/2];
	while (red < white - 1)							//                 
	{	const int WHITE = white - 1;				//            
		if (data[WHITE] < PIVOT)					//               
		{	red++;	                					//                       
			swap (data, red, WHITE) ;
		}
		else if (data[WHITE] == PIVOT)			//                 
			white-- ;									//                      
		else											//                
		{
		    white--;
            blue--;							//                     
			swap (data, WHITE, blue);
		}
	}
}

void second_dnf (vector<Track>& data, int first, int last, int& red, int& blue)
{
    //               
    assert(size(data) >= 0 && first >= 0 && last <= size(data));
    /*                
                                                  */

    red		= first-1;								//               
	blue		= last+1;								//                 
	int orange	= last+1;								//                   
	const Track PIVOT = data [first+(last-first)/2];
	while (red < orange - 1)							//                 
	{	const int WHITE = orange - 1;				//            
		if (data[WHITE] < PIVOT)					//               
		{	red++;	                					//                       
			swap (data, red, WHITE) ;
		}
		else if (data[WHITE] == PIVOT)			//                  
			orange-- ;									//                       
		else											//                
		{
		    orange--;
            blue--;							//                      
			swap (data, WHITE, blue);
		}
	}
}

void quicksort (vector<Track>& data, int first, int last)
{
    //               
    assert (0 <= first && last < size (data));
    /*                
                                         */

    if (first >= last)
        return;
    else
    {
        int red, blue ;
        //                                   
        second_dnf (data, first, last, red, blue);  //                                            
        quicksort (data, first, red);
        quicksort (data, blue, last);
    }
}

vector<int> test = {50, 21, 52, 2, 1, -54, 25 , 75, 69, -3};

int size (vector<int>& v)
{
//                
    assert (true);
//                 
//                                                       
    return static_cast<int> (v.size());
}

void show_ints (vector<int>& v)
{
    //               
    assert(size(v) >= 0);
    /*                
                                           */

    for (int i = 0; i < size(v); i++)
    {
        cout << v[i] << ' ';
    }
    cout << endl;
}

int largest (vector<int>& v, int low, int up)
{
    //              
    assert(size(v) >= 0 && low >= 0 && up >= 0);
    /*                
                                */

    int result = v[low];        //                                 
    int index = 0;              //                                       
    while (low <= up)
    {
        if (result < v[low])
        {
            result = v[low];
            index = low;
        }
        low++;
    }
    return index;
}

void second_swap (vector<int>& v, int a, int b)
{
    //               
    assert(size(v) >= 0 && a >= 0 && a <= size(v) && b >= 0 && b <= size(v));
    /*                
                                            */

    const int temp = v[a];
    v[a] = v[b];
    v[b] = temp;
}

void sort (vector<int>& v, int n)
{
    //              
    assert(size(v) >= 0 && n >= 1);
    /*                             */

    while (n > 1)
    {
        const int POS = largest(v, 0, n-1);
        second_swap(v, POS, n-1);
        n--;
    }
}

int main()
{
//                                                     
//	                    
//	 
//                                                                   
//	                       
//     
//
//                                       
//                                        

/*                                                                                      */

    sort(test, size(test));
    show_ints(test);
    return 0;
}

