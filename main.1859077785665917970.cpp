//                      
//                       

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <assert.h>
#include <algorithm>
#include <sstream>

using namespace std;

struct Length
{
	int minutes;
	int seconds;
};

struct Track {
    string artist;
    string cd;
    int year;
    int track_no;
    string title;
    string tags;
    Length time;
    string country;
};

vector<Track> songs =  {{"Adele",                          "19",                          2008,1, "Daydreamer",                  "pop,debut album",                   { 3,40},"England"}
,{"Adele",                          "19",                          2008,10,"My same",                     "pop,debut album",                   { 3,15},"England"}
,{"Adele",                          "19",                          2008,11,"Tired",                       "pop,debut album",                   { 4,18},"England"}
,{"Adele",                          "19",                          2008,12,"Hometown glory",              "pop,debut album",                   { 4,31},"England"}
,{"Adele",                          "19",                          2008,2, "Best for last",               "pop,debut album",                   { 4,18},"England"}
,{"Adele",                          "19",                          2008,3, "Chasing pavements",           "pop,debut album",                   { 3,30},"England"}
,{"Adele",                          "19",                          2008,4, "Cold shoulder",               "pop,debut album",                   { 3,11},"England"}
,{"Adele",                          "19",                          2008,5, "Crazy for you",               "pop,debut album",                   { 3,28},"England"}
,{"Adele",                          "19",                          2008,6, "Melt my heart to stone",      "pop,debut album",                   { 3,23},"England"}
,{"Adele",                          "19",                          2008,7, "First love",                  "pop,debut album",                   { 3,10},"England"}
,{"Adele",                          "19",                          2008,8, "Right as rain",               "pop,debut album",                   { 3,17},"England"}
,{"Adele",                          "19",                          2008,9, "Make you feel my love",       "pop,debut album",                   { 3,32},"England"}
,{"Adele",                          "21",                          2011,1, "Rolling in the deep",         "pop",                               { 3,49},"England"}
,{"Adele",                          "21",                          2011,10,"Lovesong",                    "pop",                               { 5,16},"England"}
,{"Adele",                          "21",                          2011,11,"Someone like you",            "pop",                               { 4,47},"England"}
,{"Adele",                          "21",                          2011,2, "Rumour has it",               "pop",                               { 3,43},"England"}
,{"Adele",                          "21",                          2011,3, "Turning tables",              "pop",                               { 4,10},"England"}
,{"Adele",                          "21",                          2011,4, "Don't you remember",          "pop",                               { 4, 3},"England"}
,{"Adele",                          "21",                          2011,5, "Set fire to the rain",        "pop",                               { 4, 1},"England"}
,{"Adele",                          "21",                          2011,6, "He won't go",                 "pop",                               { 4,37},"England"}
,{"Adele",                          "21",                          2011,7, "Take it all",                 "pop",                               { 3,48},"England"}
,{"Adele",                          "21",                          2011,8, "I'll be waiting",             "pop",                               { 4, 1},"England"}
,{"Adele",                          "21",                          2011,9, "One and only",                "pop",                               { 5,48},"England"}
,{"All them witches",               "Dying surfer meets his maker",2015,1, "Call me star",                "alternative,rock",                  { 3,54},"U.S.A."}
,{"All them witches",               "Dying surfer meets his maker",2015,2, "El centro",                   "alternative,rock,instrumental",     { 8,25},"U.S.A."}
,{"All them witches",               "Dying surfer meets his maker",2015,3, "Dirt preachers",              "alternative,rock",                  { 3,44},"U.S.A."}
,{"All them witches",               "Dying surfer meets his maker",2015,4, "This is where it falls apart","alternative,rock",                  { 7, 2},"U.S.A."}
,{"All them witches",               "Dying surfer meets his maker",2015,5, "Mellowing",                   "alternative,instrumental",          { 3,11},"U.S.A."}
,{"All them witches",               "Dying surfer meets his maker",2015,6, "Open passageways",            "alternative,rock",                  { 3,14},"U.S.A."}
,{"All them witches",               "Dying surfer meets his maker",2015,7, "Instrumental 2 (welcome to the caveman future)"
,"alternative,rock,instrumental",     { 2,33},"U.S.A."}
,{"All them witches",               "Dying surfer meets his maker",2015,8, "Talisman",                    "alternative,rock",                  { 6, 7},"U.S.A."}
,{"All them witches",               "Dying surfer meets his maker",2015,9, "Blood and sand / milk and endless waters","alternative,rock",      { 7,20},"U.S.A."}
,{"The decemberists",               "The tain",                    2005,1, "The tain (parts i-iv)",       "progressive,experimental,folk,rock",{18,35},"U.S.A."}
,{"Colin Stetson and Sarah Neufeld","Never were the way she was",  2015,1, "The sun roars into view",     "jazz,instrumental,experimental",    { 7,37},"U.S.A.,Canada"}
,{"Colin Stetson and Sarah Neufeld","Never were the way she was"  ,2015,2, "Won't be a thing to become",  "jazz,instrumental,experimental",    { 3,24},"U.S.A.,Canada"}
,{"Colin Stetson and Sarah Neufeld","Never were the way she was",  2015,3, "In the vespers",              "jazz,instrumental,experimental",    { 6, 2},"U.S.A.,Canada"}
,{"Colin Stetson and Sarah Neufeld","Never were the way she was",  2015,4, "And still they move",         "jazz,instrumental,experimental",    { 2,56},"U.S.A.,Canada"}
,{"Colin Stetson and Sarah Neufeld","Never were the way she was",  2015,5, "With the dark hug of time",   "jazz,instrumental,experimental",    { 6,34},"U.S.A.,Canada"}
,{"Colin Stetson and Sarah Neufeld","Never were the way she was",  2015,6, "The rest of us",              "jazz,instrumental,experimental",    { 6,30},"U.S.A.,Canada"}
,{"Colin Stetson and Sarah Neufeld","Never were the way she was",  2015,7, "Never were the way she was",  "jazz,instrumental,experimental",    { 8,12},"U.S.A.,Canada"}
,{"Colin Stetson and Sarah Neufeld","Never were the way she was",  2015,8, "Flight",                      "jazz,instrumental,experimental",    { 1,38},"U.S.A.,Canada"}
} ;

bool operator<(const Length&a, const Length&b) {
    int seconds_a = a.seconds + a.minutes * 60;
    int seconds_b = b.seconds + b.minutes * 60;
    return seconds_a < seconds_b;
}

bool operator==(const Length&a, const Length&b) {
    return a.minutes == b.minutes && a.seconds == b.seconds;
}

bool operator<(const Track& a, const Track& b)
{
    if (a.time == b.time) {
        if (a.artist == b.artist) {
            if (a.title == b.title) {
                return a.cd < b.cd;
            } else {
                return a.title < b.title;
            }
        } else {
            return a.artist < b.artist;
        }
    } else {
        return a.time < b.time;
    }
}

bool operator==(const Track& a, const Track& b)
{
    return a.artist == b.artist && a.cd == b.cd && a.year == b.year && a.track_no == b.track_no && a.time == b.time;
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

ostream& operator<< (ostream& out, const Length length)
{
    out << length.minutes << ':';
    if (length.seconds < 10)
        out << '0';
    out << length.seconds;
    return out ;
}

ostream& operator<< (ostream& out, const Track track)
{
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

void swap (vector<Track>& data, int  i, int  j )
{
    //               
    assert( i >= 0 && j >= 0 && i < data.size () && j < data.size () );
    //                
    //                           
    Track HELP = data [i];
    data [i] = data [j] ;
    data [j] = HELP;
}

void dnf(vector<Track>& data, int first, int last, int& red, int& blue)
{
    //               
    assert( first >= 0 && last >= 0 && first < data.size () && first < data.size () && first <= last );
    //                
    //                         
    red = first - 1;
    blue = last + 1;
    int white = last + 1;
    const Track PIVOT = data [first + (last-first)/2];
    while (red < white - 1)
    {
        const int NEXT = white - 1;
        if(data[NEXT] < PIVOT)
        {
            red++;
            swap(data, red, NEXT);
        }
        else if(data [NEXT] == PIVOT)
            white--;
        else
        {
            white --;
            blue--;
            swap(data, NEXT, blue);
        }
    }
}

void dnf_adjusted(vector<Track>& data, int first, int last, int& red, int& blue)
{
    //               
    assert( first >= 0 && last >= 0 && first < data.size () && first < data.size () && first <= last );
    //                
    //                                  
    int white = red = first - 1;
    blue = last + 1;
    const Track pivot = data[first+(last-first)/2];
    while(white + 1 < blue) {
        const int NEXT = white + 1;
        if (data[NEXT]< pivot) {
            red++;
            white++;
            swap(data, red, NEXT);
        } else if (data[NEXT] == pivot) {
            white++;
        } else {
            blue--;
            swap(data, NEXT, blue);
        }
    }
}

void quicksort(vector<Track>& data, int first, int last)
{
    //               
    assert (true);
    //                
    //                                  
    if (first >= last)
        return;
    else
        {
        int red, blue;
        dnf(data, first, last, red, blue);
        quicksort (data, first, red);
        quicksort(data, blue, last);
        }
}

int largest (vector<Track>& songs, int low, int last)
{
    //               
    assert (low < songs.size () && last < songs.size ());
    //                
    //                                                             
    int largest = low;
    for (int i = low + 1; i < last; i++)
    {
        Track current = songs[i];
        {
            if (current > songs[largest]){
                largest = i;
            }
        }
    }
    return largest;
}

void sort(vector<Track>& songs, int last)
{
    //               
    assert (last < songs.size () && last >= 0);
    //                
    //                    

    while( last > 1)
    {
        const int POS = largest(songs, 0, last );
        swap (songs, POS, last);
        last--;
    }
}

int main ()
{
    sort(songs, songs.size () -1);
    for (Track t : songs) {
        cout << t.time << endl;
    }
    cout << "Tracks sorted." << endl;
    return 0;
}
