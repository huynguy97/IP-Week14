#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>

using namespace std;

//                                              
//                                                   

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

vector<Track> songs;
ifstream infile;

istream& operator>> (istream& in, Length& length){
//                
    assert(true);
/*                 
                                                                                                      
*/
    char colon;
    in >> length.minutes >> colon >> length.seconds;
    return in;
}

ostream& operator<< (ostream& out, const Length length){
//                
    assert(true);
/*                 
                                                                       
*/
    out << length.minutes << ':';
	if (length.seconds < 10)
		out << '0';
	out << length.seconds;
	return out;
}

istream& operator>> (istream& infile, Track& track){
//                
    assert(true);
/*                 
                                                                                                                   
                                      
*/
    string str;
    getline(infile,track.artist);       //       
    getline(infile,track.cd);           //   
    infile >> track.year;              //     
    getline(infile, str);
    infile >> track.track_no;          //             
    getline(infile, str);
    getline(infile,track.title);        //            
    getline(infile,track.tags);         //           
    infile >> track.time;              //           
    getline(infile, str);
    getline(infile,track.country);      //        
    getline(infile, str);
    return infile;
}

ostream& operator<< (ostream& out, const Track track){
//                
    assert(true);
/*                 
                                                                                
*/
    out << track.artist   << endl;
    out << track.cd       << endl;
    out << track.year     << endl;
    out << track.track_no << endl;
    out << track.title    << endl;
    out << track.tags     << endl;
    out << track.time     << endl;
    out << track.country  << endl;
    out << endl;
    return out;
}

bool operator< (const Length a, const Length b){
    return (a.minutes * 60 + a.seconds) < (b.minutes * 60 + b.seconds);
}

bool operator== (const Length a, const Length b){
    return a.minutes == b.minutes && a.seconds == b.seconds;
}

bool operator<(const Track& a, const Track& b){
    if (a.artist == b.artist){
        if(a.cd == b.cd){
            return a.track_no < b.track_no;
        }
        return a.cd < b.cd;
    }
    return a.artist < b.artist;
}

bool operator>(const Track& a, const Track& b){
	return b < a ;
}

bool operator==(const Track& a, const Track& b){
    return a.artist == b.artist && a.cd == b.cd && a.year == b.year && a.track_no == b.track_no;
}

void show_all_tracks (vector<Track>& songs, int no_of_songs){
//                
    assert(no_of_songs >= 0);
/*                 
                                                                  
*/
    for (int i = 0 ; i < songs.size(); i++){
        cout << i+1 << ". " << songs[i] << endl ;
    }
}

int read_file (ifstream& infile){
//                
    assert(songs.size() == 0);
/*                 
                                                                       
*/
    int i = 0;
    Track temp;
    infile.open("Tracks.txt");
    while(infile){
        infile >> temp;
        songs.push_back(temp);
        i++;
    }
    cout << i << " numbers are stored" << endl;
    return i;
}

void swap_tracks(vector<Track>& data, int a, int b){
//                
    assert(true);
/*                 
                                   
*/
    Track temp;
    temp = data[a];
    data[a] = data[b];
    data[b] = temp;
}

void dnf (vector<Track>& data, int first, int last, int& red, int& blue);

void quicksort (vector<Track>& data, int first, int last){
//                
    assert(0 <= first);
/*                 
                                        
*/
    if(first >= last){
        return;
    } else {
        int red, blue ;
        dnf (data, first, last, red, blue);
        quicksort (data, first, red);
        quicksort (data, blue, last);
    }
}

void dnf (vector<Track>& data, int first, int last, int& red, int& blue){
//                
    assert(0 <= first);
/*                 
                                        
*/
    red = first-1;
    blue = last+1;
    int white = first-1;
    const Track PIVOT = data[first+(last-first)/2];

    while(blue > white + 1){
        const int NEXT = white + 1;
        if(data[NEXT] < PIVOT){
            red++;
            white++;
            swap_tracks(data, red, NEXT);
        }
        else if(data[NEXT] == PIVOT){
            white++;
        } else {
            blue--;
            swap_tracks(data, NEXT, blue);
        }
    }
}

void dnf_time(vector<Track>& data, int first, int last, int& red, int& blue);

void quicksort_time(vector<Track>& data, int first, int last){
//                
    assert(0 <= first);
/*                 
                                                  
*/
    if(first >= last){
        return;
    } else {
        int red, blue ;
        dnf_time(data, first, last, red, blue);
        quicksort_time(data, first, red);
        quicksort_time(data, blue, last);
    }
}

void dnf_time(vector<Track>& data, int first, int last, int& red, int& blue){
//                
    assert(0 <= first);
/*                 
                                                  
*/
    red = first-1;
    blue = last+1;
    int white = last+1;
    const Track PIVOT = data[first+(last-first)/2];

    while(red < white - 1){
        const int NEXT = white - 1;
        if(data[NEXT].time < PIVOT.time){
            red++;
            swap_tracks(data, red, NEXT) ;
        }
        else if(data[NEXT].time == PIVOT.time){
            white--;
        } else {
            white--; blue--;
            swap_tracks(data, NEXT, blue);
        }
    }
}

void dnf_2(vector<Track>& data, int first, int last, int& red, int& blue);

void quicksort_2(vector<Track>& data, int first, int last){
//                
    assert(0 <= first);
/*                 
                                                                                         
*/
    if(first >= last){
        return;
    } else {
        int red, blue ;
        dnf_2(data, first, last, red, blue);
        quicksort_2(data, first, red);
        quicksort_2(data, blue, last);
    }
}

void dnf_2(vector<Track>& data, int first, int last, int& red, int& blue){
//                
    assert(0 <= first);
/*                 
                                                                                         
*/
    red = first-1;
    blue = last+1;
    int white = last+1;
    const Track PIVOT = data[first+(last-first)/2];

    while(red < white - 1){
        const int NEXT = white - 1;
        if(data[NEXT] < PIVOT){
            red++;
            swap_tracks(data, red, NEXT);
        }
        else if(data[NEXT] == PIVOT){
            white--;
        } else {
            white--; blue--;
            swap_tracks(data, NEXT, blue);
        }
    }
}

int main(){
//                
    assert(true);
/*                 
                                                                                                                                                            
                    
*/
    int no_of_songs = read_file(infile);

//                                                                                                               
//                                                            
    quicksort_2(songs, 0, songs.size());            //        

    show_all_tracks(songs, no_of_songs);
    return 0;
}

