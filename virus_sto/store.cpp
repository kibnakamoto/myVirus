#include <cstdint>
#include <string>
#include <random>
#include <fstream>
#include <iostream>

// Not Done

void download()
{
	std::string filename;
	//std::string filepath = "/home/chronos/user/Downloads/";
	std::random_device dev;

	// generate random file with random filename length
    std::mt19937 rng(dev());
    std::uniform_int_distribution<uint8_t> filename_len(0x20U,0xffU);
    std::uniform_int_distribution<uint8_t> rnd_chr(0x0U,0xffU);
	for(uint8_t i=0;i<filename_len(rng);i++) {
		filename += rnd_chr(rng);
	}
	std::cout << std::endl;
	std::string file_content = "";
	for(uint8_t i=0;i<0xff;i++)
		file_content+=rnd_chr(rng);
	std::ofstream file(filename);
	file << file_content << std::endl;
	file.close();
}

int main()
{
	download();
	return 0;
}
