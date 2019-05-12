#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>

using namespace std;
//                                                  

struct Length
{
    int minutes;
    int seconds;
};

struct Track
{
    string artist;                          //            
    string cd;                              //         
    int    year;                            //     
    int    track;                           //             
    string title;                           //            
    string tags;                            //           
    Length time;                            //             
    string country;                         //               
};

bool operator<(const Length& a, const Length& b)
{
//              
    assert(true);
//                                                                             
    if (a.minutes < b.minutes)
        return true;
    return a.minutes == b.minutes && a.seconds < b.seconds;
}

bool operator==(const Length& a, const Length& b)
{
//              
    assert(true);
//                                                              
    return a.minutes == b.minutes && a.seconds == b.seconds;
}

//                                        
bool operator>(const Length& a, const Length& b)
{
return b < a ;
}

bool operator<=(const Length& a, const Length& b)
{
return !(b < a) ;
}

bool operator>=(const Length& a, const Length& b)
{
return b <= a ;
}

bool operator<(const Track& a, const Track& b)
{
//              
    assert(true);
//                                                                                                                             
    if (a.artist < b.artist)
        return true;
    if (a.artist == b.artist && a.cd < b.cd)
        return true;
    return (a.artist == b.artist && a.cd == b.cd && a.track < b.track);
}

bool operator==(const Track& a, const Track& b)
{
//              
    assert(true);
//                
//                                                                         
    return (a.artist == b.artist && a.cd == b.cd && a.track == b.track);
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

istream& operator>> (istream& in, Length& length)
{//             
    assert (true) ;
/*               
                                                            
*/
    char help ;
    in >> length.minutes >> help >> length.seconds ;
    return in ;
}

ostream& operator<< (ostream& out, const Length length)
{
    out << length.minutes << ':' ;
    if (length.seconds < 10)
        out << '0' ;
    out << length.seconds ;
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
    infile >> track.track ;          //             
    skip_to_next_newline(infile) ;
    getline(infile,track.title);        //            
    getline(infile,track.tags);         //           
    infile >> track.time ;              //           
    skip_to_next_newline(infile) ;
    getline(infile,track.country);      //        
    skip_to_next_newline(infile) ;
    return infile ;
}

ostream& operator<< (ostream& out, const Track track)
{
    out << track.artist << " " << track.cd << " [" << track.track << "] (" << track.time << ")" ;
    return out ;
}

int read_songs(ifstream& infile, vector<Track>& songs)
{
//              
assert(infile);
//                                                                            
    do
    {
        Track t = {};
        infile >> t;
        if (infile)
            songs.push_back(t);
    }
    while(infile);
    return songs.size();
}

int read_file (string filename, vector<Track>& songs)
{
//              
assert (true);
//                                                                            
//                    
    ifstream songsDBS (filename.c_str());
    if (!songsDBS)
    {
        cout << "Could not open :'" << filename << "'" << endl;
        return -1;
    }
    cout << "read '" << filename << "' in." << endl;
    int number = read_songs (songsDBS, songs);
    songsDBS.close();
    return number;
}

void show_MusicDB (vector<Track>& songs, int numberofsongs)
{
//              
assert(true);
//                                                          
    for (int i = 0 ; i < numberofsongs; i++)
        cout << i+1 << ". " << songs[i] << endl ;
}

void swap(vector<Track>& data, int a, int b)
{
//                
    assert(a >= 0 && b >= 0);
//                                                                      
    Track h = data[a];
    data[a] = data[b];
    data[b] = h;
}

/*             
            
              */
void dnf (vector<Track>& data, int first, int last, int& red, int& blue)
{
    //              
    assert(true);
    //                                                                                             
    red = first - 1;
    blue = last + 1;
    int white = last + 1;
    const Track pivot = data[first + (last - first) / 2];
    while (red < white - 1)
    {
        const int next = white - 1;
        if (data[next] < pivot)
        {
            red++;
            swap(data, red, next);
        }
        else if (data[next] == pivot)
            white--;
        else
        {
            white--;
            blue--;
            swap(data, next, blue);
        }
    }
}

void quicksort(vector<Track>& data, int first, int last)
{
    //              
    assert(0 <= first && last < data.size());
    //                                                                                        
    if (first >= last)
        return;
    else
    {
        int red;
        int blue;
        dnf(data, first, last, red, blue);
        quicksort(data, first, red);
        quicksort(data, blue, last);
    }
}

/*               
            
                */
void dnftime (vector<Track>& data, int first, int last, int& red, int& blue)
{
    //              
    assert(true);
    //                                                                                       
    red = first - 1;
    blue = last + 1;
    int white = last + 1;
    const Length pivot = data[first + (last - first) / 2].time;
    while (red < white - 1)
    {
        const int next = white - 1;
        if (data[next].time < pivot)
        {
            red++;
            swap(data, red, next);
        }
        else if (data[next].time == pivot)
            white--;
        else
        {
            white--;
            blue--;
            swap(data, next, blue);
        }
    }
}

void quicksorttime(vector<Track>& data, int first, int last)
{
    //              
    assert(true);
    //                                                                                
    //                           
    if (first >= last)
        return;
    else
    {
        int red;
        int blue;
        dnftime(data, first, last, red, blue);
        quicksorttime(data, first, red);
        quicksorttime(data, blue, last);
    }
}

/*             
                
              */
void dnfadjusted(vector<Track>& data, int first, int last, int& red, int& blue)
{
    //              
    assert(true);
    //                                                              
    //                                                   
    red = first - 1;
    blue = last + 1;
    int white = first - 1;
    const Track pivot = data[first + (last - first) / 2];
    while (blue > white + 1)
    {
        const int next = white + 1;
        if (data[next] < pivot)
        {
            red++;
            white++;
            swap(data, red, next);
        }
        else if (data[next] == pivot)
            white++;
        else
        {
            blue--;
            swap(data, next, blue);
        }
    }
}

void quicksortadjusted(vector<Track>& data, int first, int last)
{
    //              
    assert(true);
    //                                                     
    if (first >= last)
        return;
    else
    {
        int red;
        int blue;
        dnfadjusted(data, first, last, red, blue);
        quicksortadjusted(data, first, red);
        quicksortadjusted(data, blue, last);
    }
}

/*            
      
             */

void trade(vector<int>& v, int a, int b)
{
//                
    assert(a >= 0 && b >= 0);
//                                                                     
    int help = v[a];
    v[a] = v[b];
    v[b] = help;
}

void iterativesort(vector<int>& v, int n)
{
//                
    assert(n <= v.size() + 1);
//                                                                                           
//                            
    while (n > 1)
    {
        int largest = 0;
        for (int i = 0; i < n; i++)
            if (v[i] > v[largest])
                largest = i;
        trade(v, largest, n - 1);
        n--;
    }
}

void show_vector(vector<int>& v)
{
//              
    assert(true);
//                                                       
    for (int i = 0; i < v.size(); i++)
        cout<<v[i]<<" ";
    cout<<endl;
}

void fill_vector(vector<int>& v, int a[], int l)
{
//              
    assert(l > 0);
//                                                                                        
//                                            
    for (int i = 0; i < l; i++)
        v.push_back(a[i]);
    cout<<"Inserted vector: \n";
    show_vector(v);
}

int main()
{
    vector<Track> songs;
    int numberofsongs = read_file ("Tracks.txt", songs);
    //                                              
    //                                       
    //                                           

    //                                               

    //                                   

    //       

    int test[] = {1, 3, 5, -1, 0, 4, 2, 6, -2, 7, -3};
    vector<int> a;
    fill_vector(a, test, 11);
    iterativesort(a, 11);
    show_vector(a);

    return 0;
}

