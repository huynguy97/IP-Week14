#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>

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

vector<Track> songs;

/*                                                                       
                                
                                                               
                                                                         
                                                                       */

//              
//                       
//                        

/*                                  
                                                                          
 
                            
                        
                                 
                                             
                                          
             
                              
     
                                     
 

                                               
 
                                                                      
 
*/

bool operator<(const Track& a, const Track& b){
    if (a.time.minutes==b.time.minutes)
        return a.time.seconds<b.time.seconds;
    return a.time.minutes<b.time.minutes;
}

bool operator==(const Track& a, const Track& b){
    return a.time.minutes==b.time.minutes && a.time.seconds==b.time.seconds;
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

bool operator<(const Length& a, const Length& b){ //                           
    if (a.minutes==b.minutes)
        return a.seconds<b.seconds;
    return a.minutes<b.minutes;
}

bool operator==(const Length& a, const Length& b)
{
    return a.minutes==b.minutes && a.seconds==b.seconds;
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

vector<Track> swap (vector<Track>& musicDB, int i, int j){
    //	              
	assert ( i >= 0 && j >= 0 ) ;	//                            
                                    //                            
    //                                                
    //                           
	const Track HELP = musicDB [i];
	musicDB [i] = musicDB [j] ;
	musicDB [j] = HELP;
	return musicDB;
}

void dnf (vector<Track>& musicDB, int first, int last, int&red, int&blue){
    //               
    assert(first>=0 /*         */ && first<=last);
    //                
    //                                                                                    
    //                                                                                      
    //                                        
    red = first-1;
    blue = last+1;
    int white = last+1;
    const Track PIVOT = musicDB [first+(last-first)/2];
    while (red < white-1){
        const int NEXT = white-1;
        if (musicDB [NEXT] > PIVOT){
            blue--;
            white--;
            swap(musicDB, blue, NEXT);
        }
        else if (musicDB[NEXT] == PIVOT){
            white--;
        }
        else{
            red++;
            swap(musicDB, NEXT, red);
        }
    }
}

void quicksort(vector<Track>& musicDB, int first, int last){
    //               
    assert (0 <= first && last <= static_cast<int>(musicDB.size()));//                          
    //                                 
    //
    //                                           
    if (first>=last)
        return;
    else{
        int red, blue ;
        dnf(musicDB, first, last, red, blue) ;
        quicksort(musicDB, first, red) ;
        quicksort(musicDB, blue, last);
    }
}

void show_all_tracks (vector<Track> songs, int no_of_songs)
{//               
    assert (true) ;
   //               
    //                                                              

    for (int i = 0 ; i < no_of_songs; i++)
        cout << i+1 << ". " << songs[i] << endl ;
}

bool is_sorted(vector<Track> songs) {
    //              
    assert (true);
    //               
    //                                                                                      
    for (int i = 0; i < static_cast<int>(songs.size()-1); i++) {
        if (songs[i] > songs[i+1]) {
            cout << i << " " << i+1 << endl;
            return false;
        }
    }
    return true;
}

int largest(vector<Track>& musicDB, int low, int up){
    //               
    assert (low >= 0 && up >= 0);
    //               
    //                                           
    if(low>=up)
        return low;
    else{
        const int POS = largest(musicDB, low+1, up);
        if (musicDB[low] > musicDB[POS])
            return low;
        else
            return POS;
    }
}

int largest_iteratively(vector<Track>& musicDB, int low, int up){
    //               
    assert (low >= 0 && up >= 0);
    //               
    //                                           
    vector<Track>stack;
    while(low<up){
        stack.push_back(musicDB[low]);
        low++;
    }
    // 
    while(stack.size()>0){
        stack[low]=stack[stack.size()-1];
        stack.pop_back();
    }
    return low;
}

void sort_iteratively(vector<Track>& musicDB, int n){
    //              
    assert(true);
    //               
    //                                        
    //                                                                   
    //                     
    while (!(n<=1)) {
        const int POS = largest(musicDB, 0, n-1);
        swap(musicDB, POS, n-1);
        n--;
    }
}

int main()
{
    //                                      
    //                                       
    sort_iteratively(testDB, testDB.size());
    cout << is_sorted(testDB) << endl;
    return 0;
}

