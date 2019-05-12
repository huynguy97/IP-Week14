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
bool time_sort = true;

bool operator<(const Length& a, const Length& b)
{
    if(a.minutes != b.minutes)
        return a.minutes < b.minutes;
    else if(a.seconds != b.seconds)
        return a.seconds < b.seconds;
    return false;
}

bool operator==(const Length& a, const Length& b)
{
    if(a.minutes == b.minutes && a.seconds == b.seconds)
        return true;
    return false;
}

bool operator!=(const Length& a, const Length& b)
{
    return !(a==b);
}

bool operator<(const Track& a, const Track& b)
{
    if(time_sort)
    {
        if(a.time != b.time)
            return a.time < b.time;
        if(a.artist != b.artist)
            return a.artist < b.artist;
        if(a.cd != b.cd)
            return a.cd < b.cd;
        if(a.year != b.year)
            return a.year < b.year;
        if(a.track_no != b.track_no)
            return a.track_no < b.track_no;
        return false;
    }
    else
    {
        if(a.artist != b.artist)
            return a.artist < b.artist;
        if(a.cd != b.cd)
            return a.cd < b.cd;
        if(a.year != b.year)
            return a.year < b.year;
        if(a.track_no != b.track_no)
            return a.track_no < b.track_no;
        return false;
    }

}

bool operator==(const Track& a, const Track& b)
{
    if(!time_sort)
    {
        if(a.artist == b.artist && a.cd == b.cd && a.year == b.year && a.track_no == b.track_no && a.time == b.time)
            return true;
        return false;
    }
    else
    {
        if(a.time == b.time)
            return true;
        return false;
    }
}

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

void skip_to_next_newline (istream& infile)
{//               
    assert (true) ;
/*                 
                                                                        
*/
    string remains;
    getline (infile, remains);
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
        Track song;
        infile >> song;
        songs.push_back(song);
        no_of_read_songs++;
    }
    while (infile);
    return no_of_read_songs ;
}

int read_file (string filename)
{//               
    assert (songs.size() == 0) ;
/*                 
                                                                              
                                                                                             
                                   
*/
    string help;
    help = filename + ".txt";
    ifstream songsDBS (help.c_str());
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

void show_all_tracks (vector<Track>& songs)
{//               
    assert (true) ;
/*                 
                                                                  
*/
    for (int i = 0 ; i < songs.size(); i++)
        cout << i+1 << ". " << songs[i] << endl ;
}

void swap (vector<Track>& data, int  i, int  j )
{//	              
	assert ( i >= 0 && j >= 0 && i <= data.size() && j<= data.size()) ;
//                                                                
	const Track HELP = data [i];
	data [i] = data [j] ;
	data [j] = HELP;
}

void dnf(vector<Track>& data, int first,int last,int& red, int& blue)
{
    assert(first >= -1  && last <= data.size() + 1);
    //                
    //                                                                                                                                          
    red = first - 1;
    blue = last + 1;
    int white = last + 1;
    const Track PIVOT = data[first+(last-first)/2];
    while(red < white - 1)
    {
        const int NEXT = white - 1;
        if(data[NEXT] < PIVOT)
        {
            red++;
            swap(data,red,NEXT);
        }
        else if(data[NEXT] == PIVOT)
            white--;
        else
        {
            white--;
            blue--;
            swap(data,NEXT,blue);
        }
    }
}

void dnf_adjusted(vector<Track>& data,int first,int last,int& red, int& blue)
{
    assert(first >= -1  && last <= data.size() + 1);
    //                
    //                                                                                                                                          
    red = first - 1;
    blue = last + 1;
    int white = first - 1;
    const Track PIVOT = data[first+(last-first)/2];
    while(blue > white + 1)
    {
        const int NEXT = white + 1;
        if(data[NEXT] < PIVOT)
        {
            red++;
            white++;
            swap(data,red,NEXT);
        }
        else if(data[NEXT] == PIVOT)
            white++;
        else
        {
            blue--;
            swap(data,NEXT,blue);
        }
    }
}

void quicksort(vector<Track>& data, int first, int last)
{
    //                                                                                  
    assert(0 <= first); //                                                                                                                                                
                       //                                                                                                                                        
    //               
    //                                      
    if(first >= last)
        return;
    else
    {
        int red,blue;
        //                             
        dnf_adjusted(data,first,last,red,blue);
        quicksort(data,first,red);
        quicksort(data,blue,last);
    }
}
int largest(vector<Track>& v, int low, int up) //                                                                                                                       
{
    assert(low >= 0 && up <= v.size());
    //                
    //                                                                             
    vector<int> stack;
    while(low < up)
    {
        stack.push_back(low);
        low++;
    }
    int pos = low;
    while(stack.size() > 0)
    {
        low = stack[stack.size() - 1];
        stack.pop_back();
        if(v[low] > v[pos])
        {
            pos = low;
        }
    }
    return pos;
}
void sorting(vector<Track>& v, int n)
{
    assert(n >= 0);
    //                
    //                         
    while(n > 1)
    {
        int POS = largest(v,0,n-1);
        swap(v,POS,n-1);
        n--;
        //                                                                                                                                                 
    }
}

int main()
{
    int i;
    do {
        cout << "Please enter the filename of file containing the needed tracks" << endl;
        string filename;
        getline(cin,filename);
        i = read_file(filename);}
    while(i <= 0);
    cout << "The amount of read words is : " << i << endl;
    cout << "Do you want to sort time dependent or not? (y/n)" << endl;
    string answer;
    getline(cin,answer);
    if (answer == "n")
        time_sort = false;
    else if (answer == "y")
        time_sort = true;
    else
        cout << "You did not answer correctly, we will resume with time-dependent sorting" << endl;
    quicksort(songs,0,songs.size()-1);
    show_all_tracks(songs);
    cout << "The last Track should be : " << endl;
    int pos = largest(songs,0,songs.size()-1);
    cout << songs[pos] << endl;
    sorting(songs,songs.size());
    //                                                                    
    return 0;
}

