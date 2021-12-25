#include "Game.h"
#include <cmath>

void Game::initTextures()
{
	waterTexture.loadFromFile("resources/waterSprite.png");
	waterTexture.setSmooth(true);

	convoyShipTexture.loadFromFile("resources/shipSprite.png");
	convoyShipTexture.setSmooth(true);

	piratesShipTexture.loadFromFile("resources/piratesShipSprite.png");
	piratesShipTexture.setSmooth(true);

	pauseTexture.loadFromFile("resources/pauseSprite.png");
	pauseTexture.setSmooth(true);

	baseATexture.loadFromFile("resources/Base_A_Sprite.png");
	baseATexture.setSmooth(true);

	baseBTexture.loadFromFile("resources/Base_B_sprite.png");
	baseBTexture.setSmooth(true);

	piratesBulletTexture.loadFromFile("resources/piratesBullet.png");
	piratesBulletTexture.setSmooth(true);

	convoyBulletTexture.loadFromFile("resources/convoyBullet.png");
	convoyBulletTexture.setSmooth(true);

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
	piratesSpawnTimerMax = 10.f;
    piratesSpawnTimer = piratesSpawnTimerMax;
	
	convoyBulletsSpawnTimerMax = 100.f;
	//convoyBulletsSpawnTimer = convoyBulletsSpawnTimerMax;

	piratesBulletsSpawnTimerMax = 100.f;
	//piratesBulletsSpawnTimer = piratesBulletsSpawnTimerMax;
	
	maxPirates = 5;
	activeShipConvoyIndex = -1;  ///No selected ship by default
}

void Game::initWindow()
{
	videoMode.width = 1280;
	videoMode.height = 720;
	
	
	window = new sf::RenderWindow(videoMode, sf::String(L"Military Convoy"),  sf::Style::Titlebar | sf::Style::Close);

	window->setFramerateLimit(144);
}

void Game::initConvoy()
{
	for (int i = 0; i < 5; ++i)
	{
		sf::Sprite convoyShip;
		convoyShip.setTexture(convoyShipTexture);

		float posX = static_cast<float>(rand() % static_cast<int>((window->getSize().x / 2 - convoyShip.getGlobalBounds().width))) + 16.f;
		float posY = static_cast<float>(rand() % static_cast<int>((window->getSize().y / 2 - convoyShip.getGlobalBounds().height))) + 16.f;
		
		convoyShip.setPosition(posX, posY);

		convoyShip.setOrigin(32.f, 32.f);


		//enemy.setScale(sf::Vector2f(0.5f, 0.5f));
		//enemy.rotate(45.f);
		//enemy.setColor(sf::Color::Green);

		//Spawn the enemy

		int id = mission->getTableConvoy().addShip(new BattleTransport);
		Point target(-9999.f, -9999.f);
		bool isShooting = false;
		float spawnTimer = convoyBulletsSpawnTimerMax;
		spritesAndIDsOfConvoyShips.push_back(std::make_tuple(convoyShip, id, target, isShooting, spawnTimer));
	}
	//sf::Sprite convoyShip;
	//convoyShip.setTexture(shipTexture);
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


void Game::initPirates()
{
	for (int i = 0; i < maxPirates; ++i)
	{
		Game::spawnPirate();
	}
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

float Game::angleInDegreesToSprite2(const sf::Sprite& sprite_1, const sf::Sprite& sprite_2)
{
	float sprite1_x = sprite_1.getPosition().x;
	float sprite1_y = sprite_1.getPosition().y;

	float sprite2_x = sprite_2.getPosition().x;
	float sprite2_y = sprite_2.getPosition().y;

	float dx = sprite2_x - sprite1_x;
	float dy = sprite2_y - sprite1_y;
	float angle = radiansToDegrees(atan2(dy, dx));
	return angle;
}

float Game::angleInDegreesToBaseB(const sf::Sprite& sprite) 
{
	return angleInDegreesToSprite2(sprite, baseBSprite);
}




//Constructors / Destructors
Game::Game()
{
	Game::initVariables();
	Game::initWindow();
	Game::initTextures();
	Game::initConvoy();
	Game::initPirates();
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
			
			else if (event.key.code == sf::Keyboard::Enter)
			{
				if (isWin || isLose)
				{
					window->close();
					spritesAndIDsOfConvoyShips.clear();
					spritesAndIDsOfPiratesShips.clear();
					convoyBullets.clear();
					piratesBullets.clear();
					delete mission;
					delete window;
					Game::initVariables();
					Game::initWindow();
					Game::initTextures();
					Game::initConvoy();
				}
			}

			break;


		default:
			break;
		}
	}
}

void Game::spawnPirate()
{
	/*
	* @return void
	* 
	* Spawns enemies and sets colors and positions.
	* -Sets a random position.
	* -Sets a random color.
	* -Adds enemy to the vector. 
	*/

	sf::Sprite pirate;
	pirate.setTexture(piratesShipTexture);
	

	float posX = static_cast<float>(rand() % static_cast<int>((window->getSize().x - pirate.getGlobalBounds().width))) + 16.f;
	float posY;
	if (posX <= static_cast<float>(window->getSize().x / 2))
	{
		posY = static_cast<float>(rand() % static_cast<int>((window->getSize().y / 2 - pirate.getGlobalBounds().height))) + static_cast<float>(window->getSize().y / 2) + 16.f;
	}
	else
	{
		posY = static_cast<float>(rand() % static_cast<int>((window->getSize().y / 2 - pirate.getGlobalBounds().height))) + 16.f;
	}

	pirate.setPosition(posX, posY);

	pirate.setOrigin(32.f, 32.f);


	//enemy.setScale(sf::Vector2f(0.5f, 0.5f));
	//enemy.rotate(45.f);
	//enemy.setColor(sf::Color::Green);

	//Spawn the enemy
	
	int id = mission->getTablePirates().addShip(new BattleTransport);
	Point target(-9999.f, -9999.f);
	bool isShooting = false;
	float spawnTimer = piratesBulletsSpawnTimerMax;
	spritesAndIDsOfPiratesShips.push_back(std::make_tuple(pirate, id, target, isShooting, spawnTimer));

	//Remove enemies at end of screen

}	


void Game::spawnConvoyBullet(const sf::Sprite& spriteBegin, const sf::Sprite& spriteEnd)
{
	sf::Sprite convoyBulletSprite;
	convoyBulletSprite.setTexture(convoyBulletTexture);
	convoyBulletSprite.setPosition(spriteBegin.getPosition());

	convoyBulletSprite.setOrigin(4.f, 4.f);

	float angle = angleInDegreesToSprite2(spriteBegin, spriteEnd);
	convoyBulletSprite.setRotation(angle);

	convoyBullets.push_back(convoyBulletSprite);
}

void Game::spawnPiratesBullet(const sf::Sprite& spriteBegin, const sf::Sprite& spriteEnd)
{
	sf::Sprite piratesBulletSprite;
	piratesBulletSprite.setTexture(piratesBulletTexture);
	piratesBulletSprite.setPosition(spriteBegin.getPosition());

	piratesBulletSprite.setOrigin(4.f, 4.f);

	float angle = angleInDegreesToSprite2(spriteBegin, spriteEnd);
	piratesBulletSprite.setRotation(angle);

	piratesBullets.push_back(piratesBulletSprite);
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


void Game::updateConvoy()
{
	if (!isPaused && !(isWin || isLose))
	{
		if (spritesAndIDsOfConvoyShips.size() == 0)
		{
			isLose = true;
		}

		//Move and updating convoy ships
		for (int i = 0; i < static_cast<int>(spritesAndIDsOfConvoyShips.size()); ++i)
		{
			bool deleted = false;

			if (mission->getTableConvoy().getShipByID(std::get<1>(spritesAndIDsOfConvoyShips[i]))->getCurrentHP() <= 0)
			{
				deleted = true;
			}

			if (!deleted)
			{
				float minDistance = 9999.f;
				int index = 0;
				for (int j = 0; j < static_cast<int>(spritesAndIDsOfPiratesShips.size()); ++j)
				{
					float x_convoy = std::get<0>(spritesAndIDsOfConvoyShips[i]).getPosition().x;
					float y_convoy = std::get<0>(spritesAndIDsOfConvoyShips[i]).getPosition().y;

					float x_pirate = std::get<0>(spritesAndIDsOfPiratesShips[j]).getPosition().x;
					float y_pirate = std::get<0>(spritesAndIDsOfPiratesShips[j]).getPosition().y;

					float dist = distanceBetweenTwoPoints(Point(x_convoy, y_convoy), Point(x_pirate, y_pirate));

					if (dist < minDistance && dist > 32.f)
					{
						minDistance = dist;
						index = j;
					}
				}

				//float angle = angleInDegreesToSprite2(std::get<0>(spritesAndIDsOfPiratesShips[i]), std::get<0>(spritesAndIDsOfConvoyShips[index]));
				//std::get<0>(spritesAndIDsOfPiratesShips[i]).setRotation(angle);

				if (minDistance <= 256.f)
				{
					float targetPosX = std::get<0>(spritesAndIDsOfPiratesShips[index]).getPosition().x;
					float targetPosY = std::get<0>(spritesAndIDsOfPiratesShips[index]).getPosition().y;
					std::get<2>(spritesAndIDsOfConvoyShips[i]) = Point(targetPosX, targetPosY);
					std::get<3>(spritesAndIDsOfConvoyShips[i]) = true;

					
					if (std::get<4>(spritesAndIDsOfConvoyShips[i]) >= convoyBulletsSpawnTimerMax)
					{
						//Spawn the enemy and reset the timer
						Game::spawnConvoyBullet(std::get<0>(spritesAndIDsOfConvoyShips[i]), std::get<0>(spritesAndIDsOfPiratesShips[index]));
						std::get<4>(spritesAndIDsOfConvoyShips[i]) = 0.f;
					}
					else
					{
						std::get<4>(spritesAndIDsOfConvoyShips[i]) += 1.f;
					}
					
					
					

					//float curHP = mission->getTablePirates().getShipByID(std::get<1>(spritesAndIDsOfPiratesShips[index]))->getCurrentHP();
					//std::cout << "HP = " << curHP << "\n";///
					//mission->getTablePirates().getShipByID(std::get<1>(spritesAndIDsOfPiratesShips[index]))->setCurrentHP(curHP - 0.5f);//
				}
				else
				{
					std::get<3>(spritesAndIDsOfConvoyShips[i]) = false;
				}

				//if (minDistance > 128.f)
				//{
					//std::get<0>(spritesAndIDsOfPiratesShips[i]).move(0.15 * cos(degreesToRadians(angle)), 0.15 * sin(degreesToRadians(angle)));
				//}

				if (activeShipConvoyIndex != i)   //move the sprite without player if only it is not active
				{
					float angle = angleInDegreesToBaseB(std::get<0>(spritesAndIDsOfConvoyShips[i]));
					std::get<0>(spritesAndIDsOfConvoyShips[i]).setRotation(angle);

					angle = degreesToRadians(angle);
					std::get<0>(spritesAndIDsOfConvoyShips[i]).move(0.15f * cos(angle), 0.15f * sin(angle));
				}

				//Check if clicked upon
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					if (std::get<0>(spritesAndIDsOfConvoyShips[i]).getGlobalBounds().contains(mousePosView))
					{
						if (activeShipConvoyIndex != -1)
						{
							std::get<0>(spritesAndIDsOfConvoyShips[activeShipConvoyIndex]).setColor(sf::Color::White);
						}
						activeShipConvoyIndex = i;
						std::get<0>(spritesAndIDsOfConvoyShips[i]).setColor(sf::Color::Green);
						//deleted = true;

						//Gain points
						//points += 10.f;
					}
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					if (activeShipConvoyIndex != -1)
					{
						float angle = degreesToRadians(std::get<0>(spritesAndIDsOfConvoyShips[activeShipConvoyIndex]).getRotation());
						std::get<0>(spritesAndIDsOfConvoyShips[activeShipConvoyIndex]).move(0.3f * cos(angle), 0.3f * sin(angle));
					}
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					if (activeShipConvoyIndex != -1)
					{
						float angle = degreesToRadians(std::get<0>(spritesAndIDsOfConvoyShips[activeShipConvoyIndex]).getRotation());
						std::get<0>(spritesAndIDsOfConvoyShips[activeShipConvoyIndex]).move(-0.3f * cos(angle), -0.3f * sin(angle));
					}
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					if (activeShipConvoyIndex != -1)
					{
						std::get<0>(spritesAndIDsOfConvoyShips[activeShipConvoyIndex]).rotate(-0.1f);
					}
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					if (activeShipConvoyIndex != -1)
					{
						std::get<0>(spritesAndIDsOfConvoyShips[activeShipConvoyIndex]).rotate(0.1f);
					}
				}

				//If the convoy ship is out of the screen
				if (isSpriteOutOfWindow(std::get<0>(spritesAndIDsOfConvoyShips[i])))
				{
					deleted = true;
				}

				//If the ship reached Base B
				if (baseBSprite.getGlobalBounds().contains(std::get<0>(spritesAndIDsOfConvoyShips[i]).getPosition()))
				{
					isWin = true;
					deleted = true;
				}
			}

			

			//final delete from table and from vector
			if (deleted)
			{
				if (activeShipConvoyIndex == i)
				{
					activeShipConvoyIndex = -1;
				}
				else
				{
					if (activeShipConvoyIndex > i)
					{
						--activeShipConvoyIndex;
					}
				}

				mission->getTableConvoy().removeShip(std::get<1>(spritesAndIDsOfConvoyShips[i]));
				spritesAndIDsOfConvoyShips.erase(spritesAndIDsOfConvoyShips.begin() + i);
			}
		}

	}
}



void Game::updatePirates()
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
		if (spritesAndIDsOfPiratesShips.size() < maxPirates)
		{
			if (piratesSpawnTimer >= piratesSpawnTimerMax)
			{
				//Spawn the enemy and reset the timer
				Game::spawnPirate();
				piratesSpawnTimer = 0.f;
			}
			else
			{
				piratesSpawnTimer += 1.f;
			}
		}


		//Move and updating pirates
		for (int i = 0; i < static_cast<int>(spritesAndIDsOfPiratesShips.size()); ++i)
		{
			bool deleted = false;

			if (mission->getTablePirates().getShipByID(std::get<1>(spritesAndIDsOfPiratesShips[i]))->getCurrentHP() <= 0)
			{
				deleted = true;
			}

			if (!deleted)
			{
				float minDistance = 9999.f;
				int index = 0;
				for (int j = 0; j < static_cast<int>(spritesAndIDsOfConvoyShips.size()); ++j)
				{
					float x_pirate = std::get<0>(spritesAndIDsOfPiratesShips[i]).getPosition().x;
					float y_pirate = std::get<0>(spritesAndIDsOfPiratesShips[i]).getPosition().y;

					float x_convoy = std::get<0>(spritesAndIDsOfConvoyShips[j]).getPosition().x;
					float y_convoy = std::get<0>(spritesAndIDsOfConvoyShips[j]).getPosition().y;

					float dist = distanceBetweenTwoPoints(Point(x_pirate, y_pirate), Point(x_convoy, y_convoy));

					if (dist < minDistance && dist > 32.f)
					{
						minDistance = dist;
						index = j;
					}
				}

				float angle = angleInDegreesToSprite2(std::get<0>(spritesAndIDsOfPiratesShips[i]), std::get<0>(spritesAndIDsOfConvoyShips[index]));
				std::get<0>(spritesAndIDsOfPiratesShips[i]).setRotation(angle);

				if (minDistance <= 512.f)
				{
					float targetPosX = std::get<0>(spritesAndIDsOfConvoyShips[index]).getPosition().x;
					float targetPosY = std::get<0>(spritesAndIDsOfConvoyShips[index]).getPosition().y;
					std::get<2>(spritesAndIDsOfPiratesShips[i]) = Point(targetPosX, targetPosY);
					std::get<3>(spritesAndIDsOfPiratesShips[i]) = true;

					
					if (std::get<4>(spritesAndIDsOfPiratesShips[i]) >= piratesBulletsSpawnTimerMax)
					{
						//Spawn the enemy and reset the timer
						Game::spawnPiratesBullet(std::get<0>(spritesAndIDsOfPiratesShips[i]), std::get<0>(spritesAndIDsOfConvoyShips[index]));
						std::get<4>(spritesAndIDsOfPiratesShips[i]) = 0.f;
					}
					else
					{
						std::get<4>(spritesAndIDsOfPiratesShips[i]) += 1.f;
					}
					
					

					//float curHP = mission->getTableConvoy().getShipByID(std::get<1>(spritesAndIDsOfConvoyShips[index]))->getCurrentHP();
					//std::cout << "HP = " << curHP << "\n";///
					//mission->getTableConvoy().getShipByID(std::get<1>(spritesAndIDsOfConvoyShips[index]))->setCurrentHP(curHP - 0.1f);//
				}
				else
				{
					std::get<3>(spritesAndIDsOfPiratesShips[i]) = false;
				}

				if (minDistance > 128.f)
				{
					std::get<0>(spritesAndIDsOfPiratesShips[i]).move(0.15 * cos(degreesToRadians(angle)), 0.15 * sin(degreesToRadians(angle)));
				}




				//If the pirate is out of the screen
				if (isSpriteOutOfWindow(std::get<0>(spritesAndIDsOfPiratesShips[i])))
				{
					deleted = true;
				}
			}

			//final delete from table and from vector
			if (deleted)
			{
				mission->getTablePirates().removeShip(std::get<1>(spritesAndIDsOfPiratesShips[i]));
				spritesAndIDsOfPiratesShips.erase(spritesAndIDsOfPiratesShips.begin() + i);
			}
		}

	}
}


void Game::updatePiratesBullets()
{
	if (!isPaused && !(isWin || isLose))
	{
		for (int i = 0; i < static_cast<int>(piratesBullets.size()); ++i)
		{
			bool deleted = false;

			for (int j = 0; j < static_cast<int>(spritesAndIDsOfConvoyShips.size()); ++j)
			{
				if (std::get<0>(spritesAndIDsOfConvoyShips[j]).getGlobalBounds().contains(piratesBullets[i].getPosition()))
				{
					deleted = true;
					float curHP = mission->getTableConvoy().getShipByID(std::get<1>(spritesAndIDsOfConvoyShips[j]))->getCurrentHP();
					//std::cout << "HP = " << curHP << "\n";///
					mission->getTableConvoy().getShipByID(std::get<1>(spritesAndIDsOfConvoyShips[j]))->setCurrentHP(curHP - 5.f);//
				}
				else
				{
					float angle = degreesToRadians(piratesBullets[i].getRotation());
					piratesBullets[i].move(0.3f * cos(angle), 0.3f * sin(angle));
				}


				if (isSpriteOutOfWindow(piratesBullets[i]))
				{
					deleted = true;
				}
			}

			if (deleted)
			{
				piratesBullets.erase(piratesBullets.begin() + i);
			}
		}
	}
}

void Game::updateConvoyBullets()
{
	if (!isPaused && !(isWin || isLose))
	{
		for (int i = 0; i < static_cast<int>(convoyBullets.size()); ++i)
		{
			bool deleted = false;

			for (int j = 0; j < static_cast<int>(spritesAndIDsOfPiratesShips.size()); ++j)
			{
				if (std::get<0>(spritesAndIDsOfPiratesShips[j]).getGlobalBounds().contains(convoyBullets[i].getPosition()))
				{
					deleted = true;
					float curHP = mission->getTablePirates().getShipByID(std::get<1>(spritesAndIDsOfPiratesShips[j]))->getCurrentHP();
					//std::cout << "HP = " << curHP << "\n";///
					mission->getTablePirates().getShipByID(std::get<1>(spritesAndIDsOfPiratesShips[j]))->setCurrentHP(curHP - 15.f);//
				}
				else
				{
					float angle = degreesToRadians(convoyBullets[i].getRotation());
					convoyBullets[i].move(0.3f * cos(angle), 0.3f * sin(angle));
				}


				if (isSpriteOutOfWindow(convoyBullets[i]))
				{
					deleted = true;
				}
			}

			if (deleted)
			{
				convoyBullets.erase(convoyBullets.begin() + i);
			}
		}
	}
}





//Functions
void Game::update()
{
	Game::pollEvents();
	Game::updateMousePositions();
	Game::updateConvoy();
	Game::updatePirates();
	Game::updatePiratesBullets();
	Game::updateConvoyBullets();
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


void Game::renderConvoy()
{
	//Rendering all convoy ships
	for (const auto& sh : spritesAndIDsOfConvoyShips)
	{
		window->draw(std::get<0>(sh));

		float hp;
		if (mission->getTableConvoy().getShipByID(std::get<1>(sh))->getCurrentHP() <= 0)
		{
			hp = 0;
		}
		else
		{
			hp = mission->getTableConvoy().getShipByID(std::get<1>(sh))->getCurrentHP();
		}
		float maxHP = mission->getTableConvoy().getShipByID(std::get<1>(sh))->getMaxHP();

		sf::RectangleShape rectangleHP(sf::Vector2f(64.f * hp / maxHP, 8.f));
		//rectangleHP.setOrigin(sf::Vector2f(rectangleHP.getSize().x / 2, rectangleHP.getSize().y / 2));
		rectangleHP.setPosition(std::get<0>(sh).getPosition() + sf::Vector2f(-32.f, 40.f));
		//rectangleHP.setRotation(std::get<0>(sh).getRotation());
		rectangleHP.setFillColor(sf::Color::Blue);
		rectangleHP.setOutlineColor(sf::Color::Black);
		rectangleHP.setOutlineThickness(2.f);

		window->draw(rectangleHP);

		/*
		if (std::get<3>(sh) == true)  //convoy ship is shooting
		{
			sf::Vertex line[2];
			line[0].position = std::get<0>(sh).getPosition();
			line[0].color = sf::Color::Green;
			line[1].position = sf::Vector2f(std::get<2>(sh).x, std::get<2>(sh).y);
			line[1].color = sf::Color::Green;

			window->draw(line, 2, sf::Lines);
		}
		*/
	}
}

void Game::renderPirates()
{
	//Rendering all pirates ships
	for (const auto& sh : spritesAndIDsOfPiratesShips)
	{
		window->draw(std::get<0>(sh));

		float hp;
		if (mission->getTablePirates().getShipByID(std::get<1>(sh))->getCurrentHP() <= 0)
		{
			hp = 0;
		}
		else
		{
			hp = mission->getTablePirates().getShipByID(std::get<1>(sh))->getCurrentHP();
		}
		float maxHP = mission->getTablePirates().getShipByID(std::get<1>(sh))->getMaxHP();

		sf::RectangleShape rectangleHP(sf::Vector2f(64.f * hp / maxHP, 8.f));
		//rectangleHP.setOrigin(sf::Vector2f(rectangleHP.getSize().x / 2, rectangleHP.getSize().y / 2));
		rectangleHP.setPosition(std::get<0>(sh).getPosition() + sf::Vector2f(-32.f, 40.f));
		//rectangleHP.setRotation(std::get<0>(sh).getRotation());
		rectangleHP.setFillColor(sf::Color::Red);
		rectangleHP.setOutlineColor(sf::Color::Black);
		rectangleHP.setOutlineThickness(2.f);

		window->draw(rectangleHP);

		/*
		if (std::get<3>(sh) == true)  //pirate ship is shooting
		{
			sf::Vertex line[2];
			line[0].position = std::get<0>(sh).getPosition();
			line[0].color = sf::Color::Red;
			line[1].position = sf::Vector2f(std::get<2>(sh).x, std::get<2>(sh).y);
			line[1].color = sf::Color::Red;
			
			window->draw(line, 2, sf::Lines);
		}
		*/
	}
}


void Game::renderPiratesBullets()
{
	for (const auto& bullet : piratesBullets)
	{
		window->draw(bullet);
	}
}


void Game::renderConvoyBullets()
{
	for (const auto& bullet : convoyBullets)
	{
		window->draw(bullet);
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
	Game::renderConvoy();
	Game::renderPirates();
	Game::renderPiratesBullets();
	Game::renderConvoyBullets();
	Game::renderPause();
	Game::renderEndGame();

	window->display();
}


