CPPFLAGS += -Wall -O2 -std=c++11

ALLEGROFLAGS = -lallegro -lallegro_image -lallegro_ttf -lallegro_font

GAMELIB = -Isrc/minigames

genius.o:genius.cpp
	g++ -c genius.cpp $(ALLEGROFLAGS) $(CPPFLAGS)

all:
	g++ main.cpp $(CPPFLAGS) $(ALLEGROFLAGS)  -o CinBomb
clean:
	rm CinBomb
run:
	./CinBomb