ALLEGRO_FLAG = -lallegro -lallegro_image -lallegro_ttf -lallegro_font 
CPPFLAGS += -std=c++11 -Wall -O2 -O3 

all:
	g++ main.cpp $(CPPFLAGS) $(ALLEGRO_FLAG) -o CinBomb
	echo "Main compilada"
	./CinBomb
clean:
	rm -f *.o CinBomb
