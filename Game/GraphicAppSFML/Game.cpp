#include "Game.h"
#include <cmath>

void Game::initTextures()
{
	waterTexture.loadFromFile("resources/waterSprite.png");
	waterTexture.setSmooth(true);

	sf::Image shipImage;
	shipImage.loadFromFile("resources/shipSprite.png");
	shipTexture.loadFromImage(shipImage);
	shipTexture.setSmooth(true);

	pauseTexture.loadFromFile("resources/pauseSprite.png");
	pauseTexture.setSmooth(true);

	baseATexture.loadFromFile("resources/Base_A_Sprite.png");
	baseATexture.setSmooth(true);

	baseBTexture.loadFromFile("resources/Base_B_sprite.png");
	baseBTexture.setSmooth(true);

	winGameTexture.loadFromFile("resources/winSprite.png");
	winGameTexture.setSmooth(true);

	loseGameTexture.loadFromFile("resources/loseSprite.png");
	loseGameTexture.setSmooth(true);
}

//Private functions
void Game::initVariables()
{
	window = nullptr;

	//Game logic
	mission = new Mission;
	//points = 0;
	isPaused = false;
	isWin = false;
	isLose = false;
	enemySpawnTimerMax = 10.f;
    enemySpawnTimer = enemySpawnTimerMax;
	maxEnemies = 5;
	activeShipIndex = -1;  ///No selected ship by default
}

void Game::initWindow()
{
	videoMode.width = 1280;
	videoMode.height = 720;
	
	
	window = new sf::RenderWindow(videoMode, sf::String(L"Military Convoy"),  sf::Style::Titlebar | sf::Style::Close);

	window->setFramerateLimit(144);
}

void Game::initEnemies()
{
	//sf::Sprite enemy;
	//enemy.setTexture(shipTexture);
	//enemy.setPosition(10.f, 10.f);
	//enemy.setSize(sf::Vector2f(100.f, 100.f));
	//enemy.setScale(sf::Vector2f(0.5f, 0.5f));
	//enemy.setColor(sf::Color::Green);
	//enemy.setFillColor(sf::Color::Cyan);
	//enemy.setOutlineColor(sf::Color::Green);
	//enemy.setOutlineThickness(1.f);


}



bool Game::isSpriteOutOfWindow(const sf::Sprite& sprite)
{
	if (
		sprite.getPosition().y > window->getSize().y ||
		sprite.getPosition().x > window->getSize().x ||
		sprite.getPosition().y < 0 ||
		sprite.getPosition().x < 0
		)
	{
		return true;
	}
	return false;
}




//Constructors / Destructors
Game::Game()
{
	Game::initVariables();
	Game::initWindow();
	Game::initTextures();
	Game::initEnemies();
}

Game::~Game()
{
	delete mission;
	delete window;
}



//Accessors
const bool Game::getWindowIsOpen() const
{
	return window->isOpen();
}



void Game::pollEvents()
{
	while (window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window->close();
			break;

		case sf::Event::KeyReleased:
			if (event.key.code == sf::Keyboard::Escape)
			{
				if (isWin || isLose)  //game finished, esc to exit
				{
					window->close();
					break;
				}
				else //game is not finished
				{
					isPaused = !isPaused; 
				}
				
			}
			break;


		default:
			break;
		}
	}
}

void Game::spawnEnemy()
{
	/*
	* @return void
	* 
	* Spawns enemies and sets colors and positions.
	* -Sets a random position.
	* -Sets a random color.
	* -Adds enemy to the vector. 
	*/

	sf::Sprite enemy;
	enemy.setTexture(shipTexture);

	

	enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>((window->getSize().x - enemy.getGlobalBounds().width))),
		32.f
	);

	enemy.setOrigin(32.f, 32.f);

	//enemy.setScale(sf::Vector2f(0.5f, 0.5f));
	//enemy.rotate(45.f);
	//enemy.setColor(sf::Color::Green);

	//Spawn the enemy
	
	int id = mission->getTablePirates().addShip(new BattleTransport);
	spritesAndIDsOfShips.push_back(std::make_pair(enemy, id));

	//Remove enemies at end of screen

}	

void Game::updateMousePositions()
{
	/*
	@ return void
	Updates the mouse positions:
		- Mouse position relative to window
	*/

	mousePosWindow = sf::Mouse::getPosition(*window);
	mousePosView = window->mapPixelToCoords(mousePosWindow);
	 
	//std::cout << "x = " << mousePosView.x << " y = " << mousePosView.y << std::endl;
}

void Game::updateEnemies()
{
	/*
	* @return void
	* 
	* Updates the enemy spawn timer and spawns enemies
	* when the total amount of enemies is smaller than maximum.
	* Moves the enemies downwards.
	* Removes the enemies at the edge of the screen. //TODO
	*/

	//Updating the timer for enemy spawning

	if (!isPaused && !(isWin || isLose) )
	{
		if (spritesAndIDsOfShips.size() < maxEnemies)
		{
			if (enemySpawnTimer >= enemySpawnTimerMax)
			{
				//Spawn the enemy and reset the timer
				Game::spawnEnemy();
				enemySpawnTimer = 0.f;
			}
			else
			{
				enemySpawnTimer += 1.f;
			}
		}


		//Move and updating enemies
		for (int i = 0; i < static_cast<int>(spritesAndIDsOfShips.size()); ++i)
		{
			bool deleted = false;


			//enemies[i].move(0.f, 1.f);

			if (activeShipIndex != i)   //move the sprite without player if only it is not active
			{
				float baseB_x = baseBSprite.getPosition().x;
				float baseB_y = baseBSprite.getPosition().y;

				float ship_x = spritesAndIDsOfShips[i].first.getPosition().x;
				float ship_y = spritesAndIDsOfShips[i].first.getPosition().y;

				float dx = baseB_x - ship_x;
				float dy = baseB_y - ship_y;
				float angle = radiansToDegrees(atan2(dy, dx));  //angle to move to B base

				
				//spritesAndIDsOfShips[i].first.setRotation(45.f);
				spritesAndIDsOfShips[i].first.setRotation(angle);
				angle = degreesToRadians(spritesAndIDsOfShips[i].first.getRotation());
				spritesAndIDsOfShips[i].first.move(0.15f * cos(angle), 0.15f * sin(angle));
			}



			//Check if clicked upon
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (spritesAndIDsOfShips[i].first.getGlobalBounds().contains(mousePosView))
				{
					if (activeShipIndex != -1)
					{
						spritesAndIDsOfShips[activeShipIndex].first.setColor(sf::Color::White);
					}
					activeShipIndex = i;
					spritesAndIDsOfShips[i].first.setColor(sf::Color::Green);
					//deleted = true;

					//Gain points
					//points += 10.f;
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				if (activeShipIndex != -1)
				{
					float angle = degreesToRadians(spritesAndIDsOfShips[activeShipIndex].first.getRotation());
					spritesAndIDsOfShips[activeShipIndex].first.move(0.5f * cos(angle), 0.5f * sin(angle));
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				if (activeShipIndex != -1)
				{
					float angle = degreesToRadians(spritesAndIDsOfShips[activeShipIndex].first.getRotation());
					spritesAndIDsOfShips[activeShipIndex].first.move(-0.5f * cos(angle), -0.5f * sin(angle));
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				if (activeShipIndex != -1)
				{
					spritesAndIDsOfShips[activeShipIndex].first.rotate(-0.1f);
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				if (activeShipIndex != -1)
				{
					spritesAndIDsOfShips[activeShipIndex].first.rotate(0.1f);
				}
			}

			//If the enemy is out of the screen
			if (isSpriteOutOfWindow(spritesAndIDsOfShips[i].first))
			{
				isLose = true;
				deleted = true;
			}

			//If the ship reached Base B
			if (baseBSprite.getGlobalBounds().contains(spritesAndIDsOfShips[i].first.getPosition()))
			{
				isWin = true;
				deleted = true;
			}

			//final delete from table and from vector
			if (deleted)
			{
				if (activeShipIndex == i)
				{
					activeShipIndex = -1;
				}
				else
				{
					if (activeShipIndex > i)
					{
						--activeShipIndex;
					}
				}

				mission->getTablePirates().removeShip(spritesAndIDsOfShips[i].second);
				spritesAndIDsOfShips.erase(spritesAndIDsOfShips.begin() + i);
			}
		}

	}
}





//Functions
void Game::update()
{
	Game::pollEvents();
	
	Game::updateMousePositions();

	Game::updateEnemies();

}


void Game::renderWater()
{
	sf::Sprite waterSprite;
	waterSprite.setTexture(waterTexture);
	window->draw(waterSprite);
}


void Game::renderBases()
{
	//render base A
	baseASprite.setTexture(baseATexture);
	window->draw(baseASprite);

	//render base B
	baseBSprite.setTexture(baseBTexture);
	baseBSprite.setOrigin(128.f, 128.f);
	baseBSprite.setPosition(window->getSize().x, window->getSize().y);
	window->draw(baseBSprite);
}


void Game::renderEnemies()
{
	//Rendering all the enemies
	for (const auto& e : spritesAndIDsOfShips)
	{
		window->draw(e.first);
	}

}

void Game::renderPause()
{
	if (isPaused)
	{
		sf::Sprite pauseSprite;
		pauseSprite.setTexture(pauseTexture);
		window->draw(pauseSprite);
	}
}

void Game::renderEndGame()
{
	if (isWin)
	{
		sf::Sprite winSprite;
		winSprite.setTexture(winGameTexture);
		window->draw(winSprite);
	}
	
	//(TO DO: is lost)
	else if (isLose)
	{
		sf::Sprite loseSprite;
		loseSprite.setTexture(loseGameTexture);
		window->draw(loseSprite);
	}

	else //the game is not finished yet
	{
		return;
	}
}


void Game::render()
{
	/*
	* @return void
	* 
	*
	* -clear old frame
	* -render objects
	* -display frame in window
	* 
	* Renders the game objects.
	*/

	window->clear();


	//Draw game objects
	Game::renderWater();
	Game::renderBases();
	Game::renderEnemies();
	Game::renderPause();
	Game::renderEndGame();

	window->display();
}


