#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
	int hello_test_fd = 0;
	char hello_read_buff[1024] = {0};

	if(argc < 2) {
		printf("Usage: %s <dev> [string]\n", argv[0]);
		return -1;
	}

	hello_test_fd = open(argv[1], O_RDWR);
	if (hello_test_fd < 0)
	{	
		printf("open fail\n");
		return -1;
	}

	if(3 == argc)
	{
		write(hello_test_fd, argv[2], strlen(argv[2]));
	}
	else if(2 == argc)
	{
		read(hello_test_fd, hello_read_buff, 100);
		hello_read_buff[100] = '\0';
		printf("%s\n", hello_read_buff);
	}

	close(hello_test_fd);
	
	return 0;
}

