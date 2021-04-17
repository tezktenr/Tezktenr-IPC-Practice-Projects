CFLAGS=-std=c99 -pedantic -Wall -Wextra -Werror -Wwrite-strings -Wno-unused-variable

OPTION=-lrt -pthread -D_POSIX_C_SOURCE=200112L

all: app

app: $(SOURCES)
	@echo ------------------ compiling all source files to executable -------------------
	gcc $(CFLAGS) producer.c ipc.c buf_util.c -o Producer $(OPTION)
	gcc $(CFLAGS) consumer.c ipc.c buf_util.c -o Consumer $(OPTION)

clean:
	@echo ------------------ removing object files and executable -------------------
	/bin/rm -f app *.o
	/bin/rm -f Producer Consumer

