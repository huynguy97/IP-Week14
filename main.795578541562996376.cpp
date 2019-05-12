#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>

//                                                                                

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
                       ,{"The Decemberists",               "The tain",                    2005,1, "The tain (parts i-iv)",       "progressive,experimental,folk,rock",{18,35},"U.S.A."}
                       ,{"Colin Stetson and Sarah Neufeld","Never were the way she was",  2015,1, "The sun roars into view",     "jazz,instrumental,experimental",    { 7,37},"U.S.A.,Canada"}
                       ,{"Colin Stetson and Sarah Neufeld","Never were the way she was"  ,2015,2, "Won't be a thing to become",  "jazz,instrumental,experimental",    { 3,24},"U.S.A.,Canada"}
                       ,{"Colin Stetson and Sarah Neufeld","Never were the way she was",  2015,3, "In the vespers",              "jazz,instrumental,experimental",    { 6, 2},"U.S.A.,Canada"}
                       ,{"Colin Stetson and Sarah Neufeld","Never were the way she was",  2015,4, "And still they move",         "jazz,instrumental,experimental",    { 2,56},"U.S.A.,Canada"}
                       ,{"Colin Stetson and Sarah Neufeld","Never were the way she was",  2015,5, "With the dark hug of time",   "jazz,instrumental,experimental",    { 6,34},"U.S.A.,Canada"}
                       ,{"Colin Stetson and Sarah Neufeld","Never were the way she was",  2015,6, "The rest of us",              "jazz,instrumental,experimental",    { 6,30},"U.S.A.,Canada"}
                       ,{"Colin Stetson and Sarah Neufeld","Never were the way she was",  2015,7, "Never were the way she was",  "jazz,instrumental,experimental",    { 8,12},"U.S.A.,Canada"}
                       ,{"Colin Stetson and Sarah Neufeld","Never were the way she was",  2015,8, "Flight",                      "jazz,instrumental,experimental",    { 1,38},"U.S.A.,Canada"}
                       };

bool match (string sub, string source)
{
//               
    assert (true) ;
/*                
                                                                                  
*/
    return source.find(sub) != string::npos ;
}

ostream& operator<< (ostream& out, const Length length)
{
//               
    assert (true) ;
/*                
                                                                                          
*/
    out << length.minutes << ":" << (length.seconds < 10 ? "0" : "") << length.seconds;
    return out;
}

istream& operator>> (istream& in, Length& length)
{
//               
    assert (true) ;
/*                
                                                                                    
*/
    string s;
    in >> s;
    length.minutes = std::stoi(s.substr(0, s.find(":")));
    length.seconds = std::stoi(s.substr(s.find(":")+1));
    return in;
}

Length operator+ (const Length& a, const Length& b)
{
//               
    assert (0 <= a.minutes && 0 <= a.seconds && a.seconds < 60 && 0 <= b.minutes && 0 <= b.seconds && b.seconds < 60) ;
/*                
                                 
*/
    Length c;
    c.minutes = a.minutes + b.minutes + (a.seconds + b.seconds) / 60;
    c.seconds = (a.seconds + b.seconds) % 60;
    return c;
}

bool operator< (const Length& a, const Length& b)
{
//               
    assert (true);
/*                
                                                                             
*/
    return (a.minutes*60 + a.seconds < b.minutes*60 + b.seconds);
}

bool operator== (const Length& a, const Length& b)
{
//               
    assert (true);
/*                
                                                                               
*/
    return (a.minutes*60 + a.seconds == b.minutes*60 + b.seconds);
}

//	                                  
bool operator> (const Length& a, const Length& b)
{
//               
    assert (true);
/*                
                                                                             
*/
	return b < a;
}

bool operator<= (const Length& a, const Length& b)
{
//               
    assert (true);
/*                
                                                                              
*/
	return !(b < a);
}

bool operator>= (const Length& a, const Length& b)
{
//               
    assert (true);
/*                
                                                                              
*/
	return b <= a;
}

bool operator< (const Track& a, const Track& b)
{
//               
    assert (true);
/*                
                                                                                                                                                 
                                                                                                                   
                                
*/
    if (a.artist < b.artist)
        return true;
    else if (a.artist == b.artist)
    {
        if (a.cd < b.cd)
            return true;
        else if (a.cd == b.cd)
        {
            if (a.year < b.year)
                return true;
            else if (a.year == b.year)
            {
                if (a.track < b.track)
                    return true;
                else if (a.track == b.track)
                {
                    if (a.title < b.title)
                        return true;
                    else if (a.title == b.title)
                    {
                        if (a.tags < b.tags)
                            return true;
                        else if (a.tags == b.tags)
                        {
                            if (a.time < b.time)
                                return true;
                            else if (a.time == b.time)
                            {
                                if (a.country < b.country)
                                    return true;
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool operator== (const Track& a, const Track& b)
{
//               
    assert (true);
/*                
                                                                                     
*/
    return (a.artist == b.artist && a.cd == b.cd && a.year == b.year && a.track == b.track && a.title == b.title && a.tags == b.tags &&
    a.time == b.time && a.country == b.country);
}

//	                                 
bool operator> (const Track& a, const Track& b)
{
//               
    assert (true);
/*                
                              
*/
	return b < a;
}

bool operator<= (const Track& a, const Track& b)
{
//               
    assert (true);
/*                
                              
*/
	return !(b < a);
}

bool operator>= (const Track& a, const Track& b)
{
//               
    assert (true);
/*                
                              
*/
	return b <= a;
}

void show_track (Track track, TrackDisplay lt)
{
//              
    assert (true);
/*                
                                                                                         
*/
    cout << (lt.showArtist ? track.artist + "\n" : "") << (lt.showAlbum ? track.cd + "\n" : "") << (lt.showYear ? to_string(track.year) + "\n" : "")
    << (lt.showTrack ? to_string(track.track) + "\n" : "") << (lt.showTitle ? track.title + "\n" : "") << (lt.showTags ? track.tags + "\n" : "")
    << (lt.showCountry ? track.country + "\n" : "");
    if (lt.showLength)
        cout << track.time << endl; //                                                                                                   
}

istream& operator>> (istream& in, Track& track)
{//              
    assert (true) ;
/*                
                                                                                                                 
                                                                                                                       
                                                                                              
*/
    string temp; //                                                                                                                      
    getline(in, track.artist);
    getline(in, track.cd);
    getline(in, temp);
    track.year = std::stoi(temp);
    getline(in, temp);
    track.track = std::stoi(temp);
    getline(in, track.title);
    getline(in, track.tags);
    in >> track.time;
    getline(in, temp);
    getline(in, track.country);
    getline(in, temp);
//                                                                                                                                   
    return in;
}

int ReadFile (vector<Track>& archive, ifstream& infile)
{
//               
    assert (infile.is_open());
/*                
                                              
*/
    Track temp;
    while (!infile.eof())
    {
        infile >> temp;
        archive.push_back(temp);
    }
    return archive.size();
}

void VectorSwap(vector<Track>& data, int i, int j)
{
//               
    assert (i >= 0 && i < data.size() && j >= 0 && j < data.size());
/*                
                                                                    
*/
    const Track TEMP = data[i];
    data[i] = data[j];
    data[j] = TEMP;
}

void DNF(vector<Track>& archive, int first, int last, int& red, int& blue, bool timeSort)
{
//               
    assert (first >= 0 && last < archive.size()); //                                                                                      
                                                  //                                                                                          
/*                
                                                                                                                                                     
                                                                                                                                                
                                                                                                                                        
*/
    Track pivot = archive[last - (last - first)/2];
    red = first - 1;
    blue = last + 1;
    int white = last + 1;
    while(red < white - 1)
    {
        int next = white - 1;
        if ((archive[next] == pivot && !timeSort) || (archive[next].time == pivot.time && timeSort))
            white--;
        else if ((archive[next] < pivot && !timeSort) || (archive[next].time < pivot.time && timeSort))
        {
            red++;
            VectorSwap(archive, red, next);
        }
        else
        {
            white--;
            blue--;
            VectorSwap(archive, blue, next);
        }
    }
}

void DNFAdjusted(vector<Track>& archive, int first, int last, int& red, int& blue, bool timeSort)
{
//               
    assert (first >= 0 && last < archive.size()); //                                                                                      
                                                  //                                                                                          
/*                
                                                                                                                                                     
                                                                                                                                                
                                                                                                                                        
*/
    const Track PIVOT = archive[last - (last - first)/2];
    red = first - 1;
    blue = last + 1;
    int white = first - 1;
    while(blue - 1 > white)
    {
        int next = white + 1;
        if ((archive[next] == PIVOT && !timeSort) || (archive[next].time == PIVOT.time && timeSort))
            white++;
        else if ((archive[next] < PIVOT && !timeSort) || (archive[next].time < PIVOT.time && timeSort))
        {
            red++;
            white++;
            VectorSwap(archive, red, next);
        }
        else
        {
            blue--;
            VectorSwap(archive, blue, next);
        }
    }
}

void Quicksort(vector<Track>& archive, int first, int last, bool timeSort = false)
{
//               
    assert(first >= 0 && last < archive.size());
/*                
                                                                                                       
*/
    if (first >= last)
        return;
    else
    {
        int red, blue;
        DNFAdjusted(archive, first, last, red, blue, timeSort);
        Quicksort(archive, first, red, timeSort);
        Quicksort(archive, blue, last, timeSort);
    }
}

struct Slice //                                               
{
    int first;
    int last;
};

void QuicksortIterative(vector<Track>& archive, int first, int last, bool timeSort = false)
{
//               
    assert (first >= 0 && last < archive.size());
/*                
                                                                                                       
*/
    vector<Slice> slices;
    slices.push_back({first, last});
    cout << slices.back().first << " " << slices.back().last << endl;
    int red, blue;
    Slice current;
    while(!slices.empty())
    {
        current = slices.back();
        slices.pop_back();
        DNF(archive, current.first, current.last, red, blue, timeSort);

        if(current.first < red)
            slices.push_back({current.first, red});

        if(blue < current.last)
            slices.push_back({blue, current.last});

    }
}

void PrintVector(vector<Track>& archive)
{
//               
    assert (true);
/*                
                                                    
*/
    TrackDisplay lt = {true, true, true, true, true, true, true, true}; //                                                                   
    for (Track t : archive)
    {
        show_track(t, lt);
        cout << endl;
    }
}

int main()
{
    ifstream inputfile;
    vector<Track> allTracks;
    inputfile.open("Tracks.txt");
    ReadFile(allTracks, inputfile);
    QuicksortIterative(allTracks, 0, allTracks.size() - 1);
    PrintVector(allTracks);
    inputfile.close();
	return 0;
}

