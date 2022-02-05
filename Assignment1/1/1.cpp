#include <bits/stdc++.h>
using namespace std;

void SRTF(vector<int> arrival_time,vector<int> remaining_time,int count)
{
	int finish_count = 0;
	int min_time;
	int min_index;

	int wait_time[count] = {0};

	vector<int> gantt_chart;

	//Loop till all processes are finished
	for(int tq=0;finish_count!=count;tq++) {
		
		//Finds the process with minimum remaining time that isn't zero
		min_time = INT_MAX;
		for(int i=0;i<count;i++) {
			if(arrival_time[i] <= tq && remaining_time[i]<min_time && remaining_time[i]>0){
				min_time = remaining_time[i];
				min_index = i;
			}
		}

		//We add one time quantum of that process to gantt chart
		gantt_chart.push_back(min_index);
		remaining_time[min_index]--;

		//If process time becomes zero
		if(remaining_time[min_index]==0) {
			finish_count++;										//Increment total finished processes
		 	wait_time[min_index] = tq-arrival_time[min_index];	//Add its wait time
		}
	}

	cout<<"GANTT CHART:"<<endl;

	cout<<"Time:\t";
	for(int i=0;i<gantt_chart.size();i++) {
		cout<<i<<"\t";
	}
	cout<<endl<<"Order:\t";
	for(int i=0;i<gantt_chart.size();i++) {
		cout<<"p"<<gantt_chart[i]<<"\t";
	}

	float avg_wait=0;
	for(int i=0;i<count;i++) {
		avg_wait += wait_time[i];
	}

	avg_wait /= count;

	cout<<endl<<endl<<"AVERAGE WAIT: "<<avg_wait;
}

int main()
{
	ifstream myFile("arrival.txt");	//Input file

	int testcases = 0;
	
	//No. of testcases = number of lines in the file
	string line;
	while(getline(myFile,line)) {
		testcases++;
	}

	//Resetting pointer to file
	myFile.clear();
	myFile.seekg(0);

	srand(time(0));	//Seed for random number generation

	for(int t=0;t<testcases;t++) {

		getline(myFile,line);

		//Separating numbers by using delimiter as space
		char *line_arr = &line[0];
		char *ptr = strtok(line_arr," ");

		vector<int> arrival_time;		//Arrival time of each process
		vector<int> remaining_time;		//Remaining time of each process (initially it will be burst time)
		
		int count=0;

		//Read all numbers in a line
		while(ptr) {
			
			int bt = (rand()%8)+1;

			arrival_time.push_back(atoi(ptr));
			remaining_time.push_back(bt);

			count++;

			ptr = strtok(NULL," ");
		}

		cout<<"Testcase "<<t<<":"<<endl;

		cout<<endl<<"BURST TIMES:"<<endl;
		for(int i=0;i<count;i++) {
			cout<<"p"<<i<<"\t";
		}
		cout<<endl;
		for(int i=0;i<count;i++) {
			cout<<remaining_time[i]<<"\t";
		}
		cout<<endl<<endl;

		//Calling function to do desired scheduling
		SRTF(arrival_time,remaining_time,count);

		cout<<endl<<"---------------------------------"<<endl;

		//Clear all data before moving to next testcase
		arrival_time.clear();
		remaining_time.clear();
	}

	return 0;
}