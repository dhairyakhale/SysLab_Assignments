#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <chrono>

std::mutex read, write, order, print;
std::condition_variable cv;
std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
int number_of_friends_reading = 0;

void write_to_card(int c){


        //TODO: Reader-Writer logic

        std::unique_lock<std::mutex> ul(order);
        cv.wait(ul, [c]{return pq.top() == c;});
        
        write.lock();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Friend " << c << " is writing\n";
        write.unlock();

        pq.pop();
        cv.notify_all();
}

void read_from_card(int c){
        //TODO: Reader-Writer logic
        std::unique_lock<std::mutex> ul(order);
        cv.wait(ul, [c]{return pq.top() == c;});

        read.lock();
        number_of_friends_reading ++;
        if(number_of_friends_reading == 1)
                write.lock();
        read.unlock();

        pq.pop();
        cv.notify_all();
        
        //perform read
        print.lock();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Friend " << c << " is reading\n";
        print.unlock();

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
                coupon[i] = rand() % ((999 - 100) + 1) + 100;
                pq.push(coupon[i]);
        }
        
        std::vector<bool> random(n);
        for(int i=0; i<n; ++i){
                random[i] = rand() % 2;
                // random[i] = 0;
                // if(!random[i]) pq.push(coupon[i]); //pushing the write operations in priority queue so as to maintain order
        }

        for(int i=0; i<n; ++i){
                threads[i] = random[i] ? std::thread(read_from_card, coupon[i]) : std::thread(write_to_card, coupon[i]);
        }
        
        for(auto& th : threads)
                th.join();
        
        return 0;
}