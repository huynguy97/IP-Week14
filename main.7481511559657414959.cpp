/*  
                          
                 
                     
            
  */

#include <iostream>
#include <cassert>
#include <vector>
#include <fstream>

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

typedef Track El ;

vector<Track> songs;

int size_v(vector<Track> v){
    int s = v.size();
    return s;
}

int minimum(int a, int b){
    if (a < b){
        return a;
    }
    else{
        return b;
    }
}

int maximum(int a, int b){
    if (a > b){
        return a;
    }
    else{
        return b;
    }
}

/*                                                                       
                                
                                                                       */

//                                      
bool operator<(const Length& a, const Length& b)
{
    if(a.minutes < b.minutes)
    {
        return true;
    }
    else if (a.minutes== b.minutes && a.seconds < b.seconds)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool operator==(const Length& a, const Length& b)
{
    return (a.minutes == b.minutes && a.seconds==b.seconds);
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

bool operator<(const Track& a, const Track& b)
{
    if(a.time < b.time)
    {
        return true;
    }
    else if(a.artist < b.artist && a.time == b.time )
    {
        return true;
    }
    else if(a.title < b.title && a.artist == b.artist && a.time == b.time )
    {
        return true;
    }
    else if(a.cd < b.cd && a.title == b.title && a.artist == b.artist && a.time == b.time )
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool operator==(const Track& a, const Track& b)
{
    if(a.time == b.time ){
        return true;
    }
    else{
        return false;
    }
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
    assert (infile.is_open()) ;
/*                 
                                                                              
                                                           
*/
    do {
        Track t;
        infile >> t;
        songs.push_back(t);
    }
    while (infile);
    return size_v(songs) ;
}

int read_file (string filename)
{//               
//                                
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

void show_all_tracks (vector<Track>& songs)
{//               
    assert (true) ;
//                                                                                

    for (int i = 0 ; i < songs.size(); i++)
        cout << i+1 << ". " << songs[i] << endl ;
}

void swap (vector<El>& data, int  i, int  j )
{//	              
	assert ( i >= 0 && j >= 0 ) ;	//                         
						            //                         
//                                                                
	const El HELP = data [i];
	data [i] = data [j] ;
	data [j] = HELP;
}

/*                                                                       
             
                                                                       */

//                                    
void DNF_adjusted (vector<El>& data, int low, int high, int& red, int& blue )
{  //            
    assert(0 <= low && high < data.size());
    //                                                                    
    red =low-1;
    blue = high+1;
    int white = low-1;
    const El pivot = data[low+(high-low)/2];

    while (blue > white+1)
    {
        const int next = white + 1;
        if (data [next] < pivot)
        {
            white ++;
            red++;
            swap(data, red, next);
        }
        else if (data [next]== pivot)
        {
            white ++;
        }
        else
        {
            blue--;
            swap(data, next, blue);
        }
    }

}

//                           
void DNF(vector<El>& data, int low, int high, int& red, int& blue)
{  //            
    assert(0 <= low && high < data.size());
    //                                                                    
    red = low - 1;
    blue = high + 1;
    int white = high + 1;
    const El pivot = data[low+(high-low)/2];

    while (red < white - 1)
    {
        const int next = white - 1;
        if (data[next] < pivot)
        {
            red++;
            swap(data, red, next);
        }
        else if (data[next]== pivot)
        {
            white --;
        }
        else
        {
            white--;
            blue--;
            swap(data, next, blue);
        }
    }
}

//                                 
void quicksort(vector<El>& data, int low, int high )
{   //            
    assert(0 <= low && high < data.size());
    //                                                                              
    if (low >= high)
    {
        return;
    }
    else{
        int red, blue;
        //       
        DNF(data, low, high, red, blue);
        //       
        //                                         
        quicksort(data, low, red);
        quicksort(data, blue, high);
    }
}

//                                            
int largest (vector<El>& v, int lower ,int upper)
{   //             
    assert(0 <= lower && upper < v.size());
    //                                                
    if(lower>=upper)
    {
        return lower;
    }
    else
    {
        const int POS = largest(v,lower+1, upper);
        if(v[lower] > v[POS])
        {
            return lower;
        }
        else
        {
            return POS;
        }
    }
}

//                                         
void sort (vector<El>& v, int n)
{   //             
    assert(n < v.size());
    //                                  
    if(n>1)
    {
        const int POS = largest(v, 0, n-1);
        swap(v,POS,n-1);
        sort(v,n-1);
    }
}

int main()
{
    cout << "This program reads a file 'Tracks.txt' and sorts it using Quicksort and DNF\n";
    int NO_OF_SONGS = read_file ("Tracks.txt");
	if (NO_OF_SONGS < 0)
	{
        cout << "Reading file failed. Program terminates." << endl;
	    return NO_OF_SONGS;
    }

    quicksort(songs, 0, NO_OF_SONGS-1);
    //                       
    return 0;
}

