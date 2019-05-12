#include <iostream>
#include <cassert>
#include <vector>
#include <fstream>

using namespace std;

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

vector<Track> tracks;

bool operator< (const Length& a, const Length& b)
{
    if (a.minutes < b.minutes)
        return true;
    else if (a.minutes == b.minutes && a.seconds < b.seconds)
        return true;
    return false;
}

bool operator== (const Length& a, const Length& b)
{
    if (a.minutes == b.minutes)
        if (a.seconds == b.seconds)
            return true;
    return false;
}

bool operator<(const Track& a, const Track& b)
{
    if (a.artist == b.artist)
        if (a.cd == b.cd)
            if (a.year == b.year)
                return a.track_no < b.track_no;
            else
                return a.year < b.year;
        else
            return a.cd < b.cd;
    else
        return a.artist < b.artist;
}

bool operator==(const Track& a, const Track& b)
{
    if (a.time == b.time)
        if (a.artist == b.artist)
            if (a.title == b.title)
                if (a.cd == b.cd)
                    return true;

    return false;
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

int maximum (int a, int b)
{
    return max(a, b);
}

int minimum (int a, int b)
{
    return min(a, b);
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

int size (vector<Track>& v)
{
    return static_cast<int> (v.size ());
}

void swap (vector<Track>& tracks, int  i, int  j )
{//	              
	assert ( i >= 0 && j >= 0 ) ;	//                           
						            //                           
//                                                                        
	const Track HELP = tracks [i];
	tracks [i] = tracks [j] ;
	tracks [j] = HELP;
}

void dnf (vector<Track>& data, int first, int last, int& red , int& blue)
{
//                
    assert (0 <= first && last < size(data));
//                 
//                                              

    red = first - 1;
    blue = last + 1;
    int white = last + 1;
    const Track PIVOT = data[first+(last-first)/2];

//                                                 
    while (red < white - 1)
    {
        const int NEXT = white -1;
        if (data[NEXT] < PIVOT)
        {
            red++;
            swap(data, red, NEXT);
        } else if (data[NEXT] == PIVOT)
            white--;
        else {
            white--;
            blue--;
            swap(data, NEXT, blue);
        }
    }

/*                                
                           
     
                                  
                                         
         
                  
                                  
                                                 
                    
              
                    
                   
                                   
         
     
*/
}

void dnf_adjusted(vector<Track>& data, int first, int last, int& red, int& blue)
{
//                
    assert (0 <= first && last < size(data));
//                 
//                                              

    red = first - 1;
    blue = last + 1;
    int white = first - 1;
    const Track PIVOT = data[first + (last - first) / 2];
//                                                 
    while (white < blue - 1)
    {
        const int NEXT = blue - 1;

        if (data[NEXT] < PIVOT)
        {
            red++;
            white++;
            swap(data, red, NEXT);
            if(white != red)
                swap(data, white, NEXT);
        } else if (data[NEXT] == PIVOT)
        {
            white++;
            swap(data, NEXT, white);
        } else
            blue--;
    }

/*                                 
                            
     
                                  

                                         
         
                  
                    
                                  
                            
                                        
                                                 
         
                    
                                    
              
                   
     
*/
}

void quicksort (vector<Track>& data, int first, int last)
{
//                
    assert ( 0 <= first && last < size(data));
//                 
//                                      

    if (first >= last)
        return;
    else {
        int red, blue;
        dnf_adjusted(data, first, last, red, blue);
        quicksort(data, first, red);
        quicksort(data, blue, last);
    }
}

int read_songs (ifstream& infile, vector<Track>& tracks)
{//               
    assert (infile.is_open ()) ;
/*                 
                                                                               
                                                           
*/
    do {
        Track song ;
        infile >> song ;
        if (infile)
            tracks.push_back(song);
    }
    while (infile);
}

void show_all_tracks (vector<Track>& tracks)
{//               
    assert ( true) ;
/*                 
                                                                    
*/
    for (int i = 0 ; i < tracks.size(); i++)
        cout << tracks[i] << endl ;
}

int largest (vector<int>& data, int low, int up)
{
    int bigger = low;

    while(!(low >= up))
    {
        if (data[low] > data[bigger])
            return low;
        else
            return bigger;
        low++;
    }

    return low;
}

void sort (vector<int>& data, int n)
{
    while (n > 1)
    {
        const int POS = largest(data, 0 , n-1);
        swap(data[POS], data[n-1]);
        n--;
    }
}

int main()
{
    ifstream infile;
    infile.open("Tracks.txt");

    read_songs(infile, tracks);
    quicksort(tracks, 0, tracks.size()-1);
    show_all_tracks(tracks);
    infile.close();
    return 0;
}

