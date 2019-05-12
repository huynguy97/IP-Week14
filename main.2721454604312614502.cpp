//                          
//                            
/*                                                                    
                                              
            
                                                                                                            
                                  
                              
                                                           
                                                                    
                                                          
                                                               
                                                                     */
#define NDEBUG
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

int counter;
const int MAX_NO_OF_SONGS = 6000;           //                                
vector<Track> songs;                        //                                     
vector<int> test;

/*                                                                       
                                
                                                               
                                                                         
                                                                       */
bool operator<(const Track& a, const Track& b)
{
    counter ++;
    if(a.time.minutes==b.time.minutes&&a.time.seconds==b.time.seconds)
    {
        if(a.artist == b.artist)
        {
            if(a.cd==b.cd)
            {
                if(a.year==b.year)
                {
                    return a.track_no<b.track_no;

                }
                else return a.year<b.year;
            }
            else return a.cd<b.cd;
        }
        else return a.artist < b.artist ;

    }
    else if(a.time.minutes==b.time.minutes) return a.time.seconds<b.time.seconds;
    else return a.time.minutes<b.time.minutes;
}

bool operator<(const Length& a, const Length& b)
{
    if(a.minutes==b.minutes)
    {
        return a.seconds<b.seconds;
    }
    else
    {
        return a.minutes<b.minutes;
    }

}

/*
                                               
 
               
                                                                                                                
                     
 
*/

bool operator==(const Length& a, const Length& b)
{
    if(a.minutes == b.minutes && a.seconds == b.seconds)
        return true;
}

bool operator==(const Track& a, const Track& b)
{
    counter ++;
    if(a.time == b.time)
        return true ;   /*                                                 */
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

//                                                                           
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
    while (infile && songs.size() < MAX_NO_OF_SONGS);
    return songs.size() ;
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
	cout << " Read " << NO_OF_SONGS << " tracks." << endl;
	return NO_OF_SONGS;
}

//                                                                           
void show_all_tracks (vector<Track>& songs, int song_length)
{//               
    assert (song_length < MAX_NO_OF_SONGS) ;
/*                 
                                                                  
*/
    for (int i = 0 ; i < songs.size(); i++)
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

/*                                                                       
              
 
                                                                       */

void dnf(vector<Track>& data, int first, int last, int& red, int& blue)
{
    //   
    assert(data.size()>0 && first >= 0 && last <= data.size());
    /*    
                                                                                      
    */
    red = first-1;
    blue = last+1;
    int white = last+1;
    const Track PIVOT = data[first+(last-first)/2];
    while(red<white-1)
    {
        const int NEXT = white -1;
        if(data[NEXT] < PIVOT)
        {
            red = red +1;
            swap(data, red, NEXT);
        }
        else if(data[NEXT]==PIVOT)
        {
            white = white -1;
        }
        else
        {
            white= white -1;
            blue--;
            swap(data, NEXT, blue);
        }
    }
}

void dnf_time (vector<Track>& data, int first, int last, int& red, int& blue)
{
    //   
    assert(data.size()>0 && first >= 0 && last <= data.size());
    /*    
                                                                                      
    */
    red = first -1;
    blue = last +1;
    int white = last+1;
    const Track PIVOT = data.at(first+(last-first)/2);

    while (red < white - 1)
    {
        const int NEXT = white - 1;
        {
            cout << NEXT << "--" << red << "--" << white << "--" << data.size() << endl;
            if (data.at(NEXT) < PIVOT)
            {
                red++;
                swap(data, red, NEXT) ;
            }
            else if (data.at(NEXT) == PIVOT)
            {
                white--;
            }
            else
            {
                white--;
                blue--;
                swap (data, NEXT, blue);
            }
        }
    }

}

void dnf2 (vector<Track>& data, int first, int last, int& red, int& blue)
{
    //   
    assert(data.size()>0 && first >= 0 && last <= data.size());
    /*    
                                                                                      
    */
    red = first -1;
    blue = last+1;
    int white = first-1;
    const Track PIVOT = data[first+(last-first)/2];
    while (blue > white + 1)
    {   const int NEXT = white + 1;
        {if (data[NEXT] < PIVOT)
        {
            white++;
            red++;
            swap (data, NEXT, red);
            }
        else if (data[NEXT] == PIVOT)
            white++;
        else
        {
            blue--;
            swap (data, NEXT, blue);}
        }
    }

}

void quicksort(vector<Track>& data, int first, int last)
{
    //    
    assert(0<= first && last< data.size());
    /*     
                                       
    */
    if(first>=last)
    {
        return ;
    }
    else
    {
        int red,blue;
        dnf_time(data,first, last, red, blue);
        quicksort(data, first, red);
        quicksort(data, blue, last);
    }
}

int iter_largest(vector<int>& v, int low, int up)
{
    //   
    assert(v.size()>0);
    /*    
                                                                              
    */
    int POS = up;
    while(low<up)
    {
        if(v[low]>v[POS])
        {
            POS = low;
        }
        low++;
    }
    return POS;
}

void swapi(vector<int>& v, int i, int j)
{
    //	              
	assert ( i >= 0 && j >= 0 ) ;	//                      
						            //                      
//                                                    
	const int HELP = v[i];
	v[i] = v[j] ;
	v[j] = HELP;
}

void iter_sort(vector<int>& v, int n)
{
    //    
    assert(v.size()>0);
    /*
                                                             
    */
    while(n > 1)
    {
        n--;
        int POS = iter_largest(v, 0, n);
        swapi(v, POS, n);
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

    cout << "Quick sort" <<endl;
    quicksort(songs, 0, NO_OF_SONGS-1);

    test = {0,2,5,4,8,6,9,4,5,8,5,45,5,78,4};
    int a = iter_largest(test,5,9);
    cout << "largest index " << a <<endl;
    cout << "corresponding element " << test[a] << endl;

    iter_sort(test,test.size());
    cout << "sorted array test." << endl;
    int b = 0;
    int j = test.size();
    for(int i =0; i<j; i++)
    {
        b = test[i];
        cout << b << " ";
    }

	return 0;
}

