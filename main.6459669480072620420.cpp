#include <iostream>
#include <cassert>
#include <vector>
//                                           

using namespace std;

struct Time
{
    int min;
    int sec;
};

struct Track
{
    string title;
    string album;
    int trackno;
    Time length;
};

bool operator< (Time& a, const Time& b)
{
    //    
    assert(a.min >= 0 && a.sec >= 0 && b.min >= 0 && b.sec >= 0 && a.sec < 60 && b.sec < 60);
    //     
    //                                   
    if(a.min < b.min)
        return true;
    else if(a.min == b.min && a.sec < b.sec)
        return true;
    return false;
}

bool operator== (Time& a, const Time& b)
{
    //    
    assert(a.min >= 0 && a.sec >= 0 && b.min >= 0 && b.sec >= 0 && a.sec < 60 && b.sec < 60);
    //     
    //                            
    return (a.min == b.min && a.sec == b.sec);
}

bool operator> (Time& a, const Time& b)
{
    //    
    assert(a.min >= 0 && a.sec >= 0 && b.min >= 0 && b.sec >= 0 && a.sec < 60 && b.sec < 60);
    //     
    //                                   
    return (!(a < b) && !(a == b));
}

int size(vector<Track>& data)
{
    return static_cast<int>(data.size());
}

//                                                            
/*
                                         
 
         
                 
          
                                                                                                                   
                         
                    
                               
                                      
                 
 

                                          
 
         
                 
          
                                                
                                                                                                                                               
 
*/

//                                                                       

bool operator< (Track& a, const Track& b)
{
    return a.length < b.length;
}

bool operator== (Track& a, const Track& b)
{
    //   
    assert(true);
    //    
    //                                           
    return a.length == b.length;

}

bool operator> (Track& a, const Track& b)
{
    return (!(a < b) && !(a == b));
}

ostream& operator<< (ostream& out, vector<Track>& data)
{
    //     
    assert(true);
    //      
    //                                                           

    for(int i = 0; i< size(data); i++)
    {
        out << data[i].title << "\t" << data[i]. album << "\t" << data[i].trackno << "\t" << data[i].length.min << ":" << data[i].length.sec << endl;
    }
}

void swap(vector<Track>& data, int a, int b)
{
    //    
    assert(a >= 0 && a < size(data) && b >= 0 && b < size(data));
    //      
    //                      

    Track c = data[a];
    data[a] = data[b];
    data[b] = c;
}

void dnf (vector<Track>& data, int first, int last, int& red, int& blue) //                 
{
    //    
    assert(first >= 0 && last >= 0 && red >= -1 && blue >= 0);
    //     
    //                                                     

    red = first-1;           //               
    blue = last+1;           //                 
    int white= last+1;       //                  
    const Track PIVOT = data[first+(last-first)/2];
    while(red < white- 1)            //                   
    {
        const int NEXT = white - 1;     //            
        if(data[NEXT] < PIVOT)     //                 
        {
            red++;                  //                       
            swap (data, red, NEXT) ;
        }
        else if(data[NEXT] == PIVOT)        //                   
            white-- ;                       //                        
        else                            //                  
        {   white--; blue--;                     //                     
            swap (data, NEXT, blue);
        }
    }
}

void quicksort(vector<Track>& data, int first, int last)
{
    //     
    assert(0 <= first && last < size(data)) ;
    //                                          
    if (first >= last)
        return;
    else
    {
        int red,  blue ;
        dnf (data, first, last, red,  blue) ;
        quicksort(data, first, red) ;
        quicksort(data, blue, last) ;
    }

}

//      
int largest(vector<Track>& v, int low, int up)
{

    //    
    assert(low>=0 && up >= 0 && up < size(v));
    //      
    //                                                      

    int pos = low;
    for(int i = low; i <= up; i++)
    {
        if(v[i]>v[pos])
            pos = i;
    }
    return pos;
}

void sort(vector<Track>& v, int n)
{
    //    
    assert(n>0 && n < size(v));
    //     
    //                                 
    while(n > 1)
    {
        const int POS = largest(v, 1, n-1);
        swap(v, POS, n-1);
        n--;
    }

}

int main()
{
    vector<Track> data =   {{"I","R",1,{2,10}},
                            {"D","B",2,{5,10}},
                            {"Y","S",4,{0,2}},
                            {"N","p",1,{4,20}},
                            {"W","O",3,{1,30}},
                            {"R","K",1,{1651654654,30}},
                            {"R","K",3,{6,30}},
                            {"a", "M",2,{1,10}},
                            {"Y","E",2,{5,10}}};

    int red = -1;
    int blue = 0;
    quicksort(data, 0 ,7);
    cout << data;
    sort(data,6);
    cout << data << endl;

    return 0;
}

