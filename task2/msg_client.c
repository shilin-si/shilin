#include "header.h"

int main()
{
	mqd_t mqdes;
	ssize_t writebuf;
	char buf[100];

	printf("Enter the message to server: ");
	fgets(buf,30,stdin);

	mqdes = mq_open("que1", O_RDWR);
	if (mqdes == (mqd_t) -1)
		perror("mq_open");

	if((writebuf = mq_send (mqdes, buf, 30, 0)) < 1) {
	
		perror("mq_receive");
	}
}
