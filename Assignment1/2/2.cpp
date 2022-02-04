#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <chrono>

std::mutex read, write, order;
std::condition_variable cv;
std::priority_queue<int, std::vector<int>, std::greater<int>> pq; //maintaing a priority queue to allow ordered access
int number_of_friends_reading = 0;

void write_to_card(int c){
        //we are locking for the order
        std::unique_lock<std::mutex> ul(order);
        cv.wait(ul, [c]{return pq.top() == c;});
        
        //locking for write
        write.lock();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Friend " << c << " is writing\n";
        write.unlock();

        pq.pop();
        cv.notify_all(); //notifying all the threads to check the condition variable
}

void read_from_card(int c){
        //locking to maintain order access
        std::unique_lock<std::mutex> ul(order);
        cv.wait(ul, [c]{return pq.top() == c;});

        read.lock();
        number_of_friends_reading ++;
        if(number_of_friends_reading == 1)
                write.lock();
        read.unlock();

        pq.pop();
        cv.notify_all(); //notifying the threads to check the condition variable
        
        //performing read
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Friend " << c << " is reading\n";

        read.lock();
        number_of_friends_reading --;
        if(number_of_friends_reading == 0)
                write.unlock();
        read.unlock();
}

int main(){
        srand((unsigned)time(0));
        int n;
        std::cout << "Enter number of friends:";
        std::cin >> n;

        std::vector<std::thread> threads(n);
        std::vector<int> coupon(n);
        

        for(int i=0; i<n; ++i){
                coupon[i] = rand() % ((999 - 100) + 1) + 100; //giving random 3 digit as coupon id
                pq.push(coupon[i]);
        }
        
        std::vector<bool> random(n);
        for(int i=0; i<n; ++i){
                random[i] = rand() % 2; //randomly making the friends read or write
        }

        for(int i=0; i<n; ++i){
                threads[i] = random[i] ? std::thread(read_from_card, coupon[i]) : std::thread(write_to_card, coupon[i]);
        }
        
        for(auto& th : threads)
                th.join();
        
        return 0;
}