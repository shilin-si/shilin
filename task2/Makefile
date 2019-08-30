CC=gcc

LDFLAG=-o

CFLAG=-lrt

all:
	$(CC) $(LDFLAG) server msg_server.c $(CFLAG)
	$(CC) $(LDFLAG) client msg_client.c $(CFLAG)

clean:
	rm client server
