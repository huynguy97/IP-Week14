#include <cassert>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*                                                                   
                 
                                 
                              
                                                                   */

struct Length {
  int minutes; //               
  int seconds; //                 
};
struct Track {
  string artist;  //            
  string cd;      //         
  int year;       //                   
  int track_no;   //             
  string title;   //            
  string tags;    //                            
  Length time;    //             
  string country; //                                         
};

vector<Track> songs;
bool COMPARE_TYPE_TIME = true;

int size(vector<Track> &tracks) { return static_cast<int>(tracks.size()); }

bool operator<(const Track &a, const Track &b) {
  if (!COMPARE_TYPE_TIME) {
    if (a.artist == b.artist) {
      if (a.cd == b.cd) {
        return a.track_no < b.track_no;
      }
      return a.cd < b.cd;
    }
    return a.artist < b.artist;
  } else {
    if (a.time.minutes == b.time.minutes) {
      return a.time.seconds < b.time.seconds;
    }
    return a.time.minutes < b.time.minutes;
  }
}

bool operator==(const Track &a, const Track &b) {
  //                              
  if (!COMPARE_TYPE_TIME) {
    return a.artist == b.artist && a.cd == b.cd && a.track_no == b.track_no;
  } else {
    return a.time.minutes == b.time.minutes && a.time.seconds == b.time.seconds;
  }
}

//	                                 
bool operator>(const Track &a, const Track &b) { return b < a; }

bool operator<=(const Track &a, const Track &b) { return !(b < a); }

bool operator>=(const Track &a, const Track &b) { return b <= a; }

/*                                                                       
                             
                                                                        */
istream &operator>>(istream &in, Length &length) { //               
  assert(true);
  /*                 
                                                                          
                           
*/
  char colon;
  in >> length.minutes >> colon >> length.seconds;
  return in;
}

ostream &operator<<(ostream &out, const Length length) { //               
  assert(true);
  /*                 
                                                                     
*/
  out << length.minutes << ':';
  if (length.seconds < 10)
    out << '0';
  out << length.seconds;
  return out;
}

void skip_to_next_newline(istream &infile) { //               
  assert(true);
  /*                 
                                                                      
*/
  string remains;
  getline(infile, remains);
}

istream &operator>>(istream &infile, Track &track) { //               
  assert(true);
  /*                 
                                                                          
                                                                           
*/
  getline(infile, track.artist); //       
  getline(infile, track.cd);     //   
  infile >> track.year;          //     
  skip_to_next_newline(infile);
  infile >> track.track_no; //             
  skip_to_next_newline(infile);
  getline(infile, track.title); //            
  getline(infile, track.tags);  //           
  infile >> track.time;         //           
  skip_to_next_newline(infile);
  getline(infile, track.country); //        
  skip_to_next_newline(infile);
  return infile;
}

//                                                                            
//                            
ostream &operator<<(ostream &out, const Track track) { //               
  assert(true);
  /*                 
                                                                       
            
  */
  out << "Artist\t" << track.artist << endl;
  out << "Cd\t" << track.cd << endl;
  out << "Year\t" << track.year << endl;
  out << "TrackNr\t" << track.track_no << endl;
  out << "Title\t" << track.title << endl;
  out << "Tags\t" << track.tags << endl;
  out << "Time\t" << track.time << endl;
  out << "Country\t" << track.country << endl;
  out << endl;
  return out;
}

//                                                                           
int read_songs(ifstream &infile,
               vector<Track> &songs) { //               
  assert(infile.is_open());
  /*                 
                                                                            
                                                         
*/
  int no_of_read_songs = 0;
  do {
    Track song;
    infile >> song;
    if (infile)
      songs.push_back(song);
    no_of_read_songs++;
  } while (infile);
  return no_of_read_songs;
}

int read_file(string filename) {
  /*                
                               
                     
                                                                     
                                                                             
                                                                     
  */

  ifstream songsDBS(filename.c_str());
  if (!songsDBS) {
    cout << "Could not open '" << filename << "'." << endl;
    return -1;
  }
  cout << "Reading '" << filename << "'." << endl;
  const int NO_OF_SONGS = read_songs(songsDBS, songs);
  songsDBS.close();
  cout << " Read " << NO_OF_SONGS << " tracks." << endl;
  return NO_OF_SONGS;
}

void show_all_tracks(vector<Track> &songs, int no_of_songs) {
  //               
  assert(no_of_songs >= 0);
  //                
  //                                                               

  for (int i = 0; i < no_of_songs; i++) {
    cout << "Track number " << (i + 1) << endl;
    cout << songs[i] << endl;
  }
}

void swap(vector<Track> &data, int i, int j) {
  assert(i >= 0 && j >= 0);
  //                         
  //                         
  //                                                                
  const Track HELP = data[i];
  data[i] = data[j];
  data[j] = HELP;
}

void dnf(vector<Track> &data, int first, int last, int &red, int &blue) {
  assert(first >= 0 && first < last && last < size(data));
  //                                                             

  red = first - 1;
  blue = last + 1;
  int white = last + 1;
  const Track PIVOT = data[first + (last - first) / 2];
  while (red < white - 1) {
    const int NEXT = white - 1;
    if (data[NEXT] < PIVOT) {
      red++;
      swap(data, red, NEXT);
    } else if (data[NEXT] == PIVOT) {
      white--;
    } else {
      white--;
      blue--;
      swap(data, NEXT, blue);
    }
  }
}

void dnf_adjusted(vector<Track> &data, int first, int last, int &red,
                  int &blue) {
  assert(first >= 0 && first < last && last < size(data));
  //                                                             

  red = first - 1;
  blue = last + 1;
  int white = red + 1;
  const Track PIVOT = data[first + (last - first) / 2];
  while (white < blue - 1) {
    const int NEXT = blue - 1;
    if (data[NEXT] < PIVOT) {
      red++;
      white++;
      swap(data, NEXT, white);
      swap(data, red, white);
    } else if (data[NEXT] == PIVOT) {
      white++;
      swap(data, NEXT, white);
    } else {
      blue--;
      swap(data, NEXT, blue);
    }
  }
}

void quicksort(vector<Track> &tracks, int first, int last) {
  //               
  assert(0 <= first && last < size(tracks));
  //                
  //                                     
  if (first >= last) {
    return;
  } else {
    int red;
    int blue;
    dnf(tracks, first, last, red, blue);
    //                                              
    quicksort(tracks, first, red);
    quicksort(tracks, blue, last);
  }
}

//                                                                        
//            

//                                               
//                     
//                     
//                                          
//                          
//    
//                                                 
//                                                           
//                      
//                                                      
//      
//  

//              
//           
//          
//  

//                                                
//                      
//                         
//                                    
//                   
//             
//    
//                                               
//                                                            
//                      
//                           
//                      
//                    
//      
//    
//              
//  

int main(int argc, char const *argv[]) {
  const int NO_OF_SONGS = read_file("Tracks.txt");
  if (NO_OF_SONGS < 0) {
    cout << "Reading file failed. Program terminates." << endl;
    return NO_OF_SONGS;
  }
  cout << "Sorting on basis of "
       << (COMPARE_TYPE_TIME ? "TIME" : "ARTIST-ALBUM-TRACKNR") << endl;
  //                                       
  quicksort(songs, 0, size(songs) - 1);
  show_all_tracks(songs, NO_OF_SONGS);

  while (true) {
    cout << "Program exit" << endl;
    string test;
    cin >> test;
  }
  return 0;
}

