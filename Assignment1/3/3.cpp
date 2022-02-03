#include <bits/stdc++.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

using namespace std;

int n; 
int m;
int count_processes_executed = 0;
vector<int> qty; // quantity available
vector<vector<int>> alloc; //current allocation matrix
vector<vector<int>> req; //
vector<int> sequence; //final safe sequence
vector<vector<int>> need;

mutex lock_resources, check;
condition_variable cv;

void execute(int id){

	// condition check
	unique_lock<mutex> ul(lock_resources);
	cv.wait(ul, [id]{return id == sequence[count_processes_executed];});

	ofstream out("output.txt", ios_base::app);    

	cout << "\n--> Process " << id;
	out << "Process: " << id << "\n";
	// printf("\n\tAllocated : ");
	cout << "\n\tAllocated: ";
	out << "Allocated: ";
	for(int i=0; i<m; i++){
		printf("%3d", alloc[id][i]);
		out << alloc[id][i] << " ";
	}
	out << "\n";

	cout << "\n\tNeeded    : ";
	out << "Needed: ";
	
	for(int i=0; i<m; i++){
		printf("%3d", need[id][i]);
		out << need[id][i] << " ";
	}
	out << "\n";

	cout << "\n\tAvailable : ";
	out << "Available: ";
	for(int i=0; i<m; i++){
		printf("%3d", qty[i]);
		out << qty[i] << " ";
	}
	out << "\n";

	printf("\n"); this_thread::sleep_for(chrono::seconds(1));

	printf("\tResource Allocated!");
	printf("\n"); this_thread::sleep_for(chrono::seconds(1));
	printf("\tProcess Code Running...");
	printf("\n"); this_thread::sleep_for(chrono::seconds(rand()%3 + 2)); // process code
	printf("\tProcess Code Completed...");
	printf("\n"); this_thread::sleep_for(chrono::seconds(1));
	printf("\tProcess Releasing Resource...");
	printf("\n"); this_thread::sleep_for(chrono::seconds(1));
	printf("\tResource Released!");

	for(int i=0; i<m; i++)
		qty[i] += alloc[id][i];

	cout << "\n\tNow Available : ";
	out << "Now available: ";
	for(int i=0; i<m; i++){
		printf("%3d", qty[i]);
		out << qty[i] << " ";
	}
	out << "\n";
	printf("\n\n");

	this_thread::sleep_for(chrono::seconds(1));

	// condition broadcast
    count_processes_executed++;

	out << "-------------------------------\n";
	out.close();
	cv.notify_all();
}

bool safeSeq()
{
	fill(sequence.begin(), sequence.end(), -1);
	vector<int> temp(qty);

	//Calculating need matrix
	need.resize(n);
	for(int i=0; i<n; ++i) need[i].resize(m);
	
	for(int i=0;i<n;i++) {
		for(int j=0;j<m;j++) {
			need[i][j] = req[i][j] - alloc[i][j];
			cout<<need[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<"----------------"<<endl;

	vector<bool> finish(n, false);
	int finish_count=0;

	while(finish_count<n) {
		bool safe = false;

		for(int i=0;i<n;i++) {
			if(!finish[i]) {
				bool flag = true;

				for(int j=0;j<m;j++) {
					if(need[i][j] > temp[j]) {
						flag=false;
						break;
					}
				}
				if(flag) {
					for(int j=0; j<m; j++)
                        temp[j] += alloc[i][j];

                    sequence[finish_count] = i;
                    cout<<finish_count<<endl;
                    finish[i] = true;
                    ++finish_count;
                    safe = true;
				}
			}
		}
		if(!safe) {
			for(int j=0;j<n;j++)
				sequence[j] = -1;
			return false;
		}
	}
	return true;
}

int main()
{
	ifstream myFile("input.txt");
	ofstream out("output.txt");

	string line;
	getline(myFile,line);	//Reading line 1

	stringstream ss(line);
	
	//n=process count, m=resource count
	ss>>n>>m;

	qty.resize(m);		//Quantity available
	alloc.resize(n);	//Current allocation matrix
	req.resize(n);
	sequence.resize(n);

	for(int i=0; i<n; ++i){
		alloc[i].resize(m);
		req[i].resize(m);
	}
	

	int i=0, j=0;	//Iterators

	getline(myFile,line);
	ss.clear();
	ss.str(line);

	//Reading array for quantity of each item
	for(i=0;i<m;i++) {
		ss>>qty[i];
	}

	//Reading array for each item currently in use
	for(i=0;i<n;i++) {
		getline(myFile,line);
		ss.clear();
		ss.str(line);
		for(j=0;j<m;j++) {
			ss>>alloc[i][j];
			cout<<alloc[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<"----------------"<<endl;

	//Reading array for maximum item requirement
	for(i=0;i<n;i++) {
		getline(myFile,line);
		ss.clear();
		ss.str(line);
		for(j=0;j<m;j++) {
			ss>>req[i][j];
			cout<<req[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<"----------------"<<endl;
	
	bool check = safeSeq();
	
	if(check){
		out << "Safe Sequence: ";
		for(int i=0;i<n;i++){
			cout<<sequence[i]<<" ";
			out << sequence[i] << " ";
		}
	}

	out << "\n-------------------------------\n";
	out.close();
	vector<thread> threads(n);
	for(int i=0; i<n; ++i)
		threads[i] = thread(execute, i);

	for(auto &th : threads)
		th.join();
	return 0;
}