#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "../MilitaryConvoy/Mission/Mission.h"

#include <iostream>
#include <vector>
#include <ctime>
#include <utility>


constexpr float PI = 3.14159265358979323846;

inline float degreesToRadians(float degrees)
{
	return degrees * PI / 180;
}

inline float radiansToDegrees(float radians)
{
	return radians * 180 / PI;
}

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
	sf::Texture pauseTexture;
	sf::Texture baseATexture;
	sf::Texture baseBTexture;
	sf::Texture winGameTexture;
	sf::Texture loseGameTexture;

	//Mouse positions
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;


	//Game logic
	bool isPaused;
	bool isWin;
	bool isLose;
	//int points;
	double enemySpawnTimer;
	double enemySpawnTimerMax;
	size_t maxEnemies;
	int activeShipIndex;


	//Game objects
	   //sf::Sprite
	sf::Sprite baseASprite;
	sf::Sprite baseBSprite;
	std::vector <std::pair<sf::Sprite, int> > spritesAndIDsOfShips;
	Mission* mission;
	//sf::RectangleShape enemy;


	//Private functions
	void initTextures();
	void initVariables();
	void initWindow();
	void initEnemies();
	void pollEvents();

	bool isSpriteOutOfWindow(const sf::Sprite& sprite);


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
	//void updatePause();
	void update();

	void renderPause();
	void renderWater();
	void renderBases();
	void renderEnemies();
	void renderEndGame();
	void render();

};

