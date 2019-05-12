#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>
#include <cmath>

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
	int    track;							//             
	string title;                           //            
	string tags;                            //     
	Length time;							//             
	string country;                         //                             
};

struct TrackDisplay
{
	bool showArtist;						//                             
	bool showAlbum;							//                       
	bool showYear;							//                                 
	bool showTrack;							//                           
	bool showTitle;							//                          
	bool showTags;                          //                   
	bool showLength;						//                           
	bool showCountry;                       //                                      
};

/*                                                                                 
                                                                                     
*/
vector<Track> testDB = {{"Adele",                          "19",                          2008,1, "Daydreamer",                  "pop,debut album",                   { 3,40},"England"}
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

vector<Track> list_of_tracks (0) ;

bool match (string sub, string source)
{//              
    assert (true) ;
/*                
                                                                                  
*/
    return source.find(sub) != string::npos ;
}

ostream& operator<< (ostream& out, const Length length)
{//              
    assert (true) ;
/*                
                                                                                          
*/
    out << length.minutes << ':' << length.seconds ;
    return out ;
}

istream& operator>> (istream& in, Length& length)
{//              
    assert (true) ;
/*                
                                                                                    
*/
    in >> length.minutes ;
    in.get();
    in >> length.seconds ;
    return in ;
}

Length operator+ (const Length& a, const Length& b)
{//              
    assert (0 <= a.minutes && 0 <= a.seconds && a.seconds < 60 && 0 <= b.minutes && 0 <= b.seconds && b.seconds < 60) ;
/*                
                                 
*/
    Length sum ;
    int Total = ( a.minutes + b.minutes ) * 60 + a.seconds + b.seconds ;
    sum.seconds = Total % 60 ;
    sum.minutes = Total / 60 ;
    return sum ;
}

void show_track (Track track, TrackDisplay lt)
{//              
    assert (true) ;
/*                
                                                                                         
*/
    if (lt.showAlbum)
        cout << track.cd << '\n' ;
    if (lt.showArtist)
        cout << track.artist << '\n' ;
    if (lt.showCountry)
        cout << track.country << '\n' ;
    if (lt.showTags)
        cout << track.tags << '\n' ;
    if (lt.showTrack)
        cout << track.track << '\n' ;
    if (lt.showTitle)
        cout << track.title << '\n' ;
    if (lt.showLength)
        cout << track.time << '\n' ;
    if (lt.showYear)
        cout << track.year << '\n' ;
    cout << '\n' ;
}

istream& operator>> (istream& in, Track& track)
{//              
    assert (true) ;
/*                
                                                                                                                 
                                                          
*/
    getline(in, track.artist);
    getline(in, track.cd) ;
    in >> track.year ;
    in.get();
    in >> track.track ;
    in.get() ;
    getline(in, track.title) ;
    getline(in, track.tags);
    in >> track.time ;
    in.get() ;
    getline(in, track.country) ;
    in.get() ;
    return in ;
}

bool file(ifstream& trackfile)
{//              
    assert (true);
/*               
                                                  
*/
    string filename;
    cout << "please enter a filename: \n" ;
    cin >> filename ;
    trackfile.open(filename) ;
    if (trackfile)
    {
        cout << "\nOpening of " << filename << " was succesful.\n" ;
        return true ;
    }
        return false;
}

void read(ifstream& trackfile)
{//              
    assert (trackfile);
/*               
                                                
*/
    Track track;
    while (trackfile >> track)
        list_of_tracks.push_back(track) ;
}

void swap(vector<Track>& data, int a, int b)
{//              
    assert (true);
/*               
                                        
*/
    Track c = data[b] ;
    data[b] = data[a] ;
    data[a] = c ;
}

void dnftime (vector<Track>& data, int first, int last, int& red, int& blue)
{//              
    assert (true);
/*               
                                                                            
                                              
                                                                                     
                                                                   
                                                                                       
                                        */

    red = first-1 ;
    blue = last+1 ;
    int white = last+1 ;
    const Track PIVOT = data[first+(last-first)/2] ;
    while (red < white-1)
    {
        const int NEXT = white - 1 ;
        int timenext = data[NEXT].time.minutes*60 + data[NEXT].time.seconds ;
        int timepivot = PIVOT.time.minutes*60 + PIVOT.time.seconds ;
        if (timenext < timepivot)
        {
            red++;
            swap(data, red, NEXT) ;
        }
        else if (timenext == timepivot)
            white--;
        else
        {
            white--;
            blue--;
            swap (data, NEXT, blue) ;
        }
    }
}

void dnftime_adjusted (vector<Track>& data, int first, int last, int& red, int& blue)
{//              
    assert (true);
/*               
                                                                            
                                                                     
                                  */

    red = first-1 ;                     //        
    blue = last+1 ;                     //          
    int white = first-1 ;               //          
    const Track PIVOT = data[first+(last-first)/2] ;
    while (white < blue-1)              //                      
    {
        const int NEXT = white + 1 ;    //            
        int timenext = data[NEXT].time.minutes*60 + data[NEXT].time.seconds ;
        int timepivot = PIVOT.time.minutes*60 + PIVOT.time.seconds ;
        if (timenext < timepivot)       //                 
        {
            red++;                      //          
            white++;                    //            
            swap(data, red, NEXT) ;     //                  
        }
        else if (timenext == timepivot) //                   
            white++;                    //            
        else                            //                  
        {
            blue--;                     //            
            swap (data, NEXT, blue) ;   //                          
        }
    }
}

void quicksorttime (vector<Track>& data, int first, int last)
{//              
    assert (0 <= first && last < static_cast<int>(data.size()));
/*               
                                                                                  */

    assert (0<= first && last < static_cast<int>(data.size()));
    if (first>= last)
        return;
    else
    {
        int red;
        int blue;
        dnftime(data, first, last,red, blue) ;
        quicksorttime(data,first,red) ;
        quicksorttime(data,blue,last) ;
    }
}

void quicksorttime_adjusted (vector<Track>& data, int first, int last)
{//              
    assert(0 <= first && last < static_cast<int>(data.size()));
/*               
                                                                                   
                                                                                     */

    assert (0<= first && last < static_cast<int>(data.size()));
    if (first>= last)
        return;
    else
    {
        int red;
        int blue;
        dnftime_adjusted(data, first, last,red, blue) ;
        quicksorttime_adjusted(data,first,red) ;
        quicksorttime_adjusted(data,blue,last) ;
    }
}

void dnftrack (vector<Track>& data, int first, int last, int& red, int& blue)
{//              
    assert (true);
/*               
                                                                            
                                              
                                                                                     
                                                                   
                                                                                       
                                        */

    red = first-1 ;
    blue = last+1 ;
    int white = last+1;
    const Track PIVOT = data[first+(last-first)/2];
    while (red < white - 1)
    {
        const int NEXT = white-1;
        if(data[NEXT].track < PIVOT.track)
        {
            red = red + 1;
            swap (data,red,NEXT);
        }
        else if (data[NEXT].track == PIVOT.track)
            white = white - 1;
        else
        {
            white = white - 1;
            blue = blue - 1;
            swap (data,NEXT,blue);
        }
    }
}

void quicksorttrack (vector<Track>& data, int first, int last)
{
//              
    assert (0 <= first && last < static_cast<int>(data.size())) ;
/*               
                                                                                                      */

    if (first >= last)
        return;
    else
    {
        int red, blue ;
        dnftrack(data,first,last,red,blue);
        quicksorttrack(data,first,red);
        quicksorttrack(data,blue,last);
    }
}

void dnftrack_adjusted (vector<Track>& data, int first, int last, int& red, int& blue)
{//              
    assert (true);
/*               
                                                                            
                                                                     
                                  */
    red = first-1 ;
    blue = last+1 ;
    int white = first - 1;
    const Track PIVOT = data[first+(last-first)/2];
    while (white < blue - 1)
    {
        const int NEXT = white+1;
        if(data[NEXT].track < PIVOT.track)
        {
            red++;
            white++ ;
            swap (data,red,NEXT);
        }
        else if (data[NEXT].track == PIVOT.track)
            white = white + 1;
        else
        {
            blue = blue - 1;
            swap (data,NEXT,blue);
        }
    }
}

void quicksorttrack_adjusted (vector<Track>& data, int first, int last)
{//              
    assert (0 <= first && last < static_cast<int>(data.size())) ;
/*               
                                                                                                      */
    if (first >= last)
        return;
    else
    {
        int red, blue ;
        dnftrack_adjusted(data,first,last,red,blue);
        quicksorttrack_adjusted(data,first,red);
        quicksorttrack_adjusted(data,blue,last);
    }
}

void sort_albums_by_tracks (vector<Track>& data)
{//               
    assert (true);
//                
    /*                                                                                                 
    */
    vector<Track> albums ;
    vector<string> cdmemory ;
    string cd ;
    for (int i = 0; i <= data.size() - 1; i++)
    {
        cd = data[i].cd;
        bool is_in = false ;
        for (int n = 0; n < cdmemory.size(); n++)
        {
            if (cd == cdmemory[n])
                is_in = true ;
        }
        if (is_in == false)
        {
            vector<Track> temporary ;
            cdmemory.push_back(cd) ;
            for (int m = 0; m < data.size(); m++)
            {
                if (data[m].cd == cd)
                    temporary.push_back(data[m]);
            }
            quicksorttrack(temporary,0,temporary.size() - 1) ;
            for(int i = 0; i < temporary.size(); i++)
            {
                albums.push_back(temporary[i]);
            }
        }
    }
    data = albums ;
}

void sort_albums_by_tracks_adjusted (vector<Track>& data)
{//               
    assert (true);
//                
    /*                                                                                                 
    */
    vector<Track> albums ;
    vector<string> cdmemory ;
    string cd ;
    for (int i = 0; i <= data.size() - 1; i++)
    {
        cd = data[i].cd;
        bool is_in = false ;
        for (int n = 0; n < cdmemory.size(); n++)
        {
            if (cd == cdmemory[n])
                is_in = true ;
        }
        if (is_in == false)
        {
            vector<Track> temporary ;
            cdmemory.push_back(cd) ;
            for (int m = 0; m < data.size(); m++)
            {
                if (data[m].cd == cd)
                    temporary.push_back(data[m]);
            }
            quicksorttrack_adjusted(temporary,0,temporary.size() - 1) ;
            for(int i = 0; i < temporary.size(); i++)
            {
                albums.push_back(temporary[i]);
            }
        }
    }
    data = albums;
}

void show_vector(vector<Track> myvector)
{//             
    assert(myvector.size() != 0);
/*              
                                                            */
       for (int i = 0 ; i < myvector.size() ; i++)
        {
            show_track(myvector[i], {true,true,true,true,true,true,true,true}) ;
        }
}

bool start_program ()
{//             
    assert (true);
/*                                                                 
                                                                            */
    cout << "choose one of the following sorting methods:\n" ;
    cout << "sort tracks by length - type: \'1\'\n" ;
    cout << "sort tracks by length, with a \'red, white, orange, blue\'-manner - type: \'2\'\n" ;
    cout << "sort tracks by number of track in it\'s album - type: \'3\'\n" ;
    cout << "sort tracks by number of track in it\'s album, with a \'red, white, orange, blue\'-manner - type: \'4\'\n\n" ;
    char choice ;
    cin >> choice;
    if (choice = '1')
        quicksorttime(list_of_tracks, 0, list_of_tracks.size()-1) ;
    else if (choice = '2')
        quicksorttime_adjusted(list_of_tracks, 0, list_of_tracks.size()-1);
    else if (choice = '3')
        sort_albums_by_tracks(list_of_tracks);
    else if (choice = '4')
        sort_albums_by_tracks_adjusted(list_of_tracks);
    else
    {
        cout << "wrong, try again." ;
        return false ;
    }
    cout << "\n\n" ;
    show_vector(list_of_tracks) ;
    return true ;
}

typedef int El ;

void swap_el (vector<El>& data, int a, int b)
{//              
     assert (true);
/*                                          */
    El c = data[b] ;
    data[b] = data[a] ;
    data[a] = c ;
}

int largest_recursive (vector<El>& v, int low, int up)
{//              
    assert (true);
    /*                                                   */
    cout << low << endl;
    cout << up << endl;
    if (low >= up)
        return low ;
    else
    {
        const int POS = largest_recursive(v, low+1, up);
        if (v[low] > v[POS])
            return low ;
        else
            return POS ;
    }
}

int largest_iterative (vector<El>& v, int low, int up)
{//              
    assert (true);
    /*               
                                       */
    vector<int> lowstack;
    vector<int> upstack;
    vector<int> posstack;
    while (low < up)
    {
        if (v[low] > v[up])
        {
            posstack.push_back(low);
        }
        else
        {
            posstack.push_back(up) ;
        }
        low = low+1 ;
    }
    posstack.push_back(low);
    while (posstack.size() > 0)
    {
        up = posstack[posstack.size()-1];
        posstack.pop_back();
    }
}

void sort_recursive (vector<El>& v, int n)
{//              
    assert (true);
    /*               
                               */
    if (n > 1)
    {
        const int POS = largest_recursive (v, 0, n-1);
        swap_el (v,POS, n-1);
        sort_recursive(v,n-1);
    }
}

int main()
{
    ifstream trackfile;
    while (!file(trackfile))
        cout << "*Failed to open file. Try again*\n" ;
    read(trackfile);
    start_program();
    vector<El> v = {2,5,6,4,34,1};
    sort_recursive(v, v.size()) ;
    for (int i = 0 ; i < v.size() ; i++)
        cout << v[i] << ' ';
    return 0;
}

