#include <bits/stdc++.h>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std;

#define MAX 1000

int a[MAX], top = -1;
mutex s;

void push(int x)
{
    s.lock();
	if (top >= (MAX - 1)) {
		cout << "Stack Overflow\n";
	}
	else {

		a[++top] = x;
		cout << x << " pushed into stack\n";
	}
    s.unlock();
}

void pop()
{
    s.lock();
	if (top < 0) {
		cout << "Stack Underflow\n";
	}
	else {
		int x = a[top--];
		cout << x << " popped from stack\n";
	}
    s.unlock();
}

int main()
{

    while(true){
        thread t1, t2;
        int r = rand() % 2;

        t1 = r ? thread(push, rand() % (int)1e6) :  thread(pop);

        this_thread::sleep_for(chrono::seconds(5));

        t2 = !r ? thread(push, rand() % (int)1e6) : thread(pop);

        this_thread::sleep_for(chrono::seconds(5));

        t1.join(); t2.join();
    }

	return 0;
}
