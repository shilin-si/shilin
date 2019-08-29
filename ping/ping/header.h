#include <fcntl.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <stdlib.h>
#include <stdio.h>
#include<stdio.h> 
#include<sys/types.h> 
#include<sys/socket.h> 
#include<netinet/in.h> 
#include<arpa/inet.h> 
#include<netdb.h> 
#include<unistd.h> 
#include<string.h> 
#include<stdlib.h> 
#include<netinet/ip_icmp.h> 
#include<time.h> 
#include<fcntl.h> 
#include<signal.h> 
#include<time.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PACKETSIZE	64

struct packet
{
	struct icmphdr hdr;
	char msg[PACKETSIZE-sizeof(struct icmphdr)];
};

char dstadr[40];
int pid=-1;

unsigned short checksum(void *b, int len)
{
	unsigned short *buf = b;
	unsigned int sum=0;
	unsigned short result;

	for ( sum = 0; len > 1; len -= 2 )
		sum += *buf++;
	if ( len == 1 )
		sum += *(unsigned char*)buf;
	sum = (sum >> 16) + (sum & 0xFFFF);
	sum += (sum >> 16);
	result = ~sum;

	return result;
}

