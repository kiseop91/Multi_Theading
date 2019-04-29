/*
bounded buffer problem example
2019-04-29 kiseop
*/
#include <iostream>      
#include <thread>        
#include <mutex>         
#include <condition_variable>

std::mutex mtx;   // mutex for critical section
std::condition_variable empty;
std::condition_variable full;

int buffer[10];
int buffer_count; // limit 10
void produce(int x)
{
	std::unique_lock<std::mutex> lck(mtx);
	if (buffer_count == 10)
	{
		empty.wait(lck);
	}
	buffer_count++;
	buffer[x] = 1;
	std::cout << x << "th tread (produce) : " << buffer[x] << std::endl;
	full.notify_all();
}

void consume(int x)
{
	std::unique_lock<std::mutex> lck(mtx);
	if (buffer_count == 0)
	{
		std::cout << "Thread Number : " << x << " : ";
		std::cout << " [ wait until produce buffer..]\n";
		full.wait(lck);
	}
	buffer[x] = 0;
	std::cout << x << "th tread (consume): " << buffer[x] << "\n";
	empty.notify_all();
}

int main() {

	int threadnum = 10;
	std::thread threads[10];

	/* spawn threadnum threads */
	for (int id = 0; id < 5; id++)
		threads[id] = std::thread(consume, id);

	for (int id = 5; id < 10; id++)
		threads[id] = std::thread(produce, id);

	/* Merge all threads to the main thread */
	for (int id = 0; id < threadnum; id++)
		threads[id].join();

	std::cout << "\nCompleted semaphore example!\n";
	std::cout << std::endl;

	return 0;
}
