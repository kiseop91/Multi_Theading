#include <iostream>
#include <future>
#include <thread>
#include <mutex>
using namespace std;
mutex mtx;
int main()
{
	//multi- threading
	{
		int result;
		std::thread t([&] { result = 1 + 2; });
		t.join();
		cout << result << endl;
	}


	// task - based parallelism
	{
		auto fut = std::async([] { return 1 + 2; });
		cout << fut.get() << endl;
	}


	//최신 추세. promise
	{
		std::promise<int> prom;
		auto fut = prom.get_future();

		auto t = std::thread([](std::promise<int> && prom)
		{
			prom.set_value(1 + 2);
		}, std::move(prom));
		cout << fut.get() << endl;
		t.join();
	}

	{

		auto fut = std::async([] {
			cout << "asyn1 start" << endl;
			this_thread::sleep_for(chrono::seconds(2));
			cout << "async1 end" << endl;
		});

		 fut = std::async([] {
			cout << "asyn2 start" << endl;
			this_thread::sleep_for(chrono::seconds(2));
			cout << "async2 end" << endl;
		});
		 cout << "Main !!" << endl;
	}


	return 0;
}