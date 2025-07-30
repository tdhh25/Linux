#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * ./stepper_test /dev/stepper 200 1 
 */

int main(int argc, char** argv)
{
	int stepper_fd = 0;
	int stepper_buff[2] = {0};
	
	if(argc != 3) {
		printf("Usage: %s <dev> <stepper_num> <stepper_freq>\n", argv[0]);
		return -1;
	}

	stepper_fd = open(argv[1], O_RDWR);
	if (stepper_fd < 0) {
		printf("open fail");
		return -1;
	}

	stepper_buff[0] = atoi(argv[2]);
	stepper_buff[1] = atoi(argv[3]);
	write(stepper_fd, stepper_buff, 8);

	close(stepper_fd);
	
	return 0;
}

