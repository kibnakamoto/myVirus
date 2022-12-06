#include <array>
#include <cstdint>
#include <thread>
#include <vector>
#include <fstream>
#include <iostream>

// hogs all the memory, including virtual ram
void decl()
{
	while (true) std::array<uint64_t,2> *test = new std::array<uint64_t, 2>[3000];
}

// hogs all the cpu's
void decl_fixed(size_t thr_count)
{
	std::string f_line;
	uint64_t size=5; // KB
    std::ifstream file("/proc/meminfo");
   	while (file >> f_line) {
   		if(f_line == "MemTotal:") {
   			if(file >> size) break;
   		}
   		file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
   	}
   	file.close();
	size = (__uint128_t)size;
	uint32_t loop_count = 4000000;
	size *= 1000; // convert _size to bytes
	size /= 8*thr_count*loop_count; // every test element is 8 bytes

	// cause memory leakage
	for(uint32_t i=0;i<loop_count;i++)
		std::array<uint64_t,2> *test = new std::array<uint64_t,2>[size];
	
	while (1) {}
}

int main()
{
    const size_t thr_count = std::thread::hardware_concurrency();
	std::vector<std::thread> threads(thr_count);

    // iterate through all threads, will work even if the amount of threads is larger than the amount
    // of threads
    for(uint32_t i=0;i<thr_count;i++) threads[i] = std::thread(decl);
    for(uint32_t i=0;i<thr_count;i++) threads[i].join();
	return 0;
}

