#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <chrono>

using namespace std;

mutex mtx; // ( 방법2 ) 뮤텍스락

int main()
{
	//atomic<int> shared_memory(0);  // (방법 1) 아토믹쓰기
	int shared_memory(0);
	
	auto count_func = [&]() {
		for (int i = 0; i < 1000; ++i)
		{
			
			this_thread::sleep_for(chrono::milliseconds(1));
		//	mtx.lock();
			std::lock_guard<mutex> lock(mtx);// (방법3 락가드)
			
			shared_memory++;

		//	mtx.unlock();
		}
	};


	thread t1 = thread(count_func);
	thread t2 = thread(count_func);

	t1.join();
	t2.join();

	cout << "After" << endl;
	cout << shared_memory << endl;

	return 0;
}