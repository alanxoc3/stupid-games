# A pretty make file for a pretty game.

FLAGS=-lallegro -lallegro_main -lallegro_color -lallegro_primitives\
-lallegro_font -lallegro_ttf -lallegro_acodec -lallegro_audio -lm

pong: main.c drawing.o music.o game_logic.o
	cd argparse; make
	$(CC) -Wall -pedantic -std=c99 -o pong $^ argparse/libargparse.a $(FLAGS)

drawing.o: pong_header.h drawing.c
	$(CC) -Wall -pedantic -std=c99 -c drawing.c

game_logic.o: pong_header.h game_logic.c
	$(CC) -Wall -pedantic -std=c99 -c game_logic.c

music.o: pong_header.h music.c
	$(CC) -Wall -pedantic -std=c99 -c music.c

clean:
	rm *.o
