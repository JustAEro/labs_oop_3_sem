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
	return degrees * PI / 180.f;
}

inline float radiansToDegrees(float radians)
{
	return radians * 180.f / PI;
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
	sf::Texture convoyShipTexture;   //texture of ship (TODO: Type of ship?)
	sf::Texture piratesShipTexture;
	sf::Texture pauseTexture;
	sf::Texture baseATexture;
	sf::Texture baseBTexture;
	sf::Texture convoyBulletTexture;
	sf::Texture piratesBulletTexture;
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
	double piratesSpawnTimer;
	double piratesSpawnTimerMax;
	//double convoyBulletsSpawnTimer;
	double convoyBulletsSpawnTimerMax;
	//double piratesBulletsSpawnTimer;
	double piratesBulletsSpawnTimerMax;
	size_t maxPirates;

	int activeShipConvoyIndex;


	//Game objects
	   //sf::Sprite
	sf::Sprite baseASprite;
	sf::Sprite baseBSprite;
	std::vector <std::tuple<sf::Sprite, int, Point, bool, float> > spritesAndIDsOfConvoyShips;
	std::vector <std::tuple<sf::Sprite, int, Point, bool, float> > spritesAndIDsOfPiratesShips;
	std::vector <sf::Sprite> convoyBullets;
	std::vector <sf::Sprite> piratesBullets;
	Mission* mission;
	//sf::RectangleShape enemy;


	//Private functions
	void initTextures();
	void initVariables();
	void initWindow();
	void initConvoy();
	void initPirates();
	void pollEvents();

	bool isSpriteOutOfWindow(const sf::Sprite& sprite);
	float angleInDegreesToSprite2(const sf::Sprite& sprite_1, const sf::Sprite& sprite_2);
	float angleInDegreesToBaseB(const sf::Sprite& sprite);


public:
	//Constructors / Destructors
	Game();
	virtual ~Game();

	//Accessors
	const bool getWindowIsOpen() const;

	//Functions
	void spawnPirate();
	void spawnConvoyBullet(const sf::Sprite& spriteBegin, const sf::Sprite& spriteEnd);
	void spawnPiratesBullet(const sf::Sprite& spriteBegin, const sf::Sprite& spriteEnd);

	void updateMousePositions();

	void updateConvoy();
	void updatePirates();
	void updatePiratesBullets();
	void updateConvoyBullets();
	//void updatePause();
	void update();

	void renderPause();
	void renderWater();
	void renderBases();
	void renderConvoy();
	void renderPirates();
	void renderPiratesBullets();
	void renderConvoyBullets();
	void renderEndGame();
	void render();

};

