#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>
#define NDEBUG

using namespace std;
int GLOBALCOUNTER = 0;

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

vector<Track> songs;              //                                     

int size (vector<Track>& v)
{
    //            
    assert(true);
    //                             
    return static_cast<int> (v.size ());
}

//                                     
 bool operator<(const Track& a, const Track& b)
{   GLOBALCOUNTER++;
    if (a.artist != b.artist){
        return a.artist < b.artist;
    }
    if (a.cd != b.cd){
        return a.cd < b.cd;
    }
    if (a.year != b.year){
        return a.year < b.year;
    }
    return a.track_no < b.track_no;
}

bool operator< (const Length& a, const Length& b)
{

    if (a.minutes != b.minutes)
    {
        return a.minutes < b.minutes;
    }
    return a.seconds < b.seconds;
}

bool operator== (const Length& a, const Length& b)
{
    return (a.minutes == b.minutes && a.seconds == b.seconds);
}

bool operator!= (const Length& a, const Length& b)
{
    return !(a.minutes == b.minutes && a.seconds == b.seconds);
}

//                                        
/*                                              
 
                    
                          
                               
     
                              
                                   
     
                            
                                 
     
                       
 */

//                                     
bool operator==(const Track& a, const Track& b)
{
    GLOBALCOUNTER++;
	return (a.artist == b.artist && a.cd == b.cd && a.year == b.year && a.track_no == b.track_no);
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
int read_songs (ifstream& infile, vector<Track>& songs, int maxS)
{//               
    assert (infile.is_open ()) ;
/*                 
                                                                              
                                                           
*/
    int no_of_read_songs = 0 ;
    do {
        Track song ;
        infile >> song ;
        if (infile){
            songs.push_back(song);
            no_of_read_songs++;
        }
    }
    while (infile && no_of_read_songs < maxS);
    return no_of_read_songs ;
}

int read_file (string filename, int maxSongs, bool verbose)
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
    if (verbose){
            cout << "Reading '" << filename << "'." << endl;
    }
	const int NO_OF_SONGS = read_songs (songsDBS, songs, maxSongs);
	songsDBS.close();
	if (verbose){
            cout << " Read " << NO_OF_SONGS << " tracks." << endl;
	}
	return NO_OF_SONGS;
}

//                                                                           
void show_all_tracks (vector<Track>& songs)
{//               
    assert (true) ;
/*                 
                                                                  
*/
    int no_of_songs = size(songs);
    for (int i = 0 ; i < no_of_songs; i++)
        cout << i+1 << ". " << songs[i] << endl ;
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

void dnf(vector<Track>& data, int first, int last, int& redBorder, int& blueBorder)
{
    //              
    assert(size(data) > 0 && first >= 0 && first < size(data) && last > first && last < size(data));
    //                                                                                                                            

    const Track pivot = data[first+(last-first)/2];
    //                          
    int whiteBorder = last+1;
    redBorder = first - 1;
    blueBorder = last + 1;

    while (whiteBorder-1 > redBorder){ //                                    
        const int nextIndex = whiteBorder-1;
        if (data[nextIndex] > pivot){ //          
            //                                                           
            blueBorder--;
            swap(data, nextIndex, blueBorder);
            whiteBorder--; //                                         
        } else if (data[nextIndex] == pivot){ //            
            whiteBorder--;
        } else { //         
            //                                                       
            redBorder++;
            swap(data, redBorder, nextIndex);
        }
    }
}

//                       
/*
                                                                                   
 
                    
                                                                                                    
                                                                                                                                  

	                                               
	                            
	                          
	                      
	                      
	                                                                          
    	                                    
    	                                          
        	             
        	                                  
    	                                                    
        	              
    	                    
        	                                                         
        	              
        	            
        	                                 
    	 
	 
  */

void quicksort(vector<Track>& song, int first, int last )
{
    //              
    assert (0 <= first && last < size (song)) ;
    //                                                                                        

	if (first >= last) {
            return;
	} else {
    	int red, blue;
    	dnf (song, first, last, red, blue);
    	quicksort(song, first, red);
    	quicksort(song, blue,last);
	}
}

//          
void swapInt(vector<int>& v, int a, int b)
{
    //            
    int vs = static_cast<int>(v.size());
    assert(vs > 0 && a >= 0 && a < vs && b >= 0 && b < vs);
    //                                                                        

    int store = v[a];
    v[a] = v[b];
    v[b] = store;
}

int largestInt(vector<int>& v, int low, int up)
{
    //            
    int vs = static_cast<int>(v.size());
    assert(vs > 0 && low >= 0 && low < vs && up >= 0 && up < vs);
    //                                                                                   

    int largestIndex = -1; //                                  
    vector<int> Stack;
    //                                                               
    while (low < up){
        Stack.push_back(low); //               
        low = low + 1; //        
    }

    largestIndex = low; //    
    while (static_cast<int>(Stack.size()) > 0){
        low = Stack[static_cast<int>(Stack.size()) - 1]; //                       
        Stack.pop_back(); //                

        //     
        if (v[low] > v[largestIndex]) { //               
            largestIndex = low; //          
        } else {
            //                             
            //                            
        }
    }
    return largestIndex; //                       
}

void sortInt(vector<int>& v)
{
    //            
    assert(true);
    //                                          

    int n = static_cast<int>(v.size());

    //                                                        
    while (n>1){
        const int pos = largestInt(v, 0, n-1);
        swapInt(v, pos, n-1);
        n = n-1; //        
    }
}

void check_slice(int nMax, bool TrackOutput, bool verbose)
{
    //            
    assert(nMax > 0);
    //                                                                                       
    const int NO_OF_SONGS = read_file ("Tracks.txt", nMax, verbose);
	if (NO_OF_SONGS < 0)
	{
        cout << "Reading file failed. Program terminates." << endl;
        return;
    }

    GLOBALCOUNTER = 0;

    quicksort(songs,0,size(songs)-1);

    if (verbose){
            cout << "Tracks sorted." << endl;
    }

    if (TrackOutput){
            show_all_tracks (songs) ;
    } else {
            int stars = GLOBALCOUNTER/100000;
            for (int i =0; i < stars; i++){
                cout << "*";
            }
            if (GLOBALCOUNTER%100000 >0)
            {
                cout << ".";
            }
            cout << endl;
    }
    //                         
    songs.clear();
}

int main()
{

    cout << "Sorting tracks with QuickSort" << endl;
	check_slice(5000000, true, true); //                                          

    cout << "===========================================" << endl << "ABOVE TRACKS WHERE SORTED WITH QUICKSORT" << endl << "===========================================" << endl << "START OF EXERCISE 3";
    cout << endl << "===========================================" << endl;

    vector<int> vec = {8,7,2,7,9,1,2,7,3,1,8,9,7,0,0,4,8,79,1,2,6,7,1,-5,-89,-4,-5,-32,0,18};
    sortInt(vec);
    int ms = static_cast<int>(vec.size());
    cout << "Sorted Integer Vector: " << endl;
    for (int i = 0; i < ms; i++){
        cout << vec[i] << ", ";
    }
    cout << endl;

	return 0;

}

