//
//          
//               
//
//                                 
//                                                 
//

#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <cstring>
#include <fstream>

using namespace std;
struct Length
{
    int minutes;                            //               
    int seconds;                            //                 
};

struct Track
{
    string artist;                          //            
    string cd;                              //         
    int    year;                            //                   
    int    track_no;                        //             
    string title;                           //            
    string tags;                            //                            
    Length time;                            //             
    string country;                         //                                         
};

vector<Track> data;
int choice;

int size (vector<Track> data)
{
    int volume = static_cast<int> (data.size());
    return volume;
}

bool check_choice (int choice)
{
    if (choice == 1 || choice == 2) return true;
    else return false;
}

bool operator<(const Track& a, const Track& b)
{
    //             
    assert(check_choice(choice));
    //              
    switch(choice)
    {
        case 1:
            if (a.cd != b.cd) return a.cd < b.cd;
            else if(a.artist != b.artist) return a.artist < b.artist;
        else return a.track_no < b.track_no;
            break;
        case 2:
            if (a.time.minutes != b.time.minutes)
                return a.time.minutes < b.time.minutes;
            else return a.time.seconds < b.time.seconds;
        default:
            break;
    }
    return true;
}

bool operator == (const Track& a, const Track& b)
{
    //             
    assert(check_choice(choice));
    //             
    switch(choice)
    {
        case 1:
            return ((a.cd == b.cd) && (a.artist == b.artist) && (a.track_no  == b.track_no));
            break;
        case 2:
            return ((a.time.minutes == b.time.minutes) && (a.time.seconds == b.time.seconds));
        default:
            break;
    }
    return true;
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

void swap (vector<Track>& data, int red, int NEXT)
{
    swap(data[red],data[NEXT]);
}

void dnf (vector<Track>& data, int first, int last, int& red, int& blue)
{
    //                                                                 
    red = first - 1;
    blue = last + 1;
    int white = first - 1;
    const Track PIVOT = data [first+(last-first)/2];
    while(blue>white + 1)
    {
        const int NEXT = white + 1;
        if(data[NEXT] < PIVOT)
        {
            red++; white++;
            swap(data, red, NEXT);
        }
        else if (data[NEXT] == PIVOT)
            white++;
        else
        {
            blue--;
            swap (data, NEXT, blue);
        }
    }
}

void quicksort (vector<Track>& data, int first, int last)
{
    //              
    assert(0<= first && last < size(data));
    //               
    //                                    
    if (first >= last) {return;}
    else
    {
        int red, blue;
        dnf(data, first, last, red, blue);
        quicksort(data, first, red);
        quicksort(data, blue, last);
    }
}

void show_tracks (vector<Track> data)
{
    //              
    assert(true);
    //               
    //                                     
    cout <<"After sorted: "<<endl;
    for (int i = 0; i < size(data) - 1; i++)
    {
        cout << "Track "<<i+1<<":"<<endl;
        cout <<data[i].artist <<endl;
        cout <<data[i].cd<<endl;
        cout <<data[i].year<<endl;
        cout <<data[i].track_no<<endl;
        cout <<data[i].title<<endl;
        cout <<data[i].tags<<endl;
        cout <<data[i].time<<endl;
        cout <<data[i].country<<endl;
        cout<<endl;
    }
}

int main(int argc, const char * argv[]) {
    ifstream file;
    file.open("Tracks.txt");
    if (!file.is_open())
    {
        cout<< "Cant open the file, please check the file and retry.";
        return 0;
    }
    
    while (file)
    {
        Track data_test;
        file >> data_test;
        data.push_back(data_test);
    }
    
    cout << "Please enter the way you would like to sort your data."<<endl;
    cout << "1. album -> artist -> track number."<<endl;
    cout << "2. time only."<<endl;
    cout << "Choice: ";
    cin>>choice;
    
    while(!check_choice(choice) || !cin)
    {
        cout<<"The choice you made is wrong. Please enter again, in form of 1 or 2 only.";
        cin >> choice;
    }
    
    quicksort(data, 0, size(data) - 1);
    show_tracks(data);
    
    return 0;
}
/*                                                 
                                          

                                                                                                                                                             
*/

