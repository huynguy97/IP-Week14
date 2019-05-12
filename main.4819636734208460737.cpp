#include <math.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
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

const int MAX_NO_OF_SONGS = 6000;           //                                
Track songs [MAX_NO_OF_SONGS];              //                                     

bool operator==(const Length& a, const Length& b)
{
    if(a.minutes == b.minutes)
        return a.seconds == b.seconds;
    return false;
}

bool operator<(const Length& a, const Length& b)
{
 	if(a.minutes == b.minutes)
        return a.seconds < b.seconds;
    return a.minutes < b.minutes;
}

bool operator<(const Track& a, const Track& b)
{
    int n = a.track_no;
    int m = b.track_no;
    if (a.artist == b.artist)
    {
        if(a.cd == b.cd)
        {
            if(n == m)
            {
                return false;
            }
            else
            {

                return(int) n < (int) m;
            }

        }
        else
            return a.cd < b.cd;
    }
    else
        return a.artist < b.artist;

    //                                                                                       
}

bool operator==(const Track& a, const Track& b)
{
    return a.artist == b.artist && a.cd == b.cd && a.track_no == b.track_no;

    //                                                                                        
}

bool operator>(const Track& a, const Track& b)
{
	return b < a ;
}

bool operator>(const Length& a, const Length& b)
{
	if(a.minutes == b.minutes)
        return a.seconds > b.seconds;
    return a.minutes > b.minutes;
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

ostream& operator<< (ostream& out, const Track track)
{
    cout << track.artist << "\t";
    cout << track.cd << "\t";
    cout << track.year << "\t";
    cout << track.track_no << "\t";
    cout << track.title << "\t";
    cout << track.tags << "\t";
    cout << track.time << "\t";
    cout << track.country << "\n";
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

void read_in_data (ifstream& database, vector <Track>& data)
{//               
    assert (database);
    //                                                                                  
    Track t;
    while(database)
    {
        database >> t;
        data.push_back(t);
    }
}

void swap(vector<Track>& data, int a, int b)
{
    Track c = data[b];
    data[b] = data[a];
    data[a] = c;
}

int size (vector <Track>& data)
{
    return data.size();
}

void dnf (vector<Track>& data, int first, int last, int& red, int& blue)
{//               
    assert (0 <= first && last < size (data));
    //                                                                                                   
    red= first-1;
    blue= last+1;
    int white= last+1;
    const Track PIVOT = data [first+(last-first)/2];
    while (red < white - 1)
    {
        const int NEXT = white - 1;
        if (data[NEXT] < PIVOT)
        {
            red++;
            swap (data, red, NEXT);
        }
        else if (data[NEXT] == PIVOT)
            white--;
        else
        {
            white--;
            blue--;
            swap (data, NEXT, blue);
        }
    }
}

void dnf_adjusted (vector<Track>& data, int first, int last, int& red, int& blue)
{//               
    assert (0 <= first && last < size (data));
    //                                                                                                                                                      
    red = first - 1;
    blue = last + 1;
    int white = first - 1;
    const Track PIVOT = data[first+(last-first)/2];
    while (white < (blue - 1))
    {
        const int NEXT = blue - 1;
        if (data[NEXT] < PIVOT)
        {
            red++;
            white++;
            swap (data, white, NEXT);
            swap (data, red, white);

        }
        else if (data[NEXT] == PIVOT)
        {
            white++;
            swap (data, white, NEXT);
        }
        else
        {
            blue--;
        }
    }
}
void quicksort (vector<Track>& data, int first, int last)
{//               
    assert (0 <= first && last < size (data));
    //                                                    
    if (first >= last) {
        return ;
    }
    else
    {
        int red, blue;
        dnf_adjusted(data, first, last, red, blue);
        quicksort (data, first, red);
        quicksort (data, blue, last);
    }

}
/*
                                                                                                                        
                                  
                                                                                                                        

                                
 
              
     
                                            
                            
                      
     
 

                                          
 
            
                
     
                              
                          
            
     
 

                                                     
 
                  
                   
     
                              
              
     
                        
                        
     
                                    
                                     
                     
     
 

                                           
 
                   
                    
        
     
                                               
                              
                        
            
                        
     
 */

int main()
{
    vector <Track> data;
    ifstream database ("Tracks.txt");
    read_in_data(database,data);
    database.close();
    int lower = 0;
    int upper = (int) size(data) - 1;
    quicksort(data,lower,upper);
    for(int i = 0;i < data.size();i++)
    {
        cout << data[i] << "\n";
    }
    return 0;
}

