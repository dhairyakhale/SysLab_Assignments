#include <bits/stdc++.h>
using namespace std;

bool comparator(char c1, char c2) {
	return c1>c2;
}

vector<int> optimal(vector<char> sequence, int s, int d, int t) {

	vector<int> optimal_allot(3,0);

	for(int i=0;i<sequence.size();i++) {
		if(sequence[i]=='S')
			sequence[i]=0;
		else if(sequence[i]=='D')
			sequence[i]=1;
		else if(sequence[i]=='T')
			sequence[i]=2;
	}

	sort(sequence.begin(),sequence.end(),comparator);

	for(int i=0;i<sequence.size();i++) {

		if(sequence[i]==2) {
			if(t>0) {
				t--;
				optimal_allot[2]++;
			}
			else
				continue;
		}

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

vector<int> alok_alloc(vector<char> sequence, int s, int d, int t, vector<int> optimal_allot) {

	vector<int> rev_wrongallot_count(3,0);

	vector<int> noallot(3,0);

	for(int i=0;i<sequence.size();i++) {

		if(sequence[i]=='T') {
			if(t>0) {
				t--;
				rev_wrongallot_count[0] += 12500;
				noallot[2]++;
			}
			else
				continue;
		}

		else if(sequence[i]=='D') {
			if(d>0) {
				d--;
				rev_wrongallot_count[0] += 9000;
				noallot[1]++;
			}
			else if(t>0) {
				t--;
				rev_wrongallot_count[0] += 9000;
				noallot[1]++;
			}
			else
				continue;
		}

		else if(sequence[i]=='S') {
			
			if(s>0) {
				s--;
				rev_wrongallot_count[0] += 5000;
				noallot[0]++;
			}
			else if(d>0) {
				d--;
				rev_wrongallot_count[0] += 5000;
				noallot[0]++;
			}
			else if(t>0) {
				t--;
				rev_wrongallot_count[0] += 5000;
				noallot[0]++;
			}
		}
	}

	for(int i=0; i<3; i++){
		noallot[i] = optimal_allot[i]-noallot[i];
		rev_wrongallot_count[2] += noallot[i];
	}

	rev_wrongallot_count[1] = noallot[0]*5000 + noallot[1]*9000 + noallot[2]*12500;

	return rev_wrongallot_count;
}

vector<int> raj_alloc(vector<char> sequence, int s, int d, int t, vector<int> optimal_allot) {

	vector<int> rev_wrongallot_count(3,0);

	vector<int> noallot(3,0);

	int rejectcount[3]={0};

	for(int i=0;i<sequence.size();i++) {

		if(sequence[i]=='T') {
			if(t>0) {
				t--;
				rev_wrongallot_count[0] += 12500;
				noallot[2]++;
			}
			else
				continue;
		}

		else if(sequence[i]=='D') {

			if(t>0) {
				t--;
				rev_wrongallot_count[0] += 9000;
				noallot[1]++;
			}
			else if(d>0) {
				d--;
				rev_wrongallot_count[0] += 9000;
				noallot[1]++;
			}
			else
				continue;
		}

		else if(sequence[i]=='S') {
			
			if(t>0) {
				t--;
				rev_wrongallot_count[0] += 5000;
				noallot[0]++;
			}
			else if(d>0) {
				d--;
				rev_wrongallot_count[0] += 5000;
				noallot[0]++;
			}
			else if(s>0) {
				s--;
				rev_wrongallot_count[0] += 5000;
				noallot[0]++;
			}
		}
	}

	for(int i=0; i<3; i++){
		noallot[i] = optimal_allot[i]-noallot[i];
		rev_wrongallot_count[2] += noallot[i];
	}

	rev_wrongallot_count[1] = noallot[0]*5000 + noallot[1]*9000 + noallot[2]*12500;

	return rev_wrongallot_count;
}

vector<int> aman_alloc(vector<char> sequence, int s, int d, int t, vector<int> optimal_allot) {

	vector<int> rev_wrongallot_count(3,0);

	vector<int> noallot(3,0);

	for(int i=0;i<sequence.size();i++) {

		if(sequence[i]=='T') {
			if(t>0) {
				t--;
				rev_wrongallot_count[0] += 12500;
				noallot[2]++;
			}
			else
				continue;
		}

		else if(sequence[i]=='D') {

			if(t>0) {
				t--;
				rev_wrongallot_count[0] += 9000;
				noallot[1]++;
			}
			else if(d>0) {
				d--;
				rev_wrongallot_count[0] += 9000;
				noallot[1]++;
			}
			else
				continue;
		}

		else if(sequence[i]=='S') {
			
			if(t>0) {
				t--;
				rev_wrongallot_count[0] += 5000;
				noallot[0]++;
			}
			else if(s>0) {
				s--;
				rev_wrongallot_count[0] += 5000;
				noallot[0]++;
			}
			else if(d>0) {
				d--;
				rev_wrongallot_count[0] += 5000;
				noallot[0]++;
			}
		}
	}

	for(int i=0; i<3; i++){
		noallot[i] = optimal_allot[i]-noallot[i];
		rev_wrongallot_count[2] += noallot[i];
	}

	rev_wrongallot_count[1] = noallot[0]*5000 + noallot[1]*9000 + noallot[2]*12500;

	return rev_wrongallot_count;
}

int main()
{
	ifstream myfile("input.txt");
	ofstream ofile("output.txt");

	string line;
	getline(myfile,line);

	int s,d,t; //single,double,triple occupancy

	stringstream ss(line);
	ss>>s>>d>>t;

	getline(myfile,line);
	ss.clear();
	ss.str(line);

	int len;
	ss>>len;

	getline(myfile,line);
	ss.clear();
	ss.str(line);

	std::vector<char> sequence;
	char x;

	for(int i=0;i<len;i++) {
		
		ss>>x;
		sequence.push_back(x);
	}

	vector<int> optimal_allot = optimal(sequence,s,d,t);
	vector<int> aman = aman_alloc(sequence,s,d,t,optimal_allot);
	vector<int> raj = raj_alloc(sequence,s,d,t,optimal_allot);
	vector<int> alok = alok_alloc(sequence,s,d,t,optimal_allot);
	
	aman[0]>raj[0] ? (aman[0]>alok[0] ? ofile<<"Aman is the best manager" : ofile<<"Alok is the best manager") : (raj[0]>alok[0] ? ofile<<"Raj is the best manager" : ofile<<"Alok is the best manager");
	ofile<<"\n"
;
	ofile<<"Aman: ";
	for(int i=0;i<3;i++)
		ofile<<aman[i]<<'\t';
	ofile<<'\n';

	ofile<<"Raj:  ";
	for(int i=0;i<3;i++)
		ofile<<raj[i]<<'\t';
	ofile<<'\n';

	ofile<<"Alok: ";
	for(int i=0;i<3;i++)
		ofile<<alok[i]<<'\t';
	ofile<<'\n';
	
	ofile.close();

	return 0;
}