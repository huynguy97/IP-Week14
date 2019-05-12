#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>

//                        
//                                                                                                                        
//                                       

using namespace std;

void dnf (vector <int>& data, int first, int last, int& red, int& blue){
    red = first-1;
    blue = last+1;
    int white = last+1;
    int PIVOT = data[first+(last-first)/2];

    while (red<white-1){
        int NEXT = white-1;

        if (data[NEXT] < PIVOT){
            red++;
            swap(data[red],data[NEXT]);
        }
        else if (data[NEXT] == PIVOT)
            white--;
        else {
            white--;
            blue--;
            swap(data[NEXT], data[blue]);
        }
    }
}

void quicksort (vector <int>& data , int first, int last){
    if (first >= last)
        return;
    else {
        int red;
        int blue;
        dnf (data, first, last, red, blue);
        quicksort(data, first, red);
        quicksort(data, blue, last);
    }
}

void dnf2 (vector <int>& data, int first, int last, int& red, int& blue){
    red = first-1;
    blue = last+1;
    int white = first-1;
    int PIVOT = data[first+(last-first)/2];

    while (white < blue-1){
        int NEXT = blue-1;

        if (data[NEXT] < PIVOT){
            red++;
            white++;
            swap(data[red],data[NEXT]);
            if (white != red){
                swap(data[white], data[NEXT]);
            }
        }

        else if (data[NEXT] == PIVOT){
            white++;
            swap(data[NEXT], data[white]);
        }
        else {
            blue--;
        }
    }
}

void quicksort2 (vector <int>& data , int first, int last){
    if (first >= last)
        return;
    else {
        int red;
        int blue;
        dnf2 (data, first, last, red, blue);
        quicksort2(data, first, red);
        quicksort2(data, blue, last);
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

int largest2 (vector <int>& k, int low, int up){
    vector <int> stack;
    while (low <= up){
        stack.push_back(low);
        low++;
    }

    int largest = 0;

    while (stack.size() > 0){
        int x = stack[stack.size()-1];
        stack.pop_back();

        if (k[x] > k[largest])
            largest = x;
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

void sort2 (vector <int>& k, int n){
    while (n<1){
        int POS = largest2(k, low, up);
        swap (k, POS, n-1);
        n--;
    }
}

int main()
{
    vector <int> data = {3,4,5,1,4,2,3,7,8};
    int first = 0;
    int last = 8;
    int red = 0;
    int blue = 0;

    for (int i = 0; i < data.size(); i++){
        cout << data[i];
    }
    cout << endl;

    quicksort(data, first, last);

    for (int i = 0; i < data.size(); i++){
        cout << data[i];
    }
    cout << endl;

    quicksort2(data, first, last);

    for (int i = 0; i < data.size(); i++){
        cout << data[i];
    }

    return 0;
}

