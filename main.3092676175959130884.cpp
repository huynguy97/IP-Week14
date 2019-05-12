#include <iostream>
#include <fstream>
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

vector<Track> songs;

typedef Track El;

bool operator<(const Length& a, const Length& b)
{
    //               
    assert(true);
    //                
    //                                              
    return (a.seconds + a.minutes*60) < (b.seconds + b.minutes*60);
}

bool operator>=(const Length& a, const Length& b)
{
    //               
    assert(true);
    //                                                          
    return !(a < b);
}

bool operator==(const Length& a, const Length &b)
{
    //               
    assert(true);
    //                
    //                                            
    return a.seconds == b.seconds && a.minutes == b.minutes;
}

bool operator<(const Track& a, const Track& b)
{
    //               
    assert(true);
    //                
    //                                                                                      
    return a.time < b.time;
}

bool operator==(const Track& a, const Track& b)
{
    //               
    assert(true);
    //                
    //                                                                              
    return a.time == b.time;
}

//	                                 
bool operator>(const Track& a, const Track& b)
{
    //               
    assert(true);
    //                
    //                                            
	return b < a ;
}

bool operator<=(const Track& a, const Track& b)
{
    //               
    assert(true);
    //                
    //                                                        
	return !(b > a) ;
}

bool operator>=(const Track& a, const Track& b)
{
    //               
    assert(true);
    //                                                        
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

int size(vector<El> &v) {
    //               
    assert(true);
    //                
    //                                        
    return static_cast<int> (v.size());
}

int minimum(int a, int b) {
    //               
    assert(true);
    //                
    //                                                      
    if(a < b)
        return a;
    else
        return b;
}

int maximum(int a, int b) {
    //               
    assert(true);
    //                
    //                                     
    if(a > b)
        return a;
    else
        return b;
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
            songs.insert(songs.begin()+no_of_read_songs++, song);
    } while (infile);
    return no_of_read_songs ;
}

enum SortingMethod {QuickSort,NoOfSortingMethods};
string methods [] = {"quick"} ;

int read_file (string filename)
{//               
    assert (size (songs) == 0) ;
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

SortingMethod get_sorting_method ()
{
    //               
    assert(true);
    //                
    //                                               
    cout << "What sorting method do you want to use? " << endl ;
    for (int m = 0; m < NoOfSortingMethods; m++)
        cout << m+1 << ": " << methods[m] << " sort" << endl ;
    int choice ;
    cin >> choice ;
    choice = maximum (1, minimum (choice, NoOfSortingMethods)) ;
    return static_cast<SortingMethod>(choice-1) ;
}

void show_all_tracks(vector<Track>& songs) {
    //               
    assert(true);
    //                
    //                           
    for(int i = 0; i < size(songs); i++) cout << songs[i];
}

//                                         

void swap(vector<El>& v, const int POS, int n) {
    //               
    assert(POS >= 0 && POS < size(v) && n >= 0 && n < size(v));
    //                
    //                             
    const El TMP = v[POS];
    v[POS] = v[n];
    v[n] = TMP;
}

void dnf(vector<El>& songs, int first, int last, int& blue, int& red) {
    //               
    assert(0 <= first && last < size(songs));
    //                
    //                                                                        
    //                                 
    red = last+1;
    blue = first-1;
    int white = last+1;
    const El PIVOT = songs[first+(last-first)/2];
    while(blue < white-1) {
        const int NEXT = white-1;
        if(songs[NEXT] < PIVOT) {
            blue++;
            swap(songs,blue,NEXT);
        }
        else if(songs[NEXT] == PIVOT)
            white--;
        else {
            white--; red--;
            swap(songs, NEXT, red);
        }
    }
}

void quick_sort(vector<Track>& songs, int first, int last) {
    //               
    assert(0 <= first && last < size(songs));
    //                
    //                                     
    //                                 
    if(first >= last) return;
    else {int red;
        int blue;
    dnf(songs,first,last,red,blue);
    quick_sort(songs,first,red);
    quick_sort(songs,blue,last);
    }
}

//                                   

int largest(vector<El>& v, int low, int up);

void sort(vector<El>& v, int n) {
    //               
    assert(n < size(v));
    //                
    //                        
    while(n > 1) {
        const int POS = largest(v, 0, n-1);
        swap(v, POS, n-1);
        n--;
    }
}

int largest(vector<El>& v, int low, int up) {
    //               
    assert(low >= 0);
    //                
    //                                                       
    vector<int> stack;
    int pos = up;
    while(low < up) {
        stack.push_back(low);
        low++;
    }
    while(stack.size() > 0) {
        int x = stack[stack.size()-1];
        stack.pop_back();
        if(v[x] > v[pos]) pos = x;
    }
    return pos;
}

int main()
{
    const int NO_OF_SONGS = read_file("Tracks.txt");
    sort(songs, songs.size()-1);
    /*                    
	 
                                                                   
	                       
     
                                             
                                                                    
              
     
                                                                     
                                                
     
                                     */
    show_all_tracks(songs);
	return 0;
}

