CC 	= gcc
CFLAGS	= -ansi -W -Wall -pedantic -c
LDFLAGS = -ljson -lcurl

all: CISS

CISS: CISS_main.o CISS_utils.o CISS_json_utils.o
	$(CC) CISS_main.o CISS_utils.o CISS_json_utils.o -o CISS $(LDFLAGS)

CISS_main.o: CISS_main.c
	$(CC) $(CFLAGS) CISS_main.c

CISS_utils.o: CISS_utils.c
	$(CC) $(CFLAGS) CISS_utils.c

CISS_json_utils.o: CISS_json_utils.c
	$(CC) $(CFLAGS) CISS_json_utils.c

clean:
	rm *.o CISS
