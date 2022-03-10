#include <bits/stdc++.h>
#include <fstream>
using namespace std;

class FIFOScheduler {  

private:
    int no_of_subjects;
    int tray_capacity;
    vector<int> tray;
    vector<int> freq;
    vector<int> last_used;
    int tray_counter=0;
    int fifo_counter=0;
    int time=0;

public:

    int miss=0; //Making this public because we need to display total misses in the end

    FIFOScheduler(){;}

    //Constructor for initialization of values
    FIFOScheduler(int a,int b)
    {
        no_of_subjects = a;
        tray_capacity = b;
        tray.resize(tray_capacity,0);
        freq.resize(no_of_subjects,0);
        last_used.resize(no_of_subjects,0);
    }

    //Returns -1 if subject is not present in tray, else returns subject number
    int search(int subno)
    {
        for (int i=0;i<tray_counter;i++)
        {
            if (tray[i]==subno)
                return subno;
        }
        return -1;
    }

    void replace(int subno)
    {
        //front element removed, all others shift 1 step ahead
        for (int i=0;i<tray_capacity-1;i++)
        {
            tray[i]=tray[i+1];
        }
        tray[tray_capacity-1]=subno;    //New element enters in the end
    }

    //Driver function
    void makeQuery(string query)
    {
        int subno=stoi(query.substr(1))-1;  //M31 returns 31 in int
        int index=search(subno);    //Finding index of the subject number

        if(index==-1)  //subject not found
        {
            miss++; //Else increment miss

            if (tray_counter<tray_capacity) {   //if there is a space for element, no replacement
                tray[tray_counter++] = subno;
                fifo_counter++;
            }
            else    //Else replace using queried subject
            {
                replace(subno);
            }
        }
 
        freq[subno]++;          //number of queries on a subject
        last_used[subno]=time;
        time++;
        //displayTray();
    }
 
    //Function to display all relevant details
    void displayTray(ofstream &out)
    {
        cout<<"Tray content for BTech is: ";
        out<<"Tray content for BTech is: ";
        for (int i=0;i<tray_counter;i++)
        {
            cout<<"B"<<tray[i]+1<<"_"<<freq[tray[i]]<<"|";
            out<<"B"<<tray[i]+1<<"_"<<freq[tray[i]]<<"|";
        }
        cout<<endl;
        out<<'\n';

        int max=0;
        for (int i=0;i< freq.size();i++)
        {
            if (freq[max]<freq[i])
                max=i;
        }

        cout<<"Most issued subject is: "<<"B"<<max+1<<" -> "<<freq[max]<<" no of times"<<endl<<endl;
        out<<"Most issued subject is: "<<"B"<<max+1<<" -> "<<freq[max]<<" no of times"<<"\n\n";
    }
};

//For next 2 classes, everything is same except replace()

class LFUScheduler{

private:
    int no_of_subjects;
    int tray_capacity;
    vector<int> tray;
    vector<int> freq;
    vector<int> last_used;
    int tray_counter=0;
    int fifo_counter=0;
    int time=0;

public:
    int miss=0;

    LFUScheduler(int a,int b)
    {
        no_of_subjects = a;
        tray_capacity = b;
        tray.resize(tray_capacity,0);
        freq.resize(no_of_subjects,0);
        last_used.resize(no_of_subjects,0);
    }
    void makeQuery(string query)
    {
        int subno=stoi(query.substr(1))-1;
        int index=search(subno);

        if (index==-1)
        {
            miss++;
            if (tray_counter<tray_capacity) {
                tray[tray_counter++] = subno;
                fifo_counter++;
            }
            else
            {
                replace(subno);
            }
        }
 
        freq[subno]++;
        last_used[subno]=time;
        time++;
        
    }
 
    int search(int subno)
    {
        for (int i=0;i<tray_counter;i++)
        {
            if (tray[i]==subno)
                return subno;
        }
        return -1;
    }

    //LFU replacement
    void replace(int subno)
    {
        int min=0;

        //The least frequency element is found
        for (int i=0;i<tray_capacity;i++)
        {
            if (freq[tray[i]]<freq[tray[min]])
                min=i;
        }
        tray[min]=subno;    //replacing least freq element
    }

    void displayTray(ofstream &out)
    {
        cout<<"Tray content for MTech is: ";
        out<<"Tray content for MTech is: ";
        for (int i=0;i<tray_counter;i++)
        {
            cout<<"M"<<tray[i]+1<<"_"<<freq[tray[i]]<<"|";
            out<<"M"<<tray[i]+1<<"_"<<freq[tray[i]]<<"|";
        }
        cout<<endl;
        out<<'\n';

        int max=0;
        for (int i=0;i< freq.size();i++)
        {
            if (freq[max]<freq[i])
                max=i;
        }

        cout<<"Most issued subject is: "<<"M"<<max+1<<" -> "<<freq[max]<<" no of times"<<endl<<endl;
        out<<"Most issued subject is: "<<"M"<<max+1<<" -> "<<freq[max]<<" no of times"<<"\n\n";
    }
};

class LRUScheduler{
    int no_of_subjects;
    int tray_capacity;
    vector<int> tray;
    vector<int> freq;
    vector<int> last_used;
    int tray_counter=0;
    int fifo_counter=0;
    int time=1;
    
public:
    int miss=0;

    LRUScheduler(int a,int b)
    {
        no_of_subjects = a;
        tray_capacity = b;
        tray.resize(tray_capacity,0);
        freq.resize(no_of_subjects,0);
        last_used.resize(no_of_subjects,0);
    }
    void makeQuery(string query)
    {
        int subno=stoi(query.substr(1))-1;
        int index=search(subno);
        
        if (index==-1)
        {
            miss++;
            if (tray_counter<tray_capacity) {
                tray[tray_counter++] = subno;
                fifo_counter++;
            }
            else
            {
                replace(subno);
            }
        }
 
        freq[subno]++;
        last_used[subno]=time;
        time++;
       // displayTray();
    }
 
    int search(int subno)
    {
        for (int i=0;i<tray_counter;i++)
        {
            if (tray[i]==subno)
                return subno;
        }
        return -1;
    }

    //LRU replacement
    void replace(int subno)
    {
        int min=0;

        //Finding element which was used last; one with least time stamp
        for (int i=0;i<tray_capacity;i++)
        {
            if (last_used[tray[i]]<last_used[tray[min]])
                min=i;
        }

        tray[min]=subno;    //replacing earliest element
    }

    void displayTray(ofstream &out)
    {
        cout<<"Tray content for PhD is: ";
        out<<"Tray content for PhD is: ";
        for (int i=0;i<tray_counter;i++)
        {
            cout<<"P"<<tray[i]+1<<"_"<<freq[tray[i]]<<"|";
            out<<"P"<<tray[i]+1<<"_"<<freq[tray[i]]<<"|";
        }
        cout<<endl;
        out<<'\n';

        int max=0;
        for (int i=0;i< freq.size();i++)
        {
            if (freq[max]<freq[i])
                max=i;
        }

        cout<<"Most issued subject is: "<<"P"<<max+1<<" -> "<<freq[max]<<" no of times"<<endl<<endl;
        out<<"Most issued subject is: "<<"P"<<max+1<<" -> "<<freq[max]<<" no of times"<<"\n\n";
    }
};

int main() {
    
    //Taking input from file
    ifstream in("input.txt");
    ofstream out("output.txt");

    int nb, nm, np;  //nb = no. of subs for btech, nm = for mtech, np = for phd
    int tb, tm, tp;  //tb = tray capacity for btech, tm = for mtech, tp = for phd

    vector<string> input;   //vector to read queries of books from the string

    in >> nb >> nm >> np >> tb >> tm >> tp; //Reading sizes from input file

    //reading queries of books and storing in input vector
    while(!in.eof()){
        string str; in >> str;
        input.push_back(str);
    }

    //Making objects for each class
    FIFOScheduler *fs = new FIFOScheduler(nb,tb);
    LFUScheduler *lfs = new LFUScheduler(nm,tm);
    LRUScheduler *lrs = new LRUScheduler(np,tp);

    //reading each element of input vector
    for(int x=0; x<input.size(); x++)
    {
        string temp = input[x];
        int ch=temp[0];             //Reading first letter to check if it's for BTech, MTech or PhD

        //IF B, call fifo; if M, call LFU; if P, call LRU
        if(ch=='B')
            fs->makeQuery(temp);
        if(ch=='M')
            lfs->makeQuery(temp);
        if(ch=='P')
            lrs->makeQuery(temp);   
    }
    
    cout<<"Total misses: "<<fs->miss+lfs->miss+lrs->miss<<endl<<endl;
    out<<"Total misses: "<<fs->miss+lfs->miss+lrs->miss<<"\n\n";

    //Displaying current tray situation
    fs->displayTray(out);
    lfs->displayTray(out);
    lrs->displayTray(out);
}