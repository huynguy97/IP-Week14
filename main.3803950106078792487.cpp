#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>

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
	int    track_no;						//             
	string title;                           //            
	string tags;                            //                            
	Length time;							//             
	string country;                         //                                         
};

bool compare_strings(string a, string b) //                                                 
{
    assert(a!=b);
    for(int items=0; items<min(a.length(),b.length());items++)
        {
            if (a[items]<b[items])
                return true;
            if (b[items]<a[items])
                return false;//                
        }
        //                                                    
        if (a.length()<b.length())
            return true;
        else
            return false; //                       
}

bool operator<(const Length& a, const Length& b)
{
    if (a.minutes<b.minutes || (a.minutes==b.minutes && a.seconds<b.seconds))
        return true;
    return false; //                
}

bool operator==(const Length& a, const Length& b)
{
    if (a.minutes==b.minutes && a.seconds==b.seconds )
        return true;
    return false;
}
//                                        
bool operator<(const Track& a, const Track& b) //                                                           
{
    //                                                                                            
    if (a.time<b.time)  //                              
        return true;
    if (b.time<a.time)//                                                                           
        return false;
    if (a.artist!=b.artist) //                         
        return compare_strings(a.artist,b.artist);
    if (a.title!=b.title)
        return compare_strings(a.title,b.title);
    if (a.cd!=b.cd)
        return compare_strings(a.cd,b.cd) ;
    //                                                               
    if(b.year<a.year)  //              
        return false ;
    if (a.year<b.year) //                                                     
        return true;
    if(b.track_no<a.track_no) //                                                   
        return false ;
    if(a.track_no<b.track_no)
        return true;
    if(a.tags!=b.tags)
        return compare_strings(a.tags,b.tags);
    if(a.country!=b.country) //                                                                              
        return compare_strings(a.country,b.country) ;
    if (a.country==b.country)
        return false;
    return true;//
}

bool operator==(const Track& a, const Track& b) //                            
{
    if (a.artist==b.artist && a.cd==b.cd && a.year==b.year && a.track_no==b.track_no && a.title==b.title && a.tags==b.tags && a.time==b.time && a.country==b.country)
        return true ;
    return false; //                                         
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
//          
void swap(vector<Track>& tracks, int el1, int el2)
{
    Track storage=tracks[el1];
    tracks [el1]=tracks[el2];
    tracks[el2]=storage;
}
//                          

//      

void dnfrowb(vector<Track>& tracks,int first, int last, int& red, int& blue )
{
    assert(true);//                                                                                                                                                                         
    /*                                                                                                                                                             
    */
    red=first-1;
    blue= last+1;
    int white= last+1;
    const Track PIVOT = tracks[first+(last-first)/2];
    while(red<white-1)
    {
        const int NEXT= white-1;
        if(tracks[NEXT]<PIVOT)
        {
            red++;
            swap(tracks,red,NEXT);
        }
        else if(tracks[NEXT]==PIVOT)
            white--;
        else
        {
            white--;
            blue--;
            swap(tracks,NEXT,blue);
        }
    }
}
void quicksort(vector<Track>& tracks, int first, int last)
{
    assert(0<=first && last<tracks.size());
    /*                                                               
    */
    if (first>=last)
        return;
    else
    {
        int red, blue;
        dnfrowb(tracks,first,last,red,blue);
        quicksort(tracks,first,red);
        quicksort(tracks,blue,last);
    }
}//                                                                                                                                                                

//      
void dnfrwob(vector<Track>& tracks,int first, int last, int& red, int& blue )
{
    assert(true);
    red=first-1;//                         
    blue= last+1;
    int white= first-1; //                                                                                               
    //                                                                             
    const Track PIVOT = tracks[first+(last-first)/2];//          
    while(blue>white+1)//                                                                                                                                                                                                                              
    {
        const int NEXT= white+1;//                                                                                                          
        if(tracks[NEXT]<PIVOT)//                                                                        
        {
            red++;//                                                                
            white++;
            swap(tracks,red,NEXT);
        }
        else if(tracks[NEXT]==PIVOT)//                                          
            white++;
        else //                                                                          
        {
            blue--;
            swap(tracks,NEXT,blue);
        }
    }
}
//      

/*
                                                              
 
                    
                     
        
     
                                                            
                                     
                         
            
                       
     
 
*/
int largeststacked(vector<Track>& tracks, int first, int last)
{
    assert(last>=first);//                                                                                                
    /*                                                                                                                                 
    */
    vector<Track> stacked;
    while (first<last)
    {
        stacked.push_back(tracks[first]);//                                                                                                      
        first++;
    }
    Track memory=tracks[last];//                                                  
    int largest=last;
    while (stacked.size()>0)
    {
        Track x= stacked[stacked.size()-1];
        stacked.pop_back();
        if(x>memory)
        {
            memory=x;
            largest=stacked.size();
        }
    }
    return largest;
}
int largest(vector<Track> tracks, int first, int last)//                                                         
{
    assert(last>=first);//                                                                                      
    /*                                                                                                                                 
    */
    int largest=first;//                                                                                                                                                      
    Track best=tracks[first];//                     
    first++;//                                
    while (first<=last)
    {
        if (tracks[first]>best)
        {
            best=tracks[first];
            largest=first;
        }
        first++;
    }
    return largest;
}
/*
                                              
 
                                       
     
                                             
                             
                                                
     
 
*/
void sorts(vector<Track>& tracks, int n)
{
    assert(true);//                          
    /*                                                                                   
    */
    while(n>1)//                                                                                                                                                       
    {
        int pos=largest(tracks,0,n-1);
        swap(tracks,pos,n-1);
        n--;
    }
}

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}

