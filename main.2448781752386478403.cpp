//                                                     

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

/*                                                                    
                                            
                                                                     */
struct Length{
	int minutes;							//              
	int seconds;							//                
};
struct Track{
	string artist;						  //            
	string cd;							  //         
	int	year;							//                   
	int	track_no;						//             
	string title;						   //            
	string tags;							//                           
	Length time;							//             
	string country;						 //                                        
};

vector<Track> songs;
int numComparison = 0;

/*                                                                       
                                            
 	                                                          
 	                                                                   
                                                                       */
bool operator<(const Length& a, const Length& b){
	//            
	assert(true);
	//             
	//                                                 
	if (a.minutes!=b.minutes) return a.minutes<b.minutes;
	if (a.seconds!=b.seconds) return a.seconds<b.seconds;
	return false;
}
bool operator==(const Length& a, const Length& b){
	//            
	assert(true);
	//             
	//                                                
	if (a.minutes!=b.minutes) return false;
	if (a.seconds!=b.seconds) return false;
	return true;
}

bool operator!=(const Length& a, const Length& b){
	//            
	assert(true);
	//             
	//                                                    
	return not operator==(a,b);
}

bool operator<(const Track& a, const Track& b){
	//            
	assert(true);
	//             
	//                                            
	numComparison++;
	//                
	if(a.artist!=b.artist) return a.artist<b.artist;
	if(a.cd!=b.cd) return a.cd<b.cd;
	if(a.year!=b.year) return a.year<b.year;
	if(a.track_no!=b.track_no) return a.track_no<b.track_no;
	return false;
	//              
	//                                         
	//                                                 
	//                                             
	//                                 
	//              
	
}

bool operator==(const Track& a, const Track& b){
	//            
	assert(true);
	//             
	//                                              
	numComparison++;
	//                
	if(a.artist!=b.artist) return false;
	if(a.cd!=b.cd) return false;
	if(a.year!=b.year) return false;
	if(a.track_no!=b.track_no) return false;
	return true;
	//              
	//                                 
	//                                     
	//                                   
	//                             
	//             
}

//	                                 
bool operator>(const Track& a, const Track& b){
	return b < a;
}

bool operator<=(const Track& a, const Track& b){
	return !(b < a);
}

bool operator>=(const Track& a, const Track& b){
	return b <= a;
}

/*                                                                       
                            
                                                                       */
istream& operator>>(istream& in, Length& length){//               
	assert(true);
/*                 
	                                                                                                  
*/
	char colon;
	in >> length.minutes >> colon >> length.seconds;
	return in;
}

ostream& operator<<(ostream& out, const Length length){//               
	assert(true);
/*                 
	                                                                  
*/
	out << length.minutes << ':';
	if(length.seconds < 10)
		out << '0';
	out << length.seconds;
	return out;
}

void skip_to_next_newline(istream& infile){//               
	assert(true);
/*                 
	                                                                    
*/
	string remains;
	getline(infile, remains);
}

istream& operator>>(istream& infile, Track& track){//               
	assert(true);
/*                 
	                                                                                                               
	                                  
*/
	getline(infile,track.artist);	   //       
	getline(infile,track.cd);		   //   
	infile >> track.year;			  //     
	skip_to_next_newline(infile);
	infile >> track.track_no;		  //             
	skip_to_next_newline(infile);
	getline(infile,track.title);		//            
	getline(infile,track.tags);		 //           
	infile >> track.time;			  //           
	skip_to_next_newline(infile);
	getline(infile,track.country);	  //        
	skip_to_next_newline(infile);
	return infile;
}

//                                                                                                       
ostream& operator<<(ostream& out, const Track track){//               
	assert(true);
/*                 
	                                                                            
*/
	out << track.artist   << endl;
	out << track.cd	   << endl;
	out << track.year	 << endl;
	out << track.track_no << endl;
	out << track.title	<< endl;
	out << track.tags	 << endl;
	out << track.time	 << endl;
	out << track.country  << endl;
	out << endl;
	return out;
}

//                                                                           
int read_songs(ifstream& infile, vector<Track>& songs){//               
	assert(infile.is_open());
/*                 
	                                                                          
	                                                       
*/
	int no_of_read_songs = 0;
	do {
		Track song;
		infile >> song;
		if(infile){
			no_of_read_songs++;
			songs.push_back(song);
		}
	}
	while(infile);
	return no_of_read_songs;
}

int read_file(string filename){
//               
	assert(true);
/*                 
	                                                                          
	                                                                                         
	                                    
*/
	ifstream songsDBS(filename.c_str());
	if(!songsDBS){
		cout << "Could not open '" << filename << "'." << endl;
		return -1;
	}
	cout << "Reading '" << filename << "'." << endl;
	const int NO_OF_SONGS = read_songs(songsDBS, songs);
	songsDBS.close();
	cout << " Read " << NO_OF_SONGS << " tracks." << endl;
	return NO_OF_SONGS;
}

//                                                                           
void show_all_tracks(vector<Track> songs){//               
	assert(true);
/*                 
	                                                              
*/
	for(int i = 0; i < static_cast<int>(songs.size()); i++)
		cout << i+1 << ". " << songs[i] << endl;
}

/*                                                                       
                                                         
                                                                       */
struct Slice{
	int from; 	//  	       
	int to; 	//           
};

Slice mkSlice(int from, int to){//	              
	assert(true);
/*                 
	                                          
*/	Slice s = { from, to };
	return s;
}

bool valid_slice(Slice s){//               
	assert(true);
/*                 
	                                                                                  
*/
	return 0 <= s.from && s.from <= s.to;
}

bool is_sorted(vector<Track> data, Slice s){//	              
	assert(valid_slice(s));	//                           
//	               
//	                 	                                
//						                                
//						   
//						                            
	bool sorted = true;
	for(int i = s.from; i < s.to && sorted; i++)
		if(data[i] > data[i+1])
			sorted = false;
	return sorted;
}

void swap(vector<Track>& data, int  i, int  j){
//	              
	assert(i >= 0 && j >= 0);	//                         
								//                         
//                                                                
	const Track HELP = data [i];
	data [i] = data [j];
	data [j] = HELP;
}

void dnf(vector<Track>& a, Slice t, int& red, int& blue){
	//              
	assert(true);
	//               
	//                                                                                                                                                                                  
	int white;
	Track pivot = a[(t.from+t.to)/2];
	white = blue = t.to+1;
	red = t.from-1;
	while(white-1>red){
		int orange = white-1;
		if(a[orange].time<pivot.time){
			red++;
			swap(a[red], a[orange]);
		} else if(a[orange].time==pivot.time){
			white--;
			swap(a[white], a[orange]);
		} else {
			blue--;
			swap(a[blue], a[orange]);
			white--;
		}
	}
}

void dnf_rwob(vector<Track>& a, Slice t, int& red, int& blue){
	//              
	assert(true);
	//               
	//                                                                                                                                                                                                                                                                              
	int white;
	Track pivot = a[(t.from+t.to)/2];
	blue = t.to+1;
	white = red = t.from-1;
	while(white+1<blue){
		int orange = white+1;
		if(a[orange].time<pivot.time){
			red++;
			swap(a[red], a[orange]);
			white++;
		} else if(a[orange].time==pivot.time){
			white++;
			swap(a[white], a[orange]);
		} else {
			blue--;
			swap(a[blue], a[orange]);
		}
	}
}

void quicksort(vector<Track>& a, Slice t){
	//              
	assert(true);
	//               
	//                                                    
	if(t.from>t.to){
		//              
		return;
	}
	int red, blue;
	dnf(a, t, red, blue);
	quicksort(a, mkSlice(t.from, red));
	quicksort(a, mkSlice(blue, t.to));
}

//       
int largest(vector<Track>& v, int low, int up){
	//              
	assert(0<=low&&0<=up&&low<=v.size()&&up<=v.size());
	//               
	//                                                     
	vector<int> low_st;
	while(low<up){
		low_st.push_back(low);
		low++;
	}
	while(!low_st.empty()){
		int clow = low_st[low_st.size()-1]; low_st.pop_back();
		if(v[clow]>v[low])
			low = clow;
	}
	return low;
}

void sort(vector<Track>& v, int n){
	//              
	assert(n>=0);
	//                         
	while(n>1){
		const int POS = largest(v, 0, n-1);
		swap(v, POS, n-1);
		n--;
	}
}

int main(){
	const int NO_OF_SONGS = read_file("Tracks.txt");
	if(NO_OF_SONGS < 0){
		cout << "Reading file failed. Program terminates." << endl;
		return NO_OF_SONGS;
	}
	int numSort = NO_OF_SONGS;
	vector<Track> dbcopy(songs);
	numComparison = 0;
	//                      
	//                                               
	sort(dbcopy, NO_OF_SONGS);
	//                                     
	for(int x=0; x<dbcopy.size(); x++){
			cout << dbcopy[x] << endl;
	}
	return 0;
}

