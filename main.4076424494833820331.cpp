#include <iostream>
#include <assert.h>

using namespace std;

//                            

//                                                                                        
void dnf (vector<El>& data, int first, int last, int& red, int& blue)
{
    //              
    assert(last>=last && size(data)>0);
    /*                
                                                                                    
    */
    red = first-1;
    blue = last+1;
    int white = last+1;
    const El Pivot = data [first+(last-first)/2];
    while(red<white-1)
    {
        const int Next = white-1;
        if (data[Next]<Pivot)
        {
            red++;
            swap(data,red,Next);
        }
        else if (data[Next]==Pivot)
            white--;
        else
        {
            white--;
            blue--;
            swap(data,Next,blue);
        }
    }
    for (int i=0; int j=1; j>=last; i++; j++)
    {
         if (data [j] > data [i])
            swap(data,i,j);
    }

}

void quicksort (vector<El>& data , int first, int last)
{
    //             
    assert(last>=first && size(data)>0);
    /*                
                                                 
    */
    if (first<=last)
        return;
    else
    {
        int red, blue;
        dnf (data,first,last,red,blue);
        quicksort (data,first,red);
        quicksort (data,blue,last);

    }

}

void dnf_2 (vector<El>& data, int first, int last, int& red, int& blue)
{
    //             
    assert(last>=first && size(data)>0);
    /*                
                                                                                    
    */
    red = first-1;
    blue = last+1;
    int white = Pivot;
    const El Pivot = data [first+(last-first)/2];
    while(red<white-1)
    {
        const int Next = white-1;
        if (data[Next]<Pivot)
        {
            red++;
            swap(data,red,Next);
        }
        else if (data[Next]==Pivot)
            white++;
            swap(data,Pivot+1,Next);
        else
        {
            blue--;
            swap(data,Next,blue);
        }

    }
}

int largest(vector<El>& v, int low, int up)
{
    //               
    assert(up>=low && size(v)>0);
    /*                
                                                                   
    */
    while ( low <= up)
    {
        for (int i=0; i<=up; i++;)
        {
            if (v [low] > v [i])
                swap(v,low,i);
        }

        low = low+1;
    }
    return v [low];
}

void sort (vector<El>& v, int n)
{
    //               
    assert(n>1 && size(v)>0);
    /*                
                                        
    */
    while (n > 1)
    {
        const int POS = largest(v, 0, n-1);
        swap (v, POS, n-1);
        n--;
    }
    return v;
}

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}

