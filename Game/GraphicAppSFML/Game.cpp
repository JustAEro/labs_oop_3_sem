#include "Game.h"

void Game::initTextures()
{
	waterTexture.loadFromFile("resources/water.jpg");
	waterTexture.setSmooth(true);

	shipTexture.loadFromFile("resources/SingleShip.jpg");
	shipTexture.setSmooth(true);
}

//Private functions
void Game::initVariables()
{
	window = nullptr;

	//Game logic
	points = 0;
	enemySpawnTimerMax = 10.f;
    enemySpawnTimer = enemySpawnTimerMax;
	maxEnemies = 5;
}

void Game::initWindow()
{
	videoMode.width = 1280;
	videoMode.height = 720;
	
	
	window = new sf::RenderWindow(videoMode, sf::String(L"Military Convoy"), sf::Style::Titlebar | sf::Style::Close);

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

		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
			{
				window->close();
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
		static_cast<double>(rand() % static_cast<int>((window->getSize().x - enemy.getGlobalBounds().width))),
		0.f
	);

	//enemy.setScale(sf::Vector2f(0.5f, 0.5f));
	//enemy.rotate(45.f);
	//enemy.setColor(sf::Color::Green);

	//Spawn the enemy
	enemies.push_back(enemy);

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
	if (enemies.size() < maxEnemies)
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
	for (size_t i = 0; i < enemies.size(); ++i)
	{
		bool deleted = false;
		

		enemies[i].move(0.f, 1.f);
		enemies[i].rotate(-0.1f);

		//Check if clicked upon
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (enemies[i].getGlobalBounds().contains(mousePosView))
			{
				deleted = true;

				//Gain points
				points += 10.f;
			}
		}

		//If the enemy is past the bottom of the screen
		if (enemies[i].getPosition().y > window->getSize().y)
		{
			deleted = true;
		}

		//final delete
		if (deleted)
		{
			enemies.erase(enemies.begin() + i);
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

void Game::renderEnemies()
{
	//Rendering all the enemies
	for (auto& e : enemies)
	{
		window->draw(e);
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
	Game::renderEnemies();
	

	window->display();
}


