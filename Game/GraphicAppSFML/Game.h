#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <vector>
#include <ctime>


/*
* Class that acts the game engine.
* Wrapper class
*/

class Game
{
private:
	//Variables
	//Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event event;

	//Textures
	sf::Texture waterTexture;  //texture of water background
	sf::Texture shipTexture;   //texture of ship (TODO: Type of ship?)

	//Mouse positions
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;


	//Game logic
	int points;
	double enemySpawnTimer;
	double enemySpawnTimerMax;
	int maxEnemies;


	//Game objects
	   //sf::Sprite
	std::vector<sf::Sprite> enemies;
	//sf::RectangleShape enemy;


	//Private functions
	void initTextures();
	void initVariables();
	void initWindow();
	void initEnemies();
	void pollEvents();

public:
	//Constructors / Destructors
	Game();
	virtual ~Game();

	//Accessors
	const bool getWindowIsOpen() const;

	//Functions
	void spawnEnemy();

	void updateMousePositions();

	void updateEnemies();
	void update();

	void renderWater();
	void renderEnemies();
	void render();

};

