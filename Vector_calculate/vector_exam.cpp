#include <chrono>
#include <iostream>
#include <mutex>
#include <random>
#include <thread>
#include <utility>
#include <vector>
#include <atomic>
#include <future>
#include <numeric>
#include <execution>

using namespace std;

mutex mtx;

void dotProductnaive(const vector<int>& v0, const vector<int>& v1,
	const unsigned i_start, const unsigned i_end, unsigned long long & sum)
{
	for (unsigned i = i_start; i < i_end; ++i)
	{

	}
}