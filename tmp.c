#include <unistd.h>

int main(void)
{
	write(1, "lol", 3);
	return 123;
}
