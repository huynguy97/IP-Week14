#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <fstream>

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

typedef Track El;

int size(vector<El> vectorlist)
{
    return static_cast<int>(vectorlist.size());
}

int size(vector<int> vectorlist)
{
    return static_cast<int>(vectorlist.size());
}

void swap(vector<El>& data, int a, int b)
{
    //             
    assert((0 <= a && a < size(data)) && (0 <= b && b < size(data)));
    //                                                        
    El t = data[a];
    data[a] = data[b];
    data[b] = t;
}

/*         */
vector<Track> songs;              //                                     
int counter_comparisons = 0;

/*                                                                       
                                
                                                                       */

//                             

/*                                                  
                                              
 
                                                                                                               
                          
                                            
                                  
     
                                    
                             
         
                                            
                                      
             
                                                        
             
         
     
                 
 
*/

//           

bool operator<(const Length& a, const Length& b)
{
    if (a.minutes < b.minutes)
        return true;
    else if (a.minutes == b.minutes)
    {
        if(a.seconds < b.seconds)
            return true;
        else
            return false;
    }
    else
    {
        return false;
    }
}

bool operator==(const Length& a, const Length& b)
{
    if (a.minutes == b.minutes && a.seconds == b.seconds)
        return true;
    return false;
}
//                             

bool operator<(const Track& a, const Track& b)
{
    //                                                                                                    
    if (a.time<b.time)
        return true;
    else if (a.time == b.time)
    {
        if(a.artist < b.artist)
            return true;
        else if(a.artist == b.artist)
        {
            if(a.cd < b.cd)
                return true;
            else if (a.cd == b.cd)
            {
                if(a.title < b.title)
                    return true;
            }
        }
    }
    return false;
}

bool operator==(const Track& a, const Track& b)
{
    if(a.artist == b.artist && a.cd == b.cd && a.country==b.country && a.tags==b.tags&&a.time==b.time && a.title==b.title && a.track_no == b.track_no && a.year == b.year)
        return true;
    return false;
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
{
    //               
    assert (true) ;
    /*                 
                                                                                                          
    */
    char colon ;
    in >> length.minutes >> colon >> length.seconds ;
    return in ;
}

ostream& operator<< (ostream& out, const Length length)
{
    //               
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
{
    //               
    assert (true) ;
    /*                 
                                                                            
    */
    string remains ;
    getline (infile, remains) ;
}

istream& operator>> (istream& infile, Track& track)
{
    //               
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
{
    //               
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
int read_songs (ifstream& infile, vector<Track>& songs, int x)
{
    //               
    assert (infile.is_open ()) ;
    /*                 
                                                                                                               
                                                               
    */
    //              
    int no_of_read_songs = 0 ;
    songs.clear();
    do
    {
        Track song ;
        infile >> song ;
        if (infile)
        {
            songs.push_back(song) ;
            no_of_read_songs++;
        }
    }
    while (infile && no_of_read_songs < x);
    return no_of_read_songs ;
}

int read_file (string filename, int x)
{
    //               
    assert (true);
    /*                 
                                                                                  
                                                                                                 
                                            
    */
    ifstream songsDBS (filename.c_str());
    if (!songsDBS)
    {
        cout << "Could not open '" << filename << "'." << endl;
        return -1;
    }
    //                                                
    const int NO_OF_SONGS = read_songs (songsDBS, songs, x);
    songsDBS.close();
    cout << " Read " << NO_OF_SONGS << " tracks." << endl;
    return NO_OF_SONGS;
}

void print_vector(vector<El> data)
{
    //             
    assert(size(data) >= 0);
    //                                                                             
    for(int i = 0; i < size(data); i++)
    {
        cout << data[i] << '\t';
    }
    cout << '\n';
}

/*                                               
                      
                                               */

void dnf_orange_after(vector<El>& data, int first, int last, int& red, int&blue)
{
    //             
    assert(first <= last);
    //                                                                                                                                    
    //                                                                                                
    red = first-1;
    blue = last+1;
    int white = first - 1;
    const El PIVOT = data[first+(last-first)/2];
    while(blue > white + 1)
    {
        const int NEXT = white+1;
        if(data[NEXT] > PIVOT)
        {
            blue--;
            swap(data,blue,NEXT);
        }
        else if(data[NEXT] == PIVOT)
        {
            white++;
        }
        else
        {
            white++;red++;
            swap(data, NEXT, red);
        }
    }
}

void dnf_orange_first(vector<El>& data, int first, int last, int& red, int&blue)
{
    //             
    assert(first <= last);
    //                                                                                                                                    
    //                                                                                               
    red = first-1;
    blue = last+1;
    int white = last + 1;
    const El PIVOT = data[first+(last-first)/2];
    while(red<white-1)
    {
        const int NEXT = white -1;
        if(data[NEXT] < PIVOT)
        {
            red++;
            swap(data,red,NEXT);
        }
        else if(data[NEXT] == PIVOT)
        {
            white--;
        }
        else
        {
            white--;blue--;
            swap(data, NEXT, blue);
        }
    }
}

void quicksort_after(vector<El>& data, int first, int last)
{
    //              
    assert(0 <= first && last < size(data));
    //                                                                          
    if(first >= last) return;
    else
    {
        int red, blue;
        dnf_orange_after(data, first, last, red, blue);
        quicksort_after(data, first, red);
        quicksort_after(data, blue, last);
    }
}

void quicksort_first(vector<El>& data, int first, int last)
{
    //              
    assert(0 <= first && last < size(data));
    //                                                                          
    if(first >= last) return;
    else
    {
        int red, blue;
        dnf_orange_first(data, first, last, red, blue);
        quicksort_first(data, first, red);
        quicksort_first(data, blue, last);
    }
}

/*                                                          
                                 
                                                          */

int largest(vector<El>& data, int low, int up)
{
    //             
    assert(low <= up);
    //                                                                          
    vector<int> stack;
    int x = low;
    int largest_till_now = 0;
    while(!(x > up))
    {
        stack.push_back(x);
        x++;
    }
    while(stack.size()>0)
    {
        int pos = stack[size(stack)-1];
        if(data[pos] > data[largest_till_now])
            largest_till_now = pos;
        stack.pop_back();
    }
    return largest_till_now;
}

void sort(vector<El>& data, int n)
{
    //             
    assert(n <= size(data));
    //                                              
       if(n>1)
       {
           const int pos = largest(data, 0, n-1);
           swap(data, pos, n-1);
           sort(data, n-1);
       }
}

int main()
{
    const int NO_OF_SONGS = read_file ("Tracks.txt", 900);
    if (NO_OF_SONGS < 0)
    {
        cout << "Reading file failed. Program terminates." << endl;
        return 0;
    }
    vector<El> data = songs;
    sort(data, size(data));
    print_vector(data);
    quicksort_after(data, 0, size(data)-1);
    //                   

    return 0;
}

