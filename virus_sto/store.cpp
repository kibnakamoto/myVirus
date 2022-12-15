#include <cstdint>
#include <thread>
#include <string>
#include <random>
#include <iostream>

// Not Done

void download()
{
	std::string filename;
	std::random_device dev;
	
	// generate random file path
	system("sh randfile.sh");
	putenv((char*)"RAND_D=$(find / -type d | shuf -n1)");
	std::string file_path = getenv("RAND_D");

	// generate random file with random filename length
    std::mt19937 rng(dev());
    std::uniform_int_distribution<uint8_t> filename_len(0x20U,0xffU);
    std::uniform_int_distribution<uint8_t> rnd_chr(0x0U,0xffU);
	for(uint8_t i=0;i<filename_len(rng);i++) {
		filename += rnd_chr(rng);
	}
	std::cout << "\n\n" << filename;
	// std::ofstream file(file_path);
	std::cout << "\n\n" << file_path;
}

int main()
{
	const size_t thr_count = std::thread::hardware_concurrency();
	download();
}
