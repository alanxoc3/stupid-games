# Makefile!

# $$HOME will escape the $, in order to have $HOME, which bash will later
# interpret as the home directory.
EXECUTABLE_NAME=simplegame
DIRECTORY=$$HOME/.simplegame/
FLAGS=-lallegro -lallegro_image -lallegro_font -lallegro_ttf -DHOME_DIR="\"$(DIRECTORY)\""

bin/$(EXECUTABLE_NAME): main.cpp bin/sprite.o bin/player.o bin/score.o bin/coin.o\
           bin/spriteList.o bin/enemy.o
	g++ -o $@ $^ $(FLAGS)

# Testing executable.
bin/tst/spriteTest.out : src/tst/spriteTest.cpp bin/sprite.o
	g++ -o $@ $^ $(FLAGS)

# Binary files.
bin/sprite.o : src/sprite.cpp src/sprite.h src/constants.h
	g++ -c -o $@ $< $(FLAGS)

bin/player.o : src/player.cpp src/player.h src/constants.h
	g++ -c -o $@ $< $(FLAGS)

bin/score.o : src/score.cpp src/score.h src/constants.h
	g++ -c -o $@ $< $(FLAGS)

bin/coin.o : src/coin.cpp src/coin.h src/constants.h
	g++ -c -o $@ $< $(FLAGS)

bin/spriteList.o : src/spriteList.cpp src/spriteList.h src/constants.h
	g++ -c -o $@ $< $(FLAGS)

bin/enemy.o: src/enemy.cpp src/enemy.h src/sprite.o src/constants.h
	g++ -c -o $@ $< $(FLAGS)

clean:
	rm bin/*.o
	rm bin/*.out

install:
	mkdir -p $(DIRECTORY)
	cp bin/$(EXECUTABLE_NAME) $(DIRECTORY)
	cp -r bin/res $(DIRECTORY)
