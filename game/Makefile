CPPFLAGS += -Wall -O2 -std=c++11

ALLEGROFLAGS = -lallegro -lallegro_image -lallegro_ttf -lallegro_font

GAMELIB = -Isrc/minigames



genius.o: 
	g++ -c src/minigames/genius.cpp $(ALLEGROFLAGS) $(GAMELIB) $(CPPFLAGS)
all: genius.o
	g++ main.cpp genius.o $(CPPFLAGS) $(ALLEGROFLAGS) $(GAMELIB)  -o CinBomb
clean:
	rm CinBomb
run:
	./CinBomb
