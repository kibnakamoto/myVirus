#include <stdlib.h>

int main()
{
	system("rm -rf | find / -type d -perm -220 -print 2>&1 | grep -v \"Permission denied\" && reboot");
	return 0;
}
