
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>
#include<cmath>
#include<vector>

/*                                                                    
                         
                            
                                                                     */

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

const int MAX_NO_OF_SONGS = 6000;           //                                
Track songs [MAX_NO_OF_SONGS];              //                                     

/*                                                                       
                                
                                                               
                                                                         
                                                                       */
string string_to_lowercase(string input) //                
{
	for(int i = 0; i < input.length(); i++)
		if(input[i] >= 65 && input[i] <= 90)
			input[i] = input[i] + 32;
	return input;
}

bool operator<(const string& q, const string& r)
{	//            
	//	                      
	//	                                      
	//	         
	//	                                                             
	//	                                        
	int i = 0;
	string a, b;
	a = string_to_lowercase(q);
	b = string_to_lowercase(r);
	while(a[i] == b[i] && i < a.length() && i < b.length() )
		i++; //                                            
	if(i == a.length() || i == b.length())
		return a.length() < b.length();
	return a[i] < b[i];
}

bool operator<(const Track& a, const Track& b)
{
	//            
	//	                                
	//	                                  
	//	                                         
	// 	                                             

	//   
    if(a.artist == b.artist)
			if(a.cd == b.cd) //   
				return a.track_no < b.track_no;
			else //   
				return a.cd < b.cd;
	else
		return a.artist < b.artist;
}

bool operator==(const Track& a, const Track& b)
{
	bool q = a.artist == b.artist;
	bool r = a.cd == b.cd;
	bool s = a.title == b.title;
	bool t = a.track_no == b.track_no;
	return q && r && s && t;
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

int length_to_int(Length input)
{
	return input.minutes * 60 + input.seconds;
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
int read_songs (ifstream& infile, Track songs [MAX_NO_OF_SONGS])
{//               
    assert (infile.is_open ()) ;
/*                 
                                                                              
                                                           
*/
    int no_of_read_songs = 0 ;
    do {
        Track song ;
        infile >> song ;
        if (infile)
            songs[no_of_read_songs++] = song ;
    }
    while (infile && no_of_read_songs < MAX_NO_OF_SONGS);
    return no_of_read_songs ;
}

int read_file (string filename)
{//               
    assert (true) ;
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

string fix(string input)
{
		return input.erase(input.size() - 1);
}

//                                                                           
void show_all_tracks (Track songs [MAX_NO_OF_SONGS], int no_of_songs)
{//               
    assert (no_of_songs < MAX_NO_OF_SONGS) ;
/*                 
                                                                  
*/
    for (int i = 0 ; i < no_of_songs; i++)
	{
        cout << i << ") ";
		cout << fix(songs[i].artist) << " (";
		cout << songs[i].track_no;
		cout << ") " << fix(songs[i].cd) << " ";
		cout << " runtime: " << length_to_int(songs[i].time) << " seconds" << endl;

	}
}

/* 
 		             
*/

void swap(Track songs [MAX_NO_OF_SONGS], int a, int b)
{
	//                         
	if(a == b) return;

	const Track HELP = songs[a];
	songs[a] = songs[b];
	songs[b] = HELP;
}

//                            
void dnf(Track songs [MAX_NO_OF_SONGS], int first, int last, int& red, int& blue)
{
	//                                              
	red 		= first - 1;
	blue		= last + 1;
	int white	= last + 1;
	const Track PIVOT = songs[ first + (last - first) / 2 ];

	while(red < white - 1)
	{
		const int NEXT = white - 1;
		if( songs[NEXT] < PIVOT )
		{
			red++;
			swap(songs, red, NEXT);
		}
		else if ( songs[NEXT] == PIVOT )
		{
			white--;
		}
		else
		{
			white--;
			blue--;
			swap(songs, NEXT, blue);
		}
	}
}

void quicksort(Track songs [MAX_NO_OF_SONGS], int first, int last)
{
	//           
	//                                                                         
	//            
	//                                  
	if(first >= last)
		return;
	else
	{
		int red, blue;
		dnf(songs, first, last, red, blue);
		quicksort(songs, first, red);
		quicksort(songs, blue, last);
	}
}

/* 
 	                 
*/

void dnf_runtime(Track songs [MAX_NO_OF_SONGS], int first, int last, int& red, int& blue)
{
	//                                              
	red 		= first - 1;
	blue		= last + 1;
	int white	= last + 1;
	const int PIVOT = length_to_int(songs[ first + (last - first) / 2 ].time);

	while(red < white - 1)
	{
		const int NEXT = white - 1;
		if( length_to_int(songs[NEXT].time) < PIVOT )
		{
			red++;
			swap(songs, red, NEXT);
		}
		else if ( length_to_int(songs[NEXT].time)  == PIVOT )
		{
			white--;
		}
		else
		{
			white--;
			blue--;
			swap(songs, NEXT, blue);
		}
	}

}

void runtimeQuickSort(Track songs [MAX_NO_OF_SONGS], int first, int last)
{
	//           
	//                                                                         
	//            
	//                                  
	if(first >= last)
		return;
	else
	{
		int red, blue;
		dnf_runtime(songs, first, last, red, blue);
		runtimeQuickSort(songs, first, red);
		runtimeQuickSort(songs, blue, last);
	}
}

/* 
 		                
*/

int largest (vector<int>& v, int low, int up)
{
	if (low >= up)
		return low;
	else
	{
		const int POS = largest(v, low + 1, up);
		if (v[low] > v[POS])
			return low;
		else
			return POS;
	}
}

int largest_iterative (vector<int>& v, int up = -1)
{
	int low = 0;
	if(up == -1)
		up = v.size();

	vector<int> stack;
	if(up == low)
		return up;

	while(! (low >= up) )
		stack.push_back(low++);

	int pos = stack.back();
	while( stack.size() > 0 )
	{
		if(v[stack.back()] > v[pos])
			pos = stack.back();
		stack.pop_back();
	}

	return pos;
}

void int_swap (vector<int>& v, int a, int b)
{
	const int HELP = v[a];
	v[a] = v[b];
	v[b] = HELP;
}

void rec_sort (vector<int>& v, int n)
{
	if (n > 1)
	{
		const int POS = largest (v, 0, n-1) ;
		int_swap (v, POS, n-1) ;
		rec_sort (v, n-1) ;
	}
}

void dump_integer ( vector<int>& v )
{
	cout << "(";
	for(int i = 0; i < v.size(); i++)
		cout << v[i] << ", ";
	cout << ")" << endl;
}

void iterative_sort(vector<int>& v)
{
	vector<int> stack;

	int n = 0;

	while(n < v.size())
		stack.push_back(n++);

	dump_integer(stack);
	while(stack.size() > 0)
	{
		const int POS = largest_iterative(v, stack.back() + 1);
		int_swap (v, POS, stack.back());
		dump_integer(v);
		stack.pop_back();
	}
}

int main()
{
	/*
	                                                           
	                  
	                
	*/

	const int NO_OF_SONGS = read_file ("Tracks.txt");
	if (NO_OF_SONGS < 0)
	{
        cout << "Reading file failed. Program terminates." << endl;
	    return NO_OF_SONGS;
    }
	quicksort(songs, 0, NO_OF_SONGS - 1); //                          
	//                                                            
    show_all_tracks (songs, NO_OF_SONGS);
	return 0;
}

