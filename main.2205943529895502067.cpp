#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
using namespace std;
//                                  
//                                                                

struct Length {
	int minutes; //               
	int seconds; //                 
};
struct Track {
	string artist; //            
	string cd; //         
	int year; //                   
	int track_no; //             
	string title; //            
	string tags; //                            
	Length time; //             
	string country; //                                         
};

bool operator < (const Track & a, const Track & b) {
	//              
	assert(true);
	//                                                           
	//                                           
	if (a.artist == b.artist) {
		if (a.cd == b.cd) {
			if (a.year == b.year) {
				return a.track_no < b.track_no;
			} else {
				return a.year < b.year;
			}
		} else {
			return a.cd < b.cd;
		}
	} else {
		return a.artist < b.artist;
	}
}

bool operator == (const Track & a, const Track & b) {
	//              
	assert(true);
	//                                                       
	//                                           
	return a.artist == b.artist && a.cd == b.cd && a.year == b.year && a.track_no == b.track_no;
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
bool operator > (const Track & a, const Track & b) {
	return b < a;
}

bool operator <= (const Track & a, const Track & b) {
	return !(b < a);
}

bool operator >= (const Track & a, const Track & b) {
	return b <= a;
}

istream & operator >> (istream & in, Length & length) {
    //               
	assert(true);
	/*                 
	                                                                                                  
	 */
	char colon;
	in >> length.minutes >> colon >> length.seconds;
	return in;
}

ostream & operator << (ostream & out, const Length length) {
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

void skip_to_next_newline(istream & infile) {
    //               
	assert(true);
	/*                 
	                                                                    
	 */
	string remains;
	getline(infile, remains);
}

istream & operator >> (istream & infile, Track & track) {
    //               
	assert(true);
	/*                 
	                                                                                                               
	                                  
	 */
	getline(infile, track.artist); //       
	getline(infile, track.cd); //   
	infile >> track.year; //     
	skip_to_next_newline(infile);
	infile >> track.track_no; //             
	skip_to_next_newline(infile);
	getline(infile, track.title); //            
	getline(infile, track.tags); //           
	infile >> track.time; //           
	skip_to_next_newline(infile);
	getline(infile, track.country); //        
	skip_to_next_newline(infile);
	return infile;
}

ostream & operator << (ostream & out, const Track track) {
    //               
	assert(true);
	/*                 
	                                                                            
	 */
	out << track.artist << endl;
	out << track.cd << endl;
	out << track.year << endl;
	out << track.track_no << endl;
	out << track.title << endl;
	out << track.tags << endl;
	out << track.time << endl;
	out << track.country << endl;
	out << endl;
	return out;
}

int size(vector <Track>& v) {
	//              
	assert(true);
	//                                                                       
	return static_cast < int > (v.size());
}

int read_songs(ifstream & infile, vector <Track>& songs) {
    //               
	assert(infile.is_open());
	/*                 
	                                                                          
	                                                       
	 */
	do {
		Track song;
		infile >> song;
		if (infile)
			songs.push_back(song);
	} while (infile);
	return size(songs);
}

int read_file(string filename, vector <Track>& songs) {
    //               
	assert(songs.size() == 0);
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

void show_all_tracks(vector <Track>& songs) {
    //               
	assert(true);
	/*                 
	                                 
	 */
	for (int i = 0; i < size(songs); i++)
		cout << i + 1 << ". " << songs[i] << endl;
}
//                             

void swap(vector <Track>& vec, int i, int j) {
	//              
	assert(size(vec) > i && size(vec) > j &&i>=0&&j>=0);
	//                                                                   
	const Track TEMP = vec[i];
	vec[i] = vec[j];
	vec[j] = TEMP;
}
//                                     
//                                                                    
//                                                                         
//                                                                                            
//                                     
void dnf2(vector <Track>& data, int first, int last, int& red, int& blue) {
    //              
    assert(first>=0 && first<size(data) && last>=0 && last<size(data) && first<last);
    //                                                                                                             
    //                                                                                                                                   
	red = first-1; //               
	blue = last+1; //                 
	int white = first-1; //                 
	const Track PIVOT = data[first + (last - first) / 2];
	//                                   
	while(white<blue-1){
        const int i=white+1;
        if(data[i]<PIVOT){
            //                        
            red++;
            white++;
            swap(data, red, i);
        }
        else if(data[i]>PIVOT){
            //                         
            blue--;
            swap(data,blue-1,i);
            //                                                                                           
        }
        else{
            //                          
            white++;
        }
	}
}
//                                                                      
void dnf(vector <Track>& data, int first, int last, int& red, int& blue) {
    //              
    assert(first>=0 && first<size(data) && last>=0 && last<size(data) && first<last);
    //                                                                                                              
    //                                                                                                                                  
	red = first - 1; //               
	blue = last + 1; //                 
	int white = last + 1; //                  
	const Track PIVOT = data[first + (last - first) / 2];
	while (red < white -1) { //                   
		const int NEXT = white - 1; //            
		if (data[NEXT] < PIVOT) { //               
			red++; //                       
			swap(data, red, NEXT);
		} else if (data[NEXT] == PIVOT) { //                   
			white--;
		} //                        
		else { //                     
			white--;
			blue--; //                     
			swap(data, NEXT, blue);
		}
	}
}

void quicksort(vector <Track>& data, int first, int last) {
	//     
	assert(0 <= first && last < size(data));
	//                                          
	if (first >= last)
		return;
	else {
		int red, blue;
		dnf2(data, first, last, red, blue);
		quicksort(data, first, red);
		quicksort(data, blue, last);
	}
}
//                    

//                                                         
int largest_iter(vector<int>& v, int low, int up){
    int max_i=0;
    while(!(low>up)){
        if(v[low]>v[max_i]){
            max_i=low;
        }
        low++;
    }
    return max_i;
}

int size(vector <int>& v) {
	//              
	assert(true);
	//                                                                       
	return static_cast < int > (v.size());
}

void swap(vector<int>& vec, int i, int j){
    //              
	assert(size(vec) > i && size(vec) > j &&i>=0&&j>=0);
	//                                                                   
	const int TEMP=vec[i];
	vec[i]=vec[j];
	vec[j]=TEMP;
}

void sort_iter(vector<int>& v, int n){
    while(n>1){
        int POS = largest_iter(v, 0, n-1);
        swap(v, POS, n-1);
        n--;
    }
}

int main() {
	vector <Track> songlist = {};
	read_file("Tracks.txt", songlist);
	quicksort(songlist, 0, size(songlist) - 1);
	show_all_tracks(songlist);
	return 0;
}

