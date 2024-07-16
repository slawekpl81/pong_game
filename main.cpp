#include <iostream>
#include <string>
#include <sstream>

#include "Bat.hpp"
#include "Ball.hpp"

int main()
{
	std::cout << "hello c++/n";
	sf::VideoMode vm{1920, 1080};
	sf::RenderWindow window(vm, "PONG"); //, sf::Style::Fullscreen);
	int score{0};
	int lives{3};
	// =================================================================
	// Create a bat
	Bat bat(1920 / 2, 1080 - 60);
	// Create a ball
	Ball ball(1920 / 2, 0);
	ball.setDirections();
	// =================================================================
	sf::Text hud;
	sf::Font font;
	font.loadFromFile("fonts/DS-DIGIT.TTF");
	hud.setFont(font);
	hud.setCharacterSize(75);
	hud.setFillColor(sf::Color::White);
	hud.setPosition(20, 20);
	// ==================================================================
	sf::Clock clock;
	// ==================================================================
	while (window.isOpen())
	{ /*
	 Handle the player input
	 ****************************
	 ****************************
	 ****************************
	 */
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				// Quit the game when the window is closed
				window.close();
		}
		// Handle the player quitting
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}
		// Handle the pressing and releasing of the arrow keys
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			bat.moveLeft();
		}
		else
		{
			bat.stopLeft();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			bat.moveRight();
		}
		else
		{
			bat.stopRight();
		}
		/*
		Update the bat, the ball and the HUD
		*****************************
		*****************************
		*****************************
		*/
		sf::Time dt = clock.restart();
		bat.update(dt);
		ball.update(dt);
		std::stringstream ss;
		ss << "Score: " << score << " Lives: " << lives;
		hud.setString(ss.str());
		// ===========================================================
		// Handle ball hitting the bottom
		if (ball.getPosition().top > window.getSize().y)
		{
			// reverse the ball direction
			ball.reboundBottom();
			// Remove a life
			lives--;
			// Check for zero lives
			if (lives < 1)
			{
				// reset the score
				score = 0;
				// reset the lives
				lives = 3;
			}
			ball.resetSpeed();
			ball.setDirections();
		}
		// Handle ball hitting top
		if (ball.getPosition().top < 0)
		{
			ball.reboundBatOrTop();
			// Add a point to the players score
			score++;
			ball.increaseSpeed();
		}
		// Handle ball hitting sides
		if (ball.getPosition().left < 0 ||
			ball.getPosition().left + ball.getPosition().width > window.getSize().x)
		{
			ball.reboundSides();
		}
		// Has the ball hit the bat?
		if (ball.getPosition().intersects(bat.getPosition()))
		{
			// Hit detected so reverse the ball and score a point
			ball.reboundBatOrTop();
		}

		/*
		Draw the bat, the ball and the HUD
		*****************************
		*****************************
		*****************************
		*/
		window.clear();
		window.draw(hud);
		window.draw(bat.getShape());
		window.draw(ball.getShape());
		window.display();
	}
	// ==================================================================
	return 0;
}
