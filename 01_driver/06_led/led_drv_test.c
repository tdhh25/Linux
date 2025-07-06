#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * ./led_test 0 on/off
 * ./led_test 0
 */
int main(int argc, char** argv)
{
	int led_fd = 0;
	char led_buff[2] = {0};

	if(argc < 2)
	{
		printf("Usage: %s <index> [on/off]\n", argv[0]);
	}

	led_fd = open("/dev/led0", O_RDWR);
	if(led_fd < 0) {
		return -1;
	}

	led_buff[0] = atoi(argv[1]);
	if(2 == argc)
	{
		read(led_fd, led_buff, 2);
		if(0 == led_buff[1])
		{
			printf("led0 on\n");
		}
		else
		{
			printf("led0 off\n");
		}
	}
	else if(3 == argc)
	{
		if(0 == strcmp("on", argv[2]))
		{
			led_buff[1] = 0;
		}
		else
		{
			led_buff[1] = 1;
		}
		write(led_fd, led_buff, 2);
	}
	
	close(led_fd);
	
	return 0;
}

