CC 	= gcc
CFLAGS	= -ansi -W -c
LDFLAGS = -ljson -lcurl -lpython2.7

all: CISS

CISS: CISS_send_proc.o CISS_utils.o CISS_json_utils.o CISS_sensor_proc.py
	$(CC) CISS_send_proc.o CISS_utils.o CISS_json_utils.o -o CISS $(LDFLAGS)

CISS_send_proc.o: CISS_send_proc.c
	$(CC) $(CFLAGS) CISS_send_proc.c

CISS_utils.o: CISS_utils.c
	$(CC) $(CFLAGS) CISS_utils.c

CISS_json_utils.o: CISS_json_utils.c
	$(CC) $(CFLAGS) CISS_json_utils.c

clean:
	rm *.o CISS
