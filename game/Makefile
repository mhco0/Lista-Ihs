CPPFLAGS += -Wall -O2 -std=c++11

ALLEGROFLAGS := -lallegro -lallegro_image -lallegro_ttf -lallegro_font

GAMELIB := -Isrc/minigames
MGPATH := src/minigames

.cpp.o:
	g++ $(CPPFLAGS) -c -o $@ $<

genius.o: $(MGPATH)/genius.cpp 
	g++ $(CPPFLAGS) -c $(MGPATH)/genius.cpp 
	
main.o: main.cpp 
	g++ $(CPPFLAGS) $(GAMELIB) $(ALLEGROFLAGS) -c main.cpp 
	
all: main.o genius.o
	g++ $(CPPFLAGS) $(GAMELIB) $(ALLEGROFLAGS) main.o genius.o -o CinBomb
	
clean:
	rm *.o
	rm CinBomb
	
run:
	./CinBomb
