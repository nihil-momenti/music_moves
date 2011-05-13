CC = g++
CPP = g++
CFLAGS = `pkg-config opencv --cflags`
CPPFLAGS = `pkg-config opencv --cflags`
LFLAGS = `pkg-config opencv --libs`

OBJS = music_moves.o

all: music_moves

main.o:

music_moves: ${OBJS}
	${CC} -o music_moves ${LFLAGS} ${OBJS}
