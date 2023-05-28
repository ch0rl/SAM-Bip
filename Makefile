OBJS = reciter.o sam.o render.o main.o processframes.o createtransitions.o
CC = gcc

# libsdl present
CFLAGS =  -Wall -O2 -DUSESDL `sdl-config --cflags`
LFLAGS = `sdl-config --libs`

build: $(OBJS)
	$(CC) -o sam-bip $(OBJS) $(LFLAGS)

%.o: src/%.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm *.o
