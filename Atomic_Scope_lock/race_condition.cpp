#include <iostream>
#include <thread>
#include <Windows.h>
#include <mutex>
using namespace std;

//전역변수
//CRITICAL_SECTION CS;

mutex mtx;
long shared_memory = 0;
void inc()
{
	InterlockedIncrement(&shared_memory);
}
int main()
{
	//InitializeCriticalSection(&CS);

	auto count_func = []() {   
		for (int i = 0; i < 100000; ++i)
		{
		//	EnterCriticalSection(&CS);
			mtx.lock();
			shared_memory++;
			mtx.unlock();
		//	InterlockedIncrement(&shared_memory);
		//	LeaveCriticalSection(&CS);
		}
	};

	thread t1 = thread(count_func);
	thread t2 = thread(count_func);

	t1.join();
	t2.join();

	cout << shared_memory << endl;
	//DeleteCriticalSection(&CS);

	return 0;
}