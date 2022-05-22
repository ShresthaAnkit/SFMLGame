#include "SFML/Graphics.hpp"  
#include <iostream>
#include<vector>
#include "Player.h"
#include "Platform.h"

static const float VIEW_HEIGHT = 512.0f;

void resizeView(const sf::RenderWindow& window, sf::View& view) {
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);

	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

int main() {

	sf::RenderWindow window(sf::VideoMode(512, 512), "Test", sf::Style::Close | sf::Style::Resize);
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));
	sf::Texture playerTexture, tileTexture;
	playerTexture.loadFromFile("sprite.png");
	tileTexture.loadFromFile("tile.png");


	Player player(&playerTexture, sf::Vector2u(4, 4), 0.3f,150.0f, 200);

	//Platform platform1(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(500.0f, 200.0f));
	//Platform platform2(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(500.0f, 0.0f));

	std::vector<Platform> platforms;

	platforms.push_back(Platform(&tileTexture, sf::Vector2f(100.0f, 100.0f), sf::Vector2f(450.0f, 200.0f)));
	platforms.push_back(Platform(&tileTexture, sf::Vector2f(100.0f, 100.0f), sf::Vector2f(200.0f, 300.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(1000.0f, 200.0f), sf::Vector2f(500.0f, 500.0f)));
	
	float deltaTime = 0.0f;
	sf::Clock clock;

	
	while (window.isOpen()) {
		deltaTime = clock.restart().asSeconds();

		sf::Event e;
		while (window.pollEvent(e)) {
			switch (e.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				resizeView(window, view);
				break;
			}
		}

		player.update(deltaTime);

		sf::Vector2f direction;

		for (Platform platform : platforms) {
			Collider pCollider = player.getCollider();

			if (platform.getCollider().checkCollision(pCollider,direction, 1.0f))
				player.onCollision(direction);	
		}
		//platform1.getCollider().checkCollision(pCollider, 0.0f);
		//platform2.getCollider().checkCollision(pCollider, 1.0f);

		view.setCenter(player.getPosition());

		window.clear();
		window.setView(view);
		player.draw(window);
		//platform1.draw(window);
		//platform2.draw(window);
		for (Platform& platform : platforms) {
			platform.draw(window);
		}
		window.display();
	}


	return 0;
} 