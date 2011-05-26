CC = g++
CPP = g++

CFLAGS += -I/usr/local/include -I/usr/include
CFLAGS += -g -Wall

CPPFLAGS += -I/usr/local/include -I/usr/include
CPPFLAGS += -g -Wall

LDFLAGS += -L/usr/local/lib -L/usr/lib
LDFLAGS += -lportmidi
LDFLAGS += `pkg-config --libs-only-l opencv`

OBJS = $(addsuffix .o, $(basename $(wildcard *.cpp)))

all: music_moves

main.o:

music_moves: ${OBJS}
	${CC} -o music_moves ${LDFLAGS} ${OBJS}

clean:
	-rm -f $(OBJS)
