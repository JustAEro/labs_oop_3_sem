all: Application.cpp
	g++ -std=c++17 -Wall -Wextra -c PlayingCards.cpp
	ar -rcs libPlayingCards.a PlayingCards.o
	g++ -std=c++17 -Wall -Wextra -c Application.cpp Menu.cpp
	g++ -std=c++17 Application.o Menu.o -L. -lPlayingCards -o app.elf
