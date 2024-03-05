#include <sys/errno.h>
#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	write(2,"a",1);
	if (chdir("fkjfd") != 0)
		perror(NULL);
	return (0);
}