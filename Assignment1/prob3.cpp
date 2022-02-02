#include <bits/stdc++.h>
using namespace std;

bool safeSeq(int n, int m, int *qty, int **alloc, int **req, int **sequence)
{
	free(*sequence);

    *sequence = (int*)malloc(n * sizeof(int));

    for(int i=0;i<n;i++)
    	(*sequence)[i] = -1;

	//Calculating need matrix
	int need[n][m];
	for(int i=0;i<n;i++) {
		for(int j=0;j<m;j++) {
			need[i][j] = req[i][j]-alloc[i][j];
			cout<<need[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<"----------------"<<endl;

	bool finish[n] = {false};
	int finish_count=0;

	while(finish_count<n) {
		bool safe = false;

		for(int i=0;i<n;i++) {
			if(!finish[i]) {
				bool flag = true;

				for(int j=0;j<m;j++) {
					if(need[i][j] > qty[j]) {
						flag=false;
						break;
					}
				}
				if(flag) {
					for(int j=0; j<m; j++)
                        qty[j] += alloc[i][j];

                    (*sequence)[finish_count] = i;
                    cout<<finish_count<<endl;
                    finish[i] = true;
                    ++finish_count;
                    safe = true;
				}
			}
		}
		if(!safe) {
			for(int j=0;j<n;j++)
				(*sequence)[j] = -1;
			return false;
		}
	}
	return true;
}

int main()
{
	ifstream myFile("input.txt");

	string line;
	getline(myFile,line);	//Reading line 1

	stringstream ss(line);

	int n,m;	//n=process count, m=resource count
	ss>>n>>m;

	cout<<n<<" "<<m<<endl;

	int qty[m];		//Quantity available
	int **alloc;	//Current allocation matrix
	alloc = new int *[n];

	int **req;	//Maximum requirement matrix
	req = new int *[n];

	int i=0,j=0;	//Iterators

	getline(myFile,line);
	ss.clear();
	ss.str(line);

	//Reading array for quantity of each item
	for(i=0;i<m;i++) {
		ss>>qty[i];
	}

	//Reading array for each item currently in use
	for(i=0;i<n;i++) {
		alloc[i] = new int[m];
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
		req[i] = new int[m];
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

	int *sequence;
	sequence = new int[n];
	
	bool out = safeSeq(n,m,qty,alloc,req,&sequence);

	if(out){
		for(int i=0;i<n;i++)
			cout<<sequence[i]<<" ";
	}
	return 0;
}