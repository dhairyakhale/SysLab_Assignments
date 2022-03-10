#include <bits/stdc++.h>
using namespace std;

//For sorting in desc
bool comparator(char c1, char c2) {
	return c1>c2;
}

//Optimal Case
vector<int> optimal(vector<char> sequence, int s, int d, int t) {

	vector<int> optimal_allot(3,0);	//Returns number of rooms allotted for S,D,T respectively

	//Convert S->0, D->1, T->2 for easy sorting
	for(int i=0;i<sequence.size();i++) {
		if(sequence[i]=='S')
			sequence[i]=0;
		else if(sequence[i]=='D')
			sequence[i]=1;
		else if(sequence[i]=='T')
			sequence[i]=2;
	}

	sort(sequence.begin(),sequence.end(),comparator);

	//Goes through entire sequence vector
	for(int i=0;i<sequence.size();i++) {

		//T -> only 3 occupancy
		if(sequence[i]==2) {
			if(t>0) {
				t--;
				optimal_allot[2]++;
			}
			else
				continue;
		}

		//D -> double > triple
		else if(sequence[i]==1) {
			if(d>0) {
				d--;
				optimal_allot[1]++;
			}
			else if(t>0) {
				t--;
				optimal_allot[1]++;
			}
			else
				continue;
		}

		//S -> single > double > triple
		else if(sequence[i]==0) {
			
			if(s>0) {
				s--;
			}
			else if(d>0) {
				d--;
			}
			else if(t>0) {
				t--;
			}
			optimal_allot[0]++;
		}
	}
	return optimal_allot;
}

//Best Case
//Same as optimal, but without sorting sequence
vector<int> alok_alloc(vector<char> sequence, int s, int d, int t, vector<int> optimal_allot) {

	//[revenue, wrong allotment cost, wrong allotment count], returning this for all 3 managers.
	vector<int> rev_wrongallot_count(3,0);

	vector<int> alloted(3,0);

	for(int i=0;i<sequence.size();i++) {

		if(sequence[i]=='T') {
			if(t>0) {
				t--;
				rev_wrongallot_count[0] += 12500;
				alloted[2]++;
			}
			else
				continue;
		}

		else if(sequence[i]=='D') {
			if(d>0) {
				d--;
				rev_wrongallot_count[0] += 9000;
				alloted[1]++;
			}
			else if(t>0) {
				t--;
				rev_wrongallot_count[0] += 9000;
				alloted[1]++;
			}
			else
				continue;
		}

		else if(sequence[i]=='S') {
			
			if(s>0) {
				s--;
				rev_wrongallot_count[0] += 5000;
				alloted[0]++;
			}
			else if(d>0) {
				d--;
				rev_wrongallot_count[0] += 5000;
				alloted[0]++;
			}
			else if(t>0) {
				t--;
				rev_wrongallot_count[0] += 5000;
				alloted[0]++;
			}
		}
	}

	for(int i=0; i<3; i++){
		alloted[i] = optimal_allot[i]-alloted[i];	//Calculating missed rooms allotment for each type
		rev_wrongallot_count[2] += alloted[i];		//Summing it
	}

	rev_wrongallot_count[1] = alloted[0]*5000 + alloted[1]*9000 + alloted[2]*12500;	//Calculating total loss due to wrong allotment

	return rev_wrongallot_count;
}

//Worst Case
vector<int> raj_alloc(vector<char> sequence, int s, int d, int t, vector<int> optimal_allot) {

	vector<int> rev_wrongallot_count(3,0);

	vector<int> alloted(3,0);

	int rejectcount[3]={0};

	for(int i=0;i<sequence.size();i++) {

		//T -> Only 3 occupancy
		if(sequence[i]=='T') {
			if(t>0) {
				t--;
				rev_wrongallot_count[0] += 12500;
				alloted[2]++;
			}
			else
				continue;
		}

		//D -> 3 > 2
		else if(sequence[i]=='D') {

			if(t>0) {
				t--;
				rev_wrongallot_count[0] += 9000;
				alloted[1]++;
			}
			else if(d>0) {
				d--;
				rev_wrongallot_count[0] += 9000;
				alloted[1]++;
			}
			else
				continue;
		}

		//S -> 3 > 2 > 1
		else if(sequence[i]=='S') {
			
			if(t>0) {
				t--;
				rev_wrongallot_count[0] += 5000;
				alloted[0]++;
			}
			else if(d>0) {
				d--;
				rev_wrongallot_count[0] += 5000;
				alloted[0]++;
			}
			else if(s>0) {
				s--;
				rev_wrongallot_count[0] += 5000;
				alloted[0]++;
			}
		}
	}

	for(int i=0; i<3; i++){
		alloted[i] = optimal_allot[i]-alloted[i];
		rev_wrongallot_count[2] += alloted[i];
	}

	rev_wrongallot_count[1] = alloted[0]*5000 + alloted[1]*9000 + alloted[2]*12500;

	return rev_wrongallot_count;
}

//First Case
vector<int> aman_alloc(vector<char> sequence, int s, int d, int t, vector<int> optimal_allot) {

	vector<int> rev_wrongallot_count(3,0);

	vector<int> alloted(3,0);

	for(int i=0;i<sequence.size();i++) {

		//T -> only 3 occupancy
		if(sequence[i]=='T') {
			if(t>0) {
				t--;
				rev_wrongallot_count[0] += 12500;
				alloted[2]++;
			}
			else
				continue;
		}

		//D -> 3 > 2
		else if(sequence[i]=='D') {

			if(t>0) {
				t--;
				rev_wrongallot_count[0] += 9000;
				alloted[1]++;
			}
			else if(d>0) {
				d--;
				rev_wrongallot_count[0] += 9000;
				alloted[1]++;
			}
			else
				continue;
		}

		//S -> 3 > 1 > 2 (in the order of the location of rooms)
		else if(sequence[i]=='S') {
			
			if(t>0) {
				t--;
				rev_wrongallot_count[0] += 5000;
				alloted[0]++;
			}
			else if(s>0) {
				s--;
				rev_wrongallot_count[0] += 5000;
				alloted[0]++;
			}
			else if(d>0) {
				d--;
				rev_wrongallot_count[0] += 5000;
				alloted[0]++;
			}
		}
	}

	for(int i=0; i<3; i++){
		alloted[i] = optimal_allot[i]-alloted[i];
		rev_wrongallot_count[2] += alloted[i];
	}

	rev_wrongallot_count[1] = alloted[0]*5000 + alloted[1]*9000 + alloted[2]*12500;

	return rev_wrongallot_count;
}

int main()
{
	ifstream myfile("input.txt");
	ofstream ofile("output.txt");

	string line;
	getline(myfile,line);

	int s,d,t; //single,double,triple occupancy

	//Reads single, double, triple occupancy room counts from file line 1
	stringstream ss(line);
	ss>>s>>d>>t;

	getline(myfile,line);
	ss.clear();
	ss.str(line);

	//Reads next line, equals number of queries in next line
	int len;
	ss>>len;

	getline(myfile,line);
	ss.clear();
	ss.str(line);

	std::vector<char> sequence;
	char x;

	//Loop and add all queries to sequence vector
	for(int i=0;i<len;i++) {
		
		ss>>x;
		sequence.push_back(x);
	}

	//Make array for count in optimal case
	//Make arrays of all vectors of each manager and pass optimal
	vector<int> optimal_allot = optimal(sequence,s,d,t);
	vector<int> aman = aman_alloc(sequence,s,d,t,optimal_allot);
	vector<int> raj = raj_alloc(sequence,s,d,t,optimal_allot);
	vector<int> alok = alok_alloc(sequence,s,d,t,optimal_allot);
	

	//Print best manager
	if(aman[0]>raj[0]) {
		if(aman[0]>alok[0])
			ofile<<"Aman is the best manager";
		else if (aman[0]<alok[0])
			ofile<<"Alok is the best manager";
		else
			ofile<<"Both Aman and Alok are best managers";
	}
	else if(aman[0]<raj[0]){
		if(raj[0]>alok[0])
			ofile<<"Raj is the best manager";
		else if(raj[0]<alok[0])
			ofile<<"Alok is the best manager";
		else
			ofile<<"Both Raj and Alok are best managers";
	}
	else {
		if(raj[0]>alok[0])
			ofile<<"Both Raj and Aman are best managers";
		else if(raj[0]<alok[0])
			ofile<<"Alok is the best manager";
		else
			ofile<<"All of Aman, Raj and Alok are best managers";
	}
	ofile<<"\n";

	//Print stats of aman
	ofile<<"Aman: ";
	for(int i=0;i<3;i++)
		ofile<<aman[i]<<'\t';
	ofile<<'\n';

	//Print stats of raj
	ofile<<"Raj:  ";
	for(int i=0;i<3;i++)
		ofile<<raj[i]<<'\t';
	ofile<<'\n';

	//Print stats of alok
	ofile<<"Alok: ";
	for(int i=0;i<3;i++)
		ofile<<alok[i]<<'\t';
	ofile<<'\n';
	
	ofile.close();

	return 0;
}