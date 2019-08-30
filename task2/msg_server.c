#include "header.h"           

static void sigNotifier(union sigval sv)
{
	struct mq_attr attrib;
	ssize_t readbuf;
	char *buf;
	mqd_t mqdes = *((mqd_t *) sv.sival_ptr);
	
	printf ("There is a messgae from client\n");
	
	

	if (mq_getattr(mqdes, &attrib) == -1) {  				 // get message queue attributes 
		perror("mq_getattr error");
	}
	
	if((buf = malloc(attrib.mq_msgsize)) == NULL) {

		perror("malloc");
		exit(-1);
	}

	if ((readbuf = mq_receive(mqdes, buf, attrib.mq_msgsize, NULL)) < 0 ) {
	
		perror("mq_receive error");
		exit(-1);
	}

	printf("Message from client : %s \n", buf);
	free(buf);
	exit(0);      
} 

int main()
{
	mqd_t mqdes;
	struct sigevent sev;

	printf("Waiting for message from client\n");
	mqdes = mq_open("que1",O_RDWR | O_CREAT, 0666, NULL);
	if (mqdes == (mqd_t) -1)
		perror("mq_open");

	/* sev is to define values for sigevent, structure for notification */
 
	sev.sigev_notify = SIGEV_THREAD;
	sev.sigev_notify_function = sigNotifier; 	/* Data passed with notification */

	sev.sigev_notify_attributes = NULL;
	sev.sigev_value.sival_ptr = &mqdes;

	if (mq_notify(mqdes, &sev) == -1)
		perror("mq_notify");

	pause();					/* wait for signal */

	mq_close(mqdes);
	mq_unlink("que1");
}
