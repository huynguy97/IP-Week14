#include <iostream>
#include<fstream>
#include<vector>
#include<cassert>
#include<cmath>

//                                
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
	int    track_no;						//             
	string title;                           //            
	string tags;                            //                            
	Length time;							//             
	string country;                         //                                         
};

bool operator ==(const Length& a, const Length& b)
{
    if(a.minutes == b.minutes)
    {

        return a.seconds==b.seconds;
    }
    else
        return a.minutes==b.minutes;
}

bool operator <(const Length& a, const Length& b)
{
    if (a.minutes==b.minutes)
    {

        return a.seconds < b.seconds;
    }
    else
        return a.minutes < b.minutes;
}

void skip_to_next_newline (istream& infile)
{
    //               
    assert (true) ;
    /*                 
                                                                            
    */
    string remains ;
    getline (infile, remains) ;
}

istream& operator>> (istream& in, Length& length)
{
    //               
    assert (true) ;
    /*                 
                                                                                                          
    */
    char colon ;
    in >> length.minutes >> colon >> length.seconds ;
    return in ;
}

ostream& operator<< (ostream& out, const Length length)
{
    //               
    assert (true) ;
    /*                 
                                                                           
    */
    out << length.minutes << ':';
    if (length.seconds < 10)
        out << '0';
    out << length.seconds;
    return out ;
}

istream& operator>> (istream& infile, Track& track)
{
    //               
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

ostream& operator<< (ostream& out, const Track track)
{
    //               
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

void read_file_to_vector(ifstream& infile, vector<Track>& songs )
{
    //            
    assert(true);
    //                                                        

    Track tmp;
    infile>>tmp;
    while(infile)
    {
        songs.push_back(tmp);
        infile>>tmp;
    }
}

void show(vector<Track>& songs)
{
    //            
    assert(true);
    //                                                                 
    for(int unsigned i=0;i<songs.size();i++)
    {
        cout<<songs[i];
    }
}

bool comp_tracks(vector<Track>& songs, int a , int b)
{
    //            
    assert(a>=0 && b>=0);
    //                                                                        
    return (songs[a].artist==songs[b].artist) && (songs[a].cd==songs[b].cd);
}

void swapp(vector<Track>& songs, int a, int b)
{
    //            
    assert(a>=0 && b>=0);
    //                                                                        
    Track tmp;
    tmp=songs[a];
    songs[a]=songs[b];
    songs[b]=tmp;

}

void swappp(vector<int>& v, int a, int b)
{
    //            
    assert(a>=0 && b>=0);
    //                                                                        
    int tmp;
    tmp=v[a];
    v[a]=v[b];
    v[b]=tmp;

}

int sizee(vector<Track>& songs)
{
    //           
    assert(true);
    //                                           
    return songs.size();
}

int sizeee(vector<int>& v)
{
    //           
    assert(true);
    //                                           
    return v.size();
}

void dnf(vector<Track>& songs , int first , int last, int& red, int& blue)
{
    //            
    assert(last<=songs.size());
    //                                                              
    red=first-1;
    blue=last+1;
    int white = last +1;
    int const p=songs[first].track_no;
    while(red<white-1)
    {
        const int next=white-1;
        if(songs[next].track_no<p && comp_tracks(songs,next,first))
        {
            red++;
            swapp(songs,red,next);
        }
        else if((songs[next].track_no==p) &&(comp_tracks(songs,next,first)))
        {
            white--;
        }
        else
        {
            white--;
            blue--;
            swapp(songs,next,blue);
        }

    }

}

void quicksort(vector<Track>& songs , int first, int last)
{
    //            
    assert(0<= first && last < sizee(songs));
    //                                                               
    if(first>=last)
        return;
    else
    {
        int red, blue;
        dnf(songs, first, last,red,blue);
        quicksort(songs,first,red);
        quicksort(songs,blue,last);
    }
}

void dnf_time(vector<Track>& songs , int first , int last, int& red, int& blue)
{
    //            
    assert(last<=songs.size());
    //                                                              
    red=first-1;
    blue=last+1;
    int white = last +1;
    Length const p=songs[first].time;
    while(red<white-1)
    {
        const int next=white-1;
        if(songs[next].time<p)
        {
            red++;
            swapp(songs,red,next);
        }
        else if((songs[next].time==p))
        {
            white--;
        }
        else
        {
            white--;
            blue--;
            swapp(songs,next,blue);
        }

    }

}

void quicksort_time(vector<Track>& songs , int first, int last)
{
    //            
    assert(0<= first && last < sizee(songs));
    //                                                               
    if(first>=last)
        return;
    else
    {
        int red, blue;
        dnf_time(songs, first, last,red,blue);
        quicksort_time(songs,first,red);
        quicksort_time(songs,blue,last);
    }
}

/*                                                                                                                                  

                                                                                 
 
                  
                               
                                                                    
                
                
                         
                                      
                       
     
                                
                                                                   
         
                  
                                  
         
                                                                            
         
                     
         
            
         
                     
                   
                                   
         

     

 

                                                                 
 
                  
                                             
                                                                     
                   
               
        
     
                      
                                                
                                          
                                          
     
 

                                                                                      
 
                  
                               
                                                                    
                
                
                         
                                     
                       
     
                                
                              
         
                  
                                  
         
                                      
         
                     
         
            
         
                     
                   
                                   
         
     
 

                                                                      
 
                  
                                             
                                                                     
                   
               
        
     
                      
                                                     
                                               
                                               
     
 */

int largest_iterative(vector<int>& v, int low, int up)
{
    //            
    assert(low>=0 && up< sizeee(v));
    //                                                      
    vector<int> stack;
    int pos;
    while (!(low >= up))
    {
        stack.push_back (low) ;
        low = low + 1;
    }
    pos = low;
    while (stack.size() > 0)
    {
        low = stack [stack.size()-1] ;
        stack.pop_back () ;
        if (v [low] > v [pos])
            pos = low;
        else
            pos = pos;
    }
    return pos;
}

void sort_iterative(vector<int>& v, int n)
{
    //            
    assert(n<=sizeee(v));
    //                                             

    while(n>1)
    {
        int pos=largest_iterative(v,0,n-1);
        swappp(v,pos,n-1);
        n=n-1;
    }
}

int main()
{
    /*                                                      
                              
                        
                                      
                   
                                                           
                                                          
                */
    /*                                                                                     
                        
                                
     
                        
     */

    return 0;
}

