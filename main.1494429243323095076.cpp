#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>

using namespace std;

//                          
//                            
//                          

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

/*                                                                       
                                           
                                                                       */

//                               
bool operator<(const Length& a, const Length& b)
{
	//              
	assert (true);
	//               
	//                                                                         

	if (a.minutes < b.minutes) return true;
	else if (a.minutes > b.minutes) return false;
	if (a.seconds < b.seconds) return true;
	return false;
}

bool operator==(const Length& a, const Length& b)
{
	//              
	assert (true);
	//               
	//                                                                      

	if (a.minutes == b.minutes && a.seconds == b.seconds) return true;
	return false;
}

//                                                                        

bool operator<(const Track& a, const Track& b)
{ //               
	assert (true);
	//                                                                                      

	if (a.artist < b.artist) return true;
	else if (a.artist > b.artist) return false;
	if (a.cd < b.cd) return true;
	else if (a.cd > b.cd) return false;
	if (a.year < b.year) return true;
	else if (a.year > b.year) return false;
	if (a.track_no < b.track_no) return true;
	else if (a.track_no > b.track_no) return false;
    return false;
}

bool operator==(const Track& a, const Track& b)
{
	//             
	assert(true);
	//               
	//                                                                         

    if (a.artist == b.artist && a.cd == b.cd && a.year == b.year && a.track_no == b.track_no) return true;
	return false;
}

//                                                         

/*                                              
                 
	              
                                                                                    

	                                
	                         
	 
		                                    
		                                          
		                                  
		                                        
		                            
		                                  
	 
	             
 

                                               
 
	               
	             
	                 
	                                                                           

                                                                                                    
	             
 */

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

void dnf_ass1(vector<Track>& data, int first, int last, int& red, int& blue)
{

	//              
	assert(true);
	//               
	//                                                                                                       
	red = first - 1;
	blue = last + 1;
	int white = last + 1;
	const Track PIVOT = data[first + (last - first) / 2];
	while(red < white - 1)
	{
		const int NEXT = white - 1;
		if(data[NEXT] < PIVOT)
		{
			red++;
			swap(data[red], data[NEXT]);
		}
		else if(data[NEXT] == PIVOT)
		{
			white--;
		}
		else
		{
			white--;
			blue--;
			swap(data[NEXT], data[blue]);
		}
	}
}

void quicksort_ass1(vector<Track>& data, int first, int last)
{
	//              
	assert(true);
	//               
	//                                                                              
	if(first >= last) return;
	else
	{
		int red, blue;
		dnf_ass1(data, first, last, red, blue);
		quicksort_ass1(data, first, red);
		quicksort_ass1(data, blue, last);
	}
}

void dnf_ass2(vector<Track>& data, int first, int last, int& red, int& blue)
{
	//              
	assert(true);
	//               
	//                                                                                                        
	red = first - 1;
	blue = last + 1;
	int white = first - 1;
	const Track PIVOT = data[first + (last - first) / 2];
	while(blue > white + 1)
	{
		const int NEXT = white + 1;
		if(data[NEXT] < PIVOT)
		{
			blue--;
			swap(data[blue], data[NEXT]);
		}
		else if(data[NEXT] == PIVOT)
		{
			white++;
		}
		else
		{
			white++;
			red++;
			swap(data[NEXT], data[red]);
		}
	}
}

void quicksort_ass2(vector<Track>& data, int first, int last)
{
	//              
	assert(true);
	//               
	//                                                                           
	if(first >= last) return;
	else
	{
		int red, blue;
		dnf_ass2(data, first, last, red, blue);
		quicksort_ass2(data, first, red);
		quicksort_ass2(data, blue, last);
	}
}

void print_songs()
{
	//              
	assert(true);
	//               
	//                                                   
	int i = 0;
	for(Track t : songs)
	{
		cout << "===== " << i << " =====" << endl;
		cout << t.artist << endl;
		cout << t.cd << endl;
		cout << t.year << endl;
		cout << t.track_no << endl;
		cout << t.title << endl;
		cout << t.tags << endl;
		cout << t.time.minutes << ":" << t.time.seconds << endl;
		cout << t.country << endl;
		i++;
	}
	cout << "=============" << endl;
}

//                                

int largest(vector<int>& v, int low, int up)
{
	//              
	assert(low >= 0 && up < v.size());
	//               
	//                                              
	int large = low;
	for(int i = low; i <= up; i++)
		if(v[i] > v[large]) large = i;
	return large;
}

void sort(vector<int>& v, int n)
{
	//              
	assert(n < v.size());
	//               
	//                    
	while(n > 1)
	{
		int large = largest(v, 0, n);
		swap(v[n], v[large]);
		n--;
	}
}

int main()
{
	const int NO_OF_SONGS = read_file ("Tracks.txt");
	if (NO_OF_SONGS < 0)
	{
        cout << "Reading file failed. Program terminates." << endl;
	    return NO_OF_SONGS;
    }

	cout << "Sorting tracks..." << endl;
	quicksort_ass1(songs, 0, songs.size() - 1);
	//                                           

	print_songs();

    cout << "Tracks sorted." << endl;

    cin.clear();
    cin.ignore(1000);

    cout << "Done." << endl;
    int i;
    cin >> i;
    return i;
}

