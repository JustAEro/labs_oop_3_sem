all: Application.cpp libPlayingCards.a
	g++ -Wall -Wextra -c PlayingCards.cpp
	ar -rcs libPlayingCards.a PlayingCards.o
	g++ -Wall -Wextra -c Application.cpp Menu.cpp
	g++  Application.o Menu.o -L. -lPlayingCards -o app.elf
