//                                   
//                                   

#include <iostream>
#include <vector>
#include <cassert>
#include <fstream>
#include <string>

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

bool operator<(const Track& a, const Track& b)
{

	if (a.artist == b.artist) {
		if (a.cd == b.cd) {
			if (a.year == b.year) {
				return (a.track_no < b.track_no);
			}
			else return (a.year < b.year);
		}
		else return (a.cd < b.cd);
	}
	else return (a.artist < b.artist);
}

bool operator<(const Length& a, const Length& b)
{
	if (a.minutes == b.minutes) {
		return (a.seconds < b.seconds);
	}
	return (a.minutes < b.minutes);
}
bool operator>(const Length& a, const Length& b)
{
	if (a.minutes == b.minutes) {
		return (a.seconds < b.seconds);
	}
	return (a.minutes > b.minutes);
}
bool operator==(const Length& a, const Length& b)
{
	if (!(a < b) && !(a > b)) return true;
	else return false;
}
bool operator>=(const Length& a, const Length& b)
{
	return (a > b || a == b);
}
bool operator<=(const Length& a, const Length& b)
{
	return (a < b || a == b);
}
bool operator==(const Track& a, const Track& b)
{

	return (a.artist == b.artist && a.track_no == b.track_no && a.time == b.time && a.cd == b.cd);
}
bool operator>(const Track& a, const Track& b)
{
	return b < a;
}
bool operator<=(const Track& a, const Track& b)
{
	return !(b < a);
}
bool operator>=(const Track& a, const Track& b)
{
	return b <= a;
}

istream& operator>> (istream& in, Length& length)
{//               
	assert(true);
	/*                 
		                                                                                                  
	*/
	char colon;
	in >> length.minutes >> colon >> length.seconds;
	return in;
}
ostream& operator<< (ostream& out, const Length length)
{//               
	assert(true);
	/*                 
		                                                                   
	*/
	out << length.minutes << ':';
	if (length.seconds < 10)
		out << '0';
	out << length.seconds;
	return out;
}
void skip_to_next_newline(istream& infile)
{//               
	assert(true);
	/*                 
		                                                                    
	*/
	string remains;
	getline(infile, remains);
}

istream& operator>> (istream& infile, Track& track)
{//               
	assert(true);
	/*                 
		                                                                                                               
		                                  
	*/
	getline(infile, track.artist);       //       
	getline(infile, track.cd);           //   
	infile >> track.year;              //     
	skip_to_next_newline(infile);
	infile >> track.track_no;          //             
	skip_to_next_newline(infile);
	getline(infile, track.title);        //            
	getline(infile, track.tags);         //           
	infile >> track.time;              //           
	skip_to_next_newline(infile);
	getline(infile, track.country);      //        
	skip_to_next_newline(infile);
	return infile;
}
ostream& operator<< (ostream& out, const Track track)
{//               
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

int read_songs(ifstream& infile, vector<Track>& songs)
{//               
	assert(infile.is_open());
	/*                 
		                                                                          
		                                                       
	*/
	int no_of_read_songs = 0;
	do {
		Track song;
		infile >> song;
		if (infile) {
			songs.push_back(song);
			no_of_read_songs++;
		}
	} while (infile);
	return no_of_read_songs;
}
void swap(vector<Track>& data, int  i, int  j)
{//	              
	assert(i >= 0 && j >= 0);	//                         
								//                         
//                                                                
	const Track HELP = data[i];
	data[i] = data[j];
	data[j] = HELP;
}

//               
int largest(vector<int>& v, int low, int up) {
	if (low >= up) return low;
	else {
		const int POS = largest(v, low + 1, up);
		if (v[low] > v[POS])return low;
		else return POS;
	}
}

int largest_iterative(vector<int> &v, int low, int up) {
	//              
	assert(up >= low);
	//                                                              
	int largest;
	for (int i = low; i <= up; i++) {
		for (int j = low; j <= up; j++) {
			if (v[i] < v[j]) largest = j;
		}
	}
	return largest;
}

void swap(vector<int>& v, int pos1, int pos2) {
	int temp = v[pos2];
	v[pos2] = v[pos1];
	v[pos1] = temp;
}
void sort(vector<int>& v, int n) {
	if (n > 1) {
		const int POS = largest(v, 0, n - 1);
		swap(v, POS, n - 1);
		sort(v, n - 1);
	}
}

void iterative_sort(vector<int>& v, int n) {
	while (n > 1) {
		const int POS = largest(v, 0, n - 1);
		swap(v, POS, n - 1);
		n--;
	}
}

void dnf(vector<Track>& data, int first, int last, int& red, int& blue) {
	red = first - 1;
	blue = last + 1;
	int white = last + 1;
	const Track PIVOT = data[first + (last - first) / 2];
	while (red < white - 1) {
		const int NEXT = white - 1;
		if (data[NEXT] < PIVOT) {
			red++;
			swap(data, red, NEXT);
		}
		else if (data[NEXT] == PIVOT) {
			white--;
		}
		else {
			white--;
			blue--;
			swap(data, NEXT, blue);
		}
	}
}
void dnf_time(vector<Track>& data, int first, int last, int& red, int& blue) {
	red = first - 1;
	blue = last + 1;
	int white = last + 1;
	const Track PIVOT = data[first + (last - first) / 2];
	while (red < white - 1) {
		int NEXT = white - 1;
		if (data[NEXT].time < PIVOT.time) {
			red++;
			swap(data, red, NEXT);
		}
		else if (data[NEXT].time == PIVOT.time) {
			white--;
		}
		else {
			white--;
			blue--;
			swap(data, NEXT, blue);
		}
	}
}
void quicksort(vector<Track>& data, int first, int last) {

	if (first >= last) return;
	else {
		int red, blue;
		dnf_time(data, first, last, red, blue);
		quicksort(data, first, red);
		quicksort(data, blue, last);
	}
}
void show_all_tracks(vector<Track>& songs, int no_of_songs)
{//               
	
	/*                 
		                                                              
	*/
	for (int i = 0; i < no_of_songs; i++)
		cout << i + 1 << ". " << songs[i] << endl;
}
int main() {

	ifstream database_reader;
	database_reader.open("Tracks.txt");
	vector<Track> DB;
	read_songs(database_reader, DB);
	quicksort(DB, 0, DB.size()-1);
	//                                                       
	//                                        

	show_all_tracks(DB, DB.size());

	int x = 0;
	cin >> x;
	return 0;
}
